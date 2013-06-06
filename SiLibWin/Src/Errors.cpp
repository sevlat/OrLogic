// SeVlaT, 12.10.2012
#include "StdAfx.h"

#include <SiLib/Errors.h>

namespace PlatformSpecific {

unsigned int GetCurrentSystemError()
{
  return GetLastError();
}

}
