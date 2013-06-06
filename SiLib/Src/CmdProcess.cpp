// !!!!!!!! to be deleted

// SeVlaT, 23.12.2012
#include "StdAfx.h"

#include "../CmdProcess.h"

TCmdProcess::TCmdProcess(TCmdCode ccB, TSysSpan tsWait)
 : m_state(sStart),
   m_ccB(ccB),
   m_tsWait(tsWait)
{
}
  
void TCmdProcess::Sent(TSysTime t)
{
  assert(m_state==sStart);
  
  m_tLast=t+m_tsWait;
  m_state=sReqSent;
}

bool TCmdProcess::Receive(TCmdCode cc, TSysTime t)
{
  assert(m_state==sReqSent);
  
  if (t>m_tLast) {
    m_state=sTimeOut;
    return true;
  }
  
  if (cc==m_ccB) {
    m_state=sRespGot;
    return true;
  } else if (cc==CmdCd::Nak) {
    m_state=sNakGot;
    return true;
  }

  return false;
}

