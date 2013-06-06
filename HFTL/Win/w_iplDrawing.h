#ifndef w_iplDrawing_h_already_included__06_05_2011__32267333
#define w_iplDrawing_h_already_included__06_05_2011__32267333
//
// Taimanov Sergei, 06.05.2011
//

#include "../Main/m_iplSegPoint.h"

#include "w_iplUtils.h"

namespace hftl {
namespace win {

inline void FillSolidRect(HDC hDC, COLORREF cl, TpSegmB psb)
{
  if (psb.X.Size()<=0) return;
  if (psb.Y.Size()<=0) return;

  const COLORREF clBack=SetBkColor(hDC, cl);
  const RECT rect=toWin(psb);
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
  SetBkColor(hDC, clBack);
}

inline void FillSolidFrame(HDC hDC,
                           COLORREF cl,
                           TpSegmB psbInner,
                           TpSegmB psbOuter)
{
  psbInner=Intersect(psbInner, psbOuter);

  FillSolidRect(hDC, cl,
        TpSegmB(psbOuter.X.B, psbOuter.Y.B, psbInner.X.B, psbOuter.Y.E));
  FillSolidRect(hDC, cl,
        TpSegmB(psbInner.X.B, psbOuter.Y.B, psbInner.X.E, psbInner.Y.B));
  FillSolidRect(hDC, cl,
        TpSegmB(psbInner.X.E, psbOuter.Y.B, psbOuter.X.E, psbOuter.Y.E));
  FillSolidRect(hDC, cl,
        TpSegmB(psbInner.X.B, psbInner.Y.E, psbInner.X.E, psbOuter.Y.E));
}

} // namespace win
} // namespace hftl

#endif
