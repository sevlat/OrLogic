// SeVlaT, 09.06.2013
#include "StdAfx.h"

#include "DumpJob.h"

#include "Utils.h"

#include <SiLib/BsMemory.h>

#include <SiLib/Ext/CmdsPerform.h>

#ifdef _DEBUG
const int c_nBsMemSize=128*128;
#else  // _DEBUG
const int c_nBsMemSize=128*1024;
#endif // _DEBUG

////////////////////////////////////////////////////////////////////////////////
TDumpJobInfo::TDumpJobInfo(const TBsInfo &absi, bool abMaster)
 : bsi(absi),
   bMaster(abMaster),
   nCurAddr(0x100),
   nMaxAddr(c_nBsMemSize),
   Status(sOk),
   JobState(jsStart),
   MainState(msReading),
   m_TimeEstimator(GetSysTime(),
                   milliseconds(5000),
                   milliseconds(30000),
                   milliseconds(300),
                   milliseconds(1*60*60*1000))
{
}

std::wstring TDumpJobInfo::GetStatusText() const
{
  switch (MainState) {
    case msReading:
      if (Status==sAbort) return L"Aborting...";
      if (Status==sError) return L"Error.";
      if (Status==sOk)    return L"Reading";
      break;

    case msSaving:
      if (Status==sAbort) return L"Aborting. Saving...";
      if (Status==sError) return L"Error.";
      if (Status==sOk)    return L"Saving";
      break;

    case msEnd:
      if (Status==sAbort) return L"Aborted";
      if (Status==sError) return L"Stopped on error";
      if (Status==sOk)    return L"Done. OK.";
      break;
  }
  
  return L"???";
}

////////////////////////////////////////////////////////////////////////////////
TDumpJob::TDumpJob(bool abMaster, const TBsInfo &absi)
 : TDumpJobInfo(absi, abMaster)
{
  m_TimeEstimator.Reset(GetSysTime(), nCurAddr);
}

void TDumpJob::Do(TCmdTransceiver &Tr, TErrList *pErr)
{
  Tick();

  switch (MainState) {
    case msReading:
      DoNotSaved(Tr, pErr);
      break;

    case msSaving:
      DoSaving(Tr, pErr);
      break;

    case msEnd:
      DoEnd(Tr, pErr);
      break;
  }

  Tick();
}

void TDumpJob::DoEnd(TCmdTransceiver &Tr, TErrList *pErr)
{
}

void TDumpJob::DoNotSaved(TCmdTransceiver &Tr, TErrList *pErr)
{
  switch (JobState) {
    case jsStart:
      DoStart(Tr, pErr);
      break;

    case jsReadSysMem:
      DoReadingSysMem(Tr, pErr);
      break;

    case jsReadBckMem:
      DoReadingBckMem(Tr, pErr);
      break;
  }
}

void TDumpJob::DoSaving(TCmdTransceiver &Tr, TErrList *pErr)
{
  if (!MemBuf.Empty()) {
    std::string sFileName=GetDumpFileName(bsi.oSerNum.Get(TBsSerNum()).Get());

    std::ofstream fDump(sFileName.c_str(), std::ios::binary);
    MemBuf.Save(fDump);
  }

  MainState=msEnd;
}

void TDumpJob::DoStart(TCmdTransceiver &Tr, TErrList *pErr)
{
  if (Status==sAbort) {
    MainState=msEnd;
    return;
  }

  TPrefixParams PP(true, 1);
  TTransceiveParams TP(&PP, 2, 7);

  TCmdsPerf cmdperf(Tr, TP, pErr);

  TCprSetMaSlaveE cprSmsE;
  cprSmsE=cmdperf.SetMaSlaveE(bMaster);
  if (!cprSmsE) {
    MainState=msEnd;
    Status=sError;
    return;
  }

  JobState=jsReadSysMem;
}

void TDumpJob::DoReadingSysMem(TCmdTransceiver &Tr, TErrList *pErr)
{
  if (Status==sAbort) {
    MainState=msEnd;
    return;
  }

  TPrefixParams PP(true, 1);
  TTransceiveParams TP(&PP, 2, 7);

  TCmdsPerf cmdperf(Tr, TP, pErr);

  TCprGetSysValueE cprGsvE;
  cprGsvE=cmdperf.GetSysValueE(0, 0x80);
  if (!cprGsvE) {
    MainState=msEnd;
    Status=sError;
    return;
  }

  const CmdbBGetSysValueE *pCmd=cprGsvE.m_BCmds.Get();
  if (!pCmd) {
    MainState=msEnd;
    Status=sError;
    return;
  }

  if (bsi.oCode &&
      bsi.oCode->Get()!=pCmd->wCN) {
    MainState=msEnd;
    Status=sError;
    return;
  }

  MemBuf.Add(TBiasedByteBuffer(pCmd->data, pCmd->bAddr));

  JobState=jsReadBckMem;
};

void TDumpJob::DoReadingBckMem(TCmdTransceiver &Tr, TErrList *pErr)
{
  const int nBlockSize=128;

  if (Status==sAbort) {
    MainState=msSaving;
    return;
  }

  if (nCurAddr>=nMaxAddr) {
    JobState=jsEnd;
    MainState=msSaving;
    return;
  }

  TPrefixParams PP(true, 1);
  TTransceiveParams TP(&PP, 2, 7);

  TCmdsPerf cmdperf(Tr, TP, pErr);

  MemBuf.AddEmpty(nCurAddr, nBlockSize);

  TCprGetBckDataE cprGbdE;
  cprGbdE=cmdperf.GetBckDataE(nCurAddr, nBlockSize);
  nCurAddr+=nBlockSize;
  if (cprGbdE) {
    const CmdbBGetBckDataE *pCmd=cprGbdE.m_BCmds.Get();
    if (pCmd) {
      if (bsi.oCode &&
          bsi.oCode->Get()!=pCmd->wCN) {
        MainState=msSaving;
        Status=sError;
        return;
      }

      MemBuf.Add(TBiasedByteBuffer(pCmd->data, pCmd->dwAddr));
    }
  } else {
    MainState=msSaving;
    Status=sError;
    return;
  }
}

void TDumpJob::Tick()
{
  m_TimeEstimator.Tick(GetSysTime(), nCurAddr, nMaxAddr);
}

void TDumpJob::Abort()
{
  Status=sAbort;
}
