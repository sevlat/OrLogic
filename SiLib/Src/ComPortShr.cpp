// SeVlaT, 09.04.2013
#include "StdAfx.h"

#include "../Ext/ComPortShr.h"

#include "../PortEmulator.h"
#include "../bSEmulator.h"

TComPortShr::TComPortShr(bool bEmulator)
{
  if (bEmulator) {
    m_shp=TShp(new TBsEmulator());
  } else {
    m_shp=TShp(PlatformSpecific::CreateComPort(),
              &PlatformSpecific::DeleteComPort);
  }
}   

