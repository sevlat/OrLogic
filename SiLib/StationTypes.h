#ifndef StationTypes_h_already_included__13_09_2012__245C6040
#define StationTypes_h_already_included__13_09_2012__245C6040
//
// SeVlaT, 13.09.2012
//

#include "Types.h"
#include "CommandCode.h"
#include "ByteBuffer.h"
#include "Fwd.h"

//namespace Prot {

struct TPrefixParams {
  OBool obWakeUp;
  OUInt onStx;
  
  TPrefixParams() {}
  TPrefixParams(OBool obWU, OUInt onS)
   : obWakeUp(obWU), onStx(onS) {}
};

struct TMsgPrefix {
 public:
  TMsgPrefix();
  TMsgPrefix(bool abWakeUp, TUInt anStx);
  TMsgPrefix(const TMsgPrefix &wp, const TPrefixParams &Params);
 
 public:
  TUInt Size() const;
  bool Put(IOStream &os, TErrList *pErr) const;
  
 public:
  bool  bWakeUp;
  TUInt nStx;
};

enum TMsgSuffix {
  msNone,
  msEtx,
  msNak
};

struct TMsgFrame {
  TMsgPrefix Prefix;
  TMsgSuffix Suffix;
 
 public:
  void PutPrefix(IOStream &os, TErrList *pErr) const;
  void PutSuffix(IOStream &os, TErrList *pErr) const;

  TUInt Size() const;
 
 public:
  TMsgFrame()
   : Suffix(msEtx) {}

  TMsgFrame(const TMsgPrefix &aPref)
   : Prefix(aPref),
     Suffix(msEtx) {}
};

typedef TOptional<TMsgFrame> OMsgFrame;

////////////////////////////////////////////////////////////////////////////////
struct TProtCmdPacket {
  TProtCmdPacket()
   : cc(CmdCd::cNull) {}
  
  explicit TProtCmdPacket(TCmdCode acc)
   : cc(acc) {}
   
  TProtCmdPacket(TCmdCode acc, TMsgFrame aFrame)
   : cc(acc), Frame(aFrame) {}

  void SwapBuf(TByteBuffer &bb) { buf.swap(bb); }

  TCmdCode    cc;
  TByteBuffer buf;
  TMsgFrame   Frame;
};

typedef TProtCmdPacket        TStMessage;
typedef TOptional<TStMessage> OStMessage;

#endif
