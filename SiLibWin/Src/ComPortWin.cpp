// SeVlaT, 12.10.2012
#include "StdAfx.h"

#include "ComPortWin.h"

namespace MsWin {

using namespace NComPortErrors;

////////////////////////////////////////////////////////////////////////////////
class TComPortName {
 public:
  explicit TComPortName(int n)
   {
     wsprintf(m_szName, L"\\\\.\\COM%d", n);
   }

 public:
  const wchar_t* Get() const { return m_szName; }

 private:
  wchar_t m_szName[12];
};

const int c_nDefBaudRate = 4800; // Should it be moved to platform-independent?

////////////////////////////////////////////////////////////////////////////////
TComPortHandle::TComPortHandle()
 : m_h(INVALID_HANDLE_VALUE)
{
}

TComPortHandle::~TComPortHandle()
{
  Close();
}

bool TComPortHandle::Open(const wstring &sPort)
{
  m_h=CreateFileW(sPort.c_str(),
                  GENERIC_READ | GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  0,
                  NULL);
                  
  return Valid();
}

void TComPortHandle::Close()
{
  CloseHandle(m_h);
  m_h=INVALID_HANDLE_VALUE;
}

bool TComPortHandle::Valid() const
{
  return m_h!=INVALID_HANDLE_VALUE;
}



////////////////////////////////////////////////////////////////////////////////

TComPortWin::TComPortWin()
{
}

TComPortWin::~TComPortWin()
{
}

bool TComPortWin::Valid(TErrList *pErr) const
{
  return m_cph.Valid();
}

bool TComPortWin::Open(const wstring &sPort, TErrList *pErr)
{
  if (m_cph.Valid()) {
    PushError(pErr, eComPortAlreadyOpen);
    return false;
  }
  
  m_cph.Open(sPort);
                               
  m_sPort=sPort;

  return CheckValidity(pErr) && 
         SetupCommState(pErr) &&
         SetupTimeouts(pErr);
}

void TComPortWin::Close(TErrList *pErr)
{
  if (!m_cph.Valid()) return;
  
  m_cph.Close();
}

bool TComPortWin::CheckValidity(TErrList *pErr) const
{
  if (Valid(pErr)) return true;
  
  PushError(pErr, eComPortIsNotOpen);
  return false;
}

const wstring& TComPortWin::GetPortName() const
{
  return m_sPort;
}

bool TComPortWin::SetBaudRate(TUInt nBaudRate, TErrList *pErr)
{
  if (!CheckValidity(pErr)) return false;

  DCB dcb={0};
  dcb.DCBlength=sizeof(DCB);
  if (!GetCommState(m_cph.Get(), &dcb)) {
    PushError(pErr, eCannotGetComPortState);
    return false;
  }
  
  dcb.BaudRate=nBaudRate;
  
  if (!SetCommState(m_cph.Get(), &dcb)) {
    PushError(pErr, eCannotSetComPortState);
    return false;
  }
  
  return true;
}

OUInt TComPortWin::GetBaudRate(TErrList *pErr) const
{
  if (!CheckValidity(pErr)) return None;

  DCB dcb={0};
  dcb.DCBlength=sizeof(DCB);
  if (!GetCommState(m_cph.Get(), &dcb)) {
    PushError(pErr, eCannotGetComPortState);
    return None;
  }
  
  return dcb.BaudRate;
}

bool TComPortWin::SetupTimeouts(TErrList *pErr)
{
  if (!CheckValidity(pErr)) return false;
  
  COMMTIMEOUTS cto={0};
  
	cto.ReadIntervalTimeout        =50;
	cto.ReadTotalTimeoutMultiplier =10;
	cto.ReadTotalTimeoutConstant   =300;
	cto.WriteTotalTimeoutMultiplier=10;
	cto.WriteTotalTimeoutConstant  =300;

  if (!SetCommTimeouts(m_cph.Get(), &cto)) {
    PushError(pErr, eCannotSetComPortTimeouts);
    return false;
  }
  
  return true;
}

bool TComPortWin::SetupCommState(TErrList *pErr)
{
  if (!CheckValidity(pErr)) return false;

  DCB dcb={0};
  dcb.DCBlength=sizeof(DCB);
  
  if (!GetCommState(m_cph.Get(), &dcb)) {
    PushError(pErr, eCannotGetComPortState);
    return false;
  }
  
	dcb.BaudRate=c_nDefBaudRate;
	dcb.fBinary=TRUE;
	dcb.fDtrControl=DTR_CONTROL_DISABLE;
	dcb.fRtsControl=RTS_CONTROL_DISABLE;
	dcb.Parity=NOPARITY;
	dcb.StopBits=ONESTOPBIT;
	dcb.ByteSize =8;
  
  if (!SetCommState(m_cph.Get(), &dcb)) {
    PushError(pErr, eCannotSetComPortState);
    return false;
  }
  
  return true;
}

bool TComPortWin::GetRaw(void     *pBuf,
                             TUInt     nBytesToRead,
                             TUInt    &nBytesRead,
                             TErrList *pErr)
{
  assert(pBuf);
  assert(nBytesToRead>0);

  nBytesRead=0;
  
  DWORD nRead=0;
  if (!ReadFile(m_cph.Get(), pBuf, nBytesToRead, &nRead, 0)) {
    PushError(pErr, eComPortReadingFailed);
    return false;
  }

  nBytesRead=nRead;
  return true;
}
                    
bool TComPortWin::PutRaw(const void     *pBuf,
                                   TUInt     nBytesToWrite,
                                   TUInt    &nBytesWritten,
                                   TErrList *pErr)
{
  assert(pBuf);
  assert(nBytesToWrite>0);

  nBytesWritten=0;
  
  DWORD nWritten=0;
  if (!WriteFile(m_cph.Get(), pBuf, nBytesToWrite, &nWritten, 0)) {
    PushError(pErr, eComPortWritingFailed);
    return false;
  }

  nBytesWritten=nWritten;
  return true;
}

////////////////////////////////////////////////////////////////////////////////
bool ComPortAvailable(const wstring &sPort)
{
  static int sn=0;
//  if (++sn%40==0) return true;
  TComPortHandle cph;
  return cph.Open(sPort);
}

wstring GetComPortName(int nPort)
{
  wchar_t wszName[32];
  if (nPort<10) wsprintf(wszName, L"COM%d", nPort);
           else wsprintf(wszName, L"\\\\.\\COM%d", nPort);
       
  return wszName;       
}

} //namespace MsWin

////////////////////////////////////////////////////////////////////////////////
namespace PlatformSpecific {

IComPort* CreateComPort()
{
  return new MsWin::TComPortWin;
}

void DeleteComPort(IComPort* pCp)
{
  delete pCp;
}

void EnumComPorts(std::vector<std::wstring> &CpVec)
{
  CpVec.clear();
  
  for (int i=1; i<=255; ++i) {
    const wstring sName=MsWin::GetComPortName(i);
    if (MsWin::ComPortAvailable(sName)) {
      CpVec.push_back(sName);
    }
  }
}

} // namespace PlatformSpecific

