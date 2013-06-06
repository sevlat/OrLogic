#ifndef CmdTranceive_h_already_included__09_03_2013__355C7880
#define CmdTranceive_h_already_included__09_03_2013__355C7880
//
// SeVlaT, 09.03.2013
//

#include "CmdShpObject.h"
#include "CmdQueue.h"

#include "../ProtScanner.h"
#include "../Chunk.h"

// !!!!!!!!!!!!
#include "../PacketReceiver.h"
#include "../PacketSender.h"

#include "CmdsReceiver.h"
#include "CmdsSender.h"

class TCmdQueue;
class TCmdSender;
class TCmdReceiver;

////////////////////////////////////////////////////////////////////////////////

class TCmdTransceiver {
 public:
  TCmdTransceiver(TCmdQueue    &Queue,
                  TCmdReceiver &CmdReceiver,
                  TCmdSender   &CmdSender);
  
 public:
  OCmdTxInfo Send(      ShpFCmdObject  shpFCmd,
                  const TPrefixParams *pPP,
                        TErrList      *pErr);

  void Receive(TErrList *pErr);

 public:
  const TCmdExch* Receive(const OCmdTxInfo &octi,
                                TErrList   *pErr);
  const TCmdExch* Receive3(const OCmdTxInfo &octi,
                                 TErrList   *pErr);

 public:
  OCmdExch Transceive(      ShpFCmdObject  shpFCmd,
                      const TPrefixParams *pPP,
                            TErrList      *pErr);
  OCmdExch TransceiveOnce(      ShpFCmdObject  shpFCmd,
                          const TPrefixParams *pPP,
                                TErrList      *pErr);
                          
 private:
  bool ReceiveCmd(TErrList *pErr);
  const TCmdExch* LookUpQueue(TSerNum sn, TErrList *pErr);

 private:
  TMsgFrame m_mf;

 private:
  TUInt m_nQIndex;
  
 private:
  TCmdQueue &m_Queue;

 private:
  TCmdSender   &m_CmdSender;
  TCmdReceiver &m_CmdReceiver;
};

////////////////////////////////////////////////////////////////////////////////
class TCmdTransceiverEx {
 public:
  TCmdTransceiverEx(TCmdQueue &Queue,
                    IIStream  &is,
                    IOStream  &os)
   : m_ChunkSender(os),
     m_BufSender(m_ChunkSender),
     m_PktSender(m_BufSender),
     m_CmdSender(m_PktSender, Queue.Sng()),
     
     m_ChunkReceiver(is),
     m_PktReceiver(m_ChunkReceiver),
     m_CmdReceiver(m_PktReceiver, Queue.Sng()),
     
     Tr(Queue, m_CmdReceiver, m_CmdSender)   
    { }

 private:
  TChunkSender m_ChunkSender;
  TBufSender   m_BufSender;
  TPktSender   m_PktSender;
  TCmdSender   m_CmdSender;
  
  TChunkReceiver m_ChunkReceiver;
  TPktReceiver   m_PktReceiver;
  TCmdReceiver   m_CmdReceiver;

 public:
  TCmdTransceiver Tr;
};

////////////////////////////////////////////////////////////////////////////////
class TCmdsPerformer {
 public:
  TCmdsPerformer(TCmdTransceiver &Tr,
                 ShpFCmdObject    shpFCmd,
                 int              nMaxReceiveTry,
                 int              nMaxNakTry,
                 TErrList        *pErr);

 public:
  bool Do();
 
 public:
  OCmdExch Res();

 private:
  bool DoOnBegin();
  bool DoOnSent();

 private:
  enum TState {
    sBegin,
    sSent,
    sEnd,
    sError,
  };
  
  TState m_State;

  int m_nReceiveTry;
  int m_nNakTry;
  
  ShpFCmdObject m_shpFCmd;
  
  OCmdTxInfo m_octi;
  
  OCmdExch m_oExch;

 private:
  TErrList *m_pErr;
  
 private:
  const int m_nMaxReceiveTry;
  const int m_nMaxNakTry;
  
 private:
  TCmdTransceiver &m_Tr;
};

#endif
