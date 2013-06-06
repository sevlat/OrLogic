#ifndef m_Utils_h_already_included__17_03_2011__35FE37F0
#define m_Utils_h_already_included__17_03_2011__35FE37F0
//
// SeVlaT, 17.03.2011
//

#include "m_Consts.h"

namespace hftl { // HelpFul template library

inline double Gr2Rad(double g)  { return g*c_Pi/180.0; }
inline double Rad2Gr(double r)  { return r*180.0/c_Pi; }

// calculate modulo. Divident may be zero or negative,
// divider should be positive
template <typename INT>
INT Modulo(INT nDividend, INT nDivider)
{
  if (nDividend<0) nDividend+=(2-nDividend/nDivider)*nDivider;
  return nDividend%nDivider;
}

}

#endif
