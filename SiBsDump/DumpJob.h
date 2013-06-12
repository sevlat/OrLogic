#ifndef DumpJob_h_already_included__09_06_2013__5FA3D10
#define DumpJob_h_already_included__09_06_2013__5FA3D10
//
// SeVlaT, 09.06.2013
//

#include "Types.h"
#include "TimeEstimate.h"

#include <SiLib/Ext/CmdTransceive.h>

#include <SiLib/BsMemBuf.h>

struct TDumpJobInfo {
  TBsInfo      bsi;
  bool         bMaster;
  int          nCurAddr;
  int          nMaxAddr;

  TTimeEstimator m_TimeEstimator;

  enum TStatus {
    sOk,
    sAbort,
    sError
  };

  enum TJobState {
    jsStart,
    jsReadSysMem,
    jsReadBckMem,
    jsEnd,
  };

  enum TMainState {
    msReading,
    msSaving,
    msEnd,
  };

  TStatus     Status;
  TJobState   JobState;
  TMainState  MainState;

  std::wstring GetStatusText() const;

  TDumpJobInfo(const TBsInfo &absi, bool abMaster);
};

////////////////////////////////////////////////////////////////////////////////
struct TDumpJob: public TDumpJobInfo {
  TBsMemBuffer MemBuf;
  scoped_ptr<TCmdsPerformer> scpPerformer;

  TDumpJob(bool abMaster, const TBsInfo &absi);

 public:
  void Do(TCmdTransceiver &Tr, TErrList *pErr);

  void Abort();

 private:
  void Tick();

 private:
  void DoEnd(TCmdTransceiver &Tr, TErrList *pErr);
  void DoSaving(TCmdTransceiver &Tr, TErrList *pErr);
  void DoNotSaved(TCmdTransceiver &Tr, TErrList *pErr);

 private:
  void DoStart(TCmdTransceiver &Tr, TErrList *pErr);
  void DoReadingSysMem(TCmdTransceiver &Tr, TErrList *pErr);
  void DoReadingBckMem(TCmdTransceiver &Tr, TErrList *pErr);
};

typedef TCmdShpTraits_Cmd<CmdbBGetSysValueE>::ShpCmd CmdsBGetSysValueE;

#endif
