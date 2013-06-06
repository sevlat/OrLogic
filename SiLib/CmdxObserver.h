#ifndef CmdxObserver_h_already_included__04_04_2013__31904D80
#define CmdxObserver_h_already_included__04_04_2013__31904D80
//
// SeVlaT, 04.04.2013
//

#include "CmdExchange.h"

struct TCmdTxInfo;
struct TCmdRxInfo;


////////////////////////////////////////////////////////////////////////////////
// These template member functions should exist in every CmdxObserver
// Just copy them!
// Do not inherit from TSimplestCmdxObserver!
class TSimplestCmdxObserver {
 public:
  template <TCmdCode CCF>
  void OnOk(const TCommandBase<CCF, TagFwd> &FCmd,
                  OSysTime                   otF) {}

  template <TCmdCode CCB>
  void OnOk(const TCommandBase<CCB, TagBwd> &BCmd,
                  OSysTime                   otB) {}

  template <TCmdCode CCF>
  void OnOk(const TCommandBase<CCF, TagFwd> &FCmd,
                  OSysTime          otF,
                  const TCommandBase<TCmdCdTraits<CCF>::ccB, TagBwd> &BCmd,
                  OSysTime          otB) {}

 public:
  template <TCmdCode CCF>
  void OnFailed(const TCommandBase<CCF, TagFwd> &FCmd,
                      OSysTime                   otF,
                      TCmdxStatus                Status) {}
};


#endif
