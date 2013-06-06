// SeVlaT, 26.11.2012
#include "StdAfx.h"

#include "ProtScannerEngine.h"

#include "../ProtScanner.h"


using namespace ProtScannerState;

////////////////////////////////////////////////////////////////////////////////

TProtScanner::TProtScanner(TProtScannerState  &State,
                           TProtScannerOutput &Output,
                           TProtScannerCounts &Counts)
 : m_State(State),
   m_Output(Output),
   m_Counts(Counts)
{
}

bool TProtScanner::Next(TByte b) const
{
  if (m_State.IsStalledFail()) {
  } else {
    switch (m_State.GetState()) {
      case sStart: return NextAtStart(b);
      case sWUp:   return NextAtWUp  (b);
      case sStx1:  return NextAtStx1 (b);
      case sStx2:  return NextAtStx2 (b);
      case sbData: return NextAtBData(b);
      case sbDle:  return NextAtBDle (b);
      case seCmd:  return NextAtECmd (b);
      case seData: return NextAtEData(b);
      case seCrcH: return NextAtECrcH(b);
      case seCrcL: return NextAtECrcL(b);
      case sEnd:   return NextAtEnd  (b);
      default: assert(!"Unexpected State");
    }
  }
  
  return false;
}

/*
bool TProtScanner::Next(TByte b, bool &bEaten)
{
  bEaten=Next(b);
  return bEaten;
}
*/

////////////////////////////////////////////////////////////////////////////////
bool TProtScanner::TakeUnexpected(TByte b) const
{
  m_State.SetError();
  m_Output.SetUnexpectedByte(b);
  return false;
}

bool TProtScanner::TakeWakeUp(TByte b) const
{
  if (b!=SpecByte::bWup) return false;
  
  m_Output.SetPrefixWakeUp();
  m_State.SetState(sWUp);
  return true;
}

bool TProtScanner::TakeFirstStx(TByte b) const
{
  if (b!=SpecByte::bStx) return false;

  m_Output.SetPrefixStx1();
  m_Counts.NeedEnd();
  m_State.SetState(sStx1);
  return true;
}

bool TProtScanner::TakeSecondStx(TByte b) const
{
  if (b!=SpecByte::bStx) return false;

  m_Output.SetPrefixStx2();
  m_State.SetState(sStx2);
  return true;
}

bool TProtScanner::TakeLiteCmd(TByte b) const
{
  const OCmdCode occ=LiteCmdCode(b);
  if (!occ) return false;

  m_Output.SetCommand(*occ, ctLite);
  m_Counts.ReadCmdLite();
  m_State.SetState(sEnd);
  return true;
}

bool TProtScanner::TakeCmd(TByte b) const
{
  const OCmdCode occ=CmdCode(b);
  if (!occ) return false;
  
  const TCommandInfo &ci=GetCommandInfoRef(*occ);
  
  if (ci.ct==ctBase) {
    m_Output.SetCommand(*occ, ctBase);
    m_Counts.ReadCmdBase(ci.onBSize, None);
    m_State.SetState(sbData);
    return true;
  }
  
  if (ci.ct==ctExt) {
    m_Output.SetCommand(*occ, ctExt);
    m_Counts.ReadCmdExt();
    m_State.SetState(seCmd);
    return true;
  }

  return false;
}

bool TProtScanner::TakeDle(TByte b) const
{
  if (b!=SpecByte::bDle) return false;

  m_State.SetState(sbDle);
  return true;
}

bool TProtScanner::TakeBUnescapedData(TByte b) const
{
  if (NeedDle(b)) return false;
  
  m_Output.AddBDataByte(b);
  m_Counts.ReadData();
  return true;  
}

bool TProtScanner::TakeBEscapedData(TByte b) const
{
  if (!NeedDle(b)) return false;
  
  m_Output.AddBDataByte(b);
  m_Counts.ReadData();
  m_State.SetState(sbData);
  return true;  
}

bool TProtScanner::TakeELen(TByte b) const
{
  m_Output.SetELen(b);
  m_Counts.ReadLen(b);
  m_State.SetState(seData);
  return true;  
}

bool TProtScanner::TakeEData(TByte b) const
{
  if (!m_Output.AddEDataByte(b)) return false;
  m_Counts.ReadData();
  return true;  
}

bool TProtScanner::TakeECrcH(TByte b) const
{
  m_Output.SetCrcH(b);
  m_Counts.ReadCrc();
  m_State.SetState(seCrcH);
  return true;  
}

bool TProtScanner::TakeECrcLnCheck(TByte b) const
{
  m_Output.SetCrcL(b);
  m_Output.CheckCrc();
  m_Counts.ReadCrc();
  m_State.SetState(seCrcL);
  return true;
}

bool TProtScanner::TakeSuffix(TByte b) const
{
       if (b==SpecByte::bEtx) m_Output.SetSuffixEndEtx();
  else if (b==SpecByte::bNak) m_Output.SetSuffixEndNak();
  else return false;

  m_Counts.ReadEnd();
  m_State.SetState(sEnd);
  m_Counts.AssertZeroCounts();
  return true;
}

////////////////////////////////////////////////////////////////////////////////
bool TProtScanner::NextAtStart(TByte b) const
{
  return TakeWakeUp    (b) ||
         TakeFirstStx  (b) ||
         TakeLiteCmd   (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtWUp(TByte b) const
{
  return TakeFirstStx  (b) ||
         TakeLiteCmd   (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtStx1(TByte b) const
{
  return TakeSecondStx (b) ||
         TakeCmd       (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtStx2(TByte b) const
{
  return TakeCmd       (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtBData(TByte b) const
{
  return TakeDle           (b) ||
         TakeSuffix        (b) ||
         TakeBUnescapedData(b) ||
         TakeUnexpected    (b);
}

bool TProtScanner::NextAtBDle(TByte b) const
{
  return TakeBEscapedData(b) ||
         TakeUnexpected  (b);
}

bool TProtScanner::NextAtECmd(TByte b) const
{
  return TakeELen      (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtEData(TByte b) const
{
  return TakeEData(b) ||
         TakeECrcH (b);
}

bool TProtScanner::NextAtECrcH(TByte b) const
{
  return TakeECrcLnCheck(b) ||
         TakeUnexpected (b);
}

bool TProtScanner::NextAtECrcL(TByte b) const
{
  return TakeSuffix    (b) ||
         TakeUnexpected(b);
}

bool TProtScanner::NextAtEnd(TByte b) const
{
  assert(false);
  return false;
}




