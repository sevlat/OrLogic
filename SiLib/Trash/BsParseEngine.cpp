// SeVlaT, 17.01.2013
#include "StdAfx.h"

#include "../Ext/BsParseEngine.h"

TBsParseEngine::TBsParseEngine()
{
}

shpBsParser TBsParseEngine::AddByte(TByte b, bool &bEaten)
{
  if (!m_shpBsp) m_shpBsp.reset(new TBsParser());
  
  TBsParser &Bsp=*m_shpBsp;
  
  bEaten=Bsp.Next(b);
  
  shpBsParser shpBspRes;
  if (Bsp.State().IsStalled()) m_shpBsp.swap(shpBspRes);
  return shpBspRes;
}
