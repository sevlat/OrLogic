#ifndef m_iplSegPoint_h_already_included__18_07_2012__2BE8EAC
#define m_iplSegPoint_h_already_included__18_07_2012__2BE8EAC
//
// SeVlaT, 18.07.2012
//

#include "m_SegPoint.h"
#include "m_iplTypes.h"

namespace hftl { // Helpful template library

typedef TSegmU<TInd>  TiSegmU;  // isu

typedef TPointB<TInd> TiPointB; // ipb
typedef TSegmB<TInd>  TiSegmB;  // isb

typedef TPointT<TInd> TiPointT; // ipt
typedef TSegmT<TInd>  TiSegmT;  // ist

////////////////////////////////////////////////////////////////////////////////

typedef TSegmU<TLen>  TlSegmU;  // lsu 

typedef TPointB<TLen> TlPointB; // lpb 
typedef TSegmB<TLen>  TlSegmB;  // lsb 

typedef TPointT<TLen> TlPointT; // lpt 
typedef TSegmT<TLen>  TlSegmT;  // lst 

////////////////////////////////////////////////////////////////////////////////

typedef TSegmU<TPel>  TpSegmU;  // psu  

typedef TPointB<TPel> TpPointB; // ppb 
typedef TSegmB<TPel>  TpSegmB;  // psb 

typedef TPointT<TPel> TpPointT; // ppt 
typedef TSegmT<TPel>  TpSegmT;  // pst 

}

#endif
