#ifndef m_iplTrans_h_already_included__17_03_2011__33C9EE2D
#define m_iplTrans_h_already_included__17_03_2011__33C9EE2D
//

#include "m_iplSegPoint.h"
#include "m_Trans.h"

namespace hftl { // HelpFul Template Library

////////////////////////////////////////////////////////////////////////////////
typedef ITransOwU<TPel, TLen, double> IplTransOwU;
typedef ITransBwU<TPel, TLen, double> IplTransBwU;

typedef ITransOwB<TPel, TLen, double> IplTransOwB;
typedef ITransBwB<TPel, TLen, double> IplTransBwB;

////////////////////////////////////////////////////////////////////////////////
typedef ITransOwU<TLen, TPel, double> IlpTransOwU;
typedef ITransBwU<TLen, TPel, double> IlpTransBwU;

typedef ITransOwB<TLen, TPel, double> IlpTransOwB;
typedef ITransBwB<TLen, TPel, double> IlpTransBwB;

////////////////////////////////////////////////////////////////////////////////
typedef ITransOwU<TLen, TLen, double> IllTransOwU;
typedef ITransBwU<TLen, TLen, double> IllTransBwU;

typedef ITransOwB<TLen, TLen, double> IllTransOwB;
typedef ITransBwB<TLen, TLen, double> IllTransBwB;

////////////////////////////////////////////////////////////////////////////////
struct TTransU_DPI: public ITransBwU<TLen, TPel, double>
{
 public:
  TTransU_DPI(): m_pDPI(1) {}
  explicit TTransU_DPI(TPel pDPI): m_pDPI(pDPI) {}

 public:
  void SetDPI(TPel pDPI) { m_pDPI=pDPI; }
  TPel GetDPI() const { return m_pDPI; }

 public:
  virtual TLen b(TPel p) const { return p*b_factor(); }
  virtual TPel f(TLen l) const { return static_cast<TPel>(l/b_factor()); }

 public:
  virtual double b() const { return b_factor(); }
  virtual double f() const { return 1.0/b_factor(); }

 private:
  double b_factor() const { return c_LenPerInch/m_pDPI; }

 private:
  TPel m_pDPI;
};

////////////////////////////////////////////////////////////////////////////////
class TTransB_DPI: public ITransBwB<TLen, TPel, double>
{
 public:
  TTransB_DPI()
   : m_X(1),
     m_Y(1)  {}

  explicit TTransB_DPI(TPel pDPI)
   : m_X(pDPI),
     m_Y(pDPI)  {}

  explicit TTransB_DPI(TpPointB ppbDPI)
   : m_X(ppbDPI.X),
     m_Y(ppbDPI.Y)  {}

 public:
  const TTransU_DPI& X() const { return m_X; }
  const TTransU_DPI& Y() const { return m_Y; }

 public:
  virtual TPel   xf(TLen b) const { return m_X.f(b); }
  virtual double xf()       const { return m_X.f();  }

  virtual TLen   xb(TPel f) const { return m_X.b(f); }
  virtual double xb()       const { return m_X.b();  }

  virtual TPel   yf(TLen b) const { return m_Y.f(b); }
  virtual double yf()       const { return m_Y.f();  }

  virtual TLen   yb(TPel f) const { return m_Y.b(f); }
  virtual double yb()       const { return m_Y.b();  }

 public:
  void SetDPI(TpPointB ppbDPI) { m_X.SetDPI(ppbDPI.X); m_Y.SetDPI(ppbDPI.Y); }
  TpPointB GetDPI() const { return TpPointB(m_X.GetDPI(), m_Y.GetDPI()); }

 private:
  TTransU_DPI m_X;
  TTransU_DPI m_Y;
};


}

#endif
