// SeVlaT, 17.05.2013
#include "StdAfx.h"

#include "../PacketReceiver.h"

#include "../Stream.h"

void TChunkReceiver::Receive(TUInt nBytesToRead, TErrList *pErr)
{
  m_bRes=false;
  m_Chunk.buf.resize(nBytesToRead);
  
  TUInt nBytesRead=0;
  m_Chunk.t0=GetSysTime();
  if (!m_is.GetRaw(m_Chunk.buf.begin_ptr(),
                   nBytesToRead,
                   nBytesRead,
                   pErr)) return;
  m_Chunk.t1=GetSysTime();
  m_Chunk.nRequested=nBytesToRead;

  m_Chunk.buf.resize(nBytesRead);
  
  m_bRes=true;                     
}

////////////////////////////////////////////////////////////////////////////////
void TPktReceiver::Receive(TErrList *pErr)
{
  const TChunk *pChunk=0;

  if (m_isuToDo.Size()>0) {
    pChunk=m_ChunkReceiver.Get();
    if (!pChunk) return;
    
  } else {
    const TUInt nBytesToRead=hftl::Max<TUInt>(m_Counts.GetMin(), 1);
    
    m_ChunkReceiver.Receive(nBytesToRead, pErr);

    pChunk=m_ChunkReceiver.Get();
    if (!pChunk) return;
    
    m_isuToDo=TiSegmU(0, pChunk->buf.size());
  }
  
  if (m_State.IsStalled()) Reset();
  while (!m_State.IsStalled() &&
         m_isuToDo.Size()>0) {
    
    const TByte b=pChunk->buf[m_isuToDo.B];
    
    bool bEaten=false;
    ProtScanNext(b, bEaten, m_pkt, m_State, m_Data, m_Counts);
    
    if (bEaten) ++m_isuToDo.B;
  }
}

const TProtCmdPacket* TPktReceiver::Get() const
{
  if (m_State.IsStalledOk()) return &m_pkt;
  return 0;
}

void TPktReceiver::Reset()
{
  m_pkt   =TProtCmdPacket     ();
  m_State =TProtScannerState  ();
  m_Data  =TProtScannerData   ();
  m_Counts=TProtScannerCounts ();
}


