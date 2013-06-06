
#include "w_iplUtils.h"

namespace hftl {
namespace win {

inline TpSegmB GetClientRect(HWND hWnd)
{
  RECT rect={0};
  if (::GetClientRect(hWnd, &rect)) return fromWin(rect);
  return TpSegmB();
}

inline TpSegmB GetWindowRect(HWND hWnd)
{
  RECT rect={0};
  if (::GetWindowRect(hWnd, &rect)) return fromWin(rect);
  return TpSegmB();
}

} // namespace win
} // namespace hftl
