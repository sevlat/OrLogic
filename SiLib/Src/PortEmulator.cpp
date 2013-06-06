// SeVlaT, 14.06.2012
#include "StdAfx.h"

#include "../PortEmulator.h"

TPortEmulator::TPortEmulator()
 : m_bOpen(false),
   m_nBaudRate(4800)
{
}

bool TPortEmulator::Valid(TErrList *pErr) const
{
  return m_bOpen;
}

bool TPortEmulator::Open(const wstring &sPort, TErrList *pErr)
{
  m_bOpen=true;
  return true;
}

void TPortEmulator::Close(TErrList *pErr)
{
  m_bOpen=false;
}

const wstring& TPortEmulator::GetPortName() const
{
  static wstring s_s(L"Emulator");
  return s_s;
}

bool TPortEmulator::SetBaudRate(TUInt nBaudRate, TErrList *pErr)
{
  if (!m_bOpen) return false;
  m_nBaudRate=nBaudRate;
  return true;
}

OUInt TPortEmulator::GetBaudRate(TErrList *pErr) const
{
  if (!m_bOpen) return None;
  return m_nBaudRate;
}

bool TPortEmulator::GetRaw(void     *pBuf,
                           TUInt     nBytesToRead,
                           TUInt    &nBytesRead,
                           TErrList *pErr)
{
  if (!m_bOpen) return false;

  if (!pBuf) {
    return false;
  }
  
  const TUInt nBytesAvailable=m_dqRead.size();
  if (nBytesToRead<nBytesAvailable) nBytesRead=nBytesToRead;
                               else nBytesRead=nBytesAvailable;
  
  const TByteDequeIt iSrcB=m_dqRead.begin();
  const TByteDequeIt iSrcE=iSrcB+nBytesRead;
  
  TByte *iTrgB=static_cast<TByte*>(pBuf);
  
  std::copy(iSrcB, iSrcE, iTrgB);
  m_dqRead.erase(iSrcB, iSrcE);
  
  return true;
}                         
                  
bool TPortEmulator::PutRaw(const void     *pBuf,
                                 TUInt     nBytesToWrite,
                                 TUInt    &nBytesWritten,
                                 TErrList *pErr)
{
  if (!m_bOpen) return false;

  if (!pBuf) {
    return false;
  }
  
  const TByte *iSrcB=static_cast<const TByte*>(pBuf);
  const TByte *iSrcE=iSrcB+nBytesToWrite;
  
  if (iSrcB!=iSrcE && *iSrcB==0xFF) ++iSrcB;
  if (iSrcB!=iSrcE && *iSrcB==0x02) {
    const TByte *iSrcB1=iSrcB+1;
    if (iSrcB1!=iSrcE && *iSrcB1==0x02) iSrcB=iSrcB1;
  }
  
  m_dqWrite.insert(m_dqWrite.end(), iSrcB, iSrcE);
  nBytesWritten=nBytesToWrite;

  OnWrite();
  return true;
}

template<unsigned int N>
std::string MkStr(const char (&sz)[N])
{
  return std::string(sz, N-1);
}
                                
OByte TPortEmulator::Pop()
{
  if (m_dqWrite.empty()) return None;
  const TByte b= m_dqWrite.front();
  m_dqWrite.pop_front();
  return b;
}

void TPortEmulator::Push(TByte b)
{
  m_dqRead.push_back(b);
}

/////////////////////////////////////////////////////////////////////////////
void TPortTableEmulator::OnWrite()
{
  typedef std::map<std::string, std::string> TResponseMap;
  typedef TResponseMap::const_iterator       TResponseMapCIt;
  
  TResponseMap m_rm;
//   m_rm[MkStr("\x02\x70\x4D\x03")]=
//        MkStr("\x02\x70\x10\x0A\x4D\x03\x02\x66\x10\x0A\x55\xAA\x10\x00\x10\x09"
//              "\xBC\x34\x03");

  m_rm[MkStr("\x02\x70\x4D\x03")]=
       MkStr("\x02\x70\x10\x0A\x4D\x03");

  m_rm[MkStr("\x02\xF0\x01\x4D\x6D\x0A\x03")]=
       MkStr("\x02\xF0\x03\x00\x0A\x4D\x8D\x28\x03");
       
  m_rm[MkStr("\x02\xF0\x01\x53\x73\x0A\x03")]=
       MkStr("\x02\xF0\x03\x00\x0A\x53\x93\x28\x03");


  m_rm[MkStr("\x02\xFE\x01\x00\x84\x09\x03")]=
       MkStr("\x02\xFE\x03\x00\x0A\x00\x98\x2B\x03");

  m_rm[MkStr("\x02\xFE\x01\x01\x85\x09\x03")]=
       MkStr("\x02\xFE\x03\x00\x0A\x01\x99\x2B\x03");


  m_rm[MkStr("\x02\xF7\x00\xF7\x00\x03")]=
       MkStr("\x02\xF7\x09\x00\x0A\x0C\x05\x16\x15\x39\x70\x10\x0C\x13\x03");

  m_rm[MkStr("\x02\xF6\x07\x0C\x05\x16\x05\x3A\xF5\x04\xE6\x8E\x03")]=
       MkStr("\x02\xF6\x09\x00\x0A\x0C\x05\x16\x05\x3A\xF5\x04\xF0\x5A\x03");


  m_rm[MkStr("\x02\x61\x10\x00\x03")]=
       MkStr("\x02\x61\x10\x0A\x10\x00\x10\x01\x10\x01\x10\x01\x10\x01\xED\xED"
             "\xED\xED\x55\xAA\x10\x00\x10\x09\xBC\x34\xA0\x66\x10\x00\x22\x10"
             "\x04\x10\x05\x10\x18\x10\x11\x10\x1D\x90\x10\x18\x10\x0E\x10\x1D"
             "\x87\x10\x18\x10\x0C\x10\x1D\x84\x10\x08\x10\x0B\x10\x1D\x84\xFF"
             "\xFF\xFF\xFF\x10\x00\x10\x00\x10\x00\x10\x01\x20\x20\x20\x20\x54"
             "\x61\x79\x6D\x61\x6E\x6F\x76\x20\x20\x20\x20\x20\x20\x20\x20\x20"
             "\x20\x20\x20\x53\x65\x72\x67\x65\x79\x20\x20\x20\x20\x20\x20\x20"
             "\x20\x20\x20\x20\x20\x20\x20\x52\x55\x53\x20\x20\x20\x20\x20\x20"
             "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
             "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x10"
             "\x19\x03");
  
  using std::string;

  string sIn;
  
  OByte ob;
  while (ob=Pop()) sIn.push_back(*ob);
  
  const TResponseMapCIt Im=m_rm.find(sIn);
  if (Im==m_rm.end()) return;
  
  for (string::const_iterator I=Im->second.begin(); I!=Im->second.end(); ++I) {
    Push(*I);
  }
}

