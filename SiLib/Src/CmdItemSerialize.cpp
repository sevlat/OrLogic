// SeVlaT, 16.08.2012
#include "StdAfx.h"

#include "../CmdItemSerialize.h"

#include "../Stream.h"
#include "../Errors.h"

namespace NCmdItemSerializeErrors {
  
  typedef TErrorDescription<TErrorCode, eLast, 200> TErrorDescr;

  static void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }

}

using namespace NCmdItemSerializeErrors;

////////////////////////////////////////////////////////////////////////////////
bool TISerializer::Bool(TByte       bTrue,
                        TByte       bFalse,
                        bool       &b,
                        TErrorCode  ec) const
{
  TByte bByte=0;
  if (!NStreamUtils::Get1Byte(m_is, bByte, m_pErr)) return false;
  
  if (bByte==bTrue)  { b=true;  return true; }
  if (bByte==bFalse) { b=false; return true; }

  PushError(ec);

  return false;
}

bool TOSerializer::Bool(TByte bTrue,
                        TByte bFalse,
                        bool  b) const
{
  const TByte bByte=b? bTrue: bFalse;
  return NStreamUtils::Put1Byte(m_os, bByte, m_pErr);
}

TCountSerializer::TCountSerializer(int &nMinSize, int &nMaxSize)
 : m_nMinSize(nMinSize),
   m_nMaxSize(nMaxSize)
{
}

void TCountSerializer::Bool() const
{
  Add(1);
}

void TCountSerializer::Add(int n) const
{
  m_nMinSize+=n;
  m_nMaxSize+=n;
}

void TCountSerializer::Add(int nMin, int nMax) const
{
  m_nMinSize+=nMin;
  m_nMaxSize+=nMax;
}


////////////////////////////////////////////////////////////////////////////////
bool TISerializer::B1Byte(TByte &b) const
{
  return NStreamUtils::Get1Byte(m_is, b, m_pErr);
}

bool TOSerializer::B1Byte(TByte b) const
{
  return NStreamUtils::Put1Byte(m_os, b, m_pErr);
}

void TCountSerializer::B1Byte() const
{
  Add(1);
}

////////////////////////////////////////////////////////////////////////////////
bool TISerializer::B2ByteBE(TWord &w) const
{
  return NStreamUtils::Get2ByteBE(m_is, w, m_pErr);
}

bool TOSerializer::B2ByteBE(TWord w) const
{
  return NStreamUtils::Put2ByteBE(m_os, w, m_pErr);
}

void TCountSerializer::B2ByteBE() const
{
  Add(2);
}

////////////////////////////////////////////////////////////////////////////////
bool TISerializer::B3ByteBE(TDWord &dw) const
{
  return NStreamUtils::Get3ByteBE(m_is, dw, m_pErr);
}

bool TOSerializer::B3ByteBE(TDWord dw) const
{
  return NStreamUtils::Put3ByteBE(m_os, dw, m_pErr);
}

void TCountSerializer::B3ByteBE() const
{
  Add(3);
}

////////////////////////////////////////////////////////////////////////////////
bool TISerializer::B4ByteBE(TDWord &dw) const
{
  return NStreamUtils::Get4ByteBE(m_is, dw, m_pErr);
}

bool TOSerializer::B4ByteBE(TDWord dw) const
{
  return NStreamUtils::Put4ByteBE(m_os, dw, m_pErr);
}

void TCountSerializer::B4ByteBE() const
{
  Add(4);
}

////////////////////////////////////////////////////////////////////////////////
namespace {
  const TByte c_bMasterTag='M';
  const TByte c_bSlaveTag ='S';
}

bool TISerializer::MaSlave(bool &bMaster) const
{
  return Bool(c_bMasterTag, c_bSlaveTag, bMaster, eIncorrectMaSlaveData);
}

bool TOSerializer::MaSlave(bool bMaster) const
{
  return Bool(c_bMasterTag, c_bSlaveTag, bMaster);
}

void TCountSerializer::MaSlave() const
{
  Bool();
}

////////////////////////////////////////////////////////////////////////////////
namespace {
  const TByte c_bInTag ='I';
  const TByte c_bOutTag='O';
}

bool TISerializer::InOut(bool &bIn) const
{
  return Bool(c_bInTag, c_bOutTag, bIn, eIncorrectInOutData);
}

bool TOSerializer::InOut(bool bIn) const
{
  return Bool(c_bInTag, c_bOutTag, bIn);
}

void TCountSerializer::InOut() const
{
  Bool();
}

////////////////////////////////////////////////////////////////////////////////
namespace {
  const TByte c_bHighRateTag=1;
  const TByte c_bLoRageTag  =0;
}

bool TISerializer::BaudRate(bool &bHigh) const
{
  return Bool(c_bHighRateTag, c_bLoRageTag, bHigh, eIncorrectBaudRateData);
}

bool TOSerializer::BaudRate(bool bHigh) const
{
  return Bool(c_bHighRateTag, c_bLoRageTag, bHigh);
}

void TCountSerializer::BaudRate() const
{
  Bool();
}

////////////////////////////////////////////////////////////////////////////////
namespace {
  enum {
    c_nTimeBufSize=6
  };
}

bool TISerializer::Time(TStationTime &st) const
{
  hftl::TByteArray<c_nTimeBufSize> bBuf(0);
  bBuf.assign(0);

  if (!NStreamUtils::GetBuf(m_is, bBuf, m_pErr)) return false;
  
  st.bYear      =bBuf.Byte1<0>();
  st.bMonth     =bBuf.Byte1<1>();
  st.bDay       =bBuf.Byte1<2>();
  st.bWeekMidDay=bBuf.Byte1<3>();
  st.wDaySecond =bBuf.Byte2<4, BoBe>();

  return true;
}

bool TOSerializer::Time(const TStationTime &st) const
{
  hftl::TByteArray<c_nTimeBufSize> bBuf(0);
  bBuf.assign(0);

  bBuf.Set1<0>(st.bYear);
  bBuf.Set1<1>(st.bMonth);
  bBuf.Set1<2>(st.bDay);
  bBuf.Set1<3>(st.bWeekMidDay);
  bBuf.Set2<4, BoBe>(st.wDaySecond);

  return NStreamUtils::PutBuf(m_os, bBuf, m_pErr);
}

void TCountSerializer::Time() const
{
  Add(c_nTimeBufSize);
}

////////////////////////////////////////////////////////////////////////////////
namespace {
  enum {
    c_nTimeSSBufSize=7
  };
}

bool TISerializer::TimeSS(TStationTimeSS &st) const
{
  hftl::TByteArray<c_nTimeSSBufSize> bBuf(0);
  bBuf.assign(0);

  if (!NStreamUtils::GetBuf(m_is, bBuf, m_pErr)) return false;
  
  st.bYear      =bBuf.Byte1<0>();
  st.bMonth     =bBuf.Byte1<1>();
  st.bDay       =bBuf.Byte1<2>();
  st.bWeekMidDay=bBuf.Byte1<3>();
  st.wDaySecond =bBuf.Byte2<4, BoBe>();
  st.bSubSec    =bBuf.Byte1<6>();
  
  return true;
}

bool TOSerializer::TimeSS(const TStationTimeSS &st) const
{
  hftl::TByteArray<c_nTimeSSBufSize> bBuf(0);
  bBuf.assign(0);

  bBuf.Set1<0>(st.bYear);
  bBuf.Set1<1>(st.bMonth);
  bBuf.Set1<2>(st.bDay);
  bBuf.Set1<3>(st.bWeekMidDay);
  bBuf.Set2<4, BoBe>(st.wDaySecond);
  bBuf.Set1<6>(st.bSubSec);

  return NStreamUtils::PutBuf(m_os, bBuf, m_pErr);
}

void TCountSerializer::TimeSS() const
{
  Add(c_nTimeSSBufSize);
}

////////////////////////////////////////////////////////////////////////////////
bool TISerializer::Buffer(TByteBuffer &buf) const
{
  return NStreamUtils::GetBuf(m_is, buf, m_pErr);
}

bool TOSerializer::Buffer(const TByteBuffer &buf) const
{
  return NStreamUtils::PutBuf(m_os, buf, m_pErr);
}

void TCountSerializer::Buffer() const
{
  Add(0, 256); //!!!!!!
}

////////////////////////////////////////////////////////////////////////////////
void TSerializerErrorBase::PushError(TErrorCode ec) const
{
  NCmdItemSerializeErrors::PushError(m_pErr, ec);
}
