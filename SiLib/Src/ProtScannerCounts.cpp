// SeVlaT, 26.11.2012
#include "StdAfx.h"

#include "../ProtScanner.h"

////////////////////////////////////////////////////////////////////////////////
TByteCount::TByteCount(TUInt n)
 : m_nPos(n),
   m_nNeg(0)
{
  assert(m_nPos>=0);
}
  
void TByteCount::Dec()
{
  ++m_nNeg;
}

void TByteCount::Set(TUInt n)
{
  assert(m_nNeg==0);
  assert(m_nPos==0);
  assert(n>=0);

  m_nPos=n;
}

void TByteCount::AssertNonNegative() const
{
  assert(m_nPos>=m_nNeg);
}

////////////////////////////////////////////////////////////////////////////////
TProtScannerCounts::TProtScannerCounts()
 : m_bcLen(0),
   m_bcCmd(1),
   m_bcCrc(0),
   m_bcEnd(0),
   m_obcDataMin(None, TByteCount(0)),
   m_obcDataMax(None, TByteCount(0))
{
}     

OUInt TProtScannerCounts::GetMin() const
{
  if (!m_obcDataMin) return None;
  return m_obcDataMin->Get()+GetWithoutData();
}

OUInt TProtScannerCounts::GetMax() const
{
  if (!m_obcDataMax) return None;
  return m_obcDataMax->Get()+GetWithoutData();
}

int TProtScannerCounts::GetWithoutData() const {
  return m_bcLen.Get()+
         m_bcCmd.Get()+
         m_bcCrc.Get()+
         m_bcEnd.Get();
}

void TProtScannerCounts::NeedEnd()
{
  m_bcEnd.Set(1);
}

void TProtScannerCounts::ReadCmdLite()
{
  m_bcCmd.Dec();
}

void TProtScannerCounts::ReadCmdBase(OUInt onMin, OUInt onMax)
{
  assert(!m_obcDataMin);
  assert(!m_obcDataMax);
  
  m_bcCmd.Dec();
  if (onMin) m_obcDataMin=TByteCount(*onMin);
  if (onMax) m_obcDataMax=TByteCount(*onMax);
}

void TProtScannerCounts::ReadCmdExt()
{
  m_bcCmd.Dec();
  m_bcLen.Set(1);
  m_bcCrc.Set(2);
}

void TProtScannerCounts::ReadLen(TByte bLen)
{
  assert(!m_obcDataMin);
  assert(!m_obcDataMax);

  m_bcLen.Dec();
  
  m_obcDataMin=TByteCount(bLen);
  m_obcDataMax=TByteCount(bLen);
}

void TProtScannerCounts::ReadData()
{
  if (m_obcDataMin) m_obcDataMin->Dec();
  if (m_obcDataMax) m_obcDataMax->Dec();
}

void TProtScannerCounts::ReadCrc()
{
  m_bcCrc.Dec();
}

void TProtScannerCounts::ReadEnd()
{
  m_bcEnd.Dec();
}

void TProtScannerCounts::AssertNonNegative() const
{
  m_bcLen.AssertNonNegative();
  m_bcCmd.AssertNonNegative();
  m_bcCrc.AssertNonNegative();
  m_bcEnd.AssertNonNegative();

  if (m_obcDataMin) m_obcDataMin->AssertNonNegative();
  if (m_obcDataMax) m_obcDataMax->AssertNonNegative();
}

void TProtScannerCounts::AssertZeroCounts() const
{
  return; // Temporary
  AssertNonNegative();
  
  assert(GetWithoutData()==0);
  if (m_obcDataMin) assert(m_obcDataMin->Get()==0);
  if (m_obcDataMax) assert(m_obcDataMax->Get()==0);
}

