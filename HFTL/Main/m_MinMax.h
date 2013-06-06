#ifndef m_MinMax_h_already_included__20_09_2012__1579B400
#define m_MinMax_h_already_included__20_09_2012__1579B400
//
// SeVlaT, 20.09.2012
//

namespace hftl {

///////////////////////////////////////////////////////////////////////////////
template<typename T>
const T& MinRef(const T &v0, const T &v1)
 {  return v0<v1? v0: v1; }

template<typename T>
const T& MinRef(const T &v0, const T &v1, const T &v2)
 {  return MinRef(MinRef(v0, v1), v2); }

template<typename T>
const T& MinRef(const T &v0, const T &v1, const T &v2, const T &v3)
 {  return MinRef(MinRef(MinRef(v0, v1), v2), v3); }

///////////////////////////////////////////////////////////////////////////////
template<typename T>
T Min(const T &v0, const T &v1)
 {  return v0<v1? v0: v1; }

template<typename T>
T Min(const T &v0, const T &v1, const T &v2)
 {  return MinRef(v0, v1, v2); }

template<typename T>
T Min(const T &v0, const T &v1, const T &v2, const T &v3)
 {  return MinRef(v0, v1, v2, v3); }

///////////////////////////////////////////////////////////////////////////////
template<typename T>
const T& MaxRef(const T &v0, const T &v1)
 {  return v1<v0? v0: v1; }

template<typename T>
const T& MaxRef(const T &v0, const T &v1, const T &v2)
 {  return MaxRef(MaxRef(v0, v1), v2); }

template<typename T>
const T& MaxRef(const T &v0, const T &v1, const T &v2, const T &v3)
 {  return MaxRef(MaxRef(MaxRef(v0, v1), v2), v3); }

///////////////////////////////////////////////////////////////////////////////
template<typename T>
T Max(const T &v0, const T &v1)
 {  return v1<v0? v0: v1; }

template<typename T>
T Max(const T &v0, const T &v1, const T &v2)
 {  return MaxRef(v0, v1, v2); }

template<typename T>
T Max(const T &v0, const T &v1, const T &v2, const T &v3)
 {  return MaxRef(v0, v1, v2, v3); }

///////////////////////////////////////////////////////////////////////////////
template <typename VAL>
unsigned int MinIndex(VAL v0, VAL v1)
{
  if (v1<v0) return 1;
  return 0;
}

template <typename VAL>
unsigned int MinIndex(VAL v0, VAL v1, VAL v2)
{
  if (v1<v0) {
    if (v2<v1) return 2;
    return 1;
  }
    
  if (v2<v0) return 2;
  return 0;
}

template <typename VAL>
unsigned int MinIndex(VAL v0, VAL v1, VAL v2, VAL v3)
{
  if (v1<v0) {
    if (v2<v1) {
      if (v3<v2) return 3;
      return 2;
    } 
    if (v3<v1) return 3;
    return 1;
  }
    
  if (v2<v0) {
    if (v3<v2) return 3;
    return 2;
  } 

  if (v3<v0) return 3;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename VAL>
unsigned int MaxIndex(VAL v0, VAL v1)
{
  if (v0<v1) return 1;
  return 0;
}

template <typename VAL>
unsigned int MaxIndex(VAL v0, VAL v1, VAL v2)
{
  if (v0<v1) {
    if (v1<v2) return 2;
    return 1;
  }
    
  if (v0<v2) return 2;
  return 0;
}

template <typename VAL>
unsigned int MaxIndex(VAL v0, VAL v1, VAL v2, VAL v3)
{
  if (v0<v1) {
    if (v1<v2) {
      if (v2<v3) return 3;
      return 2;
    } 
    if (v1<v3) return 3;
    return 1;
  }
    
  if (v0<v2) {
    if (v2<v3) return 3;
    return 2;
  } 
  if (v0<v3) return 3;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
VAL Abs(VAL v)
{
  return v<0? -v: v;
}

} // namespace hftl

#endif
