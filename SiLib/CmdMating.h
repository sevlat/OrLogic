#ifndef CmdMating_h_already_included__31_01_2013__2F690D80
#define CmdMating_h_already_included__31_01_2013__2F690D80
//
// SeVlaT, 31.01.2013
//

#include "CommandCode.h"

bool AreCommandsMateable(TCmdCode ccF, TCmdCode ccB);
bool MayInduceResponce(TCmdCode ccF);
bool MayBeAloneResponce(TCmdCode ccB);


#endif
