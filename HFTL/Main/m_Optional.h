#ifndef m_Optional_h_already_included__18_03_2011__9408F1
#define m_Optional_h_already_included__18_03_2011__9408F1
//
// SeVlaT, 18.03.2011
//

#include "m_MinMax.h"
#include "m_Compare.h"

namespace hftl {

class TNone {};
const TNone None;

template <typename T>
class TOptional {
 public:
  static TOptional MakeFromPtr(const T *p)
 { return p? TOptional(*p): TOptional<T>(None); }
 
 public:
  TOptional(): m_v(T()), m_b(false) {}
  TOptional(TNone): m_v(T()), m_b(false) {}
  TOptional(const T &v): m_v(v), m_b(true) {}
  TOptional(TNone, const T &v): m_v(v), m_b(false) {}
  
  TOptional(const TOptional &o): m_v(o.m_v), m_b(o.m_b) {}

  TOptional& operator=(const TOptional &o) { m_v=o.m_v; m_b=o.m_b; return *this; }

 public:
  TOptional& operator=(TNone)
    { m_b=false; return *this; }

  TOptional& operator=(const T &v)
    { m_v=v; m_b=true; return *this; }

 private: // Forbidden constructor
  template <typename U>
  TOptional(const TOptional<U> &o);

 private: // Forbidden operator = 
  template <typename U>
  TOptional& operator=(const TOptional<U> &o);

 public:
  T& Set()
    { m_b=true; return m_v; }

  void Set(const T &v)
    { m_v=v; m_b=true; }

  void SetPtr(const T *pv)
    { if (pv) { m_v=*pv; m_b=true; }
      else m_b=false; }

 public:
  T const& Get() const         { return m_v; }
  T&       Get()               { return m_v; }

  T const* GetPtr() const      { return m_b? &m_v: 0; }
  T*       GetPtr()            { return m_b? &m_v: 0; }

  T const* operator ->() const { return GetPtr(); }
  T*       operator ->()       { return GetPtr(); }

  T const& operator *() const  { return Get(); }
  T&       operator *()        { return Get(); }

 public:
  T Get(const T &vDefault) const { return m_b? m_v: vDefault; }

 public:
  // implicit conversion to "bool"
  typedef T TOptional::*Bool;
  static Bool MakeBool(bool b) { return b? &TOptional::m_v: 0; }
  operator Bool() const { return MakeBool(m_b); }

  bool operator! () const { return !m_b; }

 public:
  bool Actual(const T &v)          const { return m_b && (m_v==v); }
  void Update(const T &v)                { m_b=true; m_v=v; }
  void Outdate()                         { m_b=false; }

 public:
  void operator --()    { Outdate(); }
  void operator --(int) { Outdate(); }

 public:
  template <typename TO>
  TOptional<TO> ToOpt() const
   { if (m_b) return TO(m_v); return None; }

//  TOptional<T> ToOpt()
//   { return *this; }

 public:
  friend class TCSepStamp;
  class TCSepStamp {
   public:
    TCSepStamp(const TOptional &o, const T &v): m_o(o), m_v(v) {}

   public:
    bool Actual() const { return m_o.Actual(m_v); }

   public:
    operator Bool()   const { return TOptional::MakeBool(Actual()); } 
    bool operator !() const { return !Actual(); }

   private:
    const T &m_v;
    const TOptional &m_o;
  };

  friend class TSepStamp;
  class TSepStamp {
   public:
    TSepStamp(TOptional &o, const T &v): m_o(o), m_v(v) {}

   public:
    bool Actual()  const { return m_o.Actual(m_v); }
    void Update()  const { m_o.Update(m_v); }
    void Outdate() const { m_o.Outdate(); }

   public:
    operator Bool()   const { return TOptional::MakeBool(Actual()); } 
    bool operator !() const { return !Actual(); }
    
   public:
    void operator ++()    const { Update(); }
    bool operator ++(int) const { if (Actual()) return true;
                                  Update(); return false; }

    void operator --()    const { Outdate(); }
    void operator --(int) const { Outdate(); }

   private:
    const T &m_v;
    TOptional &m_o;
  };

  TCSepStamp operator[](const T &v) const { return TCSepStamp(*this, v); }
  TSepStamp  operator[](const T &v)       { return TSepStamp(*this, v); }

 public:
  bool CompareV(const TOptional<T> &o, int &nRes) const
  {
    return hftl::CompareZ(m_b, o.m_b, nRes) ||
           hftl::CompareV(m_v,  o.m_v, nRes);
  }

  bool Equal(const TOptional<T> &o) const
  {
    int nRes=0;
    if (hftl::CompareZ(m_b, o.m_b, nRes)) return nRes==0;
    return (m_v==o.m_v);
  }

  bool Equal(const T *pv) const
  {
    int nRes=0;
    if (hftl::CompareZ(m_b, pv, nRes)) return nRes==0;
    return (m_v==pv->m_v);
  }

 private:
  T    m_v;
  bool m_b;
};

template <typename T>
inline bool CompareV(const TOptional<T> &o0, const TOptional<T> &o1, int &nRes)
{
  return o0.CompareV(o1, nRes);
}

template <typename T>
inline bool operator ==(const TOptional<T> &o0, const TOptional<T> &o1)
{
  return o0.Equal(o1);
}

template <typename T>
inline bool operator !=(const TOptional<T> &o0, const TOptional<T> &o1)
{
  return !(o0==o1);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
const T& MinRef(const TOptional<T> &ov0, const T &v1)
 { if (!ov0) return v1; return MinRef(*ov0, v1); }

template<typename T>
T Min(const TOptional<T> &ov0, const T &v1)
 { if (!ov0) return v1; return MinRef(*ov0, v1); }

////////////////////////////////////////////////////////////////////////////////
template<typename T>
const T& MaxRef(const TOptional<T> &ov0, const T &v1)
 { if (!ov0) return v1; return MaxRef(*ov0, v1); }

template<typename T>
T Max(const TOptional<T> &ov0, const T &v1)
 { if (!ov0) return v1; return MaxRef(*ov0, v1); }
///////////////////////////////////////////////////////////////////////////////


template <typename T>
TOptional<T> OptFromPtr(const T *p)
 { if (!p) return None; return *p; }
 

template <typename T, typename A>
TOptional<T> OptFromOpt(const TOptional<A> &o) { return o.ToOpt<T>(); }


////////////////////////////////////////////////////////////////////////////////

template<typename T>
class TStampers {
  typedef T ttt;

 public:
  class TStamp {
    static unsigned long GetId() { unsigned long s_dwId=0; return ++s_dwId; }

   public:
    TStamp(): m_dwId(GetId()), m_dwCount(0) {}

    bool operator == (const TStamp &s) const
      { return s.m_dwId==m_dwId && s.m_dwCount==m_dwCount; }

    bool operator != (const TStamp &s) const
      { return !operator == (s); }

   protected:
    void Change() { ++m_dwCount; }

   private:
    unsigned long m_dwId;
    unsigned long m_dwCount;
  };

 public:
  typedef TOptional<TStamp> OStamp;
  typedef TOptional<OStamp> OOStamp;
};

}

#endif
