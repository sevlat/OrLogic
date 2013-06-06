#ifndef CmdExchange_h_already_included__02_04_2013__210423C0
#define CmdExchange_h_already_included__02_04_2013__210423C0
//
// SeVlaT, 02.04.2013
//

#include "CmdObject.h"

struct TCmdTxInfo;
struct TCmdRxInfo;

class ICmdExch {
 public:
  enum TStatus {
    sOk,
    sNak,
    sTimeout,
    sNoRequest,
    sNoAnswer,
    sError
  };

 public:
  virtual TStatus Status() const=0;
  
  virtual const IFCmdObject* FCmd() const=0;
  virtual const TCmdTxInfo& FInfo() const=0;

  virtual const IBCmdObject* BCmd() const=0;
  virtual const TCmdRxInfo& BInfo() const=0;
};

typedef ICmdExch::TStatus      TCmdxStatus;
typedef TOptional<TCmdxStatus> OCmdxStatus;

void DescribeCmdExch(std::ostream &os, const ICmdExch &cmdx);

#endif
