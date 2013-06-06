#ifndef m_Time_h_already_included__28_12_2012__2219CDC0
#define m_Time_h_already_included__28_12_2012__2219CDC0
//
// SeVlaT, 28.12.2012
//

namespace hftl { // Helpful template library

////////////////////////////////////////////////////////////////////////////////
template<int SPLITSEC, typename INT=int>
class TSpanTmpl {
 public:
  static const int c_nSplitSec=SPLITSEC;
  typedef INT TInt;
  
 public:
  explicit TSpanTmpl(INT n=0)
   : m_n(n) {}
  
 public:
  TSpanTmpl& operator += (const TSpanTmpl &s)
    { m_n+=s.m_n; return *this; }
  TSpanTmpl& operator -= (const TSpanTmpl &s)
    { m_n-=s.m_n; return *this; }

 public:
  template<typename NUM> TSpanTmpl& operator *= (NUM n)
    { m_n*=n; return *this; }
  template<typename NUM> TSpanTmpl& operator /= (NUM n)
    { m_n/=n; return *this; }
 
 public:
  TSpanTmpl const& operator + () const { return *this; }
  TSpanTmpl        operator - () const { return TSpanTmpl(-m_n); }

 public:
  bool LessThan(const TSpanTmpl &s) const { return m_n<s.m_n; }
  bool Equal(const TSpanTmpl &s) const { return m_n==s.m_n; }

 public:
  INT GetRaw() const { return m_n; }
  
 private:
  INT m_n; 
};

////////////////////////////////////////////////////////////////////////////////
template<typename SPAN, typename TAG>
class TTimeTmpl {
 public:
  typedef SPAN                TSpan;
  typedef typename SPAN::TInt TInt;

  static const int c_nSplitSec=SPAN::c_nSplitSec;
  
 public:
  explicit TTimeTmpl(TInt n=0)
   : m_n(n) {}
  
 public:
  TTimeTmpl& operator += (const TSpan &s)
    { m_n+=s.GetRaw(); return *this; }
  TTimeTmpl& operator -= (const TSpan &s)
    { m_n-=s.GetRaw(); return *this; }

 public:
  bool LessThan(const TTimeTmpl &t) const { return m_n<t.m_n; }
  bool Equal(const TTimeTmpl &t) const { return m_n==t.m_n; }
  
  TSpan Minus(const TTimeTmpl &t) const { return TSpan(m_n-t.m_n); }

 public:
  TInt GetRaw() const { return m_n; }
  
 private:
  TInt m_n; 
};

////////////////////////////////////////////////////////////////////////////////
template<int SPLITSEC, typename INT>
TSpanTmpl<SPLITSEC, INT> operator + (      TSpanTmpl<SPLITSEC, INT>  s0,
                                     const TSpanTmpl<SPLITSEC, INT> &s1)
{ return s0+=s1; }

template<int SPLITSEC, typename INT>
TSpanTmpl<SPLITSEC, INT> operator - (      TSpanTmpl<SPLITSEC, INT>  s0,
                                     const TSpanTmpl<SPLITSEC, INT> &s1)
{ return s0-=s1; }

template<int SPLITSEC, typename INT, typename NUM>
TSpanTmpl<SPLITSEC, INT> operator * (TSpanTmpl<SPLITSEC, INT>  s,
                                     NUM                       n)
{ return s*=n; }

template<int SPLITSEC, typename INT, typename NUM>
TSpanTmpl<SPLITSEC, INT> operator * (NUM                       n,
                                     TSpanTmpl<SPLITSEC, INT>  s)
{ return s*=n; }

template<int SPLITSEC, typename INT, typename NUM>
TSpanTmpl<SPLITSEC, INT> operator / (TSpanTmpl<SPLITSEC, INT>  s,
                                     NUM                       n)
{ return s/=n; }

template<int SPLITSEC, typename INT>
bool operator < (const TSpanTmpl<SPLITSEC, INT> &s0,
                 const TSpanTmpl<SPLITSEC, INT> &s1)
{ return s0.LessThan(s1); }

template<int SPLITSEC, typename INT>
bool operator >= (const TSpanTmpl<SPLITSEC, INT> &s0,
                  const TSpanTmpl<SPLITSEC, INT> &s1)
{ return !s0.LessThan(s1); }

template<int SPLITSEC, typename INT>
bool operator > (const TSpanTmpl<SPLITSEC, INT> &s0,
                 const TSpanTmpl<SPLITSEC, INT> &s1)
{ return s1.LessThan(s0); }

template<int SPLITSEC, typename INT>
bool operator <= (const TSpanTmpl<SPLITSEC, INT> &s0,
                  const TSpanTmpl<SPLITSEC, INT> &s1)
{ return !s1.LessThan(s0); }


template<int SPLITSEC, typename INT>
bool operator == (const TSpanTmpl<SPLITSEC, INT> &s0,
                  const TSpanTmpl<SPLITSEC, INT> &s1)
{ return s0.Equal(s1); }

template<int SPLITSEC, typename INT>
bool operator != (const TSpanTmpl<SPLITSEC, INT> &s0,
                  const TSpanTmpl<SPLITSEC, INT> &s1)
{ return !s0.Equal(s1); }

////////////////////////////////////////////////////////////////////////////////
template<typename SPAN, typename TAG>
TTimeTmpl<SPAN, TAG> operator + (      TTimeTmpl<SPAN, TAG>  t,
                                 const SPAN                 &s)
{ return t+=s; }

template<typename SPAN, typename TAG>
TTimeTmpl<SPAN, TAG> operator - (      TTimeTmpl<SPAN, TAG>  t,
                                 const SPAN                 &s)
{ return t-=s; }


template<typename SPAN, typename TAG>
SPAN operator - (const TTimeTmpl<SPAN, TAG> &t0,
                 const TTimeTmpl<SPAN, TAG> &t1)
{ return t0.Minus(t1); }


template<typename SPAN, typename TAG>
bool operator < (const TTimeTmpl<SPAN, TAG> &t0,
                 const TTimeTmpl<SPAN, TAG> &t1)
{ return t0.LessThan(t1); }

template<typename SPAN, typename TAG>
bool operator >= (const TTimeTmpl<SPAN, TAG> &t0,
                  const TTimeTmpl<SPAN, TAG> &t1)
{ return !t0.LessThan(t1); }

template<typename SPAN, typename TAG>
bool operator > (const TTimeTmpl<SPAN, TAG> &t0,
                 const TTimeTmpl<SPAN, TAG> &t1)
{ return t1.LessThan(t0); }

template<typename SPAN, typename TAG>
bool operator <= (const TTimeTmpl<SPAN, TAG> &t0,
                  const TTimeTmpl<SPAN, TAG> &t1)
{ return !t1.LessThan(t0); }


template<typename SPAN, typename TAG>
bool operator == (const TTimeTmpl<SPAN, TAG> &t0,
                  const TTimeTmpl<SPAN, TAG> &t1)
{ return t0.Equal(t1); }

template<typename SPAN, typename TAG>
bool operator != (const TTimeTmpl<SPAN, TAG> &t0,
                  const TTimeTmpl<SPAN, TAG> &t1)
{ return !t0.Equal(t1); }

}


#endif
