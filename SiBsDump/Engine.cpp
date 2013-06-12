// SeVlaT, 07.05.2013
#include "StdAfx.h"

#include "Engine.h"

#include "Utils.h"

#include <SiLib/BsMemory.h>

#include <SiLib/Ext/CmdsPerform.h>

TEngine::TEngine(void)
 : m_cp(false),
   m_StreamLogger(GetLogFileName(), m_cp.get(), m_cp.get()),
   m_Queue(),
   m_Transceiver(m_Queue, m_StreamLogger, m_StreamLogger),
   m_obsMasterConnect(),
   m_qobsMasterConnect(m_obsMasterConnect),
   m_bAutoDetectMasterEnabled(false),
   m_bAutoDetectSlaveEnabled(false),
   m_bAutoDumpSlaveEnabled(false),
   m_bDoing(false)
{
}

void TEngine::Connect(const TString &sPort)
{
  IComPort &cp=m_cp.get();
  const bool bResOpen=m_cp.get().Open(sPort, &m_Err);
  const bool bSetRate=m_cp.get().SetBaudRate(38400, &m_Err);

  UpdateState();
}

void TEngine::Disconnect()
{
  m_cp.get().Close(0);

  UpdateState();
}

void TEngine::Detect(bool bMaster)
{
  TPrefixParams PP1(true, 1);
  TPrefixParams PP2(true, 2);
  
  TTransceiveParams TP1(&PP1, 2, 7);
  TTransceiveParams TP2(&PP2, 2, 7);

  TCmdsPerf cmdperfMst(m_Transceiver.Tr, TP1, &m_Err);

  TCprSetMaSlaveE cprSmsE;
  cprSmsE=cmdperfMst.SetMaSlaveE(bMaster);
  m_qobsMasterConnect(m_Queue);
  if (!cprSmsE) {
    m_obsMasterConnect.ObscureAll(None); //!!!!! temporary 
    m_cmdsGsveMaster=0;
    m_cmdsGsveSlave=0;
    UpdateState();
    return;
  }

  TCmdsPerf cmdperfTrg(m_Transceiver.Tr, (bMaster? TP1: TP2), &m_Err);

  TCprGetSysValueE cprGsvE;
  cprGsvE=cmdperfTrg.GetSysValueE(0, 0x80);
  m_qobsMasterConnect(m_Queue);

  if (bMaster) m_cmdsGsveMaster=cprGsvE.m_BCmds;
          else m_cmdsGsveSlave =cprGsvE.m_BCmds;

  UpdateState();
}

void TEngine::DetectMaster()
{
  Detect(true);
}

void TEngine::DetectSlave()
{
  Detect(false);
}

TBsInfo GetBsInfo(const TBsConnectData    &bcd,
                  const CmdsBGetSysValueE &cmdsBGsve)
{
  TBsInfo bsi;

  if (bcd.cvBsCodeW.oVal) {
    bsi.oCode=TBsCode(bcd.cvBsCodeW.oVal->Get());
  } else if (bcd.cvBsCodeB.oVal) {
    bsi.oCode=TBsCode(bcd.cvBsCodeB.oVal->Get());
  }

  if (bcd.cvBsSerNum.oVal) {
    bsi.oSerNum=bcd.cvBsSerNum.oVal;
  }

  if (bcd.cvBsMode.oVal) {
    bsi.oMode=bcd.cvBsMode.oVal;
  }

  if (bcd.cvBsModel.oVal) {
    bsi.oModel=bcd.cvBsModel.oVal;
  }

  if (cmdsBGsve) {
    const TBsMemoryMaskNew bsmm;

    const TBsMemory bsMem(cmdsBGsve->data, cmdsBGsve->bAddr);
    bsi.onBackupPtr=OptFromOpt<TUInt>(bsMem.Get(bsmm.bbaBackupPtr));
    bsi.obOverflow=OptFromOpt<bool>(bsMem.Get(bsmm.bbaOverflow));
  }

  return bsi;
}

void TEngine::UpdateState()
{
  const IComPort &cp=m_cp.get();
  if (cp.Valid(0)) {
    m_State.osConnected=cp.GetPortName();
  } else {
    m_State.osConnected=None;
  }

  {
    const TMasterConnectData &mcd=m_obsMasterConnect.MasterConnectData();
    if (mcd.cvbPresent.oVal &&
        m_cmdsGsveMaster) {    //!!!!! temporary 
      m_State.obsiMaster=GetBsInfo(mcd, m_cmdsGsveMaster);
    } else {
      m_State.obsiMaster=None;
    }
  }

  {
    const TSlaveConnectData &mcd=m_obsMasterConnect.SlaveConnectData();
    if (mcd.cvbPresent.oVal &&
        m_cmdsGsveSlave) {
      m_State.obsiSlave=GetBsInfo(mcd, m_cmdsGsveSlave);
    } else {
      m_State.obsiSlave=None;
    }
  }
}

void TEngine::Abort()
{
  if (IsReading()) m_shpJob->Abort();
}

bool TEngine::IsReading() const
{
  return m_shpJob && (m_shpJob->MainState==TDumpJobInfo::msReading);
}

bool TEngine::IsIdle() const
{
  return !m_shpJob || (m_shpJob->MainState==TDumpJobInfo::msEnd);
}

bool TEngine::CanStartDump(const OBsInfo &obsi) const
{
  return IsIdle() && obsi;
}

const OBsInfo& TEngine::BsInfo(bool bMaster) const
{
  if (bMaster) return m_State.obsiMaster;
               return m_State.obsiSlave;
}

void TEngine::StartDump(bool bMaster)
{
  const OBsInfo &obsi=BsInfo(bMaster);
  if (!CanStartDump(obsi)) return;

  m_shpJob.reset(new TDumpJob(bMaster, *obsi));
}

bool TEngine::CanStartDump(bool bMaster) const
{
  return CanStartDump(BsInfo(bMaster));
}

void TEngine::SetParams(bool bAutoDetectMasterEnabled,
                        bool bAutoDetectSlaveEnabled,
                        bool bAutoDumpSlaveEnabled)
{
  m_bAutoDetectMasterEnabled=bAutoDetectMasterEnabled;
  m_bAutoDetectSlaveEnabled =bAutoDetectSlaveEnabled;
  m_bAutoDumpSlaveEnabled   =bAutoDumpSlaveEnabled;
}

bool TEngine::DoJob()
{
  if (IsIdle()) return false;

  m_shpJob->Do(m_Transceiver.Tr, &m_Err);
  m_qobsMasterConnect(m_Queue);

  return true;
}

bool TEngine::DoAutoDetectMaster()
{
  if (!m_bAutoDetectMasterEnabled) return false;

  if (!IsIdle()) return false;
  if (m_State.obsiMaster) return false;

  DetectMaster();

  return true;
}

bool TEngine::DoAutoDetectSlave()
{
  if (!m_bAutoDetectSlaveEnabled) return false;

  if (!IsIdle()) return false;
  if (m_State.obsiSlave) return false;

  DetectSlave();

  return true;
}

bool TEngine::DoAutoDumpSlave()
{
  if (!m_bAutoDumpSlaveEnabled) return false;

  if (!IsIdle()) return false;
  if (!m_State.obsiSlave) return false;

//  StartDump(false, m_State.obsiSlave);
// Check previous dumped slave station
  return false;
}

bool TEngine::Do()
{
  if (m_bDoing) return false;
  const TFlag Flag(m_bDoing);

  DoJob() ||
  DoAutoDetectMaster() ||
  DoAutoDetectSlave() ||
  DoAutoDumpSlave();

  UpdateState();

  return true;
}
