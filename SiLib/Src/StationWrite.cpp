// SeVlaT, 20.05.2012
#include "StdAfx.h"

#include "../StationWrite.h"

//#include "Crc.h"
#include "crc529.h" //!!!!!!!
#include "../CommandCode.h"
#include "../ByteBufStream.h"

#include "../Errors.h"

namespace {
  enum TErrorCode {
    eUnknown,
    
    eTooManyBytesInCommand,
    
    eiBareCommandHasBuffer,
    eiCommandShouldHaveFrame,
    
    eLast
  };
  
  typedef TErrorDescription<TErrorCode, eLast, 600> TErrorDescr;

  static void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }
}

////////////////////////////////////////////////////////////////////////////////
class TStationWrite {
 public:
  explicit TStationWrite(TErrList *pErr);
  
 private:
  TStationWrite(const TStationWrite&);
  TStationWrite& operator=(const TStationWrite&);

 public:
  void MakeMessage(const TProtCmdPacket &pkt,
                         TByteBuffer    &buf) const;
  
 private:
  void MakeBaseMessage(      TCmdCode     cc,
                       const TByteBuffer &bufData,
                       const TMsgFrame   &mf,
                             TByteBuffer &buf) const;

  void MakeExtMessage(      TCmdCode     cc,
                      const TByteBuffer &bufData,
                      const TMsgFrame   &mf,
                            TByteBuffer &buf) const;

  void MakeMessage(      TCmdCode     cc,
                   const TByteBuffer &bufData,
                   const OMsgFrame   &omf,
                         TByteBuffer &buf) const;

 private:
  void PushError(TErrorCode ec) const
  { TErrorDescr::PushError(m_pErr, ec); }

  void ThrowError(TErrorCode ec) const
  { TErrorDescr::PushError(m_pErr, ec); throw TExcept(); }

 private:
  TErrList *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
TStationWrite::TStationWrite(TErrList *pErr)
 : m_pErr(pErr)
{
}

TByte CmdCdByte(TCmdCode cc)
{
  // !!!!!! Check cc value
  return cc;
}

void TStationWrite::MakeBaseMessage(      TCmdCode     cc,
                                    const TByteBuffer &bufData,
                                    const TMsgFrame   &mf,
                                          TByteBuffer &buf) const
{
  const int nDle=std::count_if(bufData.begin(), bufData.end(), &NeedDle);
  
  // Prefix, Cmd, data+dle, ETX
  const size_t nBufSize=mf.Size()+1+bufData.size()+nDle;

  buf.clear();
  buf.reserve(nBufSize);
  
  {
    TOByteBufStream bbos(buf);

    mf.PutPrefix(bbos, m_pErr);
    bbos.PutByte(CmdCdByte(cc), m_pErr);
    
    for (TByteBufferCIt I=bufData.begin(); I!=bufData.end(); ++I) {
      const TByte b=*I;
      if (NeedDle(b)) bbos.PutByte(SpecByte::bDle, m_pErr);
      bbos.PutByte(b, m_pErr);
    }

    mf.PutSuffix(bbos, m_pErr);
  }
  assert(buf.size()==nBufSize);
}                  

void TStationWrite::MakeExtMessage(      TCmdCode     cc,
                                   const TByteBuffer &bufData,
                                   const TMsgFrame   &mf,
                                         TByteBuffer &buf) const
{
  const TUInt nDataSize=bufData.size();
  if (nDataSize>255) ThrowError(eTooManyBytesInCommand);

  const TByte bDataSize=static_cast<TByte>(nDataSize);

  buf.clear();

  // Frame, Cmd, Size, data, CRC
  const size_t nPredictedBufSize=mf.Size()+1+1+bufData.size()+2;
  buf.reserve(nPredictedBufSize);
  
  {
    TOByteBufStream bbos(buf);
    mf.PutPrefix(bbos, m_pErr);

    {
      const TUInt nCrcedDataBegin=buf.size();
      const TUInt nCrcDataSize=1+1+nDataSize; // Cmd+Size+Data
      
      bbos.PutByte(CmdCdByte(cc), m_pErr);
      bbos.PutByte(bDataSize, m_pErr);
      bbos.PutBuf(bufData, m_pErr);

      const TUInt nCrcedDataSize=buf.size()-nCrcedDataBegin;
      
      assert(nCrcedDataSize==(1+1+nDataSize));
      
      const TUInt dwCrc=crc(nCrcedDataSize, buf.ptr(nCrcedDataBegin));
      const TWord wCrc=dwCrc;

      bbos.PutWordBE(wCrc, m_pErr);
    }
    
    mf.PutSuffix(bbos, m_pErr);
  }
  assert(buf.size()==nPredictedBufSize);
}                  
               

void TStationWrite::MakeMessage(      TCmdCode     cc,
                                const TByteBuffer &bufData,
                                const OMsgFrame   &omf,
                                      TByteBuffer &buf) const
{
  const TCommandInfo &cmdi=GetCommandInfoRef(cc);
  
  if (cmdi.ct==ctLite) {
    buf.Append(CmdCdByte(cc));
    if (!bufData.empty()) PushError(eiBareCommandHasBuffer);
  } else {
    if (!omf) PushError(eiCommandShouldHaveFrame);

    if (cmdi.ct==ctBase) {
      MakeBaseMessage(cc, bufData, *omf, buf);
    } else if (cmdi.ct==ctExt) {
      MakeExtMessage(cc, bufData, *omf, buf);
    }
  }
}                                

void TStationWrite::MakeMessage(const TProtCmdPacket &pkt,
                                      TByteBuffer    &buf) const
{
  MakeMessage(pkt.cc, pkt.buf, pkt.Frame, buf);
}                                      

////////////////////////////////////////////////////////////////////////////////
bool AssemblePacket(const TProtCmdPacket &pkt,
                          TByteBuffer    &buf,
                          TErrList       *pErr)
{
  try {
    TStationWrite sw(pErr);
    sw.MakeMessage(pkt, buf);
  } 
  catch (TExcept) {
    return false;
  }
  
  return true;
}                        
