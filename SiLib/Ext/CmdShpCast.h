#ifndef CmdShpCast_h_already_included__19_03_2013__6A1A120
#define CmdShpCast_h_already_included__19_03_2013__6A1A120
//
// SeVlaT, 19.03.2013
//

#include "CmdShpObject.h"

#include "../CmdCast.h"


template<typename CMD>
const TCmdPtr<typename TCmdoGen<CMD>::Type> CmdShpCast(TCmdPtr<ICmdObject<typename CMD::TDir> > shpCmd)
{
  typedef TCmdPtr<typename TCmdoGen<CMD>::Type> ShpCmd1;
  
  if (shpCmd && CmdCast<CMD>(*shpCmd))
    return ShpCmd1(shpCmd, typename ShpCmd1::StaticCastTag());
    
  return ShpCmd1();
}

#endif
