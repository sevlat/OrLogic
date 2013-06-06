// SeVlaT, 28.02.2013
#include "StdAfx.h"

#include "../CmdExchange.h"

#include "../MsgDescribe.h"

void DescribeCmdExch(std::ostream &os, const ICmdExch &cmdx)
{
  os << "-----------------" << std::endl;

  if (cmdx.FCmd()) {
    {
      TFDescrCmdVisitorV v(os);
      cmdx.FCmd()->Apply(v);
    }

    {
      TFDescrRawCmdVisitorV rv(os);
      cmdx.FCmd()->Apply(rv);
    }

    os << std::endl;
  }
  
  if (cmdx.BCmd()) {
    {
      TBDescrCmdVisitorV v(os);
      cmdx.BCmd()->Apply(v);
    }

    {
      TBDescrRawCmdVisitorV rv(os);
      cmdx.BCmd()->Apply(rv);
    }
    
    os << std::endl;
  }
}
