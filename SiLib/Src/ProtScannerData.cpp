// SeVlaT, 29.11.2012
#include "StdAfx.h"

#include "../ProtScanner.h"

#include "../Crc.h"

#include <hftl/Main/m_obbUtils.h>

TProtScannerMessage::TProtScannerMessage(TProtCmdPacket &pkt)
 : m_pkt(pkt)
{
  m_pkt.Frame.Prefix=TMsgPrefix(false, 0);
  m_pkt.Frame.Suffix=msNone;
}  

TUInt TProtScannerMessage::GetSize() const
{
  return m_pkt.buf.size();
}

void TProtScannerMessage::AddDataByte(TByte b)
{
  m_pkt.buf.Append(b);
}

void TProtScannerMessage::SetPrefixWakeUp()
{
  assert(!m_pkt.Frame.Prefix.bWakeUp);
  m_pkt.Frame.Prefix.bWakeUp=true;
}

void TProtScannerMessage::SetPrefixStx1()
{
  assert(m_pkt.Frame.Prefix.nStx==0);
  m_pkt.Frame.Prefix.nStx=1;
}

void TProtScannerMessage::SetPrefixStx2()
{
  assert(m_pkt.Frame.Prefix.nStx==1);
  m_pkt.Frame.Prefix.nStx=2;
}

void TProtScannerMessage::SetSuffixEndNak()
{
  assert(m_pkt.Frame.Suffix==msNone);
  m_pkt.Frame.Suffix=msNak;
}

void TProtScannerMessage::SetSuffixEndEtx()
{
  assert(m_pkt.Frame.Suffix==msNone);
  m_pkt.Frame.Suffix=msEtx;
}

void TProtScannerMessage::SetCommand(TCmdCode cc)
{
  m_pkt.cc=cc;
}

TWord TProtScannerMessage::CalcCrc() const
{
//  const OByte obLen=hftl::SafeCastToByte(m_msg.buf.size());
  assert(m_pkt.buf.size()<=255);
  const TByte bLen=m_pkt.buf.size();

  TCrc crc(2+bLen);
  crc.AddByte(m_pkt.cc);
  crc.AddByte(bLen);
  crc.AddBuf(m_pkt.buf);
  
  return crc.Get();
}

////////////////////////////////////////////////////////////////////////////////
TProtScannerOutput::TProtScannerOutput(TProtCmdPacket   &pkt,
                                       TProtScannerData &Data)
 : TProtScannerMessage(pkt),
   m_Data(Data)
{
}

void TProtScannerOutput::AddBDataByte(TByte b)
{
  assert(!m_Data.obELen);
  
  TProtScannerMessage::AddDataByte(b);
}

bool TProtScannerOutput::AddEDataByte(TByte b)
{
  if (!m_Data.obELen) {
    assert(!"m_Data.obELen not set");
    return false;
  }
  
  assert(TProtScannerMessage::GetSize()<=*m_Data.obELen);
  
  if (TProtScannerMessage::GetSize()>=*m_Data.obELen) return false;
  TProtScannerMessage::AddDataByte(b);
  return true;
}

void TProtScannerOutput::SetELen(TByte b)
{
  m_Data.SetELen(b);
}

void TProtScannerOutput::SetUnexpectedByte(TByte b)
{
  m_Data.SetUnexpectedByte(b);
}

void TProtScannerOutput::SetCrcH(TByte b)
{
  m_Data.SetCrcH(b);
}

void TProtScannerOutput::SetCrcL(TByte b)
{
  m_Data.SetCrcL(b);
}

void TProtScannerOutput::SetCommand(TCmdCode cc, TCommandType ct)
{
  m_Data.SetCommandType(ct);
  TProtScannerMessage::SetCommand(cc);
}

void TProtScannerOutput::CheckCrc()
{
  m_Data.CheckCrc(CalcCrc());
}


////////////////////////////////////////////////////////////////////////////////
void TProtScannerData::CheckCrc(TWord wCalculatedCrc)
{
  assert(obCrcH && obCrcL);
  assert(oct && (*oct==ctExt));
  assert(!obCrcOk);
  
  const TWord wCrc=hftl::Make2Byte(*obCrcL, *obCrcH);
    
  obCrcOk=(wCalculatedCrc==wCrc);
}


void TProtScannerData::SetCommandType(TCommandType ct)
{
  assert(!oct);
  oct=ct;
}

void TProtScannerData::SetELen(TByte b)
{
  assert(!obELen);
  obELen=b;
}

void TProtScannerData::SetUnexpectedByte(TByte b)
{
  assert(!obUnexp);
  obUnexp=b;
}

void TProtScannerData::SetCrcH(TByte b)
{
  assert(!obCrcH);
  obCrcH=b;
}

void TProtScannerData::SetCrcL(TByte b)
{
  assert(!obCrcL);
  obCrcL=b;
}

////////////////////////////////////////////////////////////////////////////////
