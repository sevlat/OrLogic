// SeVlaT, 22.01.2013
#include "StdAfx.h"

#include "../Ext/CmdQueue.h"

#include "../Stream.h"
#include "../ProtScanner.h"
#include "../CmdMating.h"
#include "../MsgDescribe.h"

////////////////////////////////////////////////////////////////////////////////
void TFCmdQueue::Push(ShpFCmdObject shpF, const TCmdTxInfo &cti)
{
}

void TBCmdQueue::Push(ShpBCmdObject shpB, const TCmdRxInfo &cri)
{
}

////////////////////////////////////////////////////////////////////////////////
OCmdxStatus CommandsMateability(const TFCmdTx &fct, const TBCmdRx &bcr)
{
  if (!fct.shpCmd) return None;
  if (!bcr.shpCmd) return None;
  
  const TCmdCode ccF=fct.shpCmd->CmdCode();
  const TCmdCode ccB=bcr.shpCmd->CmdCode();
  
  if (!AreCommandsMateable(ccF, ccB)) return None;
  
  if (ccB==CmdCd::Nak) return ICmdExch::sNak;
  return ICmdExch::sOk;
}

OCmdxStatus AloneFwdCommand(const TFCmdTx &fct)
{
  if (!fct.shpCmd) return None;

  const TCmdCode ccF=fct.shpCmd->CmdCode();
  if (!MayInduceResponce(ccF)) return ICmdExch::sOk; // MayInduceResponce !!!!!!
  return ICmdExch::sNoAnswer;
}

OCmdxStatus AloneBwdCommand(const TBCmdRx &bcr)
{
  if (!bcr.shpCmd) return None;

  const TCmdCode ccB=bcr.shpCmd->CmdCode();
  if (MayBeAloneResponce(ccB)) return ICmdExch::sOk;
  return ICmdExch::sNoRequest;
}

////////////////////////////////////////////////////////////////////////////////
const TUInt c_nMaxBqSize=5;
const TUInt c_nMaxFqSize=5;

void TCmdQueue::Push(TFCmdTx fctx)
{
  m_fq.push_back(fctx);
  Push(fctx.cti);
  Process();
}

void TCmdQueue::Push(TBCmdRx bcrx)
{
  m_bq.push_back(bcrx);
  Push(bcrx.cri);
  Process();
}

void TCmdQueue::Push(TCmdRxInfo cri)
{
  if (cri.sn<=m_cri.sn) {
    return;
  }
  
  m_cri=cri;
  Process();
}

void TCmdQueue::Push(TCmdTxInfo cti)
{
  if (cti.sn<=m_cti.sn) {
    return;
  }
  
  m_cti=cti;
}

void TCmdQueue::Flush(TCmdRxInfo cri)
{
}

const TCmdExch& TCmdQueue::Get() const
{
  return m_q.get_first();
}

const TCmdExch* TCmdQueue::GetPtr() const
{
  if (m_q.empty()) return 0;
  return &m_q.get_first();
}

void TCmdQueue::Pop()
{
  m_q.pop();
}

bool TCmdQueue::InputEmpty() const
{
  return m_fq.empty() && m_bq.empty();
}

bool TCmdQueue::OutputEmpty() const
{
  return m_q.empty();
}

void TCmdQueue::Process()
{
  while (DoProcess());
}

bool TCmdQueue::DoProcess()
{
  const bool bFEmpty=m_fq.empty();
  const bool bBEmpty=m_bq.empty();

  if (bFEmpty && bBEmpty) {
    return false;
  } else if (bFEmpty) {
    assert(!bBEmpty);

    const TBCmdRx &bcr=m_bq.front();
    
    if (m_bq.size()>c_nMaxBqSize) {
      m_q.push(TCmdExch(bcr, TCmdExch::sTimeout));
      m_bq.pop_front();
      return true;
    }

    return false;
  } else if (bBEmpty) {
    assert(!bFEmpty);

    const TFCmdTx &fct=m_fq.front();
    
    if (m_fq.size()>c_nMaxBqSize) {
      m_q.push(TCmdExch(fct, TCmdExch::sTimeout));
      m_fq.pop_front();
      return true;
    }

    return false;
  } else {
    assert(!bFEmpty);
    assert(!bBEmpty);
    
    const TFCmdTx &fct0=m_fq.front();
    const TBCmdRx &bcr0=m_bq.front();

    {
      const OCmdxStatus ocs=CommandsMateability(fct0, bcr0);
      if (ocs) {
        m_q.push(TCmdExch(fct0, bcr0, *ocs));
        m_fq.pop_front();
        m_bq.pop_front();
        return true;
      }
    }

    if (m_fq.size()>1) {
      const TFCmdTx &fct1=m_fq[1];
      const OCmdxStatus ocs=CommandsMateability(fct1, bcr0);
      if (ocs) {
        const OCmdxStatus ocsF=AloneFwdCommand(fct0);
        if (ocsF) {
          m_q.push(TCmdExch(fct0, *ocsF));
          m_fq.pop_front();
          return true;
        }
      }
    }

    if (m_bq.size()>1) {
      const TBCmdRx &bcr1=m_bq[1];
      const OCmdxStatus ocs=CommandsMateability(fct0, bcr1);
      if (ocs) {
        const OCmdxStatus ocsB=AloneBwdCommand(bcr0);
        if (ocsB) {
          m_q.push(TCmdExch(bcr0, *ocsB));
          m_bq.pop_front();
          return true;
        }
      }
    }

    return false;
  }
  
  return false;
}

