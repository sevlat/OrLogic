#ifndef Engine_h_already_included__07_05_2013__2AA2938
#define Engine_h_already_included__07_05_2013__2AA2938
//
// SeVlaT, 07.05.2013
//

#include "Types.h"
#include "DumpJob.h"

#include <SiLib/BsMasterConnect.h>
#include <SiLib/StreamLogger.h>

#include <SiLib/Ext/ComPortShr.h>
#include <SiLib/Ext/CmdQueue.h>

////////////////////////////////////////////////////////////////////////////////
struct TEngineState {
  OString osConnected;

  OBsInfo obsiMaster;
  OBsInfo obsiSlave;

 public:
  TEngineState() {}

 public:
  bool CanConnect()    const { return !osConnected; }
  bool CanDisconnect() const { return  osConnected; }
};

////////////////////////////////////////////////////////////////////////////////
class TEngine {
 public:
  TEngine();

 public:
  void Connect(const TString &sPort);
  void Disconnect();

 public:
  void DetectMaster();
  void DetectSlave();

  bool CanStartDump(bool bMaster) const;
  void StartDump(bool bMaster);

 public:
  void Abort();

 public:
  const OBsInfo& MBsInfo() const;
  const OBsInfo& SBsInfo() const;

 public:
  bool IsReading() const;
  bool IsIdle() const;

 public:
  bool Do();

 private:
  bool CanStartDump(const OBsInfo &obsi) const;
  const OBsInfo& BsInfo(bool bMaster) const;

 private:
  void Detect(bool bMaster);
  void StartDump(bool bMaster, const OBsInfo obsi);

  bool DoJob();
  bool DoAutoDetectMaster();
  bool DoAutoDetectSlave();
  bool DoAutoDumpSlave();

 public:
  const TEngineState& State() const { return m_State; }

  const TDumpJob* Job()  const { return m_shpJob.get(); }

 public:
  void SetParams(bool bAutoDetectMasterEnabled,
                 bool bAutoDetectSlaveEnabled,
                 bool bAutoDumpSlaveEnabled);

 private:
  void UpdateState();

 private:
  TEngineState m_State;

 private:
  TErrList m_Err;

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
  shared_ptr<TDumpJob> m_shpJob;

 private:
  CmdsBGetSysValueE m_cmdsGsveMaster;
  CmdsBGetSysValueE m_cmdsGsveSlave;
};

#endif
