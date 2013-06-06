// SeVlaT, 20.10.2012
#include "StdAfx.h"

#include "../DescribeUtils.h"

#include "../ByteBuffer.h"

void DescribeBool(      std::ostream &os,
                  const char         *szFalse,
                  const char         *szTrue,
                        bool          b)
{
  if (b) os << szTrue;
    else os << szFalse;
}

void DescribeBool(std::ostream &os, const char *szName, bool b)
{
  if (szName) os << szName << ":";
  os << " " << (b? "true": "false");
}

void DescribeInt(std::ostream &os, const char *szName, int n)
{
  if (szName) os << szName << ":";
  os << " " << n;
}

void DescribeHex(std::ostream &os, const char *szName, unsigned long dw)
{
  if (szName) os << szName << ":";
  os << " " << std::hex << dw << std::dec << 'h';
}

void DescribeNoonTime(std::ostream &os, const char *szName, const TNoonTime &t)
{
  const int nHour  =t.Hour();
  const int nMinute=t.Minute();
  const int nSecond=t.Second();

  if (szName) os << szName << " ";
  os << "(HMS): " << nHour << "." << nMinute << "." << nSecond;
}

void DescribeMoonTime(std::ostream &os, const char *szName, const TMoonTime &t)
{
  DescribeNoonTime(os, szName, t);
  
  const bool bMidday=t.Midday();
  const int  nWeekDay=t.WeekDay();
  const int  nWeek   =t.Week();
  
  DescribeBool(os, "am", "pm", bMidday);
  DescribeInt(os, " W",  nWeek);
  DescribeInt(os, " Wd", nWeekDay);
}

void DescribeMoonTimeSS(std::ostream &os, const char *szName, const TMoonTimeSS &t)
{
  DescribeMoonTime(os, szName, t);

  const int nSubSec  =t.bSubSec;
  os << ": " << nSubSec;
}

void DescribeDate(std::ostream &os, const char *szName, const TDate &d)
{
  const int nDay  =d.bDay;
  const int nMonth=d.bMonth;
  const int nYear =d.bYear;
  
  if (szName) os << szName << " ";
  os << "(DMY): " << nDay << "." << nMonth << "." << nYear;
}

void DescribeDateTime(std::ostream &os, const char *szName, const TDateTime &t)
{
  DescribeDate(os, szName, t);
  os << " ";
  DescribeMoonTime(os, 0, t);
}

void DescribeDateTimeSS(std::ostream &os, const char *szName, const TDateTimeSS &t)
{
  DescribeDate(os, szName, t);
  os << " ";
  DescribeMoonTimeSS(os, 0, t);
}

void DescribeBuf(std::ostream &os, const TByteBuffer &buf, int nMaxLength)
{
  os << ", {";
  
  if (nMaxLength<1) nMaxLength=1;
  const bool bAll=static_cast<int>(buf.size())<=nMaxLength;
  const TUInt nByteCount=bAll? buf.size(): (nMaxLength-1);
  
  for (TUInt i=0; i<nByteCount; ++i) {
    if (i!=0) os << ", ";
    os << std::hex << std::setw(2) << std::setfill('0') << TDWord(buf[i]);
  }    
  
  if (bAll) {
    os << "}";
  } else {
    os << "...}";
  }
}

void DescribeBufLen(std::ostream &os, const TByteBuffer &buf, int nMaxLength)
{
  os << "Len=" << buf.size();
  if (buf.empty()) return;
  
  DescribeBuf(os, buf, nMaxLength);
}

void DescribeCmdCode(std::ostream &os, TCmdCode cc, const TCommandInfo *pci)
{
  const int nCmdCode=cc;
  os << "<#" << std::hex << nCmdCode << std::dec;

  if (pci) {
    os << " " << pci->szName;
  } else {
    os << " ?cUnk";
  }
  os << ">";
}


