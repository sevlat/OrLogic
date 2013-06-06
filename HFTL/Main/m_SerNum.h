#ifndef m_SerNum_h_already_included__15_05_2013__23B91F80
#define m_SerNum_h_already_included__15_05_2013__23B91F80
//
// SeVlaT, 15.05.2013
//

namespace hftl { // Helpful template library

template <typename INT>
class TSerNum {
 public:
  class Initialize {};

 public:
  TSerNum(): m_n(0) {}
  TSerNum(INT n, Initialize): m_n(n) {}

 public:
  bool Equal(TSerNum sn) const { return m_n==sn.m_n; }
  bool Less (TSerNum sn) const { return m_n< sn.m_n; }

 private:
  INT m_n;
};

template <typename INT>
inline bool operator == (TSerNum<INT> sn0, TSerNum<INT> sn1) { return  sn0.Equal(sn1); }
template <typename INT>                           
inline bool operator != (TSerNum<INT> sn0, TSerNum<INT> sn1) { return !sn0.Equal(sn1); }
                                                                           
template <typename INT>                           
inline bool operator <  (TSerNum<INT> sn0, TSerNum<INT> sn1) { return  sn0.Less(sn1); }
template <typename INT>                           
inline bool operator <= (TSerNum<INT> sn0, TSerNum<INT> sn1) { return !sn1.Less(sn0); }
                                                                           
template <typename INT>                           
inline bool operator >  (TSerNum<INT> sn0, TSerNum<INT> sn1) { return  sn1.Less(sn0); }
template <typename INT>                           
inline bool operator >= (TSerNum<INT> sn0, TSerNum<INT> sn1) { return !sn0.Less(sn1); }


template <typename INT>
class TSerNumGen {
 public:
  typedef TSerNum<INT> TSerNum;

 public:
  TSerNumGen()
   : m_nPrev(0) {}
  
 public:
  TSerNum Generate() { return TSerNum(++m_nPrev, TSerNum::Initialize()); }
  
 private:
  INT m_nPrev;
};

} // namespace hftl

#endif
