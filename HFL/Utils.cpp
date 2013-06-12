// SeVlaT, 05.04.2012
#include "stdafx.h"

#include <HFTL/Main/m_stlUtils.h>

////////////////////////////////////////////////////////////////////////////////
std::string GenerateFileName(const std::string &sPrefix,
                             const std::string &sPostfix,
                             const std::string &sExtension,
                                   bool         bDate,
                                   bool         bTime)
{
  using std::string;
  
  time_t t;
  time(&t );

  tm *pT=localtime(&t);
  
  const int nYear=1900+pT->tm_year;

  char szDateTime[256]="";
  if (bDate && bTime) {
    sprintf(szDateTime, "%02d_%02d_%02d__%02d_%02d_%02d",
            nYear, pT->tm_mon+1,  pT->tm_mday,
            pT->tm_hour, pT->tm_min, pT->tm_sec);
  } else if (bDate && !bTime) {
    sprintf(szDateTime, "%02d_%02d_%02d",
            nYear, pT->tm_mon+1,  pT->tm_mday);
  } else if (!bDate && bTime) {
    sprintf(szDateTime, "%02d_%02d_%02d",
            pT->tm_hour, pT->tm_min, pT->tm_sec);
  }
  
  string sFileName=sPrefix;
  if (szDateTime[0]) sFileName+=string("_")+szDateTime;
  if (!sPostfix.empty()) sFileName+=string("_")+sPostfix;  
  if (!sExtension.empty()) sFileName+=string(".")+sExtension;  
  
  return sFileName;
}

////////////////////////////////////////////////////////////////////////////////
std::string W2A(const std::wstring &ws)
{
  return "";
}

std::wstring A2W(const std::string  &as)
{
  std::vector<wchar_t> ws(as.size());
  MultiByteToWideChar(CP_ACP, 0, as.c_str(), as.size(), hftl::begin_ptr(ws), as.size());
  return std::wstring(ws.begin(), ws.end());
}

