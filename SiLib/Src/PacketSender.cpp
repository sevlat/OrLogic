// SeVlaT, 17.05.2013
#include "StdAfx.h"

#include "../PacketSender.h"

#include "../Stream.h"
#include "../StationWrite.h"

////////////////////////////////////////////////////////////////////////////////
OChunkTxInfo TChunkSender::Send(const TByteBuffer &buf,
                                      TUInt        nPos,
                                      TErrList    *pErr)
{
  if (nPos>=buf.size()) {
    assert(!"Out of buffer");
    return None;
  }
  
  TUInt nBytesWritten=0;
  TUInt nBytesToWrite=buf.size()-nPos;
  
  if (!m_os.PutRaw(buf.ptr(nPos), nBytesToWrite, nBytesWritten, pErr)) return None;
  
  TChunkTxInfo cti;
  cti.nSent=nBytesWritten;
  
  return cti;
}

OBufTxInfo TBufSender::Send(const TByteBuffer &buf,
                                  TErrList    *pErr)
{
  TUInt nPos=0;
  
  while (nPos<buf.size()) {
    const OChunkTxInfo octi=m_cs.Send(buf, nPos, pErr);
    if (!octi) return None;
    
    nPos+=octi->nSent;
  }
  
  TBufTxInfo bti;
  return bti;
}

OPktTxInfo TPktSender::Send(const TProtCmdPacket &pkt, TErrList *pErr)
{
  TByteBuffer buf;
  if (!AssemblePacket(pkt, buf, pErr)) return None;
  
  const OBufTxInfo obti=m_bs.Send(buf, pErr);
  if (!obti) return None;
  
  TPktTxInfo pti;
  return pti;
}
