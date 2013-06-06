#ifndef w_Version_h_already_included__27_05_2013__19E3ADC0
#define w_Version_h_already_included__27_05_2013__19E3ADC0
//
// SeVlaT, 27.05.2013
//

#include "../Main/m_Compare.h"
#include "../Main/m_Optional.h"
#include "../Main/m_bbUtils.h"

namespace hftl {
namespace msw {

////////////////////////////////////////////////////////////////////////////////
struct TVersion {
  DWORD w0;
  DWORD w1;
  DWORD w2;
  DWORD w3;

 public:
  TVersion()
   : w0(0), w1(0), w2(0), w3(0) {}

  TVersion(DWORD dwFileVersionMS,
           DWORD dwFileVersionLS)
   : w0(Get2WordH(dwFileVersionMS)),
     w1(Get2WordL(dwFileVersionMS)),
     w2(Get2WordH(dwFileVersionLS)),
     w3(Get2WordL(dwFileVersionLS))  {}

  TVersion(DWORD aw0,
           DWORD aw1,
           DWORD aw2,
           DWORD aw3)
   : w0(aw0), w1(aw1), w2(aw2), w3(aw3) {}

 public:
  bool Compare(const TVersion &v, int &nRes) const
  {
    return CompareV(w0, v.w0, nRes) ||
           CompareV(w1, v.w1, nRes) ||
           CompareV(w2, v.w2, nRes) ||
           CompareV(w3, v.w3, nRes);
  }

  bool Equal(const TVersion &v) const
  {
    return (w0==v.w0) &&
           (w1==v.w1) &&
           (w2==v.w2) &&
           (w3==v.w3);
  }
};

typedef TOptional<TVersion> OVersion;

inline bool Compare(const TVersion &v0, const TVersion &v1, int &nRes)
{
  return v0.Compare(v1, nRes);
}

inline bool operator ==(const TVersion &v0, const TVersion &v1)
{
  return v0.Equal(v1);
}

inline bool operator !=(const TVersion &v0, const TVersion &v1)
{
  return !(v0==v1);
}


} // namespace msw
} // namespace hftl

#endif
