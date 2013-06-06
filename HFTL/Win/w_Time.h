#ifndef w_Time_h_already_included__08_05_2012__2694E3C0
#define w_Time_h_already_included__08_05_2012__2694E3C0
//
// SeVlaT, 08.05.2012
//

#include "../Main/m_OptionalTypes.h"

namespace hftl {
namespace win {

inline OInt64 GetPerformanceCounter()
{
  LARGE_INTEGER li={0};
  if (!QueryPerformanceCounter(&li)) return None;
  return li.QuadPart;
}

inline OInt64 GetPerformanceFrequency()
{
  LARGE_INTEGER li={0};
  if (!QueryPerformanceFrequency(&li)) return None;
  return li.QuadPart;
}




///////////////////////////////////////////////////////////////////////////////

} // namespace win

}

#endif
