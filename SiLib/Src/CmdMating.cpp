// SeVlaT, 31.01.2013
#include "StdAfx.h"

#include "../CmdMating.h"

#include "../CommandCode.h"

bool AreCommandsMateable(TCmdCode ccF, TCmdCode ccB)
{
  if (ccF==ccB) return true;
  
  if (ccB==CmdCd::Nak) return true;

  if (ccF==CmdCd::bGetBck && ccB==CmdCd::eGBck)  return true;
  if (ccF==CmdCd::bGBck2  && ccB==CmdCd::eGBck2) return true;
  
  return false;  
}

bool MayInduceResponce(TCmdCode ccF)
{
  return true;
}

bool MayBeAloneResponce(TCmdCode ccB)
{
  return false;
}


