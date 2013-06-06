// SeVlaT, 13.05.2013
#include "StdAfx.h"

#include "../StreamLogger.h"

char GetSafeChar(TByte b)
{
  if (b<0x20) return '.';
  
  return static_cast<char>(b);
}

void PutHexByte(std::ostream &os, TByte b)
{
  static char chDigits[] = "0123456789ABCDEF";

  const TByte bh=(b>>4) & 0x0Fu;
  const TByte bl= b     & 0x0Fu;
  
  os << chDigits[bh] << chDigits[bl];
}

void PutHexBufLine(      std::ostream &os,
                   const void         *pBuf,
                         unsigned int  nBytes)
{
  if (!pBuf) return;
  if (nBytes==0) return;
  
  if (nBytes>32) nBytes=32;
  
  const TByte *pbBuf=static_cast<const TByte*>(pBuf);
  
  for (unsigned int i=0; i<nBytes; ++i) {
    os << ' ';
    PutHexByte(os, pbBuf[i]);
  }
  
  int nPos=3*nBytes;
  int nSpaces=51-nPos;
  if (nSpaces<3) nSpaces=3;
  
  for (int i=0; i<nSpaces; ++i) os << ' ';

  for (unsigned int i=0; i<nBytes; ++i) {
    const char ch=GetSafeChar(pbBuf[i]);
    os << ch;
  }
  
}

void PutHexBuf(      std::ostream &os,
               const void         *pBuf,
                     unsigned int  nBytes)
{
  if (!pBuf) return;
  
  const TByte *pbBuf=static_cast<const TByte*>(pBuf);
  
  while (nBytes>0) {
    const int nBytesForLine=nBytes>16? 16: nBytes;
    PutHexBufLine(os, pbBuf, nBytesForLine);
    os << std::endl;
    pbBuf+=nBytesForLine;
    nBytes-=nBytesForLine;
  }
}                  

////////////////////////////////////////////////////////////////////////////////
TStreamLogger::TStreamLogger(const std::string &sFileName,
                                   IIStream    &is,
                                   IOStream    &os)
 : m_sFileName(sFileName),
   m_is(is),
   m_os(os)
{
}

void TStreamLogger::Log(      bool      bRes,
                        const void     *pBuf,
                              TUInt     nBytesRequested,
                              TUInt     nBytesDone,
                              bool      bIn) const
{
  if (m_sFileName.empty()) return;
  
  std::ofstream file(m_sFileName.c_str(), std::ios::app);
  
  const bool bDirectionChanged=(!m_obIn) || (*m_obIn!=bIn);
  const bool bNotDone=(nBytesRequested!=nBytesDone);
  
  if (!bRes || bNotDone || bDirectionChanged) {
    if (!bNotDone && nBytesDone==0) return;
    file << std::endl;
    if (bIn) file << "Answer:";
        else file << "Request:";
        
    file << " ";

    if (bNotDone) {
      file << "requested " << nBytesRequested;
      if (bRes) {
        file << " done " << nBytesDone;
      }
    }
    
    file << std::endl;
  }

  if (bRes) {
    PutHexBuf(file, pBuf, nBytesDone);
  } else {
    file << "  Error !!!";
  }
  
  file << std::endl;
}                           

bool TStreamLogger::GetRaw(void     *pBuf,
                           TUInt     nBytesToRead,
                           TUInt    &nBytesRead,
                           TErrList *pErr)
{
  const bool bRes=m_is.GetRaw(pBuf, nBytesToRead, nBytesRead, pErr);
  Log(bRes, pBuf, nBytesToRead, nBytesRead, true);
  m_obIn=true;
  return bRes;
}

bool TStreamLogger::PutRaw(const void     *pBuf,
                                 TUInt     nBytesToWrite,
                                 TUInt    &nBytesWritten,
                                 TErrList *pErr)
{
  const bool bRes=m_os.PutRaw(pBuf, nBytesToWrite, nBytesWritten, pErr);
  Log(bRes, pBuf, nBytesToWrite, nBytesWritten, false);
  m_obIn=false;
  return bRes;
}
