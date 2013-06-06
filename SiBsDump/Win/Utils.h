#ifndef Utils_h_already_included__08_05_2013__383C2B00
#define Utils_h_already_included__08_05_2013__383C2B00
//
// SeVlaT, 08.05.2013
//

#include "Types.h"

inline LPARAM CStr2LParam(LPCSTR sz)    { return LPARAM(sz); }
inline LPARAM CWStr2LParam(LPCWSTR wsz) { return LPARAM(wsz); }

inline LPARAM Str2LParam(LPSTR sz)    { return LPARAM(sz); }
inline LPARAM WStr2LParam(LPWSTR wsz) { return LPARAM(wsz); }

std::wstring GetVersionString(const std::wstring &sPrefix, int nNumbers);

#endif
