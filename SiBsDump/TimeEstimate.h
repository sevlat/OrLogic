#ifndef TimeEstimate_h_already_included__23_05_2013__4651510
#define TimeEstimate_h_already_included__23_05_2013__4651510
//
// SeVlaT, 23.05.2013
//

#include <SiLib/TimeTypes.h>

#include <HFL/Progress.h>

class TTimeEstimator {
 public:
  typedef long TValue;
  
 public:
  TTimeEstimator(TSysTime t0,
                 TSysSpan tMinSpan,
                 TSysSpan tMaxSpan,
                 TSysSpan tMinDelta,
                 TSysSpan tMaxEstimatedTime)
   : m_Impl(ToImplT(t0),
            ToImplS(tMinSpan),
            ToImplS(tMaxSpan),
            ToImplS(tMinDelta),
            ToImplS(tMaxEstimatedTime)) {}

 public:
  void Reset(TSysTime t0, TValue vInit)
   { m_Impl.Reset(ToImplT(t0), ToImplV(vInit)); }

 public:
  void Tick(TSysTime t, TValue v, TValue vFinal)
   { m_Impl.Tick(ToImplT(t), ToImplV(v), ToImplV(vFinal)); }
  void Tick(TSysTime t, TValue v)
   { m_Impl.Tick(ToImplT(t), ToImplV(v)); }
  void Tick(TSysTime t)
   { m_Impl.Tick(ToImplT(t)); }

 public:
  TSysSpan Spent() const  { return FromImplS(m_Impl.Spent()); }

  OSysSpan Total() const
   { if (!m_Impl.Trusty()) return None; return FromImplS(m_Impl.Total()); }
   
  OSysSpan Rest() const
   { if (!m_Impl.Trusty()) return None; return FromImplS(m_Impl.Rest()); }
  
 private:
  static TProgress::TTime  ToImplS(TSysSpan t) { return t.count(); }
  static TProgress::TTime  ToImplT(TSysTime t) { return t.time_since_epoch().count(); }
  static TProgress::TValue ToImplV(TValue v)   { return v; }

  static TSysSpan FromImplS(TProgress::TTime  t) { return TSysSpan(TSysSpan::rep(t)); }
  static TSysTime FromImplT(TProgress::TTime  t) { return TSysTime(TSysSpan(TSysSpan::rep(t))); }
  static TValue   FromImplV(TProgress::TValue v) { return (TValue)v; }

 private:
  TProgress m_Impl;
};



#endif
