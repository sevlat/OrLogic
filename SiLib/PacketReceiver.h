#ifndef PacketReceiver_h_already_included__17_05_2013__38CD6240
#define PacketReceiver_h_already_included__17_05_2013__38CD6240
//
// SeVlaT, 17.05.2013
//

#include "Types.h"
#include "Fwd.h"
#include "Chunk.h"

// !!!!!!!!!!!!!
#include "StationTypes.h"
#include "ProtScanner.h"

////////////////////////////////////////////////////////////////////////////////

class TChunkReceiver {
 public:
  TChunkReceiver(IIStream &is)
   : m_is(is) {}
   
  void Receive(TUInt nBytesToRead, TErrList *pErr);
  
 public:
  const TChunk* Get() const { if (!m_bRes) return 0; return &m_Chunk; }
  
 private:
  TChunk m_Chunk;
  bool   m_bRes;

 private:
  IIStream &m_is;
};

////////////////////////////////////////////////////////////////////////////////
class TPktReceiver {
 public:
  explicit TPktReceiver(TChunkReceiver &ChunkReceiver)
   : m_ChunkReceiver(ChunkReceiver) {}

 public:
  void Receive(TErrList *pErr);
  const TProtCmdPacket* Get() const;
  void Reset();

 private:
  TChunkReceiver &m_ChunkReceiver;
  
 private:
  TiSegmU m_isuToDo;
  
 private:
  TProtCmdPacket     m_pkt;
  
  TProtScannerState  m_State;
  TProtScannerData   m_Data;
  TProtScannerCounts m_Counts;
};


#endif
