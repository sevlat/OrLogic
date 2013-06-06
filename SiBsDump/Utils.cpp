// SeVlaT, 13.05.2013
#include "StdAfx.h"

#include "Utils.h"

#include <HFL/Utils.h>

std::string GetLogFileName()
{
  return GenerateFileName("Sbd_Log", "", "txt", true, true);
}

std::string GetDumpFileName(int nSerNum)
{
  char szPrefix[256];
  sprintf(szPrefix, "Sbd_Dump_%d", nSerNum);
  return GenerateFileName(szPrefix, "", "bin", true, true);
}

using boost::chrono::duration_fmt;
using boost::chrono::duration_style;

const char* GetHMSTimeString_hMS(int   nHour,
                                 int   nMin,
                                 int   nSec,
                                 char *szBuffer)
{
  assert(szBuffer);
  
  if (nHour>0) sprintf(szBuffer, "%02d.%02d.%02d", nHour, nMin, nSec);
          else sprintf(szBuffer, "%02d.%02d", nMin, nSec);
          
  return szBuffer;
}

const wchar_t* GetHMSTimeString_hMS(int      nHour,
                                    int      nMin,
                                    int      nSec,
                                    wchar_t *szBuffer)
{
  assert(szBuffer);
  
  if (nHour>0) swprintf(szBuffer, L"%02d.%02d.%02d", nHour, nMin, nSec);
          else swprintf(szBuffer, L"%02d.%02d", nMin, nSec);
          
  return szBuffer;
}

void SplitMsToHMS(int  nMilliSec,
                  int &nHour,
                  int &nMin,
                  int &nSec)
{
  nMilliSec/=1000;

  nHour=nMilliSec/3600;
  nMin =(nMilliSec%3600)/60;
  nSec =nMilliSec%60;
}                  

const char* GetTimeString_hMS(int nMilliSec, char *szBuffer)
{
  int nHour=0, nMin=0, nSec=0;
  SplitMsToHMS(nMilliSec, nHour, nMin, nSec);
  return GetHMSTimeString_hMS(nHour, nMin, nSec, szBuffer);
}

const wchar_t* GetTimeString_hMS(int nMilliSec, wchar_t *szBuffer)
{
  int nHour=0, nMin=0, nSec=0;
  SplitMsToHMS(nMilliSec, nHour, nMin, nSec);
  return GetHMSTimeString_hMS(nHour, nMin, nSec, szBuffer);
}

std::string SysSpanToStr(TSysSpan s)
{
  char szBuffer[256];
  return GetTimeString_hMS(duration_cast<milliseconds>(s).count(), szBuffer);

/*  
  std::stringstream ss;
  ss << duration_fmt(duration_style::symbol);
  ss << duration_cast<seconds>(s);
  return ss.str();
*/
}

