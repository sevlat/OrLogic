#ifndef PortEmulator_h_already_included__14_06_2012__8EAEF7
#define PortEmulator_h_already_included__14_06_2012__8EAEF7
//
// SeVlaT, 14.06.2012
//

#include "ComPort.h"

class TPortEmulator: public IComPort {
 public:
  TPortEmulator();

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
                           
 protected:
  OByte Pop();
  void Push(TByte b);
 
 private:
  virtual void OnWrite()=0;
  
 private:
  TByteDeque m_dqRead;
  TByteDeque m_dqWrite;
                            
 private:
  bool m_bOpen;
  TUInt m_nBaudRate;
};                    

/////////////////////////////////////////////////////////////////////////////////////
class TPortTableEmulator: public TPortEmulator {
 private:
  virtual void OnWrite();
};


#endif
