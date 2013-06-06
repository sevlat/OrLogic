// SeVlaT, 20.01.2013
#include "StdAfx.h"

#include "../Ext/CmdsParse.h"

#include "../CmdDispatcher.h"

ShpFCmdObject ShpFParse(const TProtCmdPacket &pkt, TErrList *pErr)
{
  return ShpParse<TagFwd>(pkt, pErr);
}

ShpBCmdObject ShpBParse(const TProtCmdPacket &pkt, TErrList *pErr)
{
  return ShpParse<TagBwd>(pkt, pErr);
}
////////////////////////////////////////////////////////////////////////////////
