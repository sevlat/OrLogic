#ifndef m_oiplSegPoint_h_already_included__20_09_2012__C190AC0
#define m_oiplSegPoint_h_already_included__20_09_2012__C190AC0
//
// SeVlaT, 20.09.2012
//

#include "m_iplSegPoint.h"
#include "m_oiplTypes.h"

namespace hftl { // Helpful template library

////////////////////////////////////////////////////////////////////////////////
typedef TOptional<TiSegmU>  OiSegmU;  // oisu

typedef TOptional<TiPointB> OiPointB; // oipb
typedef TOptional<TiSegmB>  OiSegmB;  // oisb

typedef TOptional<TiPointT> OiPointT; // oipt
typedef TOptional<TiSegmT>  OiSegmT;; // oist

//////////////////////////////////////////////////////////////////////
typedef TOptional<TlSegmU>  OlSegmU;  // olsu 

typedef TOptional<TlPointB> OlPointB; // olpb 
typedef TOptional<TlSegmB>  OlSegmB;  // olsb 

typedef TOptional<TlPointT> OlPointT; // olpt
typedef TOptional<TlSegmT>  OlSegmT;; // olst

//////////////////////////////////////////////////////////////////////
typedef TOptional<TpSegmU>  OpSegmU;  // opsu  

typedef TOptional<TpPointB> OpPointB; // oppb 
typedef TOptional<TpSegmB>  OpSegmB;  // opsb 

typedef TOptional<TpPointT> OpPointT; // oppt
typedef TOptional<TpSegmT>  OpSegmT;; // opst
}

#endif
