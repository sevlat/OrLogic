#ifndef w_Utils_h_already_included__17_03_2011__11A02742
#define w_Utils_h_already_included__17_03_2011__11A02742
//
// SeVlaT, 17.03.2011
//

#include "../Main/m_SegPoint.h"

namespace hftl {
namespace win {

///////////////////////////////////////////////////////////////////////////////
template <typename LEN>
struct ToWin {
  POINT P(const TPointB<LEN> &pb) const
  {
    const POINT point={pb.X, pb.Y};
    return point;
  }

  POINT operator()(const TPointB<LEN> &pb) const
  {
    const POINT point={pb.X, pb.Y};
    return point;
  }

  SIZE S(const TPointB<LEN> &pb) const
  {
    const SIZE size={pb.X, pb.Y};
    return size;
  }

  RECT operator ()(const TSegmB<LEN> &sb) const
  {
    const RECT rect={sb.X.B, sb.Y.B, sb.X.E, sb.Y.E};
    return rect;
  }

  RECT operator ()(const TSegmU<LEN> &suX, const TSegmU<LEN> &suY) const
  {
    const RECT rect={suX.B, suY.B, suX.E, suY.E};
    return rect;
  }
};

template <typename LEN>
struct FromWin {
  TPointB<LEN> operator ()(const POINT &point) const
  {
    return TPointB<LEN>(point.x, point.y);
  }

  TPointB<LEN> operator ()(const SIZE &size) const
  {
    return TPointB<LEN>(size.cx, size.cy);
  }

  TSegmB<LEN> operator ()(const RECT &rect) const
  {
    return TSegmB<LEN>(rect.left, rect.top, rect.right, rect.bottom);
  }
};

} // namespace win

}

#endif
