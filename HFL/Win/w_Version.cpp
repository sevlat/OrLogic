#include "stdafx.h"

#include "w_Version.h"

#include <HFTL/Main/m_Memory.h>

#pragma comment(lib, "version")

using hftl::TOptional;
using hftl::None;

TOptional<VS_FIXEDFILEINFO> GetProgramFixedFileInfo()
{
  WCHAR szExeName[MAX_PATH]={0};
  if (!GetModuleFileNameW(NULL, szExeName, MAX_PATH)) return None;

  DWORD dwDummy=0;
  const DWORD dwSize = GetFileVersionInfoSizeW(szExeName, &dwDummy);
  if (dwSize==0) return None;

  hftl::TScopedArray<BYTE> bBuffer(new BYTE[dwSize]);
  if (!GetFileVersionInfoW(szExeName, 0, dwSize, bBuffer.Get())) return None;

  LPVOID pValue=NULL;
  UINT dwValueSize=0;
  if (!VerQueryValueW(bBuffer.Get(), L"\\", &pValue, &dwValueSize)) return None;
  if (!pValue) return None;

  if (dwValueSize!=sizeof(VS_FIXEDFILEINFO)) return None;

  const VS_FIXEDFILEINFO *pFFI=static_cast<VS_FIXEDFILEINFO *>(pValue);
  return hftl::OptFromPtr(pFFI);
}

bool GetVersionString(int nNumbers, WCHAR szBuffer[], int nBufSize)
{
  if (!szBuffer) return false;
  if (nBufSize<=0) return false;
  
  szBuffer[0]=L'\0';
  
  const TOptional<VS_FIXEDFILEINFO> oFFI=GetProgramFixedFileInfo();
  if (!oFFI) return false;

  const hftl::msw::TVersion ver(oFFI->dwFileVersionMS, oFFI->dwFileVersionLS);
  
         if (nNumbers==1) {
    _snwprintf(szBuffer, nBufSize, L"%d", ver.w0);
  } else if (nNumbers==2) {
    _snwprintf(szBuffer, nBufSize, L"%d.%d", ver.w0, ver.w1);
  } else if (nNumbers==3) {
    _snwprintf(szBuffer, nBufSize, L"%d.%d.%d", ver.w0, ver.w1, ver.w2);
  } else {
    _snwprintf(szBuffer, nBufSize, L"%d.%d.%d.%d", ver.w0, ver.w1, ver.w2, ver.w3);
  }

  if (oFFI->dwFileFlagsMask & VS_FF_PRERELEASE &&
      oFFI->dwFileFlags & VS_FF_PRERELEASE) wcscat(szBuffer, L" beta"); //!!!!!! Check buf size!!!

  szBuffer[nBufSize-1]=L'\0';

  return true;
}
