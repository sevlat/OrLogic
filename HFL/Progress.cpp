// SeVlaT, 29.05.2013
#include "stdafx.h"

#include "Progress.h"

template <typename TTime>
inline void WriteTime(TTime t, int v)
{
#ifdef _DEBUG
  std::ofstream file("f:\\timing.txt", std::ios::out | std::ios::app);
  file << t;
  file << '\t';
  file << v;
  file << std::endl;
#endif//_DEBUG
}

inline void InitWriteTime()
{
#ifdef _DEBUG
  std::ofstream file("f:\\timing.txt", std::ios::out);
#endif//_DEBUG
}


TProgress::TProgress(TTime tInit,
                     TTime tMinSpan,
                     TTime tMaxSpan,
                     TTime tMinDelta,
                     TTime tMaxEstimatedTime)
 : m_tMinSpan(tMinSpan),
   m_tMaxSpan(tMaxSpan),
   m_tMinDelta(tMinDelta),
   m_tMaxEstimatedTime(tMaxEstimatedTime),
   m_nMinValCount(3),
   m_nMaxValCount(1000),

   m_tInit(tInit),
   m_vInit(0),
   m_vFinal(0),
   m_tSpent(0),
   m_tTotal(0),
   m_bTrusty(false)
{
  InitWriteTime();
}


void TProgress::Reset(TTime tInit, TValue vInit)
{
  m_Deque.clear();
  m_tInit  = tInit;
  m_vInit  = vInit;
  m_vFinal = vInit;
  m_tSpent = 0;
  m_tTotal = 0;
  m_TotalRing.clear();
  m_bTrusty = false;
}


void TProgress::Tick(TTime t, TValue v, TValue vFinal)
{
  m_vFinal=vFinal;
  Tick(t, v);
}


void TProgress::Tick(TTime t)
{
  if (m_Deque.empty()) return;
  Tick(t, m_Deque.back().second);
}

template<typename IT, typename VAL>
bool Average(IT iFirst, IT iLast, VAL &vAve)
{
  vAve=0;
  int n=0;
  for ( ; iFirst!=iLast; ++iFirst, ++n)  vAve+=*iFirst;
  if (n==0) return false;
  vAve=vAve/double(n);
  return true;
}

template<typename IT, typename VAL>
bool RMSD(IT iFirst, IT iLast, VAL vAve, VAL &vRMSD)
{
  vRMSD=0;
  int n=0;
  for ( ; iFirst!=iLast; ++iFirst, ++n) {
    VAL vD=(*iFirst-vAve);
    vRMSD+=vD*vD;
  }
  
  if (n==0 || vRMSD<0) return false;
  vRMSD=sqrt(vRMSD/double(n));
  return true;
}

template<typename IT, typename VAL>
bool AverageRMSD(IT iFirst, IT iLast, VAL &vAve, VAL &vRMSD)
{
  return Average(iFirst, iLast, vAve) &&
         RMSD(iFirst, iLast, vAve, vRMSD);
}


void TProgress::Tick(TTime t, TValue v)
{
  if (t<m_tInit || v<m_vInit) {
    m_TotalRing.clear();
    m_bTrusty=false;
    return;
  }

  if (!m_Deque.empty()) {
    std::pair<TTime, TValue> tv=m_Deque.back();
    if (t<tv.first || v<tv.second) {
      m_TotalRing.clear();
      m_bTrusty=false;
      return;
    }
    if (t==tv.first && v==tv.second) return;
  }

  m_tSpent=t-m_tInit;

  if (m_Deque.size()>2) {
    if ((t-m_Deque[m_Deque.size()-1].first==0) ||
        (t-m_Deque[m_Deque.size()-2].first<m_tMinDelta)) m_Deque.pop_back();
  }

  m_Deque.push_back(std::make_pair(t, v));
//  WriteTime(t, v);

  while ((m_Deque.size()>0) &&
         (m_Deque.size()>m_nMinValCount) &&
         (m_Deque.size()>m_nMaxValCount))
    m_Deque.pop_front();

  while ((m_Deque.size()>1) &&
         (m_Deque.size()>m_nMinValCount) &&
         (m_Deque.back().first-m_Deque.front().first>=m_tMaxSpan))
    m_Deque.pop_front();

  m_bTrusty=false;

  TTime  tSpan=m_Deque.back().first -m_Deque.front().first;
  TValue vSpan=m_Deque.back().second-m_Deque.front().second;

  if (m_Deque.size()>=m_nMinValCount && vSpan>0 && tSpan>=m_tMinSpan) {
    double fSpeed=(double)vSpan/tSpan;

    TTime tTotal=m_tSpent+(m_vFinal-m_Deque.back().second)/fSpeed;

    if (tTotal>0) {
      m_TotalRing.push(tTotal);

      TTime tAverage=0, tRMSD=0;
      
      if (AverageRMSD(m_TotalRing.begin(), m_TotalRing.end(),
                                               tAverage, tRMSD)) {
        m_tTotal=tAverage;
        if (m_tTotal<m_tSpent) m_tTotal=m_tSpent;
        m_bTrusty=(m_tTotal<m_tMaxEstimatedTime) &&
                  (double(tRMSD)/tAverage)<0.1;
      }
    }
  }
}
