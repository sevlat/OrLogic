#ifndef CmdSerialize_h_already_included__18_10_2012__8DA5150
#define CmdSerialize_h_already_included__18_10_2012__8DA5150
//
// SeVlaT, 18.10.2012
//

#include "Types.h"
#include "Fwd.h"

#include "StationTypes.h"
#include "TimeTypes.h"

#include "CmdDataSerialize.h"

template <typename CMDB>
struct TCmdSerializer: TCmdDataSerializer<typename CMDB::TData> {
  typedef typename CMDB::TData TData;
  static bool CheckCmdCode(TCmdCode nCmdCode);
  
  static bool Make(const TData          &cmdd,
                   const TMsgFrame      &mf,
                         TProtCmdPacket &pkt,
                         TErrList       *pErr);
                         
  static TProtCmdPacket Make(const TData &cmdd, TMsgFrame mf, TErrList *pErr);
  
  static bool Parse(const TProtCmdPacket &cp, TData &cmdd, TErrList *pErr);
};

////////////////////////////////////////////////////////////////////////////////

template <typename CMD>
TProtCmdPacket MakePacket(const CMD &cmd, TMsgFrame mf, TErrList *pErr);

template <typename CMD>
bool MakePacket(const CMD            &cmd,
                const TMsgFrame      &mf,
                      TProtCmdPacket &pkt,
                      TErrList       *pErr);


template <typename CMD>
bool ParsePacket(const TProtCmdPacket &pkt, CMD &cmd, TErrList *pErr);

#endif
