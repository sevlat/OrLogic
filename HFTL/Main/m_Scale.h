#ifndef m_Scale_h_already_included__22_04_2011__295F377D
#define m_Scale_h_already_included__22_04_2011__295F377D
//
// SeVT, 22.04.2011
//

#include "m_Trans.h"

namespace hftl { // Helpful template library

////////////////////////////////////////////////////////////////////////////////
template <typename LEN, typename FACTOR=double>
class TScaleU_base {
 protected:
  TScaleU_base(): m_fFactor(1.0) {}
  explicit TScaleU_base(FACTOR fFactorB2F): m_fFactor(fFactorB2F) {}

  ~TScaleU_base() {}

 public:
  LEN f2b(LEN l) const { return l/m_fFactor; }
  LEN b2f(LEN l) const { return l*m_fFactor; }

 public:
  FACTOR f2b() const { return 1.0/m_fFactor; }
  FACTOR b2f() const { return m_fFactor; }

 public:
  void SetB2F(FACTOR f) { m_fFactor=f; }

 public:
  TScaleU_base& operator *= (const TScaleU_base &s)
   { m_fFactor*=s.m_fFactor; return *this; }

  TScaleU_base& operator *= (const ITransBwU<LEN, LEN, FACTOR> &s)
   { m_fFactor*=s.B2F()(); return *this; }

 private:
  FACTOR m_fFactor;
};

template <typename LEN, typename FACTOR=double>
class TScaleU_nv: public TScaleU_base<LEN, FACTOR> {
 public:
  TScaleU_nv() {}
  explicit TScaleU_nv(FACTOR fFactorB2F): TScaleU_base(fFactorB2F) {}
};

template <typename LEN, typename FACTOR=double>
class TScaleU: public ITransBwU<LEN, LEN, FACTOR>,
               public TScaleU_base<LEN, FACTOR> {
 public:
  typedef ITransOwU<LEN, LEN, FACTOR> IB2FOwU;

 public:
  TScaleU() {}
  explicit TScaleU(FACTOR fFactorB2F)
   : TScaleU_base<LEN, FACTOR>(fFactorB2F) {}

  void SetB2FMin(const IB2FOwU &t0, const IB2FOwU &t1)
    { SetB2F(Min(t0(), t1())); }
  void SetB2FMax(const IB2FOwU &t0, const IB2FOwU &t1)
    { SetB2F(Max(t0(), t1())); }
  void SetB2FAve(const IB2FOwU &t0, const IB2FOwU &t1)
   { SetB2F(sqrt(t0()*t1())); }

 public:
  virtual LEN    f(LEN b) const { return b2f(b); }
  virtual double f()      const { return b2f(); }

  virtual LEN    b(LEN f) const { return f2b(f); }
  virtual double b()      const { return f2b(); }

 public:
  TScaleU& operator *= (const TScaleU_base &s)
   { TScaleU_base<LEN, FACTOR>::operator *=(s); return *this; }

  TScaleU& operator *= (const ITransBwU<LEN, LEN, FACTOR> &s)
   { TScaleU_base<LEN, FACTOR>::operator *=(s); return *this; }
};

////////////////////////////////////////////////////////////////////////////////
template <typename LEN, typename FACTOR=double>
class TScaleB: public ITransBwB<LEN, LEN, FACTOR> {
 public:
  TScaleB() {}
  explicit TScaleB(FACTOR fFactorB2F): m_X(fFactorB2F),
                                       m_Y(fFactorB2F)  {}

 public:
  const TScaleU_nv<LEN, FACTOR>& x() const { return m_X; }
  const TScaleU_nv<LEN, FACTOR>& y() const { return m_Y; }

 public:
  virtual LEN    xf(LEN b) const { return m_X.b2f(b); }
  virtual double xf()      const { return m_X.b2f();  }

  virtual LEN    xb(LEN f) const { return m_X.f2b(f); }
  virtual double xb()      const { return m_X.f2b();  }

  virtual LEN    yf(LEN b) const { return m_Y.b2f(b); }
  virtual double yf()      const { return m_Y.b2f();  }

  virtual LEN    yb(LEN f) const { return m_Y.f2b(f); }
  virtual double yb()      const { return m_Y.f2b();  }

 public:
  TScaleB& operator *= (const TScaleB &s)
   { m_X*=s.m_X; m_Y*=s.m_Y; return *this; }

 private:
  TScaleU_nv<LEN, FACTOR> m_X;
  TScaleU_nv<LEN, FACTOR> m_Y;
};


}

#endif
