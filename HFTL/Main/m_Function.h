#ifndef m_Function_h_already_included__26_09_2011__3A618D6F
#define m_Function_h_already_included__26_09_2011__3A618D6F
//
// SeVlaT, 26.09.2011
//

#include "m_Consts.h"
#include "m_MinMax.h"
#include "m_Optional.h"

namespace hftl {

template <typename ARG, typename RES>
struct TArgRes {
  ARG a;
  RES r;

  TArgRes() {}

  TArgRes(ARG aa, RES ar)
   : a(aa), r(ar) {}

//   template <typename FUNC> !!! Restore and use this constructor
//   TArgRes(ARG aa, FUNC f)
//    : a(aa), r(f(aa)) {}
};

////////////////////////////////////////////////////////////////////////////////

template <typename ARG, typename RES, typename FUNC>
class TMinimum {
 public:
  typedef ARG TArg;
  typedef RES TRes;

  typedef TArgRes<ARG, RES> TAR;
  typedef TOptional<TAR>    OAR;

 public:
  explicit TMinimum(FUNC f, TArg aL, TArg aR)
   : m_f(f),
     m_arL(aL, f(aL)),
     m_arR(aR, f(aR)) {}

 public:
  const TAR& GetL() const { return m_arL; }
  const TAR& GetR() const { return m_arR; }

 public:
  FUNC Func() const { return m_f; }

 public:
  void Narrow()
  {
    if (!m_oarLc || !m_oarRc) UpdateC();

    if (m_oarLc->r<m_oarRc->r) {
      m_arR=*m_oarRc;
      m_oarRc=m_oarLc;
      m_oarLc=None;
    } else {
      m_arL=*m_oarLc;
      m_oarLc=m_oarRc;
      m_oarRc=None;
    }
  }

 public:
  void Expand(TArg aL, TArg aR)
  {
    const TArg aM=m_arL.a+(m_arR.a-m_arL.a)/2;
    TAR arC(aM, m_f(aM));
    while (Expand(arC, aL, aR));
  }

 private:
  bool Expand(TAR &arC, TArg aL, TArg aR)
  {
    switch (hftl::MinIndex(m_arL.r, arC.r, m_arR.r)) {
      case 0:
        {
          if (m_arL.a<=aL) return false;
          arC=m_arL;
          const TArg aE=m_arL.a-(m_arR.a-m_arL.a);
          m_arL=TAR(aE, m_f(aE));
        }
        return true;

      case 2:
        {
          if (m_arR.a>=aR) return false;
          arC=m_arR;
          const TArg aE=m_arR.a+(m_arR.a-m_arL.a);
          m_arR=TAR(aE, m_f(aE));
        }
        return true;
    }

    return false;
  }

  void UpdateC()
  {
    const TArg aD=(m_arR.a-m_arL.a)/c_GoldenRatio;
    if (!m_oarLc) m_oarLc=TAR(m_arR.a-aD, m_f(m_arR.a-aD));
    if (!m_oarRc) m_oarRc=TAR(m_arL.a+aD, m_f(m_arL.a+aD));
  }

 private:
  FUNC m_f;

 private:
  TAR m_arL;
  TAR m_arR;

  OAR m_oarLc;
  OAR m_oarRc;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DERIVED, typename FUNC, typename ARG, typename RES>
class TInverse_crtp {
 public:
  typedef ARG TArg;
  typedef RES TRes;

  typedef TArgRes<ARG, RES> TAR;
  typedef TOptional<TAR>    OAR;

 protected:
  TInverse_crtp(const FUNC &f, RES r)
   : m_f(f),
     m_r(r)   {}

  void SetInc(ARG a, RES r)
  {
    if ((r<=m_r) && (!m_oar0 || (m_oar0->a<a))) m_oar0=TAR(a, r);
    if ((r>=m_r) && (!m_oar1 || (m_oar1->a>a))) m_oar1=TAR(a, r);
  }

  void SetDec(ARG a, RES r)
  {
    if ((r>=m_r) && (!m_oar0 || (m_oar0->a<a))) m_oar0=TAR(a, r);
    if ((r<=m_r) && (!m_oar1 || (m_oar1->a>a))) m_oar1=TAR(a, r);
  }

 public:
  void Set(ARG a) { Self().Set(a, m_f(a)); }

  bool Calc(ARG aPrec)
  {
    if (!m_oar0) return false;
    if (!m_oar1) return false;

    while (true) {
      const ARG aD=(m_oar1->a - m_oar0->a);
      if (aD<=aPrec) break;
      const ARG aM=m_oar0->a + aD/2;
      if (aM == m_oar0->a) break;
      if (aM == m_oar1->a) break;
      Self().Set(aM);
    }

    return true;
  }

  const OAR& B() const { return m_oar0; } 
  const OAR& E() const { return m_oar1; }

 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
  
 protected:
  const FUNC &m_f;
  RES m_r;

 protected:
  OAR m_oar0; 
  OAR m_oar1; 
};

////////////////////////////////////////////////////////////////////////////////
template <typename FUNC, typename ARG, typename RES>
class TInverseInc: public TInverse_crtp<TInverseInc<FUNC, ARG, RES>, FUNC, ARG, RES> {
  typedef TInverse_crtp<TInverseInc<FUNC, ARG, RES>, FUNC, ARG, RES> TBase;
  typedef typename TBase::TAR TAR;
    
 public:
  TInverseInc(const FUNC &f, RES r): TBase(f, r) {}

 public:
  using TBase::Set;
  void Set(ARG a, RES r) { SetInc(a, r); }
};

////////////////////////////////////////////////////////////////////////////////
template <typename FUNC, typename ARG, typename RES>
class TInverseDec: public TInverse_crtp<TInverseDec<FUNC, ARG, RES>, FUNC, ARG, RES> {
  typedef TInverse_crtp<TInverseDec<FUNC, ARG, RES>, FUNC, ARG, RES> TBase;
  typedef typename TBase::TAR TAR;
    
 public:
  TInverseDec(const FUNC &f, RES r): TBase(f, r) {}

 public:
  using TBase::Set;
  void Set(ARG a, RES r) { SetDec(a, r); }
};

////////////////////////////////////////////////////////////////////////////////
template <typename FUNC, typename ARG, typename RES>
class TInverse: public TInverse_crtp<TInverse<FUNC, ARG, RES>, FUNC, ARG, RES> {
  typedef TInverse_crtp<TInverse<FUNC, ARG, RES>, FUNC, ARG, RES> TBase;
  typedef typename TBase::TAR TAR;
    
 public:
  TInverse(const FUNC &f, RES r, ARG aHint0, ARG aHint1)
   : TBase(f, r) 
  {
    const RES r0=f(aHint0);
    const RES r1=f(aHint1);

    m_bInc=(aHint0<aHint1 && r0<r1);

    Set(aHint0, r0);
    Set(aHint1, r1);
  }

 public:
  using TBase::Set;
  void Set(ARG a, RES r) { m_bInc? SetInc(a, r): SetDec(a, r); }

 private:
  bool m_bInc;
};

};

#endif
