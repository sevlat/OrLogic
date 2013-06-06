// SeVT, 27.03.2011
#include "stdafx.h"

#include "Id.h"

TIdData::TIdData()
 : m_t(0),
   m_n(0)
{
}

void TIdData::Generate()
{
  static int s_nCount=0;

  m_t=time(0);
  m_n=++s_nCount;
}

////////////////////////////////////////////////////////////////////////////////
template<typename CH>
CH* StrCopy(CH *pchBegin, const CH *pchEnd, const CH *pchSrc)
{
  if (pchSrc)
    while ((pchBegin!=pchEnd) && (*pchBegin++=*pchSrc++));
/*
  if (pchSrc) {
    for (; *pchSrc && pchBegin!=pchEnd; ++pchBegin, ++pchSrc)
      *pchBegin=*pchSrc;
  }
*/

  return pchBegin;
}

////////////////////////////////////////////////////////////////////////////////
TIdLabel::TIdLabel()
{
  m_sz[0]=0;
}

void TIdLabel::Set(const char *sz)
{
  char *szE=StrCopy(m_sz, m_sz+c_nBufSize-1, sz);
  *szE=0;
}
