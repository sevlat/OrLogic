// !!!!!!!! to be deleted

// SeVlaT, 18.06.2012
#include "StdAfx.h"

#include "../Station.h"

#include "../Commands.h"
#include "../Utils.h"

#include "../CmdSerializeImpl.h"

TCmdResult ReceiveRes2Cmd(TReceiveResult rr)
{
  switch (rr) {
    case rrOK:             return crOK;
    case rrNak:            return crNak;
    case rrReceivingError: return crReceivingError;
    case rrParcingError:   return crParcingError;
  }
  
  assert(false);
  return crReceivingError;
}

TCmdResult TCmdProcessor::Do(ICmdTransmit &CmdT,
                             ICmdReceive  &CmdR,
                             IIStream     &is,
                             IOStream     &os,
                             TErrList     *pErr) const
{
  const TMsgFrame mf(m_Params.Pref);
  CmdT.Init(mf, pErr);
  
  TReceiveResult rr=rrOK;
  
  TUInt nMsWaitAnswer=m_Params.nMsWaitAnswer;
  TUInt nMsWaitOnNak=m_Params.nMsWaitOnNak;

  const int nRepeteOnNakCount=std::max<TUInt>(1, m_Params.nRepeteOnNakCount);
  for (int i=0; i<nRepeteOnNakCount; ++i) {
    if (!CmdT.Send(os, pErr)) return crTransmittingError;
    
    SleepMs(nMsWaitAnswer);
    nMsWaitAnswer+=m_Params.nMsWaitAnswerInc;

    rr=CmdR.Receive(is, pErr);
    if (rr!=rrNak) break;
    
    SleepMs(nMsWaitOnNak);
    nMsWaitOnNak+=m_Params.nMsWaitOnNakInc;
  }
  
  return ReceiveRes2Cmd(rr);
}                             

////////////////////////////////////////////////////////////////////////////////
TStation::TStation(IIOStream &ios)
 : m_is(ios),
   m_os(ios)
{
}
  
template<typename TRANSCEIVER>
TCmdResult TStation::DoCmd(TRANSCEIVER &trcv, const ICmdProcessor &proc, TErrList *pErr)
{
  return proc.Do(trcv, trcv, m_is, m_os, pErr);
}

TCmdResult TStation::Cmd(TSetMaSlaveB &cmd, const ICmdProcessor &proc, TErrList *pErr)
{
  return DoCmd(cmd, proc, pErr);
}

TCmdResult TStation::Cmd(TSetMaSlaveE &cmd, const ICmdProcessor &proc, TErrList *pErr)
{
  return DoCmd(cmd, proc, pErr);
}

TCmdResult TStation::Cmd(TSetBaudRateB &cmd, const ICmdProcessor &proc, TErrList *pErr)
{
  return DoCmd(cmd, proc, pErr);
}

TCmdResult TStation::Cmd(TSetBaudRateE &cmd, const ICmdProcessor &proc, TErrList *pErr)
{
  return DoCmd(cmd, proc, pErr);
}

