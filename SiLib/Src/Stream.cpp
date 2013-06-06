// SeVlaT, 18.08.2012
#include "StdAfx.h"

#include "../Stream.h"

#include "../Errors.h"
#include "../SerialTypes.h"
#include "../ByteBuffer.h"

#include <hftl/Main/m_bbUtils.h>

namespace {

enum TErrorCode {
  eUnknown,

  eByte_GotLess,
  e2ByteLE_GotLess,
  e2ByteBE_GotLess,
  e3ByteLE_GotLess,
  e3ByteBE_GotLess,
  e4ByteLE_GotLess,
  e4ByteBE_GotLess,
  eBuf_GotLess,

  eByte_WrittenLess,
  e2ByteLE_WrittenLess,
  e2ByteBE_WrittenLess,
  e3ByteLE_WrittenLess,
  e3ByteBE_WrittenLess,
  e4ByteLE_WrittenLess,
  e4ByteBE_WrittenLess,
  eBuf_WrittenLess,

  ieByte_GotMore,
  ie2ByteLE_GotMore,
  ie2ByteBE_GotMore,
  ie3ByteLE_GotMore,
  ie3ByteBE_GotMore,
  ie4ByteLE_GotMore,
  ie4ByteBE_GotMore,
  ieBuf_GotMore,

  ieByte_WrittenMore,
  ie2ByteLE_WrittenMore,
  ie2ByteBE_WrittenMore,
  ie3ByteLE_WrittenMore,
  ie3ByteBE_WrittenMore,
  ie4ByteLE_WrittenMore,
  ie4ByteBE_WrittenMore,
  ieBuf_WrittenMore,

  eSkippedSomeBytes,

  eLast
};

typedef TErrorDescription<TErrorCode, eLast, 200> TErrorDescr;

static void PushError(TErrList *pErr, TErrorCode ec)
{ TErrorDescr::PushError(pErr, ec); }


////////////////////////////////////////////////////////////////////////////////
template <typename BO, int N>
struct TSpecErrCode;

////////////////////////////////////////////////////////////////////////////////
template <>
struct TSpecErrCode<BoLe, 2> {
  static const TErrorCode eGotLess    = e2ByteLE_GotLess;
  static const TErrorCode eGotMore    =ie2ByteLE_GotMore;

  static const TErrorCode eWrittenLess= e2ByteLE_WrittenLess;
  static const TErrorCode eWrittenMore=ie2ByteLE_WrittenMore;
};

template <>
struct TSpecErrCode<BoBe, 2> {
  static const TErrorCode eGotLess    = e2ByteBE_GotLess;
  static const TErrorCode eGotMore    =ie2ByteBE_GotMore;

  static const TErrorCode eWrittenLess= e2ByteBE_WrittenLess;
  static const TErrorCode eWrittenMore=ie2ByteBE_WrittenMore;
};

////////////////////////////////////////////////////////////////////////////////
template <>
struct TSpecErrCode<BoLe, 3> {
  static const TErrorCode eGotLess    = e3ByteLE_GotLess;
  static const TErrorCode eGotMore    =ie3ByteLE_GotMore;

  static const TErrorCode eWrittenLess= e3ByteLE_WrittenLess;
  static const TErrorCode eWrittenMore=ie3ByteLE_WrittenMore;
};

template <>
struct TSpecErrCode<BoBe, 3> {
  static const TErrorCode eGotLess    = e3ByteBE_GotLess;
  static const TErrorCode eGotMore    =ie3ByteBE_GotMore;

  static const TErrorCode eWrittenLess= e3ByteBE_WrittenLess;
  static const TErrorCode eWrittenMore=ie3ByteBE_WrittenMore;
};

////////////////////////////////////////////////////////////////////////////////
template <>
struct TSpecErrCode<BoLe, 4> {
  static const TErrorCode eGotLess    = e4ByteLE_GotLess;
  static const TErrorCode eGotMore    =ie4ByteLE_GotMore;

  static const TErrorCode eWrittenLess= e4ByteLE_WrittenLess;
  static const TErrorCode eWrittenMore=ie4ByteLE_WrittenMore;
};

template <>
struct TSpecErrCode<BoBe, 4> {
  static const TErrorCode eGotLess    = e4ByteBE_GotLess;
  static const TErrorCode eGotMore    =ie4ByteBE_GotMore;

  static const TErrorCode eWrittenLess= e4ByteBE_WrittenLess;
  static const TErrorCode eWrittenMore=ie4ByteBE_WrittenMore;
};

////////////////////////////////////////////////////////////////////////////////
bool CheckByteCounts(TUInt       nBytesNeed,
                     TUInt       nBytesDone,
                     TErrorCode  ecLess,
                     TErrorCode  ecMore,
                     TErrList   *pErr)
{
  if (nBytesDone<nBytesNeed) {
    PushError(pErr, ecLess);
    return false;
  }
  
  if (nBytesDone>nBytesNeed) {
    PushError(pErr, ecMore);
    return false;
  }

  return true;  
}

template <typename BO, int N>
bool GetNByte(IIStream                 &is,
              typename TNByte<N>::Type &nb,
              TErrList                 *pErr)
{
  assert(TNByte<N>::Check(nb));
  
  enum { nBufSize=N };
  TByte bBuf[nBufSize]={0};
  
  TUInt nBytesGot=0;
  if (!is.GetRaw(bBuf, nBufSize, nBytesGot, pErr)) return false;
  
  if (!CheckByteCounts(nBufSize,
                       nBytesGot,
                       TSpecErrCode<BO, N>::eGotLess,
                       TSpecErrCode<BO, N>::eGotMore,
                       pErr)) return false;

  nb=hftl::MakeNByte<BO>(bBuf);
  
  return true;  
}

template <typename BO, int N>
bool PutNByte(IOStream                 &os,
              typename TNByte<N>::Type &nb,
              TErrList                 *pErr)
{
  assert(TNByte<N>::Check(nb));

  enum { nBufSize=N };
  TByte bBuf[nBufSize];
  hftl::SplitNByte<BO>(nb, bBuf);

  TUInt nBytesWritten=0;
  if (!os.PutRaw(&bBuf, nBufSize, nBytesWritten, pErr)) return false;
  
  return CheckByteCounts(nBufSize,
                         nBytesWritten,
                         TSpecErrCode<BO, N>::eWrittenLess,
                         TSpecErrCode<BO, N>::eWrittenMore,
                         pErr);
}


}

////////////////////////////////////////////////////////////////////////////////
namespace NStreamUtils {

bool Get1Byte(IIStream &is,
              TByte    &b,
              TErrList *pErr)
{
  enum { nBufSize=1 };

  TUInt nBytesGot=0;
  if (!is.GetRaw(&b, nBufSize, nBytesGot, pErr)) return false;
  
  return CheckByteCounts(nBufSize,
                         nBytesGot,
                         eByte_GotLess,
                         ieByte_GotMore,
                         pErr);
}

bool Get2ByteLE(IIStream &is,
                TWord    &w,
                TErrList *pErr)
{
  return GetNByte<BoLe, 2>(is, w, pErr);
}

bool Get2ByteBE(IIStream &is,
                TWord    &w,
                TErrList *pErr)
{
  return GetNByte<BoBe, 2>(is, w, pErr);
}

bool Get3ByteLE(IIStream &is,
                TDWord   &dw,
                TErrList *pErr)
{
  return GetNByte<BoLe, 3>(is, dw, pErr);
}

bool Get3ByteBE(IIStream &is,
                TDWord   &dw,
                TErrList *pErr)
{
  return GetNByte<BoBe, 3>(is, dw, pErr);
}

bool Get4ByteLE(IIStream &is,
                TDWord   &dw,
                TErrList *pErr)
{
  return GetNByte<BoLe, 4>(is, dw, pErr);
}

bool Get4ByteBE(IIStream &is,
                TDWord   &dw,
                TErrList *pErr)
{
  return GetNByte<BoBe, 4>(is, dw, pErr);
}

bool GetBuf(IIStream &is,
            TByte    *pbBuf,
            TUInt     nBytesToGet,
            TErrList *pErr)
{
  if (nBytesToGet==0) return true;
  
  TUInt nBytesGot=0;
  if (!is.GetRaw(pbBuf, nBytesToGet, nBytesGot, pErr)) return false;
  
  if (!CheckByteCounts(nBytesToGet,
                       nBytesGot,
                       eBuf_GotLess,
                       ieBuf_GotMore,
                       pErr)) return false;
  
  return true;  
}

bool GetBuf(IIStream    &is,
            TByteBuffer &buf,
            TErrList    *pErr)
{
  enum { nBufSize=256 };
  TByte bBuf[nBufSize];
  
  TUInt nBytesGot=0;
  do {
    nBytesGot=0;
    if (!is.GetRaw(bBuf, nBufSize, nBytesGot, pErr)) return false;
    
    if (nBytesGot>0) buf.Append(bBuf, nBytesGot);
  } while (nBytesGot==nBufSize);
  
  return true;
}            

////////////////////////////////////////////////////////////////////////////////
bool Put1Byte(IOStream &os,
             TByte     b,
             TErrList *pErr)
{
  enum { nBufSize=1 };

  TUInt nBytesWritten=0;
  if (!os.PutRaw(&b, nBufSize, nBytesWritten, pErr)) return false;
  
  return CheckByteCounts(nBufSize,
                         nBytesWritten,
                         eByte_WrittenLess,
                         ieByte_WrittenMore,
                         pErr);
}

bool Put2ByteLE(IOStream &os,
               TWord     w,
               TErrList *pErr)
{
  return PutNByte<BoLe, 2>(os, w, pErr);
}

bool Put2ByteBE(IOStream &os,
               TWord     w,
               TErrList *pErr)
{
  return PutNByte<BoBe, 2>(os, w, pErr);
}

bool Put3ByteLE(IOStream &os,
                TDWord    dw,
                TErrList *pErr)
{
  return PutNByte<BoLe, 3>(os, dw, pErr);
}

bool Put3ByteBE(IOStream &os,
                TDWord    dw,
                TErrList *pErr)
{
  return PutNByte<BoBe, 3>(os, dw, pErr);
}

bool Put4ByteLE(IOStream &os,
                TDWord    dw,
                TErrList *pErr)
{
  return PutNByte<BoLe, 4>(os, dw, pErr);
}

bool Put4ByteBE(IOStream &os,
                TDWord    dw,
                TErrList *pErr)
{
  return PutNByte<BoBe, 4>(os, dw, pErr);
}

bool PutBuf(      IOStream &os,
            const TByte    *pbBuf,
                  TUInt     nBytesToWrite,
                  TErrList *pErr)
{
  TUInt nBytesWritten=0;
  if (!os.PutRaw(pbBuf, nBytesToWrite, nBytesWritten, pErr)) return false;
  
  return CheckByteCounts(nBytesToWrite,
                         nBytesWritten,
                         eBuf_WrittenLess,
                         ieBuf_WrittenMore,
                         pErr);
 
}

bool PutBuf(      IOStream    &os,
            const TByteBuffer &bb,
                  TErrList    *pErr)
{
  TUInt nBytesWritten=0;
  const TUInt nBytesToWrite=bb.size();
  if (!os.PutRaw(bb.begin_ptr(), nBytesToWrite, nBytesWritten, pErr)) return false;
  
  return CheckByteCounts(nBytesToWrite,
                         nBytesWritten,
                         eBuf_WrittenLess,
                         ieBuf_WrittenMore,
                         pErr);
}                  

}