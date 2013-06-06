// SeVlaT, 08.05.2013
#include "StdAfx.h"

#include "Utils.h"

#include <HFL/Win/w_Version.h>

std::wstring GetVersionString(const std::wstring &sPrefix, int nNumbers)
{
  WCHAR szBuffer[256];
  if (GetVersionString(4, szBuffer, 256)) return sPrefix+szBuffer;
  
  return L"";
}


