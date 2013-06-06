#ifndef ByteBufStream_h_already_included__21_08_2012__7A804D0
#define ByteBufStream_h_already_included__21_08_2012__7A804D0
//
// SeVlaT, 21.08.2012
//

#include "Stream.h"
#include "ByteBuffer.h"


////////////////////////////////////////////////////////////////////////////////
class TIByteBufStream: public TIStream {
 public:
  TIByteBufStream(const TByteBuffer &buf);

 public:
  virtual bool GetRaw(void     *pBuf,
                      TUInt     nBytesToRead,
                      TUInt    &nBytesRead,
                      TErrList *pErr);

 public:
  bool IsEnd() const { return m_iCur==m_buf.end(); }

 private:
  void DoRead(void     *pBuf,
              TUInt     nBytesToRead,
              TUInt    &nBytesRead);
              
 private:
  const TByteBuffer &m_buf;
  TByteBufferCIt m_iCur;
};

////////////////////////////////////////////////////////////////////////////////
class TOByteBufStream: public TOStream {
 public:
  TOByteBufStream(TByteBuffer &buf);

 public:
  virtual bool PutRaw(const void     *pBuf,
                            TUInt     nBytesToWrite,
                            TUInt    &nBytesWritten,
                            TErrList *pErr);

 private:
  TByteBuffer &m_buf;
};

////////////////////////////////////////////////////////////////////////////////

#endif
