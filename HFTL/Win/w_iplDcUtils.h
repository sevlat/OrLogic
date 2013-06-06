#ifndef w_iplDcUtils_h_already_included__19_06_2011__237598A9
#define w_iplDcUtils_h_already_included__19_06_2011__237598A9
//
// SeVT, 19.06.2011
//

namespace {

inline TpPointB GetDeviceDPI(HDC hDC)
{
  return TpPointB(::GetDeviceCaps(hDC, LOGPIXELSX),
                  ::GetDeviceCaps(hDC, LOGPIXELSY));
}

}
#endif
