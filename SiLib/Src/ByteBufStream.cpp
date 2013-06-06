// SeVlaT, 13.08.2012
#include "StdAfx.h"

#include "../ByteBufStream.h"

#include "../Errors.h"

////////////////////////////////////////////////////////////////////////////////
namespace {

  enum TErrorCode {
    eUnknown,
 
    eNullBufferForReading,
    eNullBufferForWriting,
    eZeroBytesRequestedForReading,
    eZeroBytesRequestedForWriting,
    eReadingFailed,
    eWritingFailed,
   
    eComPortIsNotOpen,
    eComPortAlreadyOpen,
    eCannotGetComPortState,
    eCannotSetComPortState,
    eCannotGetComPortTimeouts,
    eCannotSetComPortTimeouts,

    eLast
  };
  
  typedef TErrorDescription<TErrorCode, eLast, 300> TErrorDescr;
  
  static void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }

}

////////////////////////////////////////////////////////////////////////////////
TIByteBufStream::TIByteBufStream(const TByteBuffer &buf)
 : m_buf(buf),
   m_iCur(buf.begin())
{
}

void TIByteBufStream::DoRead(void     *pBuf,
                            TUInt     nBytesToRead,
                            TUInt    &nBytesRead)
{
  assert((m_iCur+nBytesToRead)<=m_buf.end());
  
  const TByteBufferCIt iNext=m_iCur+nBytesToRead;
  TByte *pbBuf=static_cast<TByte*>(pBuf);
  
  std::copy(m_iCur, iNext, pbBuf);
  m_iCur=iNext;
  nBytesRead=nBytesToRead;
}                          

bool TIByteBufStream::GetRaw(void     *pBuf,
                             TUInt     nBytesToRead,
                             TUInt    &nBytesRead,
                             TErrList *pErr)
{
  if (!pBuf) {
    PushError(pErr, eNullBufferForReading);
    return false;
  }
  
  if (nBytesToRead==0) {
    PushError(pErr, eZeroBytesRequestedForReading);
    return false;
  }
  
  const TUInt nBytesAvailable=m_buf.end()-m_iCur;
  if (nBytesAvailable>=nBytesToRead) DoRead(pBuf, nBytesToRead,    nBytesRead);
                                else DoRead(pBuf, nBytesAvailable, nBytesRead);
  
  return true;
}                          

////////////////////////////////////////////////////////////////////////////////
TOByteBufStream::TOByteBufStream(TByteBuffer &buf)
 : m_buf(buf)
{
}

bool TOByteBufStream::PutRaw(const void     *pBuf,
                                   TUInt     nBytesToWrite,
                                   TUInt    &nBytesWritten,
                                   TErrList *pErr)
{
  if (!pBuf) {
    PushError(pErr, eNullBufferForWriting);
    return false;
  }
  
  if (nBytesToWrite==0) {
    PushError(pErr, eZeroBytesRequestedForWriting);
    return false;
  }
  
  m_buf.Append(pBuf, nBytesToWrite);
  nBytesWritten=nBytesToWrite;
  
  return true;
}                                 

////////////////////////////////////////////////////////////////////////////////
