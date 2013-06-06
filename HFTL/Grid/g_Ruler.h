#ifndef g_Ruler_h_already_included__15_10_2011__152F83F0
#define g_Ruler_h_already_included__15_10_2011__152F83F0
//
// SeVlaT, 15.10.2011
//

#include "../m_iplTypes.h"

namespace hftl {

template <typename RULER, typename DIST>
class TRuler_crtp {
 public:
  typedef DIST              TDist;
  typedef TFix<TInd, TDist> TdFix;
  typedef TSegmU<TdFix>     TdfSermU;

 public:
  TDist operator()(TInd iB, TInd iE) const
   { return SelfGet(iB, iE); }

  TDist operator()(TISegmU isu) const
   { return SelfGet(isu.B, isuE); }

  TDist operator()(TdFix idf0, TInd i1) const
   { return SelfGet(df0.i, i1)-df0.l; }

  TDist operator()(TInd i0, TdFix idf1) const
   { return SelfGet(i0, df1.i)+df1.l; }

  TDist operator()(TdFix idf0, TdFix idf1) const
   { return SelfGet(df0.i, df1.i)-df0.l+df1.l; }

  TDist operator()(TdfSermU idfsu) const
   { return SelfGet(dfsu.B.i, dfsu.E.i)-dfsu.B.l+dfsu.E.l; }


 private:
  const RULER& Self() const { return static_cast<const RULER&>(*this); }

  TDist SelfGet(TInd iB, TInd iE) const { return Self().Get(iB, iE); }
};

template <typename ARULER, typename DIST>
class TARuler_crtp {
 public:
  typedef DIST              TDist;
  typedef TSegmU<TDist>     TdSegmU;

  typedef TFix<TInd, TDist> TdFix;
  typedef TSegmU<TdFix>     TdfSegmU;

 public:
  TDist operator()(TInd i) const
   { return SelfGet(i); }

  TDist operator()(TdFix df) const
   { return SelfGet(df); }

 public:
  TdSegmU operator()(TInd iB, TInd iE) const
   { return TdSegmU(SelfGet(iB), SelfGet(iE)); }

  TdSegmU operator()(TISegmU isu) const
   { return TdSegmU(SelfGet(isu.B), SelfGet(isu.E)); }

 public:
  TdSegmU operator()(TdFix dfB, TInd iE) const
   { return TdSegmU(SelfGet(dfB), SelfGet(iE)); }
   
  TdSegmU operator()(TInd iB, TdFix dfE) const
   { return TdSegmU(SelfGet(iB), SelfGet(dfE)); }

  TdSegmU operator()(TdFix dfB, TdFix dfE) const
   { return TdSegmU(SelfGet(dfB), SelfGet(dfE)); }

  TdSegmU operator()(TdfSegmU dfsu) const
   { return TdSegmU(SelfGet(dfsu.B), SelfGet(dfsu.E)); }

 private:
  const ARULER& Self() const { return static_cast<const ARULER&>(*this); }

  TDist SelfGet(TInd i)   const { return Self().Get(i); }
  TDist SelfGet(TdFix df) const { return Self().Get(df); }
};

template <typename RULER>
class TRulerRef: public TRuler_crtp<TRulerRef, typename RULER::TDist> {
 public:
  typedef typename RULER::TDist TDist;

 public:
  TRulerRef(const RULER &r)
   : m_r(r) {}

 public:
  TDist operator()(TInd i0, TInd i1) const
   { return Get(i0, i1); }

  TDist Get(TInd i0, TInd i1) const
   { return m_r(i0, i1); }

 private:
  const RULER &m_r;
};

}

#endif
