// SeVlaT, 14.06.2012
#include "StdAfx.h"

#include "../BsEmulator.h"

#include "../PacketParseV.h"
#include "../StationWrite.h"
#include "../CmdSerializeImpl.h"

TBsEmulator::TBsEmulator()
 : m_bMaster(0),
   m_bHighSpeed(false),
   m_mf(TMsgPrefix(false, 1)),
   m_bsc(20)
{
}

/////////////////////////////////////////////////////////////////////////////
void TBsEmulator::OnWrite()
{
  OByte ob;
  while (ob=Pop()) Set(*ob);
}

void TBsEmulator::Received()
{
  ParsePacketV(*this, *this, m_pkt, 0);
}

bool TBsEmulator::TryNext(TByte b)
{
  bool bEaten=false;
  ScanNext(b, bEaten);
  
  if (m_State.IsStalled()) {
    if (m_State.IsStalledOk()) {
      Received();
    } else if (m_State.IsStalledFail()) {
      // AddError();
    }
    
    m_pkt   =TProtCmdPacket     ();
    m_State =TProtScannerState  ();
    m_Data  =TProtScannerData   ();
    m_Counts=TProtScannerCounts ();
  }
  
  return bEaten;
}

void TBsEmulator::Set(TByte b)
{
  if (TryNext(b)) return;
  if (TryNext(b)) return;
}

void TBsEmulator::Return(const TProtCmdPacket &pkt)
{
  TByteBuffer buf;
  AssemblePacket(pkt, buf, 0);

  for (TByteBufferCIt I=buf.begin(); I!=buf.end(); ++I) {
    Push(*I);
  }
}

TDateTimeSS TBsEmulator::GetTime() const  // !!!!!!!!!!!!!! Todo
{
  TDateTimeSS dt;

  dt.bYear=12;
  dt.bMonth=5;
  dt.bDay=10;

  dt.bSubSec=0;
  dt.bWeekMidDay=0;
  dt.wDaySecond=10000;
  
  return dt;
}

void TBsEmulator::SetTime(const TDateTimeSS &dt)
{
  // !!!!!!!!!!!!!! Todo
}

/////////////////////////////////////////////////////////////////////////////
void TBsEmulator::operator ()(const CmdbFBeep &cmd)
{
}

void TBsEmulator::operator ()(const CmdbFSetMaSlaveB &cmd)
{
  m_bMaster=cmd.bMaster;
  const CmdBSetMaSlaveB BCmd(m_bMaster, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFSetMaSlaveE &cmd)
{
  m_bMaster=cmd.bMaster;
  const CmdBSetMaSlaveE BCmd(m_bMaster, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFGetMaSlaveB &cmd)
{
  const CmdBGetMaSlaveB BCmd(m_bMaster, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFGetMaSlaveE &cmd)
{
  const CmdBGetMaSlaveE BCmd(m_bMaster, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFSetBaudRateB &cmd)
{
  m_bHighSpeed=cmd.bHigh;
  const CmdBSetBaudRateB BCmd(m_bHighSpeed, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFSetBaudRateE &cmd)
{
  m_bHighSpeed=cmd.bHigh;
  const CmdBSetBaudRateE BCmd(m_bHighSpeed, m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFGetTimeB &cmd)
{
  const CmdBGetTimeB BCmd(GetTime().DateTime(), m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFGetTimeE &cmd)
{
  const CmdBGetTimeE BCmd(GetTime(), m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFSetTimeB &cmd)
{
  SetTime(cmd.t);

  const CmdBSetTimeB BCmd(GetTime().DateTime(), m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFSetTimeE &cmd)
{
  SetTime(cmd.t);

  const CmdBSetTimeE BCmd(GetTime(), m_bsc.Get());
  TProtCmdPacket pkt;
  if (MakePacket(BCmd, m_mf, pkt, 0)) Return(pkt);
}

void TBsEmulator::operator ()(const CmdbFGetSysValueE &cmd)
{
}

void TBsEmulator::operator ()(const CmdbFGetBckDataE &cmd)
{
}
 
void TBsEmulator::operator ()(const TProtCmdPacket &pkt, TagFwd, CauseCmdUnparseable)
{
}

void TBsEmulator::operator ()(const TProtCmdPacket &pkt, TagFwd, CauseCmdUnfamiliar)
{
}

void TBsEmulator::operator ()(const CmdbFBeepE &cmd)
{
}

void TBsEmulator::operator ()(const CmdbFTurnOffB &cmd)
{
}


 
