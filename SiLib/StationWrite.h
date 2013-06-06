#ifndef StationWrite_h_already_included__12_06_2012__160950C0
#define StationWrite_h_already_included__12_06_2012__160950C0
//
// SeVlaT, 12.06.2012
//

#include "StationTypes.h"
#include "Fwd.h"

bool AssemblePacket(const TProtCmdPacket &pkt,
                          TByteBuffer    &buf,
                          TErrList       *pErr);

#endif
