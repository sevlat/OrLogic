#ifndef Engine_h_already_included__07_05_2013__2AA2938
#define Engine_h_already_included__07_05_2013__2AA2938
//
// SeVlaT, 07.05.2013
//

#include "Types.h"
#include "TimeEstimate.h"

#include <SiLib/BsMasterConnect.h>
#include <SiLib/StreamLogger.h>

#include <SiLib/Ext/ComPortShr.h>
#include <SiLib/Ext/CmdQueue.h>
#include <SiLib/Ext/CmdTransceive.h>

#include <SiLib/BsMemBuf.h>

struct TDumpJobInfo {
  TBsInfo      bsi;
  bool         bMaster;
  int          nCurAddr;
  int          nMaxAddr;
  
  TTimeEstimator m_TimeEstimator;

  TDumpJobInfo(const TBsInfo &absi, bool abMaster);
};

////////////////////////////////////////////////////////////////////////////////
struct TEngineState {
  OString osConnected;
  
  OBsInfo obsiMaster;
  OBsInfo obsiSlave;  
  
  const TDumpJobInfo *pJobInfo;
  
 public:
  TEngineState()
   : pJobInfo(0) {}
  
 public:
  bool CanConnect()    const { return !osConnected; }
  bool CanDisconnect() const { return  osConnected; }
};

////////////////////////////////////////////////////////////////////////////////
struct TDumpJob: public TDumpJobInfo {
  TBsMemBuffer MemBuf;
  scoped_ptr<TCmdsPerformer> scpPerformer;
  
  TDumpJob(const TBsInfo &absi, bool abMaster);
  
  bool Do(TCmdTransceiver &Tr, TErrList *pErr);
  bool Start(TCmdTransceiver &Tr, TErrList *pErr);
  void Save();
  void Tick();
};

typedef TCmdShpTraits_Cmd<CmdbBGetSysValueE>::ShpCmd CmdsBGetSysValueE;

////////////////////////////////////////////////////////////////////////////////
class TEngine {
 public:
  TEngine();
 
 public:
  void Connect(const TString &sPort);
  void Disconnect();
  
 public:
  void DetectMaster();
  void DumpMaster();

  void DetectSlave();
  void DumpSlave();

 public:

  void EndJob();

 public:
  const OBsInfo& MBsInfo() const;
  const OBsInfo& SBsInfo() const;

 public:
  bool Do();

 private:
  void Detect(bool bMaster);
  void StartDump(bool bMaster, const OBsInfo obsi);

  bool DoJob();
  bool DoAutoDetectMaster();
  bool DoAutoDetectSlave();
  bool DoAutoDumpSlave();

 public:
  const TEngineState& State() const { return m_State; }
  
  const TDumpJob* Job() const { return m_scpJob.get(); }
  
 public:
  void SetParams(bool bAutoDetectMasterEnabled,
                 bool bAutoDetectSlaveEnabled,
                 bool bAutoDumpSlaveEnabled);

 private:
  void UpdateState();
 
 private:
  TEngineState m_State;

 private:
  TErrList  m_Err;

 private:
  TComPortShr m_cp;
  TStreamLogger m_StreamLogger;

 private:
  TCmdQueue m_Queue;
  TCmdTransceiverEx m_Transceiver;
 
  TBsMasterConnectObs m_obsMasterConnect;
  TCmdQueueObserver<TBsMasterConnectObs> m_qobsMasterConnect;
  
 private:
  bool m_bDoing;

 private:
  bool m_bAutoDetectMasterEnabled;
  bool m_bAutoDetectSlaveEnabled;
  bool m_bAutoDumpSlaveEnabled;
  
 private:
  scoped_ptr<TDumpJob> m_scpJob;
 
 private:
  CmdsBGetSysValueE m_cmdsGsveMaster;
  CmdsBGetSysValueE m_cmdsGsveSlave;
};

#endif
