// SeVlaT, 17.05.2013
#include "StdAfx.h"

#include "../Ext/CmdsReceiver.h"

#include "../PacketReceiver.h"
#include "../Ext/CmdsParse.h"

void TCmdReceiver::Receive(TErrList *pErr)
{
  m_oCmdRx=None;
  
  m_PktReceiver.Receive(pErr);
  
  const TProtCmdPacket *ppkt=m_PktReceiver.Get();
  if (!ppkt) return;
  
  ShpBCmdObject shpBCmd(ShpBParse(*ppkt, pErr));
  const TCmdRxInfo cri(m_sng.Generate());
  m_oCmdRx=TBCmdRx(shpBCmd, cri);
}

