#ifndef w_Version_h_already_included__27_05_2013__183BA260
#define w_Version_h_already_included__27_05_2013__183BA260
//
// SeVlaT, 27.05.2013
//

#include <HFTL/Win/w_Version.h>

hftl::TOptional<VS_FIXEDFILEINFO> GetProgramFixedFileInfo();
bool GetVersionString(int nNumbers, WCHAR szBuffer[], int nBufSize);


#endif
