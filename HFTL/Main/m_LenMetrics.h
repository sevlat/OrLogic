#ifndef m_LenMetrics_h_already_included__10_03_2013__21877540
#define m_LenMetrics_h_already_included__10_03_2013__21877540
//
// SeVlaT, 10.03.2013
//

#include "m_Consts.h"
#include "m_Len.h"

namespace hftl { // Helpful template library

///////////////////////////////////////////////////////////////////////////////
inline double Cm2Mm(double f)   { return f*c_MmPerCm; }
inline double Mm2Cm(double f)   { return f/c_MmPerCm; }

inline double Cm2Inch(double f) { return Cm2Mm(f)/c_MmPerInch; }
inline double Inch2Cm(double f) { return Mm2Cm(f*c_MmPerInch); }

///////////////////////////////////////////////////////////////////////////////
extern const double c_LenPerMm; // Should be defined in application
const double c_LenPerInch=c_LenPerMm*c_MmPerInch;

inline double L2Mm(TLen l)      { return l/c_LenPerMm; }
inline double Mm2L(double m)    { return m*c_LenPerMm; }

inline double L2Cm(TLen l)      { return Mm2Cm(L2Mm(l)); }
inline double Cm2L(double c)    { return Mm2L(Cm2Mm(c)); }

inline double L2Inch(TLen l)    { return L2Mm(l)/c_MmPerInch; }
inline double Inch2L(double i)  { return Mm2L(i*c_MmPerInch); }

}

#endif
