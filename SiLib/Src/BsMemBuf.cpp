// SeVlaT, 19.05.2013
#include "StdAfx.h"

#include "../BsMemBuf.h"


void TBsMemBuffer::AddEmpty(TUInt nAddr, TUInt nSize)
{
  const TUInt nLast=nAddr+nSize;
  if (nLast>m_buf.size()) m_buf.resize(nLast);
}

void TBsMemBuffer::Add(const TBiasedByteBuffer &buf)
{
  const TUInt nLast=buf.Last();
  if (nLast>m_buf.size()) m_buf.resize(nLast);
  
  std::copy(buf.begin(), buf.end(), m_buf.begin()+buf.First()); 
}

bool TBsMemBuffer::Load(std::istream &is)
{
  const TUInt c_nBufSize=1024;
  std::istream::char_type cBuf[c_nBufSize];
  
  m_buf.clear();
  
  while (is) {
    if (!is.read(cBuf, c_nBufSize)) return false;
    m_buf.insert(m_buf.end(), cBuf, cBuf+is.gcount());
  }
  
  return true;
}

bool TBsMemBuffer::Save(std::ostream &os) const
{
  const TUInt c_nBufSize=1024;
  std::istream::char_type cBuf[c_nBufSize];
  
  TUInt nBegin=0;
  
  while (nBegin<m_buf.size()) {
    TUInt nRest=m_buf.size()-nBegin;
    if (nRest>c_nBufSize) nRest=c_nBufSize;
    
    std::copy(m_buf.begin()+nBegin, m_buf.begin()+nBegin+nRest, cBuf);
    if (!os.write(cBuf, nRest)) return false;
    
    nBegin+=nRest;
  }
  
  return true;
}
