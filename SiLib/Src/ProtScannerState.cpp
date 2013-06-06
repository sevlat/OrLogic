// SeVlaT, 29.11.2012
#include "StdAfx.h"

#include "../ProtScanner.h"

////////////////////////////////////////////////////////////////////////////////
#define CASE_RETURN(x) case (x): return #x;

namespace {
const char c_szEmpty[]="";
}

namespace ProtScannerState {
  const char* GetStateName(TState s)
  {
    switch (s) {
      CASE_RETURN(sStart);
      CASE_RETURN(sWUp);
      CASE_RETURN(sStx1);
      CASE_RETURN(sStx2);
      CASE_RETURN(sbData);
      CASE_RETURN(sbDle);
      CASE_RETURN(seCmd);
      CASE_RETURN(seData);
      CASE_RETURN(seCrcH);
      CASE_RETURN(seCrcL);
      CASE_RETURN(sEnd);
    }
    
    return c_szEmpty;
  }
}

using namespace ProtScannerState;
  
////////////////////////////////////////////////////////////////////////////////
TProtScannerState::TProtScannerState()
 : m_State(sStart),
   m_bErr(false)
{
}
  
void TProtScannerState::SetState(TState s)
{
  assert(CheckState());

  assert(!m_bErr);
  m_State=s;
}

void TProtScannerState::SetError()
{
  assert(CheckState());

  assert(!m_bErr);
  m_bErr=true;
}

bool TProtScannerState::IsAtStart() const
{
  assert(CheckState());

  if (m_bErr) return false;
  return m_State==sStart;
}

bool TProtScannerState::IsRunning() const
{
  assert(CheckState());

  return !IsAtStart() && !IsStalled();
}

bool TProtScannerState::IsStalled() const
{
  assert(CheckState());

  return m_bErr || (m_State==sEnd);
}

bool TProtScannerState::IsStalledOk() const
{
  assert(CheckState());

  return !m_bErr && (m_State==sEnd);
}

bool TProtScannerState::IsStalledFail() const
{
  assert(CheckState());
  return m_bErr;
}

//(!bErr && bEnd) || bErr;
//!(bErr || !bEnd) || bErr;

// bErr || bEnd;

bool TProtScannerState::CheckState() const
{
  return m_State!=sEnd || !m_bErr;
}


