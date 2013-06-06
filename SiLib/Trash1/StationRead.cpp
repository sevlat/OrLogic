// !!!!!!!! to be deleted

// SeVlaT, 20.05.2012
#include "StdAfx.h"

#include "../StationRead.h"

#include "../CommandCode.h"
#include "../Stream.h"
#include "../Crc.h"

#include "../Errors.h"

const int nMaxBytesToRead=1024;

namespace {
  enum TErrorCode {
    eUnknown,
    
    eTooManyBytesToRead,

    eStxExpected,
    eStxUnexpected,
    eCannotReadLen,
    eCannotReadData,
    eCannotReadCrc,
    eCannotReadEnd,
    eCannotReadByte,
    eUnexpectedByte,
    eUnknownCommand,
    eInvalidCrc,
    eInvalidFrameEnd,
    eBareCommandHasFrame,
    eCommandShouldHaveFrame,

    eInternal_ReadMoreThanRequested,
    
    eNothingToRead,

    eLast
  };
  
  typedef TErrorDescription<TErrorCode, eLast, 400> TErrorDescr;

  void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }
}

////////////////////////////////////////////////////////////////////////////////
// Make it template
// template <typename ERRORDESCR>
class TIStream2 {
 public:
  TIStream2(IIStream &is,
            TErrList *pErr);
 
 private:
  TIStream2(const TIStream2&);
  TIStream2& operator=(const TIStream2&);

 public:
  TByte SkipUntil() const;

  TByte ReadByte(TErrorCode ec) const;
  TWord ReadWord(TErrorCode ec) const;

  void ReadBuf(TByte      *pBuf,
               TUInt       nBytesToRead,
               TErrorCode  ec) const;

 public:
  void Prepare(TUInt nBytes) const;
  void PrepareMore(TUInt nBytes) const;

 protected:
  void PushError(TErrorCode ec) const
  { TErrorDescr::PushError(m_pErr, ec); }

  void ThrowError(TErrorCode ec) const
  { TErrorDescr::PushError(m_pErr, ec); throw TExcept(); }

 private:
  IIStream &m_is;
  TErrList *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
class TStationRead: private TIStream2 {
 public:
  TStationRead(IIStream &is,
               TErrList *pErr);
  
 private:
  TStationRead(const TStationRead&);
  TStationRead& operator=(const TStationRead&);

 public:
  void Read(TStMessage &sm);

 private:
  TCmdCode ReadCmdByte(OMsgFrame &omf) const;
  
  bool ParseSuffix(TByte b, TMsgSuffix &mSuf) const;

  void ReadBase(const TCommandInfo &cmdi,
                      TByteBuffer  &bufData,
                      TMsgSuffix   &mSuf) const;
                      
  void ReadExt(TByte        bCmd,
               TByteBuffer &bufData,
               TMsgSuffix  &mSuf) const;

 private:
  bool m_bAllowWakeUp;
  bool m_bAllowDblStx;
};  

////////////////////////////////////////////////////////////////////////////////
TIStream2::TIStream2(IIStream &is,
                     TErrList *pErr)
 : m_is(is),
   m_pErr(pErr)
{
}

TByte TIStream2::ReadByte(TErrorCode ec) const
{
  TByte b;
  if (!NStreamUtils::Get1Byte(m_is, b, m_pErr)) ThrowError(ec);
  return b;
}

TWord TIStream2::ReadWord(TErrorCode ec) const
{
  TWord w=0;
  if (!NStreamUtils::Get2ByteBE(m_is, w, m_pErr)) ThrowError(ec);
  return w;
}

void TIStream2::ReadBuf(TByte      *pBuf,
                        TUInt       nBytesToRead,
                        TErrorCode  ec) const
{
  if (!NStreamUtils::GetBuf(m_is, pBuf, nBytesToRead, m_pErr)) ThrowError(ec);
}

TByte TIStream2::SkipUntil() const
{
  const OByte ob=NStreamUtils::SkipUntil(m_is,
                                         SpecByte::bStx,
                                         CmdCd::lBeep,
                                         CmdCd::lNak,
                                         m_pErr);
  if (!ob) ThrowError(eCannotReadByte);
  return *ob;
}

void TIStream2::Prepare(TUInt nBytes) const
{
}

void TIStream2::PrepareMore(TUInt nBytes) const
{
}

////////////////////////////////////////////////////////////////////////////////
TStationRead::TStationRead(IIStream &is,
                           TErrList *pErr)
 : TIStream2(is, pErr),
   m_bAllowWakeUp(true),
   m_bAllowDblStx(true) 
{
}

bool CheckCrc(      TByte        bCmd,
                    TByte        bLen,
              const TByteBuffer &bufData,
                    TWord        wCrc)
{
  TCrc crc(2+bufData.size());
  crc.AddByte(bCmd);
  crc.AddByte(bLen);
  crc.AddBuf(bufData);
    
  return crc.Get()==wCrc;
}

bool TStationRead::ParseSuffix(TByte b, TMsgSuffix &mSuf) const
{
  switch (b) {
    case SpecByte::bEtx: mSuf=msEtx; return true; 
    case SpecByte::bNak: mSuf=msNak; return true; 
  }
  
  return false;
}                               

// !!!!!! maybe remove TCommandInfo
// bufData can contain partial data if function not completed
void TStationRead::ReadBase(const TCommandInfo &cmdi,
                                  TByteBuffer  &bufData,
                                  TMsgSuffix   &mSuf) const
{
  assert(bufData.empty());
  
  const TUInt nPredictedDataSize=/*cmdi.nMinSize*/0+1; // End // !!!!!!
  Prepare(nPredictedDataSize);

  bufData.reserve(nPredictedDataSize);

  while(true) {
    TByte b=ReadByte(eCannotReadData);

    if (ParseSuffix(b, mSuf)) break;

    if (b==SpecByte::bDle) {
      PrepareMore(1);
      
      b=ReadByte(eCannotReadData);
    } else if (NeedDle(b)) {
      ThrowError(eUnexpectedByte);
    }
    
    bufData.Append(b);
  }
}                            

// bufData can contain partial data if function not completed
void TStationRead::ReadExt(TByte        bCmd,
                           TByteBuffer &bufData,
                           TMsgSuffix  &mSuf) const
{
  assert(bufData.empty());

  TByte bLen=ReadByte(eCannotReadLen);

  Prepare(bLen+2+1); // Data, Crc, End
  
  bufData.assign(bLen, 0);
  ReadBuf(bufData.begin_ptr(), bLen, eCannotReadData);
  
  const TWord wCrc=ReadWord(eCannotReadCrc);
  if (!CheckCrc(bCmd, bLen, bufData, wCrc)) ThrowError(eInvalidCrc);
  
  const TByte bLast=ReadByte(eCannotReadEnd);
  if (!ParseSuffix(bLast, mSuf)) ThrowError(eInvalidFrameEnd);
}

TCmdCode TStationRead::ReadCmdByte(OMsgFrame &omf) const
{
  Prepare(3); // Stx, Cmd, + 1 byte

  TByte bCur=SkipUntil();

  bool bWakeUp=false;
  if (bCur==SpecByte::bWup) {
    if (m_bAllowWakeUp) {
      bWakeUp=true;
      bCur=ReadByte(eCannotReadByte);
    } else ThrowError(eUnexpectedByte);
  }

  int nStxCount=0;
  if (bCur==SpecByte::bStx) {
    ++nStxCount;
    bCur=ReadByte(eCannotReadByte);
  } else {
    return Ccc(bCur);
  }

  if (bCur==SpecByte::bStx) {
    if (m_bAllowDblStx) {
      ++nStxCount;
      bCur=ReadByte(eCannotReadByte);
    } else ThrowError(eStxUnexpected);
  }
  
  if (bWakeUp || nStxCount>0) {
    TMsgPrefix &Prefix=omf.Set().Prefix;
    Prefix.bWakeUp=bWakeUp;
    Prefix.nStx=nStxCount;
  }
  
  return Ccc(bCur);
}

void TStationRead::Read(TStMessage &sm)
{
  OMsgFrame omf;
  const TCmdCode cc=ReadCmdByte(omf);
  const TCommandInfo &cmdi=GetCommandInfoRef(cc);
  
  if (cmdi.ct==ctLite) {
    if (omf) ThrowError(eBareCommandHasFrame);
  } else {  
    TByteBuffer buf;
    
    if (!omf) ThrowError(eCommandShouldHaveFrame);

    if (cmdi.ct==ctBase) {
      ReadBase(cmdi, buf, omf->Suffix);
    } else if (cmdi.ct==ctExt) {
      ReadExt(cc, buf, omf->Suffix);
    } else {
      ThrowError(eUnknownCommand);
    }

    sm.SwapBuf(buf);
    sm.Frame=*omf;
  }

  sm.cc=cc;
}

////////////////////////////////////////////////////////////////////////////////
bool StationRead(IIStream   &is,
                 TStMessage &smr,
                 TErrList   *pErr)
{
  TStationRead sr(is, pErr);
  
  try {
    sr.Read(smr);
  } 
  catch (TExcept) {
    return false;
  }
  
  return true;
}                 

