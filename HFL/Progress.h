#ifndef Progress_h_already_included__29_05_2013__2B7C5100
#define Progress_h_already_included__29_05_2013__2B7C5100
//
// SeVlaT, 29.05.2013
//

#include "Ring.h"

class TProgress {
 public:
  typedef double TTime;
  typedef double TValue;

 public:
  TProgress(TTime tInit,
            TTime tMinSpan,
            TTime tMaxSpan,
            TTime tMinDelta,
            TTime tMaxEstimatedTime);

  void Reset(TTime tInit, TValue vInit);

  void Tick(TTime t, TValue v, TValue vFinal);
  void Tick(TTime t, TValue v);
  void Tick(TTime t);

 public:
  TTime Spent()  const { return m_tSpent; }

  bool Trusty() const { return m_bTrusty; }
  TTime Total()  const { return m_tTotal; }
  TTime Rest()   const { return m_tTotal-m_tSpent; }

 private:
  std::deque<std::pair<TTime, TValue> > m_Deque;

 private:
  TTime  m_tInit;
  TValue m_vInit;

  TValue m_vFinal;

 private:
  TTime  m_tSpent;

  TTime  m_tTotal;

  typedef TRingArray<TTime, 20> TTimeRing;

  TTimeRing m_TotalRing;
  bool  m_bTrusty;

 private:
  const TTime   m_tMinSpan;
  const TTime   m_tMaxSpan;
  const TTime   m_tMinDelta;
  const TTime   m_tMaxEstimatedTime;
  const size_t m_nMinValCount;
  const size_t m_nMaxValCount;
};

#endif
