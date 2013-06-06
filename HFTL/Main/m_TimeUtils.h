#ifndef m_TimeUtils_h_already_included__29_04_2013__FF82F10
#define m_TimeUtils_h_already_included__29_04_2013__FF82F10
//
// SeVlaT, 29.04.2013
//

namespace hftl { // Helpful template library

////////////////////////////////////////////////////////////////////////////////
inline int DaySeconds2Hour(int nSec)   { return nSec/3600; }
inline int DaySeconds2Minute(int nSec) { return (nSec%3600)/60; }
inline int DaySeconds2Second(int nSec) { return nSec%60; }

}

#endif
