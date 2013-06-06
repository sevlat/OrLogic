#ifndef StreamLogger_h_already_included__13_05_2013__2A5B7C40
#define StreamLogger_h_already_included__13_05_2013__2A5B7C40
//
// SeVlaT, 13.05.2013
//

#include "Stream.h"

class TStreamLogger: public IIOStream {
 public:
  TStreamLogger(const std::string &sFileName,
                      IIStream    &is,
                      IOStream    &os);

 public:
  virtual bool GetRaw(void     *pBuf,
                      TUInt     nBytesToRead,
                      TUInt    &nBytesRead,
                      TErrList *pErr);

  virtual bool PutRaw(const void     *pBuf,
                            TUInt     nBytesToWrite,
                            TUInt    &nBytesWritten,
                            TErrList *pErr);

 private:
  void Log(      bool      bRes,
           const void     *pBuf,
                 TUInt     nBytesRequested,
                 TUInt     nBytesDone,
                 bool      bIn) const;

 private:
  OBool m_obIn;

 private:
  IIStream &m_is;
  IOStream &m_os;
  
 private:
  std::string m_sFileName;
};

#endif
