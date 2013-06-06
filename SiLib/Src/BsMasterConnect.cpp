// SeVlaT, 14.12.2012
#include "StdAfx.h"

#include "../BsMasterConnect.h"

#include "../BsMemory.h"
#include "../Bs.h"

#include "../CmdTrxInfo.h"
#include "../CmdCast.h"

void TBsConnectData::Obscure(OSysTime ot)
{
  cvbPresent.Obscure(ot, otpObscured);
  cvBsCodeB. Obscure(ot, otpObscured);
  cvBsCodeW. Obscure(ot, otpObscured);
  cvBsSerNum.Obscure(ot, otpObscured);
  cvBsMode.  Obscure(ot, otpObscured);
  cvBsModel. Obscure(ot, otpObscured);
}

void TBsConnectData::ConfirmPresent(bool bPresent, OSysTime ot)
{
  cvbPresent.Set(bPresent, ot, otpObscured);
}

void TBsConnectData::ConfirmBsCodeB(TBsCodeB bsCode, OSysTime ot)
{
  cvBsCodeB.Set(bsCode, ot, otpObscured);
}

void TBsConnectData::ConfirmBsCodeW(TBsCodeW bsCode, OSysTime ot)
{
  cvBsCodeW.Set(bsCode, ot, otpObscured);
}

void TBsConnectData::ConfirmBsSerNum(TBsSerNum bssn, OSysTime ot)
{
  cvBsSerNum.Set(bssn, ot, otpObscured);
}

void TBsConnectData::ConfirmBsMode(TBsModeRaw bsm, OSysTime ot)
{
  cvBsMode.Set(bsm, ot, otpObscured);
}

void TBsConnectData::ConfirmBsModel(TBsModelRaw bsml, OSysTime ot)
{
  cvBsModel.Set(bsml, ot, otpObscured);
}

////////////////////////////////////////////////////////////////////////////////
void TMasterConnectData::Obscure(OSysTime ot)
{
  cvbSupportHiSpeed.Obscure(ot, otpObscured);
  cvbSupportLoSpeed.Obscure(ot, otpObscured);
  cvbSupportProtBase.Obscure(ot, otpObscured);
  cvbSupportProtExt.Obscure(ot, otpObscured);
  
  TBsConnectData::Obscure(ot);
}

void TMasterConnectData::ConfirmSupportHiSpeed(bool bSupport, OSysTime ot)
{
  cvbSupportHiSpeed.Set(bSupport, ot, otpObscured);
}

void TMasterConnectData::ConfirmSupportLoSpeed(bool bSupport, OSysTime ot)
{
  cvbSupportLoSpeed.Set(bSupport, ot, otpObscured);
}

void TMasterConnectData::ConfirmSupportProtBase(bool bSupport, OSysTime ot)
{
  cvbSupportProtBase.Set(bSupport, ot, otpObscured);
}

void TMasterConnectData::ConfirmSupportProtExt(bool bSupport, OSysTime ot)
{
  cvbSupportProtExt.Set(bSupport, ot, otpObscured);
}

////////////////////////////////////////////////////////////////////////////////
void TCardConnectData::Obscure(OSysTime ot)
{
  cvbPresent.Obscure(ot, otpObscured);
  cvNum.Obscure(ot, otpObscured);
  cvModel.Obscure(ot, otpObscured);
}

void TCardConnectData::ConfirmCardPresent(TCardNum cn, OSysTime ot)
{
  cvNum.Set(cn, ot, otpObscured);
}

void TCardConnectData::ConfirmCardNum(TCardNum cn, OSysTime ot)
{
  cvNum.Set(cn, ot, otpObscured);
}

void TCardConnectData::ConfirmCardModel(TCardModel cm, OSysTime ot)
{
  cvModel.Set(cm, ot, otpObscured);
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
TBsMasterConnectObs::TBsMasterConnectObs()
{
}

void TBsMasterConnectObs::ConfirmMasterBase(OSysTime ot, TByte bCN)
{
  m_mcd.ConfirmPresent(true, ot);
  m_mcd.ConfirmSupportProtBase(true, ot);
  m_mcd.ConfirmBsCodeB(TBsCodeB(bCN), ot);
}

void TBsMasterConnectObs::ConfirmMasterExt(OSysTime ot, TWord wCN)
{
  m_mcd.ConfirmPresent(true, ot);
  m_mcd.ConfirmSupportProtExt(true, ot);
  m_mcd.ConfirmBsCodeW(TBsCodeW(wCN), ot);
}

void TBsMasterConnectObs::ConfirmBase(OSysTime ot, TByte bCN)
{
  m_mcd.ConfirmPresent(true, ot);
  m_mcd.ConfirmSupportProtBase(true, ot);
  
  if (m_cvbMasterMode.otpConfirmed &&
      m_cvbMasterMode.oVal) {
    if (*m_cvbMasterMode.oVal) {
      m_mcd.ConfirmBsCodeB(TBsCodeB(bCN), ot);
    } else {
      m_scd.ConfirmPresent(true, ot);
      m_scd.ConfirmBsCodeB(TBsCodeB(bCN), ot);
    }
  }
}

void TBsMasterConnectObs::ConfirmExt(OSysTime ot, TWord wCN)
{
  m_mcd.ConfirmPresent(true, ot);
  m_mcd.ConfirmSupportProtExt(true, ot);
  
  if (m_cvbMasterMode.otpConfirmed &&
      m_cvbMasterMode.oVal) {
    if (*m_cvbMasterMode.oVal) {
      m_mcd.ConfirmBsCodeW(TBsCodeW(wCN), ot);
    } else {
      m_scd.ConfirmPresent(true, ot);
      m_scd.ConfirmBsCodeW(TBsCodeW(wCN), ot);
    }
  }
}

void TBsMasterConnectObs::ObscureAll(OSysTime ot)
{
  m_mcd.Obscure(ot);
  m_cvbMasterMode.Obscure(ot);
}

////////////////////////////////////////////////////////////////////////////////
void TBsMasterConnectObs::OnOk(const CmdbFGetMaSlaveB &FCmd,
                                     OSysTime          otF,
                               const CmdbBGetMaSlaveB &BCmd,
                                     OSysTime          otB)
{
  m_cvbMasterMode.Set(BCmd.bMaster, otB);
  ConfirmMasterBase(otB, BCmd.bCN);
}

void TBsMasterConnectObs::OnOk(const CmdbFGetMaSlaveE &FCmd,
                                     OSysTime          otF,
                               const CmdbBGetMaSlaveE &BCmd,
                                     OSysTime          otB)
{
  m_cvbMasterMode.Set(BCmd.bMaster, otB);
  ConfirmMasterExt(otB, BCmd.wCN);
}

void TBsMasterConnectObs::OnFailed(const CmdbFGetMaSlaveB &FCmd,
                                         OSysTime          otF,
                                         TCmdxStatus       Status)
{
  ObscureAll(otF);
}

void TBsMasterConnectObs::OnFailed(const CmdbFGetMaSlaveE &FCmd,
                                         OSysTime          otF,
                                         TCmdxStatus       Status)
{
  ObscureAll(otF);
}

////////////////////////////////////////////////////////////////////////////////
// SetMaSlave
void TBsMasterConnectObs::OnOk(const CmdbFSetMaSlaveB &FCmd,
                                     OSysTime          otF,
                               const CmdbBSetMaSlaveB &BCmd,
                                     OSysTime          otB)
{
  m_cvbMasterMode.Set(BCmd.bMaster, otB);
  ConfirmMasterBase(otB, BCmd.bCN);
}

void TBsMasterConnectObs::OnOk(const CmdbFSetMaSlaveE &FCmd,
                                     OSysTime          otF,
                               const CmdbBSetMaSlaveE &BCmd,
                                     OSysTime          otB)
{
  m_cvbMasterMode.Set(BCmd.bMaster, otB);
  ConfirmMasterExt(otB, BCmd.wCN);
}

void TBsMasterConnectObs::OnFailed(const CmdbFSetMaSlaveB &FCmd,
                                         OSysTime          otF,
                                         TCmdxStatus       Status)
{
  ObscureAll(otF);
}

void TBsMasterConnectObs::OnFailed(const CmdbFSetMaSlaveE &FCmd,
                                         OSysTime          otF,
                                         TCmdxStatus       Status)
{
  ObscureAll(otF);
}

////////////////////////////////////////////////////////////////////////////////
void TBsMasterConnectObs::OnOk(const CmdbFGetTimeB &FCmd,
                                     OSysTime       otF,
                               const CmdbBGetTimeB &BCmd,
                                     OSysTime       otB)
{
  ConfirmBase(otB, BCmd.bCN);
}

void TBsMasterConnectObs::OnOk(const CmdbFGetTimeE &FCmd,
                                     OSysTime       otF,
                               const CmdbBGetTimeE &BCmd,
                                     OSysTime       otB)
{
  ConfirmExt(otB, BCmd.wCN);
}

void TBsMasterConnectObs::OnFailed(const CmdbFGetTimeB &FCmd,
                                         OSysTime       otF,
                                         TCmdxStatus    Status)
{
  ObscureAll(otF);
}

void TBsMasterConnectObs::OnFailed(const CmdbFGetTimeE &FCmd,
                                         OSysTime       otF,
                                         TCmdxStatus    Status)
{
  ObscureAll(otF);
}

////////////////////////////////////////////////////////////////////////////////
void TBsMasterConnectObs::OnOk(const CmdbFSetTimeB &FCmd,
                                     OSysTime       otF,
                               const CmdbBSetTimeB &BCmd,
                                     OSysTime       otB)
{
  ConfirmBase(otB, BCmd.bCN);
}

void TBsMasterConnectObs::OnOk(const CmdbFSetTimeE &FCmd,
                                     OSysTime       otF,
                               const CmdbBSetTimeE &BCmd,
                                     OSysTime       otB)
{
  ConfirmExt(otB, BCmd.wCN);
}

void TBsMasterConnectObs::OnFailed(const CmdbFSetTimeB &FCmd,
                                         OSysTime       otF,
                                         TCmdxStatus    Status)
{
  ObscureAll(otF);
}

void TBsMasterConnectObs::OnFailed(const CmdbFSetTimeE &FCmd,
                                         OSysTime       otF,
                                         TCmdxStatus    Status)
{
  ObscureAll(otF);
}
                                         
////////////////////////////////////////////////////////////////////////////////
void TBsMasterConnectObs::OnOk(const CmdbFGetSysValueE &FCmd,
                                     OSysTime           otF,
                               const CmdbBGetSysValueE &BCmd,
                                     OSysTime           otB)
{
  m_mcd.ConfirmPresent(true, otB);
  m_mcd.ConfirmSupportProtExt(true, otB);
  
  TBsMemoryMaskNew bsmm;
  
  if (m_cvbMasterMode.otpConfirmed &&
      m_cvbMasterMode.oVal) {
    const TBsMemory bsMem(BCmd.data, BCmd.bAddr);
    
    const ODWord odwSn  =bsMem.Get(bsmm.bbaSerNum);
    const OByte  obMode =bsMem.Get(bsmm.bbaMode);
    const OWord  owModel=bsMem.Get(bsmm.bbaModel);

    if (*m_cvbMasterMode.oVal) {
      m_mcd.ConfirmBsCodeW(TBsCodeW(BCmd.wCN), otB);
      if (odwSn)   m_mcd.ConfirmBsSerNum(TBsSerNum(*odwSn), otB);
      if (obMode)  m_mcd.ConfirmBsMode(TBsModeRaw(BsModeFromByte(*obMode), *obMode), otB);
      if (owModel) m_mcd.ConfirmBsModel(TBsModelRaw(BsModelFromWord(*owModel), *owModel), otB);
    } else {
      m_scd.ConfirmPresent(true, otB);
      m_scd.ConfirmBsCodeW(TBsCodeW(BCmd.wCN), otB);
      if (odwSn)   m_scd.ConfirmBsSerNum(TBsSerNum(*odwSn), otB);
      if (obMode)  m_scd.ConfirmBsMode(TBsModeRaw(BsModeFromByte(*obMode), *obMode), otB);
      if (owModel) m_scd.ConfirmBsModel(TBsModelRaw(BsModelFromWord(*owModel), *owModel), otB);
    }
  }
}

void TBsMasterConnectObs::OnFailed(const CmdbFGetSysValueE &FCmd,
                                         OSysTime           otB,
                                         TCmdxStatus        Status)
{
}

////////////////////////////////////////////////////////////////////////////////
void TBsMasterConnectObs::OnStrange(const ICmdExch &cmdx)
{
}





