#include "StdAfx.h"

#include "../Errors.h"
// SeVlaT, 21.05.2012
//

TError::TError(TGlobalErrorCode nCode)
 : m_nCode(nCode),
   m_dwSysError(PlatformSpecific::GetCurrentSystemError())
{
}

////////////////////////////////////////////////////////////////////////////////
typedef std::vector<TError> TErrorVec;

TErrorVec& ErrorVec()
{
  static TErrorVec ErrorVec;
  return ErrorVec;
}


void TErrList::Push(TGlobalErrorCode nCode)
{
  m_vec.push_back(TError(nCode));
}

void TErrList::Reset()
{
  m_vec.clear();
}


bool TErrList::Pop()
{
  if (m_vec.empty()) return false;
  m_vec.pop_back();
  return true;  
}
  
const TError* TErrList::Top() const
{
  if (m_vec.empty()) return 0;
  return &m_vec.back();
}

const TError* TErrList::Get(int n) const
{
  const int nSize=m_vec.size();
  if (n>=nSize) return 0;
  return &m_vec[nSize-n-1];
}

