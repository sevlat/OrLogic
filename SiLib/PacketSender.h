#ifndef PacketSender_h_already_included__17_05_2013__2C20E840
#define PacketSender_h_already_included__17_05_2013__2C20E840
//
// SeVlaT, 17.05.2013
//

#include "Types.h"
#include "Fwd.h"
#include "Chunk.h"
#include "CmdTrxInfo.h"

struct TProtCmdPacket;

class TChunkSender {
 public:
  explicit TChunkSender(IOStream &os)
   : m_os(os) {}

 public:
  OChunkTxInfo Send(const TByteBuffer &buf,
                          TUInt        nPos,
                          TErrList    *pErr);
 private:
  IOStream &m_os;
};

////////////////////////////////////////////////////////////////////////////////
class TBufSender {
 public:
  explicit TBufSender(TChunkSender &cs)
   : m_cs(cs) {}

 public:
  OBufTxInfo Send(const TByteBuffer &buf,
                        TErrList    *pErr);
  
 private:
  TChunkSender &m_cs;
};

////////////////////////////////////////////////////////////////////////////////
class TPktSender {
 public:
  explicit TPktSender(TBufSender &bs)
   : m_bs(bs) {}

 public:
  OPktTxInfo Send(const TProtCmdPacket &pkt,
                        TErrList       *pErr);
  
 private:
  TBufSender &m_bs;
};


#endif
