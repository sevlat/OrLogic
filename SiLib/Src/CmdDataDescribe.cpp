// SeVlaT, 20.10.2012
#include "StdAfx.h"

#include "../CmdDataDescribe.h"
#include "../DescribeUtils.h"

namespace {

void Separate(std::ostream &os)
{
  os << ", ";
}

void DescribeMaSlave(std::ostream &os, bool bMaster)
{
  DescribeBool(os, "Slave", "Master", bMaster);
}

void DescribeSpeed(std::ostream &os, bool bHigh)
{
  DescribeBool(os, "Low speed", "High speed", bHigh);
}

}
////////////////////////////////////////////////////////////////////////////////

void DescribeCmdd(std::ostream &os, const CmddVoid &cmdd)
{
}

void DescribeCmdd(std::ostream &os, const CmddRaw &cmdd)
{
  DescribeBufLen(os, cmdd.data, 12);
}

void DescribeCmdd(std::ostream &os, const CmddFSetMaSlave &cmdd)
{
  DescribeMaSlave(os, cmdd.bMaster);
}

void DescribeCmdd(std::ostream &os, const CmddBMaSlaveB &cmdd)
{
  DescribeMaSlave(os, cmdd.bMaster);
  Separate(os);
  DescribeInt (os, "CN", cmdd.bCN);
}

void DescribeCmdd(std::ostream &os, const CmddBMaSlaveE &cmdd)
{
  DescribeMaSlave(os, cmdd.bMaster);
  Separate(os);
  DescribeInt (os, "CN", cmdd.wCN);
}

void DescribeCmdd(std::ostream &os, const CmddFSetBaudRate &cmdd)
{
  DescribeSpeed(os, cmdd.bHigh);
}

void DescribeCmdd(std::ostream &os, const CmddBSetBaudRateB &cmdd)
{
  DescribeSpeed(os, cmdd.bHigh);
  Separate(os);
  DescribeInt (os, "CN", cmdd.bCN);
}

void DescribeCmdd(std::ostream &os, const CmddBSetBaudRateE &cmdd)
{
  DescribeSpeed(os, cmdd.bHigh);
  Separate(os);
  DescribeInt (os, "CN", cmdd.wCN);
}

////////////////////////////////////////////////////////////////////////////////
void DescribeCmdd(std::ostream &os, const CmddBGetTimeB &cmdd)
{
  DescribeDateTime(os, "Time", cmdd.t);
  Separate(os);
  DescribeInt (os, "CN",   cmdd.bCN);
}

void DescribeCmdd(std::ostream &os, const CmddBGetTimeE &cmdd)
{
  DescribeDateTimeSS(os, "Time", cmdd.t);
  Separate(os);
  DescribeInt   (os, "CN",   cmdd.wCN);
}

void DescribeCmdd(std::ostream &os, const CmddFSetTimeB &cmdd)
{
  DescribeDateTime(os, "Time", cmdd.t);
}

void DescribeCmdd(std::ostream &os, const CmddBSetTimeB &cmdd)
{
  DescribeDateTime(os, "Time", cmdd.t);
  Separate(os);
  DescribeInt (os, "CN",   cmdd.bCN);
}

void DescribeCmdd(std::ostream &os, const CmddBSetTimeE &cmdd)
{
  DescribeDateTimeSS(os, "Time", cmdd.t);
  Separate(os);
  DescribeInt   (os, "CN",   cmdd.wCN);
}

void DescribeCmdd(std::ostream &os, const CmddFSetTimeE &cmdd)
{
  DescribeDateTimeSS(os, "Time", cmdd.t);
}

void DescribeCmdd(std::ostream &os, const CmddFGetSysValueE &cmdd)
{
  DescribeInt(os, "Addr", cmdd.bAddr);
  Separate(os);
  DescribeInt(os, "Len",  cmdd.bLen);
}

void DescribeCmdd(std::ostream &os, const CmddBGetSysValueE &cmdd)
{
  DescribeInt   (os, "CN",   cmdd.wCN);
  Separate(os);
  DescribeInt   (os, "Addr", cmdd.bAddr);
  Separate(os);
  DescribeBufLen(os, cmdd.data, 8);
}

void DescribeCmdd(std::ostream &os, const CmddFGetBckDataE  &cmdd)
{
  DescribeInt(os, "Addr", cmdd.dwAddr);
  Separate(os);
  DescribeInt(os, "Len",  cmdd.bLen);
}

void DescribeCmdd(std::ostream &os, const CmddBGetBckDataE  &cmdd)
{
  DescribeInt   (os, "CN",   cmdd.wCN);
  Separate(os);
  DescribeInt   (os, "Addr", cmdd.dwAddr);
  Separate(os);
  DescribeBufLen(os, cmdd.data, 8);
}

void DescribeCmdd(std::ostream &os, const CmddFBeepE &cmdd)
{
  DescribeInt(os, "Beeps", cmdd.bBeeps);
}

void DescribeCmdd(std::ostream &os, const CmddBBeepE &cmdd)
{
  DescribeInt   (os, "CN",   cmdd.wCN);
  Separate(os);
  DescribeInt   (os, "Beeps", cmdd.bBeeps);
}

void DescribeCmdd(std::ostream &os, const CmddFTurnOffB &cmdd)
{
  DescribeInt   (os, "Unknown", cmdd.bUnknown);
}

void DescribeCmdd(std::ostream &os, const CmddBTurnOffB &cmdd)
{
  DescribeInt   (os, "CN",      cmdd.bCN);
  Separate(os);
  DescribeInt   (os, "Unknown", cmdd.bUnknown);
}

void DescribeCmdd(std::ostream &os, const CmddBCardIns5RemB &cmdd)
{
  DescribeBool(os, "Removed", "Inserted", cmdd.bInsert);
}

void DescribeCmdd(std::ostream &os, const CmddBCardIns6B &cmdd)
{
  DescribeInt   (os, "CN",    cmdd.bCN);
  Separate(os);
  DescribeHex   (os, "bTI",   cmdd.bTI);
  Separate(os);
  DescribeHex   (os, "bTP",   cmdd.bTP);
  Separate(os);
  DescribeInt   (os, "CardN", cmdd.dwCardN);
}

void DescribeCmdd(std::ostream &os, const CmddBCardInsRemE &cmdd)
{
  DescribeInt   (os, "CN",    cmdd.wCN);
  Separate(os);
  DescribeHex   (os, "CardType", cmdd.bCardType);
  Separate(os);
  DescribeInt   (os, "CardN", cmdd.dwCardN);
}




