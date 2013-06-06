#ifndef m_Angle_h_already_included__02_02_2012__946CA4D
#define m_Angle_h_already_included__02_02_2012__946CA4D
//
// SeVlaT, 02.02.2012
//

#include "m_Consts.h"

namespace hftl { // HelpFul useful template library

class TagRad {};
class TagDeg {};

class TagFlat  {};
class TagRight {};
class TagFull  {};

const TagRad tagRad;
const TagDeg tagDeg;

const TagFlat  tagFlat;
const TagRight tagRight;
const TagFull  tagFull;

#ifdef ANGLE_USE_INTERNALLY_DEGREE
  const double c_AngPerRad=c_DegPerRad;
#else
  const double c_AngPerRad=1.0;
#endif

const double c_AngPerDeg=c_AngPerRad/c_DegPerRad;

///////////////////////////////////////////////////////////////////////////////
const double c_AngFlat =c_Pi*c_AngPerRad;
const double c_AngRight=c_AngFlat/2.0;
const double c_AngFull =c_AngFlat*2.0;

class TAng {
 public:
  TAng() :m_v(0) {}

  TAng(double fRad, TagRad): m_v(fRad*c_AngPerRad) {}
  TAng(double fDeg, TagDeg): m_v(fDeg*c_AngPerDeg) {}

 private:
  explicit TAng(double v): m_v(v) {}

 public:
  static TAng FromDeg(double fDeg) { return TAng(fDeg, tagDeg); }
  static TAng FromRad(double fRad) { return TAng(fRad, tagRad); }

  static TAng MakeFlat()  { return TAng(c_AngFlat);  }
  static TAng MakeRight() { return TAng(c_AngRight); }
  static TAng MakeFull()  { return TAng(c_AngFull);  }
  
 public:
  double Deg() const { return m_v/c_AngPerDeg; }
  double Rad() const { return m_v/c_AngPerRad; }

 public:
  bool Equal(TAng a) const { return m_v==a.m_v; }
  bool Less (TAng a) const { return m_v< a.m_v; }

  double Divide(TAng a) const { return m_v< a.m_v; }

 public:
  TAng Normal0() const
  {
    if (m_v>=c_AngFlat) return TAng(m_v-2*c_AngFlat*int((c_AngFlat+m_v)/(2*c_AngFlat)));
    if (m_v<-c_AngFlat) return TAng(m_v+2*c_AngFlat*int((c_AngFlat-m_v)/(2*c_AngFlat)));
    return *this;
  }

  TAng Normal0(TAng aRef) const
  {
    TAng aDiff(m_v-aRef.m_v);
    aDiff.Normalize0();
    return TAng(aDiff.m_v+aRef.m_v);
  }

 public:
  void Normalize0()
  {
         if (m_v>=c_AngFlat) m_v=m_v-2*c_AngFlat*int((c_AngFlat+m_v)/(2*c_AngFlat));
    else if (m_v<-c_AngFlat) m_v=m_v+2*c_AngFlat*int((c_AngFlat-m_v)/(2*c_AngFlat));
  }

  void Normalize0(TAng aRef)
  {
    TAng aDiff(m_v-aRef.m_v);
    aDiff.Normalize0();
    m_v=aDiff.m_v+aRef.m_v;
  }

 public:
  TAng const& operator + () const { return *this; }
  TAng        operator - () const { return TAng(-m_v); }

 public:
  TAng& operator += (TAng a)  { m_v+=a.m_v; return *this; }
  TAng& operator -= (TAng a)  { m_v-=a.m_v; return *this; }

 public:
  template<typename NUM>
  TAng& operator *= (NUM n)  { m_v*=n; return *this; }

  template<typename NUM>
  TAng& operator /= (NUM n)  { m_v/=n; return *this; }

 private:
  double m_v;
};

inline bool operator == (TAng a0, TAng a1) { return  a0.Equal(a1); }
inline bool operator != (TAng a0, TAng a1) { return !a0.Equal(a1); }

inline bool operator <  (TAng a0, TAng a1) { return  a0.Less(a1); }
inline bool operator <= (TAng a0, TAng a1) { return !a1.Less(a0); }

inline bool operator >  (TAng a0, TAng a1) { return  a1.Less(a0); }
inline bool operator >= (TAng a0, TAng a1) { return !a0.Less(a1); }

///////////////////////////////////////////////////////////////////////////////
inline TAng operator + (TAng a0, TAng a1)  { return a0+=a1; }
inline TAng operator - (TAng a0, TAng a1)  { return a0-=a1; }

///////////////////////////////////////////////////////////////////////////////
template<typename NUM>
TAng operator * (TAng a, NUM n) { return a*=n; }

template<typename NUM>
TAng operator * (NUM n, TAng a) { return a*=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename NUM>
TAng operator / (TAng a, NUM n) { return a/=n; }

template<typename NUM>
double operator / (TAng a0, TAng a1)
{ return a0.Divide(a1); }


/*
inline double A2Gr(TAng a)      { return a/c_AngPerDeg; }
inline double A2Rad(TAng a)     { return a/c_AngPerRad; }

inline TAng   Rad2A(double r)    { return r*c_AngPerRad; }
inline TAng   Gr2A(double g)     { return g*c_AngPerGr; }
*/

}
#endif
