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

void TEngine::DetectMaster()
{
  TCmdsPerf cmdperf(m_Transceiver.Tr, &m_Err);
  
  TCprSetMaSlaveE cprSmsE;
  cprSmsE=cmdperf.SetMaSlaveE(true);
  m_qobsMasterConnect(m_Queue);
  
  TCprGetSysValueE cprGsvE;
  cprGsvE=cmdperf.GetSysValueE(0, 0x80);
  m_qobsMasterConnect(m_Queue);
  m_cmdsGsveMaster=cprGsvE.m_BCmds;
  
  UpdateState();  
}

void TEngine::DetectSlave()
{
  TCmdsPerf cmdperf(m_Transceiver.Tr, &m_Err);
  
  TCprSetMaSlaveE cprSmsE;
  cprSmsE=cmdperf.SetMaSlaveE(false);
  m_qobsMasterConnect(m_Queue);
  
  TCprGetSysValueE cprGsvE;
  cprGsvE=cmdperf.GetSysValueE(0, 0x80);
  m_qobsMasterConnect(m_Queue);
  m_cmdsGsveSlave=cprGsvE.m_BCmds;
  
  UpdateState();
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
    if (mcd.cvbPresent.oVal) {
      m_State.obsiMaster=GetBsInfo(mcd, m_cmdsGsveMaster);
    } else {
      m_State.obsiMaster=None;
    }
  }
  
  {
    const TSlaveConnectData &mcd=m_obsMasterConnect.SlaveConnectData();
    if (mcd.cvbPresent.oVal) {
      m_State.obsiSlave=GetBsInfo(mcd, m_cmdsGsveSlave);
    } else {
      m_State.obsiSlave=None;
    }
  }

  m_State.pJobInfo=m_scpJob.get();
}

void TEngine::StartDump(bool bMaster, const OBsInfo obsi)
{
  if (m_scpJob) return;
  if (!obsi) return;
  
  m_scpJob.reset(new TDumpJob(*obsi, bMaster));
  
  const bool bStarted=m_scpJob->Start(m_Transceiver.Tr, &m_Err);
  m_qobsMasterConnect(m_Queue);

  if (!bStarted) EndJob();
}

void TEngine::DumpMaster()
{
  StartDump(true, m_State.obsiMaster);
}

void TEngine::DumpSlave()
{
  StartDump(false, m_State.obsiSlave);
}

void TEngine::EndJob()
{
  if (!m_scpJob) return;
  
  m_scpJob->Save();
  m_scpJob.reset();
}

bool TEngine::DoJob()
{
  if (!m_scpJob) return false;

  const bool bRes=m_scpJob->Do(m_Transceiver.Tr, &m_Err);
  m_qobsMasterConnect(m_Queue);

  if (!bRes) EndJob();
  return true;
}

bool TEngine::DoAutoDetectMaster()
{
  if (!m_bAutoDetectMasterEnabled) return false;
  
  if (m_scpJob) return false;
  if (m_State.obsiMaster) return false;
  
  DetectMaster();
  
  return true;
}

bool TEngine::DoAutoDetectSlave()
{
  if (!m_bAutoDetectSlaveEnabled) return false;

  if (m_scpJob) return false;
  if (m_State.obsiSlave) return false;
  
  DetectSlave();
  
  return true;
}

bool TEngine::DoAutoDumpSlave()
{
  if (!m_bAutoDumpSlaveEnabled) return false;

  if (m_scpJob) return false;
  if (m_State.obsiSlave) return false;

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

 
////////////////////////////////////////////////////////////////////////////////
TDumpJobInfo::TDumpJobInfo(const TBsInfo &absi, bool abMaster)
 : bsi(absi),
   bMaster(abMaster),
   nCurAddr(0x100),
//   nMaxAddr(128*1024) 
   nMaxAddr(128*100),
   m_TimeEstimator(GetSysTime(),
                   milliseconds(5000),
                   milliseconds(30000),
                   milliseconds(300),
                   milliseconds(1*60*60*1000))
{
}


////////////////////////////////////////////////////////////////////////////////
TDumpJob::TDumpJob(const TBsInfo &absi, bool abMaster)
 : TDumpJobInfo(absi, abMaster)
{
  m_TimeEstimator.Reset(GetSysTime(), nCurAddr);
}


bool TDumpJob::Start(TCmdTransceiver &Tr, TErrList *pErr)
{
  TCmdsPerf cmdperf(Tr, pErr);
  
  TCprSetMaSlaveE cprSmsE;
  cprSmsE=cmdperf.SetMaSlaveE(bMaster);
//  m_qobsMasterConnect(m_Queue);
  if (!cprSmsE) return false;
  
  TCprGetSysValueE cprGsvE;
  cprGsvE=cmdperf.GetSysValueE(0, 0x80);
//  m_qobsMasterConnect(m_Queue);
  if (!cprGsvE) return false;

  const CmdbBGetSysValueE *pCmd=cprGsvE.m_BCmds.Get();
  if (!pCmd) return false;

  if (bsi.oCode && 
      bsi.oCode->Get()!=pCmd->wCN) return false;

  MemBuf.Add(TBiasedByteBuffer(pCmd->data, pCmd->bAddr));
  return true;
}

bool TDumpJob::Do(TCmdTransceiver &Tr, TErrList *pErr)
{
  Tick();
  
  if (nCurAddr>=nMaxAddr) return false;

  TCmdsPerf cmdperf(Tr, pErr);
  
  int nBlockSize=128;
  
  MemBuf.AddEmpty(nCurAddr, nBlockSize);

  TCprGetBckDataE cprGbdE;
  cprGbdE=cmdperf.GetBckDataE(nCurAddr, nBlockSize);
  nCurAddr+=nBlockSize;
  if (cprGbdE) {
    const CmdbBGetBckDataE *pCmd=cprGbdE.m_BCmds.Get();
    if (pCmd) {
      if (bsi.oCode && 
          bsi.oCode->Get()!=pCmd->wCN) return false;

      MemBuf.Add(TBiasedByteBuffer(pCmd->data, pCmd->dwAddr));
    }
  }

  Tick();
  return true;
}

void TDumpJob::Tick()
{
  m_TimeEstimator.Tick(GetSysTime(), nCurAddr, nMaxAddr);
}

void TDumpJob::Save()
{
  if (MemBuf.Empty()) return;
  
  std::string sFileName=GetDumpFileName(bsi.oSerNum.Get(TBsSerNum()).Get());
  
  std::ofstream fDump(sFileName.c_str(), std::ios::binary);
  MemBuf.Save(fDump);
}
  

