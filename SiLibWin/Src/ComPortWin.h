#ifndef ComPortWin_h_already_included__13_10_2012__36C5CD00
#define ComPortWin_h_already_included__13_10_2012__36C5CD00
//
// SeVlaT, 13.10.2012
//

#include <SiLib/ComPort.h>

namespace MsWin {

class TComPortHandle {
 public:
  TComPortHandle();
  ~TComPortHandle();
  
 public:
  bool Open(const wstring &sPort);
  void Close();
  
  bool Valid() const;
  
  HANDLE Get() const { return m_h; }

 private:
  HANDLE m_h;
};

class TComPortWin: public IComPort {
 public:
  TComPortWin();
  virtual ~TComPortWin();

 public:
  virtual bool Valid(TErrList *pErr) const;
                             
 public:
  virtual bool Open(const wstring &sPort, TErrList *pErr);
  virtual void Close(TErrList *pErr);

  virtual const wstring& GetPortName() const;

 public:
  virtual bool SetBaudRate(TUInt nBaudRate, TErrList *pErr);
  virtual OUInt GetBaudRate(TErrList *pErr) const;

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
  virtual bool SetupTimeouts(TErrList *pErr);
  virtual bool SetupCommState(TErrList *pErr);

 protected:
  virtual bool CheckValidity(TErrList *pErr) const;

 private:
  TComPortHandle m_cph;
  wstring m_sPort;
};

};

#endif
