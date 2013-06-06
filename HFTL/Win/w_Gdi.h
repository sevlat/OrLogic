#ifndef w_Gdi_h_already_included__14_11_2011__3330B81D
#define w_Gdi_h_already_included__14_11_2011__3330B81D
//
// SeVlaT, 14.11.2011
//

#include "../Main/m_Optional.h"

namespace hftl {
namespace win {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename PARAM, PARAM (WINAPI *Function)(HDC, PARAM), PARAM FailParam>
class TDcSetter {
 public:
  explicit TDcSetter(HDC hDC)
   : m_hDC(hDC) { }

  TDcSetter(HDC hDC, PARAM Param)
   : m_hDC(hDC) { Set(Param); }

  ~TDcSetter() {  Reset();  }

 private:
  TDcSetter(const TDcSetter&);
  TDcSetter& operator=(const TDcSetter&);

 public:
  void Set(PARAM Param)
  {
    if (m_oPrevParam) {
      Function(m_hDC, Param);
    } else {
      const PARAM PrevParam=Function(m_hDC, Param);
      if (PrevParam!=FailParam) m_oPrevParam=PrevParam;
    }
  }

  void Reset()
  {
    if (m_oPrevParam) Function(m_hDC, *m_oPrevParam);
    m_oPrevParam=None;
  }

 private:
  HDC m_hDC;
  TOptional<PARAM> m_oPrevParam;
};

typedef TDcSetter<COLORREF, SetTextColor,    CLR_INVALID> TDcTextColorSetter;
typedef TDcSetter<COLORREF, SetBkColor,      CLR_INVALID> TDcBkColorSetter;
typedef TDcSetter<int,      SetBkMode,       0>           TDcBkModeSetter;
typedef TDcSetter<int,      SetROP2,         0>           TDcROP2Setter;
typedef TDcSetter<int,      SetGraphicsMode, 0>           TDcGraphicsModeSetter;
typedef TDcSetter<int,      SetMapMode,      0>           TDcMapModeSetter;

///////////////////////////////////////////////////////////////////////////////
//
template<typename OBJECT>
class TDcObjectSelector {
 public:
  explicit TDcObjectSelector(HDC hDC)
   : m_Setter(hDC)
    {  }

  TDcObjectSelector(HDC hDC, OBJECT hObj)
   : m_Setter(hDC)
    { Select(hObj); }

  void Select(OBJECT hObj)
    { if (hObj) m_Setter.Set(hObj); else m_Setter.Reset(); }

 private:
  TDcSetter<HGDIOBJ, SelectObject, 0> m_Setter;
};

typedef TDcObjectSelector<HPEN>     TDcPenSelector;
typedef TDcObjectSelector<HBRUSH>   TDcBrushSelector;
typedef TDcObjectSelector<HFONT>    TDcFontSelector;
typedef TDcObjectSelector<HBITMAP>  TDcBitmapSelector;
typedef TDcObjectSelector<HPALETTE> TDcPaletteSelector;
typedef TDcObjectSelector<HRGN>     TDcRgnSelector;

typedef TDcObjectSelector<HGDIOBJ>  TDcGdiObjSelector;

} // namespace win
}

#endif
