#ifndef m_StampUpdate_h_already_included__18_04_2012__28240B00
#define m_StampUpdate_h_already_included__18_04_2012__28240B00
//
// SeVlaT, 18.04.2012
//

namespace hftl { // HelpFul Template Library

template<typename STAMP>
bool SUpdate(STAMP &s);

template<typename STAMP0, typename STAMP1>
bool SUpdate(STAMP0 &s0, STAMP1 &s1);

template<typename STAMP0, typename STAMP1, typename STAMP2>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2);

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3);

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4);

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4, STAMP5 &s5);

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5, typename STAMP6>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4, STAMP5 &s5, STAMP6 &s6);

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5, typename STAMP6, typename STAMP7>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4, STAMP5 &s5, STAMP6 &s6, STAMP7 &s7);


///////////////////////////////////////////////////////////////////////////////
// SUpdate inlines
template<typename STAMP>
inline bool SUpdate(STAMP &s)
{
  return s++;
}

template<typename STAMP0, typename STAMP1>
inline bool SUpdate(STAMP0 &s0, STAMP1 &s1)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  return b0 && b1;
}

template<typename STAMP0, typename STAMP1, typename STAMP2>
inline bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  return b0 && b1 && b2;
}

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3>
inline bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  const bool b3 = s3++;
  return b0 && b1 && b2 && b3;
}

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4>
inline bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
                    STAMP4 &s4)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  const bool b3 = s3++;
  const bool b4 = s4++;
  return b0 && b1 && b2 && b3 && b4;
}

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5>
inline bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
                    STAMP4 &s4, STAMP5 &s5)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  const bool b3 = s3++;
  const bool b4 = s4++;
  const bool b5 = s5++;
  return b0 && b1 && b2 && b3 && b4 && b5;
}

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5, typename STAMP6>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4, STAMP5 &s5, STAMP6 &s6)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  const bool b3 = s3++;
  const bool b4 = s4++;
  const bool b5 = s5++;
  const bool b6 = s6++;
  return b0 && b1 && b2 && b3 && b4 && b5 && b6;
}

template<typename STAMP0, typename STAMP1, typename STAMP2, typename STAMP3,
         typename STAMP4, typename STAMP5, typename STAMP6, typename STAMP7>
bool SUpdate(STAMP0 &s0, STAMP1 &s1, STAMP2 &s2, STAMP3 &s3,
             STAMP4 &s4, STAMP5 &s5, STAMP6 &s6, STAMP7 &s7)
{
  const bool b0 = s0++;
  const bool b1 = s1++;
  const bool b2 = s2++;
  const bool b3 = s3++;
  const bool b4 = s4++;
  const bool b5 = s5++;
  const bool b6 = s6++;
  const bool b7 = s7++;
  return b0 && b1 && b2 && b3 && b4 && b5 && b6 && b7;
}

} // namespace hftl

#endif
