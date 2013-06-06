// !!!!!!!! to be deleted

#ifndef StationRead_h_already_included__12_06_2012__10878FC0
#define StationRead_h_already_included__12_06_2012__10878FC0
//
// SeVlaT, 12.06.2012
//

#include "StationTypes.h"
#include "Fwd.h"

////////////////////////////////////////////////////////////////////////////////
bool StationRead(IIStream   &is,
                 TStMessage &smr,
                 TErrList   *pErr);

#endif
