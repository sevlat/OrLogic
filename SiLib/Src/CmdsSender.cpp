// SeVlaT, 17.05.2013
#include "StdAfx.h"

#include "../Ext/CmdsSender.h"

#include "../PacketSender.h"

OCmdTxInfo TCmdSender::Send(const ShpFCmdObject &shpFCmd,
                            const TMsgFrame     &mf,
                                  TErrList      *pErr)
{
  const IFCmdObject *pFCmdo=shpFCmd.Get();
  if (!pFCmdo) return None;
  
  TProtCmdPacket pkt;
  if (!MakePacket(*pFCmdo, mf, pkt, pErr)) return None;
  
  const OPktTxInfo opti=m_ps.Send(pkt, pErr);
  if (!opti) return None;
  
  const TCmdTxInfo cti(m_sng.Generate());
//  TFCmdTx CmdTx(shpFCmd, cti); !!!!!
    
  return cti;
}
  
