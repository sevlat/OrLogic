// SeVlaT, 16.01.2013
#include "StdAfx.h"

#include "../CmdData.h"

CmddFSetMaSlave::CmddFSetMaSlave()
 : bMaster(false)
{
}
   
CmddFSetMaSlave::CmddFSetMaSlave(bool bM)
 : bMaster(bM)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBMaSlaveB::CmddBMaSlaveB()
 : bMaster(false),
   bCN(0)
{
}

CmddBMaSlaveB::CmddBMaSlaveB(bool abMaster, TByte abCN)
 : bMaster(abMaster),
   bCN(abCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddBMaSlaveE::CmddBMaSlaveE()
 : bMaster(false),
   wCN(0)
{
}

CmddBMaSlaveE::CmddBMaSlaveE(bool abMaster, TWord awCN)
 : bMaster(abMaster),
   wCN(awCN)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddFSetBaudRate::CmddFSetBaudRate()
{
}

CmddFSetBaudRate::CmddFSetBaudRate(bool abHigh)
 : bHigh(abHigh)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddBSetBaudRateB::CmddBSetBaudRateB()
 : bHigh(false),
   bCN(0)
{
}

CmddBSetBaudRateB::CmddBSetBaudRateB(bool abHigh, TByte abCN)
 : bHigh(abHigh),
   bCN(abCN)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBSetBaudRateE::CmddBSetBaudRateE()
 : bHigh(false),
   wCN(0)
{
}

CmddBSetBaudRateE::CmddBSetBaudRateE(bool abHigh, TWord awCN)
 : bHigh(abHigh),
   wCN(awCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddFSetTimeB::CmddFSetTimeB()
{
}

CmddFSetTimeB::CmddFSetTimeB(const TDateTime &at)
 : t(at)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddFSetTimeE::CmddFSetTimeE()
{
}

CmddFSetTimeE::CmddFSetTimeE(const TDateTimeSS &at)
 : t(at)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddFGetSysValueE::CmddFGetSysValueE()
 : bAddr(0),
   bLen(0)
{
}

CmddFGetSysValueE::CmddFGetSysValueE(TByte abAddr, TByte abLen)
 : bAddr(abAddr),
   bLen(abLen)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBGetSysValueE::CmddBGetSysValueE()
 : bAddr(0),
   wCN(0)
{
}

CmddBGetSysValueE::CmddBGetSysValueE(TByte abAddr, TWord awCN)
 : bAddr(abAddr),
   wCN(awCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddFGetBckDataE::CmddFGetBckDataE()
 : dwAddr(0),
   bLen(0)
{
}

CmddFGetBckDataE::CmddFGetBckDataE(TDWord adwAddr, TByte abLen)
 : dwAddr(adwAddr),
   bLen(abLen)
{
}


CmddBGetBckDataE::CmddBGetBckDataE()
 : dwAddr(0),
   wCN(0)
{
}

CmddBGetBckDataE::CmddBGetBckDataE(TDWord adwAddr, TWord awCN)
 : dwAddr(adwAddr),
   wCN(awCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddFBeepE::CmddFBeepE()
 : bBeeps(1)
{
}

CmddFBeepE::CmddFBeepE(TByte abBeeps)
 : bBeeps(abBeeps)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBBeepE::CmddBBeepE()
 : bBeeps(1),
   wCN(0)
{
}

CmddBBeepE::CmddBBeepE(TByte abBeeps, TWord awCN)
 : bBeeps(abBeeps),
   wCN(awCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddFTurnOffB::CmddFTurnOffB()
 : bUnknown(60) //!!!!!!!
{
}

CmddFTurnOffB::CmddFTurnOffB(TByte abUnknown)
 : bUnknown(abUnknown)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBTurnOffB::CmddBTurnOffB()
 : bUnknown(60), //!!!!!!!
   bCN(0)
{
}

CmddBTurnOffB::CmddBTurnOffB(TByte abUnknown, TByte abCN)
 : bUnknown(abUnknown),
   bCN(abCN)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmddBCardIns5RemB::CmddBCardIns5RemB()
 : bInsert(false)
{
}

CmddBCardIns5RemB::CmddBCardIns5RemB(bool abInsert)
 : bInsert(abInsert)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBCardIns6B::CmddBCardIns6B()
 : bTI(0),
   bTP(0),
   dwCardN(0)
{
}

CmddBCardIns6B::CmddBCardIns6B(TByte abCN, TByte abTI, TByte abTP, TDWord adwCardN)
 : bCN(abCN),
   bTI(abTI),
   bTP(abTP),
   dwCardN(adwCardN)
{
}

////////////////////////////////////////////////////////////////////////////////
CmddBCardInsRemE::CmddBCardInsRemE()
 : wCN(0),
   bCardType(0),
   dwCardN(0)
{
}
   
CmddBCardInsRemE::CmddBCardInsRemE(TWord awCN, TByte abCardType, TDWord adwCardN)
 : wCN(awCN),
   bCardType(abCardType),
   dwCardN(adwCardN)
{
}

