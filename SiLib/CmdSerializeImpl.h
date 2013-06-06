#ifndef CmdSerializeImpl_h_already_included__05_10_2012__12C67F60
#define CmdSerializeImpl_h_already_included__05_10_2012__12C67F60
//
// SeVlaT, 05.10.2012
//

#include "CmdSerialize.h"

#include "CmdItemSerialize.h"

#include "CmdDataSerializeImpl.h"

#include "ByteBufStream.h"

#include "Errors.h"

////////////////////////////////////////////////////////////////////////////////

namespace {
  enum TErrorCode {
    eUnknown,
    
    eIncorrectCommandCode,
    eIncorrectCommandSize,
    
    eiNoCommandBuffer,
    
    eLast
  };
  
  typedef TErrorDescription<TErrorCode, eLast, 600> TErrorDescr;

  static void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }
}

////////////////////////////////////////////////////////////////////////////////
template <typename CMDB>
bool TCmdSerializer<CMDB>::CheckCmdCode(TCmdCode cc)
{
  return CMDB::cc==cc;
}



template <typename CMDB>
bool TCmdSerializer<CMDB>::Make(const TData          &cmdd,
                                const TMsgFrame      &mf,
                                      TProtCmdPacket &pkt,
                                      TErrList       *pErr)
{
  TByteBuffer buf;
  TOByteBufStream bbos(buf);
  
  if (!Put(bbos, cmdd, pErr)) return false;
  
  pkt.cc=CMDB::cc;
  pkt.Frame=mf;
  pkt.SwapBuf(buf);
  
  return true;
}                                     

template <typename CMD>
TProtCmdPacket TCmdSerializer<CMD>::Make(const TData     &cmdd,
                                               TMsgFrame  mf,
                                               TErrList  *pErr)
{
  TProtCmdPacket pkt;
  Make(cmdd, mf, pkt, pErr); // !!!!! May return false
  return pkt;
}

template <typename CMDB>
bool TCmdSerializer<CMDB>::Parse(const TProtCmdPacket &pkt,
                                       TData          &cmdd,
                                       TErrList       *pErr)
{
  if (!CheckCmdCode(pkt.cc)) {
    PushError(pErr, eIncorrectCommandCode);
    return false;
  }
  
  TIByteBufStream bbis(pkt.buf);
  if (!Get(bbis, cmdd, pErr)) {
    return false;
  }
  
  if (!bbis.IsEnd()) {
    PushError(pErr, eIncorrectCommandSize);
    return false;
  }
  
  return true;
}

////////////////////////////////////////////////////////////////////////////////
template <typename CMD>
TProtCmdPacket MakePacket(const CMD &cmd, TMsgFrame mf, TErrList *pErr)
{
  return TCmdSerializer<typename CMD::TCmdb>::Make(cmd.data, mf, pErr);
}

template <typename CMD>
bool MakePacket(const CMD            &cmd,
                const TMsgFrame      &mf,
                      TProtCmdPacket &pkt,
                      TErrList       *pErr)
{
  return TCmdSerializer<typename CMD::TCmdb>::Make(cmd, mf, pkt, pErr);
}                      

template <typename CMD>
bool ParsePacket(const TProtCmdPacket &pkt, CMD &cmd, TErrList *pErr)
{
  return TCmdSerializer<typename CMD::TCmdb>::Parse(pk, cmdb, pErr);
}


#endif
