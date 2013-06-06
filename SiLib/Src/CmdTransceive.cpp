// SeVlaT, 09.03.2013
#include "StdAfx.h"

#include "../Ext/CmdTransceive.h"

#include "../CmdTrxInfo.h"
#include "../StationWrite.h"
#include "../ComPort.h"
#include "../Utils.h"

#include "../Ext/CmdQueue.h"
#include "../Ext/CmdsParse.h"


////////////////////////////////////////////////////////////////////////////////
TCmdTransceiver::TCmdTransceiver(TCmdQueue    &Queue,
                                 TCmdReceiver &CmdReceiver,
                                 TCmdSender   &CmdSender)
 : m_Queue(Queue),
   m_CmdReceiver(CmdReceiver),
   m_CmdSender(CmdSender),
   m_nQIndex(0)
{
}

OCmdTxInfo TCmdTransceiver::Send(      ShpFCmdObject  shpFCmd,
                                 const TPrefixParams *pPP,
                                       TErrList      *pErr)
{
  TMsgFrame mf(m_mf);
  if (pPP) mf.Prefix=TMsgPrefix(m_mf.Prefix, *pPP);
  
  const OCmdTxInfo octi=m_CmdSender.Send(shpFCmd, mf, pErr);
  if (!octi) return None;

  TFCmdTx CmdTx(shpFCmd, *octi);
  m_Queue.Push(CmdTx);

  return octi;
}

void TCmdTransceiver::Receive(TErrList *pErr)
{
  while (ReceiveCmd(pErr));
}

bool TCmdTransceiver::ReceiveCmd(TErrList *pErr)
{
  m_CmdReceiver.Receive(pErr);

  const OBCmdRx &oBCmdRx=m_CmdReceiver.Get();
  if (!oBCmdRx) return false;

  m_Queue.Push(*oBCmdRx);
  return true;
}

OCmdExch TCmdTransceiver::Transceive(      ShpFCmdObject  shpFCmd,
                                     const TPrefixParams *pPP,
                                           TErrList      *pErr)
{
  OCmdExch ocmdx;

  for (int i=0; i<7; ++i) {
    ocmdx=TransceiveOnce(shpFCmd, pPP, pErr);
    if (ocmdx && ocmdx->Status()!=ICmdExch::sNak) break;
  }

  return ocmdx;
}

OCmdExch TCmdTransceiver::TransceiveOnce(      ShpFCmdObject  shpFCmd,
                                         const TPrefixParams *pPP,
                                               TErrList      *pErr)
{
  const OCmdTxInfo octi=Send(shpFCmd, pPP, pErr);
  if (!octi) return None;

  const TCmdExch *pCmdExch=Receive3(octi, pErr);
  if (pCmdExch) return *pCmdExch;

  return None;
}

const TCmdExch* TCmdTransceiver::Receive3(const OCmdTxInfo &octi,
                                                TErrList  *pErr)
{
  int n=0;
  int nSleepMs=50;
  while (true) {
    const TCmdExch *pCmdExch=Receive(octi, pErr);
    if (pCmdExch) return pCmdExch;

    if (n>=7) break;
    ++n;

    SleepMs(nSleepMs);
         if (n<=2) nSleepMs+=50;
    else if (n<=4) nSleepMs+=100;
    else           nSleepMs+=200;
  };

  return 0;
}

const TCmdExch* TCmdTransceiver::Receive(const OCmdTxInfo &octi,
                                               TErrList  *pErr)
{
  Receive(pErr);

  return LookUpQueue(octi->sn, pErr);
}

const TCmdExch* TCmdTransceiver::LookUpQueue(TSerNum sn, TErrList *pErr)
{
  while (true) {
    const TCmdExch *pCmdExch=m_Queue.GetCurOutput(m_nQIndex);
    if (!pCmdExch) return 0;

    ++m_nQIndex;

    if (sn==pCmdExch->FInfo().sn) return pCmdExch;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
TCmdsPerformer::TCmdsPerformer(TCmdTransceiver &Tr,
                               ShpFCmdObject    shpFCmd,
                               int              nMaxReceiveTry,
                               int              nMaxNakTry,
                               TErrList        *pErr)
 : m_Tr(Tr),
   m_shpFCmd(shpFCmd),
   m_nMaxReceiveTry(nMaxReceiveTry),
   m_nMaxNakTry(nMaxNakTry),
   m_pErr(pErr),
   m_State(sBegin),
   m_nReceiveTry(0),
   m_nNakTry(0)
{
}

OCmdExch TCmdsPerformer::Res()
{
  if (m_State==sEnd) return m_oExch;
  return None;
}

bool TCmdsPerformer::Do()
{
  if (m_State==sBegin) return DoOnBegin();
  if (m_State==sSent)  return DoOnSent();

  assert(!"Unexpected state");
  return false;
}

bool TCmdsPerformer::DoOnBegin()
{
  m_octi=m_Tr.Send(m_shpFCmd, 0, m_pErr);
  if (!m_octi) {
    m_State=sError;
    return true;
  }

  m_State=sSent;
  return false;
}

bool TCmdsPerformer::DoOnSent()
{
  ++m_nReceiveTry;
  m_oExch=OptFromPtr(m_Tr.Receive(m_octi, m_pErr));
  if (!m_oExch) {
    if (m_nReceiveTry<m_nMaxReceiveTry) {
      return false;
    }

    m_State=sEnd;
    return true;
  }

  m_nReceiveTry=0;

  if (m_oExch->Status()==ICmdExch::sNak) {
    ++m_nNakTry;
    if (m_nNakTry<m_nMaxNakTry) {
      m_State=sBegin;
      return false;
    }

    return true;
  }

  m_State=sEnd;
  return true;
}


