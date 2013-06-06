// SeVlaT, 18.05.2012
#include "StdAfx.h"

#include "../Utils.h"

const char* DecIntConstName(const char *szName, int n, char szBuffer[32])
{
  if (szName && *szName) return szName;
  
  sprintf(szBuffer, "%d", n);
  return szBuffer;
}

const char* HexConstName(const char *szName, TDWord dw, char szBuffer[32])
{
  if (szName && *szName) return szName;

       if (hftl::Is1Byte(dw)) sprintf(szBuffer, "%02Xh", dw);
  else if (hftl::Is2Byte(dw)) sprintf(szBuffer, "%04Xh", dw);
  else if (hftl::Is3Byte(dw)) sprintf(szBuffer, "%06Xh", dw);
  else                        sprintf(szBuffer, "%08Xh", dw);
  
  return szBuffer;
}

const char* HexBConstName(const char *szName, TByte b, char szBuffer[32])
{
  if (szName && *szName) return szName;
  
  sprintf(szBuffer, "%02Xh", b);
  return szBuffer;
}

const char* HexWConstName(const char *szName, TWord w, char szBuffer[32])
{
  if (szName && *szName) return szName;
  
  sprintf(szBuffer, "%04Xh", w);
  return szBuffer;
}

const char* HexDwConstName(const char *szName, TDWord dw, char szBuffer[32])
{
  if (szName && *szName) return szName;
  
  sprintf(szBuffer, "%08Xh", dw);
  return szBuffer;
}

////////////////////////////////////////////////////////////////////////////////
const wchar_t* DecIntConstName(const wchar_t *szName, int n, wchar_t szBuffer[32])
{
  if (szName && *szName) return szName;
  
  swprintf(szBuffer, L"%d", n);
  return szBuffer;
}

const wchar_t* HexConstName(const wchar_t *szName, TDWord dw, wchar_t szBuffer[32])
{
  if (szName && *szName) return szName;

       if (hftl::Is1Byte(dw)) swprintf(szBuffer, L"%02Xh", dw);
  else if (hftl::Is2Byte(dw)) swprintf(szBuffer, L"%04Xh", dw);
  else if (hftl::Is3Byte(dw)) swprintf(szBuffer, L"%06Xh", dw);
  else                        swprintf(szBuffer, L"%08Xh", dw);
  
  return szBuffer;
}

const wchar_t* HexBConstName(const wchar_t *szName, TByte b, wchar_t szBuffer[32])
{
  if (szName && *szName) return szName;
  
  swprintf(szBuffer, L"%02Xh", b);
  return szBuffer;
}

const wchar_t* HexWConstName(const wchar_t *szName, TWord w, wchar_t szBuffer[32])
{
  if (szName && *szName) return szName;
  
  swprintf(szBuffer, L"%04Xh", w);
  return szBuffer;
}

const wchar_t* HexDwConstName(const wchar_t *szName, TDWord dw, wchar_t szBuffer[32])
{
  if (szName && *szName) return szName;
  
  swprintf(szBuffer, L"%08Xh", dw);
  return szBuffer;
}

////////////////////////////////////////////////////////////////////////////////
template<>
string ToStr<char>::Dec(int n) const
{
  char szBuffer[32]={0};
  
  sprintf(szBuffer, "%d", n);
  return szBuffer;
}

template<>
string ToStr<char>::Hex(TDWord dw) const
{
  char szBuffer[32]={0};
  
       if (hftl::Is1Byte(dw)) sprintf(szBuffer, "%02Xh", dw);
  else if (hftl::Is2Byte(dw)) sprintf(szBuffer, "%04Xh", dw);
  else if (hftl::Is3Byte(dw)) sprintf(szBuffer, "%06Xh", dw);
  else                        sprintf(szBuffer, "%08Xh", dw);
  
  return szBuffer;
}

template<>
string ToStr<char>::Hex1(TByte b) const
{
  char szBuffer[32]={0};
  sprintf(szBuffer, "%02Xh", b);
  return szBuffer;
}

template<>
string ToStr<char>::Hex2(TWord w) const
{
  char szBuffer[32]={0};
  sprintf(szBuffer, "%04Xh", w);
  return szBuffer;
}

template<>
string ToStr<char>::Hex3(TDWord dw) const
{
  char szBuffer[32]={0};
  sprintf(szBuffer, "%06Xh", dw);
  return szBuffer;
}

template<>
string ToStr<char>::Hex4(TDWord dw) const
{
  char szBuffer[32]={0};
  sprintf(szBuffer, "%08Xh", dw);
  return szBuffer;
}

////////////////////////////////////////////////////////////////////////////////
template<>
wstring ToStr<wchar_t>::Dec(int n) const
{
  wchar_t szBuffer[32]={0};

  swprintf(szBuffer, L"%d", n);
  return szBuffer;
}

template<>
wstring ToStr<wchar_t>::Hex(TDWord dw) const
{
  wchar_t szBuffer[32]={0};
  
       if (hftl::Is1Byte(dw)) swprintf(szBuffer, L"%02Xh", dw);
  else if (hftl::Is2Byte(dw)) swprintf(szBuffer, L"%04Xh", dw);
  else if (hftl::Is3Byte(dw)) swprintf(szBuffer, L"%06Xh", dw);
  else                        swprintf(szBuffer, L"%08Xh", dw);
  
  return szBuffer;
}

template<>
wstring ToStr<wchar_t>::Hex1(TByte b) const
{
  wchar_t szBuffer[32]={0};
  swprintf(szBuffer, L"%02Xh", b);
  return szBuffer;
}

template<>
wstring ToStr<wchar_t>::Hex2(TWord w) const
{
  wchar_t szBuffer[32]={0};
  swprintf(szBuffer, L"%04Xh", w);
  return szBuffer;
}

template<>
wstring ToStr<wchar_t>::Hex3(TDWord dw) const
{
  wchar_t szBuffer[32]={0};
  swprintf(szBuffer, L"%06Xh", dw);
  return szBuffer;
}

template<>
wstring ToStr<wchar_t>::Hex4(TDWord dw) const
{
  wchar_t szBuffer[32]={0};
  swprintf(szBuffer, L"%08Xh", dw);
  return szBuffer;
}

template ToStr<char>;
template ToStr<wchar_t>;

///////////////////////
