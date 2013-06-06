#ifndef m_Trans_h_already_included__25_09_2011__A303557
#define m_Trans_h_already_included__25_09_2011__A303557
//
// SeVlaT, 25.09.2011
//

#include "m_SegPoint.h"

namespace hftl { // Helpful template library

////////////////////////////////////////////////////////////////////////////////
template<typename TRANS, typename FROM, typename TO, typename FACTOR=double>
class TTransU_crtp {
 public:
  typedef FROM   TFrom;
  typedef TO     TTo;
  typedef FACTOR TFactor;

 public:
  TFactor operator()() const
    { return Self().tr(); }

  TTo operator()(TFrom f) const
    { return Self().tr(f); }

  TSegmU<TTo> operator()(TSegmU<TFrom> su) const
    { return TSegmU<TTo>(Self.tr(su.B), Self.tr(su.E)); }

 private:
  const TRANS& Self() const { return static_cast<const TRANS&>(*this); }
};

template<typename TRANS, typename FROM, typename TO, typename FACTOR=double>
class TTransB_crtp {
 public:
  typedef FROM   TFrom;
  typedef TO     TTo;
  typedef FACTOR TFactor;

 public:
  TPointB<TFactor> operator()() const
    { return TPointB<FACTOR>(Self().x(), Self().y()); }

  TPointB<TTo> operator()(TPointB<TFrom> pb) const
    { return TPointB<TTo>(Self().x(pb.X), Self().y(pb.Y)); }

  TSegmB<TTo> operator()(TSegmB<TFrom> sb) const
    { return TSegmB<TTo>(Self().x(sb.X.B), Self().y(sb.Y.B), 
                         Self().x(sb.X.E), Self().y(sb.Y.E)); }

 private:
  const TRANS& Self() const { return static_cast<const TRANS&>(*this); }
};

////////////////////////////////////////////////////////////////////////////////
// One-Way Unidimensional transformer
template<typename FROM, typename TO, typename FACTOR=double>
struct ITransOwU: public TTransU_crtp<ITransOwU<FROM, TO, FACTOR>, FROM, TO, FACTOR> {
  typedef FROM   TFrom;
  typedef TO     TTo;
  typedef FACTOR TFactor;

  virtual TO     tr(FROM f) const=0;
  virtual FACTOR tr()       const=0;
};

////////////////////////////////////////////////////////////////////////////////
// One-Way Bidimensional transformer
template<typename FROM, typename TO, typename FACTOR=double>
struct ITransOwB: public TTransB_crtp<ITransOwB<FROM, TO, FACTOR>, FROM, TO, FACTOR> {
  typedef FROM   TFrom;
  typedef TO     TTo;
  typedef FACTOR TFactor;

  virtual TO     x(FROM f) const=0;
  virtual FACTOR x()       const=0;

  virtual TO     y(FROM f) const=0;
  virtual FACTOR y()       const=0;

 public:
  typedef ITransOwU<FROM, TO, FACTOR> Iou;

  class Toux: public Iou {
   public:
    explicit Toux(const ITransOwB &OwB): m_OwB(OwB) {}

   public:
    virtual TO     tr(FROM f) const { return m_OwB.x(f); }
    virtual FACTOR tr()       const { return m_OwB.x(); }

   private:
    const ITransOwB &m_OwB;
  };

  class Touy: public Iou {
   public:
    explicit Touy(const ITransOwB &OwB): m_OwB(OwB) {}

   public:
    virtual TO     tr(FROM f) const { return m_OwB.y(f); }
    virtual FACTOR tr()       const { return m_OwB.y(); }

   private:
    const ITransOwB &m_OwB;
  };

  Toux X() const { return Toux(*this); }
  Touy Y() const { return Touy(*this); }
};

////////////////////////////////////////////////////////////////////////////////
// Both-Way Unidimensional transformer
template<typename BKWD, typename FRWD, typename FACTOR=double>
struct ITransBwU {
  typedef FRWD TFrwd;
  typedef BKWD TBkwd;

  virtual FRWD   f(BKWD b) const=0;
  virtual FACTOR f()       const=0;

  virtual BKWD   b(FRWD f) const=0;
  virtual FACTOR b()       const=0;

 public:
  typedef ITransOwU<BKWD, FRWD, FACTOR> Iouf;
  typedef ITransOwU<FRWD, BKWD, FACTOR> Ioub;

  class Touf: public Iouf {
   public:
    explicit Touf(const ITransBwU &BwU): m_BwU(BwU) {}

   public:
    virtual FRWD   tr(BKWD b) const { return m_BwU.f(b); }
    virtual FACTOR tr()       const { return m_BwU.f(); }

   private:
    const ITransBwU &m_BwU;
  };

  class Toub: public Ioub {
   public:
    explicit Toub(const ITransBwU &BwU): m_BwU(BwU) {}

   public:
    virtual BKWD   tr(FRWD f) const { return m_BwU.b(f); }
    virtual FACTOR tr()       const { return m_BwU.b(); }

   private:
    const ITransBwU &m_BwU;
  };

  Touf F() const { return Touf(*this); }
  Toub B() const { return Toub(*this); }
};

////////////////////////////////////////////////////////////////////////////////
// Both-Way Bidimensional transformer
template<typename BKWD, typename FRWD, typename FACTOR=double>
struct ITransBwB {
  typedef FRWD TFrwd;
  typedef BKWD TBkwd;

 public:
  virtual FRWD   xf(BKWD b) const=0;
  virtual FACTOR xf()       const=0;

  virtual BKWD   xb(FRWD f) const=0;
  virtual FACTOR xb()       const=0;

  virtual FRWD   yf(BKWD b) const=0;
  virtual FACTOR yf()       const=0;

  virtual BKWD   yb(FRWD f) const=0;
  virtual FACTOR yb()       const=0;

 public:
  typedef ITransBwU<BKWD, FRWD, FACTOR> Ibu;

  typedef ITransOwU<BKWD, FRWD, FACTOR> Iouf;
  typedef ITransOwU<FRWD, BKWD, FACTOR> Ioub;

  typedef ITransOwB<BKWD, FRWD, FACTOR> Iobf;
  typedef ITransOwB<FRWD, BKWD, FACTOR> Iobb;

  class Tobf: public Iobf {
   public:
    explicit Tobf(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual FRWD   x(BKWD b) const { return m_BwB.xf(b); }
    virtual FACTOR x()       const { return m_BwB.xf();  }

    virtual FRWD   y(BKWD b) const { return m_BwB.yf(b); }
    virtual FACTOR y()       const { return m_BwB.yf();  }

   private:
    const ITransBwB &m_BwB;
  };

  class Tobb: public Iobb {
   public:
    explicit Tobb(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual BKWD   x(FRWD f) const { return m_BwB.xb(f); }
    virtual FACTOR x()       const { return m_BwB.xb();  }

    virtual BKWD   y(FRWD f) const { return m_BwB.yb(f); }
    virtual FACTOR y()       const { return m_BwB.yb();  }

   private:
    const ITransBwB &m_BwB;
  };

  class Tbux: public Ibu {
   public:
    explicit Tbux(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual FRWD   f(BKWD b) const { return m_BwB.xf(b); }
    virtual FACTOR f()       const { return m_BwB.xf();  }

    virtual BKWD   b(FRWD f) const { return m_BwB.xb(f); }
    virtual FACTOR b()       const { return m_BwB.xb();  }

   private:
    const ITransBwB &m_BwB;
  };

  class Tbuy: public Ibu {
   public:
    explicit Tbuy(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual FRWD   f(BKWD b) const { return m_BwB.yf(b); }
    virtual FACTOR f()       const { return m_BwB.yf();  }

    virtual BKWD   b(FRWD f) const { return m_BwB.yb(f); }
    virtual FACTOR b()       const { return m_BwB.yb();  }

   private:
    const ITransBwB &m_BwB;
  };

  class ToufX: public Iouf {
   public:
    explicit ToufX(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual FRWD   tr(BKWD b) const { return m_BwB.xf(b); }
    virtual FACTOR tr()       const { return m_BwB.xf();  }

   private:
    const ITransBwB &m_BwB;
  };

  class ToubX: public Ioub {
   public:
    explicit ToubX(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual BKWD   tr(FRWD f) const { return m_BwB.xb(f); }
    virtual FACTOR tr()       const { return m_BwB.xb();  }

   private:
    const ITransBwB &m_BwB;
  };

  class ToufY: public Iouf {
   public:
    explicit ToufY(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual FRWD   tr(BKWD b) const { return m_BwB.yf(b); }
    virtual FACTOR tr()       const { return m_BwB.yf();  }

   private:
    const ITransBwB &m_BwB;
  };

  class ToubY: public Ioub {
   public:
    explicit ToubY(const ITransBwB &BwB): m_BwB(BwB) {}

   public:
    virtual BKWD   tr(FRWD f) const { return m_BwB.yb(f); }
    virtual FACTOR tr()       const { return m_BwB.yb();  }

   private:
    const ITransBwB &m_BwB;
  };
};

template<typename TRANS>
class TAbsTransU: public ITransOwU<typename TRANS::TFrom,
                                   typename TRANS::TTo,
                                   typename TRANS::TFactor> {
 public:
  typedef typename TRANS::TFrom   TFrom;
  typedef typename TRANS::TTo     TTo;
  typedef typename TRANS::TFactor TFactor;

 public:
  TAbsTransU(const TRANS &tr, TFrom fOrg, TTo tOrg)
   : m_tr(tr),
     m_fOrg(fOrg),
     m_tOrg(tOrg) {}

 public:
  TFactor tr()    const { return m_tr.tr(); }
  TTo tr(TFrom f) const { return m_tOrg+m_tr.tr(f-m_fOrg); }

 private:
  const TRANS &m_tr;

  TFrom m_fOrg;
  TTo   m_tOrg;
};

template<typename TRANS>
class TAbsTransB: public ITransOwB<typename TRANS::TFrom,
                                   typename TRANS::TTo,
                                   typename TRANS::TFactor> {
 public:
  typedef typename TRANS::TFrom   TFrom;
  typedef typename TRANS::TTo     TTo;
  typedef typename TRANS::TFactor TFactor;

 public:
  TAbsTransB(const TRANS &tr, TPointB<TFrom> fpbOrg, TPointB<TTo> tpbOrg)
   : m_tr(tr),
     m_fpbOrg(fpbOrg),
     m_tpbOrg(tpbOrg) {}

 public:

  virtual TFactor x()        const { return m_tr.x(); }
  virtual TTo     x(TFrom f) const { return m_tpbOrg.X+m_tr.x(f-m_fpbOrg.X); }

  virtual TFactor y()        const { return m_tr.y(); }
  virtual TTo     y(TFrom f) const { return m_tpbOrg.Y+m_tr.y(f-m_fpbOrg.Y); }

 private:
  const TRANS &m_tr;

  TPointB<TFrom> m_fpbOrg;
  TPointB<TTo>   m_tpbOrg;
};

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
template<typename FROM, typename TO>
TO trans(const ITransOwU<FROM,TO> &tr, FROM b) { return tr(b); }

template<typename FROM, typename TO>
TSegmU<TO> trans(const ITransOwU<FROM,TO> &tr, TSegmU<FROM> bsu)
{ return TSegmU<TO>(tr(bsu.B), tr(bsu.E)); }

////////////////////////////////////////////////////////////////////////////////
template<typename FROM, typename TO>
TPointB<TO> trans(const ITransOwU<FROM,TO> &trX,
                  const ITransOwU<FROM,TO> &trY, TPointB<FROM> bps)
{ return TPointB<TO>(trX(bps.X), trY(bps.Y)); }

template<typename FROM, typename TO>
TSegmB<TO> trans(const ITransOwU<FROM,TO> &trX,
                 const ITransOwU<FROM,TO> &trY, TSegmB<FROM> bsb)
{ return TSegmB<TO>(trX(bsb.X), trY(bsb.Y)); }

////////////////////////////////////////////////////////////////////////////////
template<typename FROM, typename TO>
TPointB<TO> trans(const ITransOwU<FROM,TO> &trXY, TPointB<FROM> bps)
{ return TPointB<TO>(trXY(bps.X), trXY(bps.Y)); }

template<typename FROM, typename TO>
TSegmB<TO> trans(const ITransOwU<FROM,TO> &trXY, TSegmB<FROM> bsb)
{ return TSegmB<TO>(trXY(bsb.X), trXY(bsb.Y)); }

////////////////////////////////////////////////////////////////////////////////
template<typename FROM, typename TO>
TPointB<TO> trans(const ITransOwB<FROM,TO> &tr, TPointB<FROM> fpb)
{ return TPointB<TO>(tr.X()(fpb.X), tr.Y()(fpb.Y)); }

template<typename FROM, typename TO>
TSegmB<TO> trans(const ITransOwB<FROM,TO> &tr, TSegmB<FROM> fsb)
{ return TSegmB<TO>(tr.X()(fsb.X), tr.Y()(fsb.Y)); }

}

#endif
