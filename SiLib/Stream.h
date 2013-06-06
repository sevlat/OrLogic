#ifndef Stream_h_already_included__18_08_2012__11956FC
#define Stream_h_already_included__18_08_2012__11956FC
//
// SeVlaT, 18.08.2012
//

#include "Types.h"
#include "Fwd.h"

class IIStream {
 public:
  virtual bool GetRaw(void     *pBuf,
                      TUInt     nBytesToRead,
                      TUInt    &nBytesRead,
                      TErrList *pErr)=0;

 protected:
  ~IIStream() {}
};

class IOStream {
 public:
  virtual bool PutRaw(const void     *pBuf,
                            TUInt     nBytesToWrite,
                            TUInt    &nBytesWritten,
                            TErrList *pErr)=0;

 protected:
  ~IOStream() {}
};


class IIOStream: public IIStream,
                 public IOStream
{
 protected:
  ~IIOStream() {}
};
      
////////////////////////////////////////////////////////////////////////////////

namespace NStreamUtils {

////////////////////////////////////////
  bool Get1Byte(IIStream &is,
                TByte    &b,
                TErrList *pErr);

  bool Get2ByteLE(IIStream &is,
                  TWord    &w,
                  TErrList *pErr);
  bool Get2ByteBE(IIStream &is,
                  TWord    &w,
                  TErrList *pErr);

  bool Get3ByteLE(IIStream &is,
                  TDWord   &dw,
                  TErrList *pErr);
  bool Get3ByteBE(IIStream &is,
                  TDWord   &dw,
                  TErrList *pErr);

  bool Get4ByteLE(IIStream &is,
                  TDWord   &dw,
                  TErrList *pErr);
  bool Get4ByteBE(IIStream &is,
                  TDWord   &dw,
                  TErrList *pErr);

  bool GetBuf(IIStream &is,
              TByte    *pbBuf,
              TUInt     nBytesToRead,
              TErrList *pErr);

  bool GetBuf(IIStream    &is,
              TByteBuffer &buf,
              TErrList    *pErr);

  template<unsigned long N>
  bool GetBuf(IIStream      &is,
              TByteArray<N> &buf,
              TErrList      *pErr)
    { return GetBuf(is, buf.data(), buf.size(), pErr); }

////////////////////////////////////////
  bool Put1Byte(IOStream &os,
                TByte     b,
                TErrList *pErr);
          
  bool Put2ByteLE(IOStream &os,
                  TWord     w,
                  TErrList *pErr);
  bool Put2ByteBE(IOStream &os,
                  TWord     w,
                  TErrList *pErr);
          
  bool Put3ByteLE(IOStream &os,
                  TDWord    dw,
                  TErrList *pErr);
  bool Put3ByteBE(IOStream &os,
                  TDWord    dw,
                  TErrList *pErr);

  bool Put4ByteLE(IOStream &os,
                  TDWord    dw,
                  TErrList *pErr);
  bool Put4ByteBE(IOStream &os,
                  TDWord    dw,
                  TErrList *pErr);

  bool PutBuf(      IOStream &os,
              const TByte    *pbBuf,
                    TUInt     nBytesToWrite,
                    TErrList *pErr);

  bool PutBuf(      IOStream    &os,
              const TByteBuffer &bb,
                    TErrList    *pErr);

  template<unsigned long N>
  bool PutBuf(      IOStream      &os,
              const TByteArray<N> &buf,
                    TErrList      *pErr)
    { return PutBuf(os, buf.data(), buf.size(), pErr); }

}

////////////////////////////////////////////////////////////////////////////////
class TIStream: public IIStream {
 public:
  bool GetByte(TByte &b, TErrList *pErr)
    { return NStreamUtils::Get1Byte(*this, b, pErr); }

  bool GetWordLE(TWord &w, TErrList *pErr)
    { return NStreamUtils::Get2ByteLE(*this, w, pErr); }
  
  bool GetWordBE(TWord &w, TErrList *pErr)
    { return NStreamUtils::Get2ByteBE(*this, w, pErr); }

  bool GetBuf(TByte    *pbBuf,
              TUInt     nBytesToRead,
              TErrList *pErr)
    { return NStreamUtils::GetBuf(*this, pbBuf, nBytesToRead, pErr); }
};

class TOStream: public IOStream {
 public:
  bool PutByte(TByte b, TErrList *pErr)
    { return NStreamUtils::Put1Byte(*this, b, pErr); }

  bool PutWordLE(TWord w, TErrList *pErr)
    { return NStreamUtils::Put2ByteLE(*this, w, pErr); }

  bool PutWordBE(TWord w, TErrList *pErr)
    { return NStreamUtils::Put2ByteBE(*this, w, pErr); }

  bool PutBuf(const TByte    *pbBuf,
                    TUInt     nBytesToWrite,
                    TErrList *pErr)
    { return NStreamUtils::PutBuf(*this, pbBuf, nBytesToWrite, pErr); }
    
  bool PutBuf(const TByteBuffer &bb,
                    TErrList    *pErr)
    { return NStreamUtils::PutBuf(*this, bb, pErr); }
};

#endif
