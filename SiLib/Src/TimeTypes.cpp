// SeVlaT, 26.12.2012
#include "StdAfx.h"

#include "../Ext/TimeTypes.h"

TSysTime GetSysTime()
{
  using namespace boost::chrono;
  typedef system_clock TSc;
  TSc::time_point t=TSc::now();
  
  return TSysTime(duration_cast<TSysSpan>(t.time_since_epoch()));// Use now()
}


