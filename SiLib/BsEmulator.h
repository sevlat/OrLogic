#ifndef BsEmulator_h_already_included__10_04_2013__11909E80
#define BsEmulator_h_already_included__10_04_2013__11909E80
//
// SeVlaT, 10.04.2013
//

#include "PortEmulator.h"

#include "ProtScanner.h"
#include "CmdVisitor.h"

#include "BsTypes.h"

class TBsEmulator: public TPortEmulator,
                   private IFCmdVisitor,
                   private IFRawPktVisitor {
 public:
  TBsEmulator();

 private:
  virtual void OnWrite();
  
 private:  
  virtual void operator ()(const CmdbFBeep &cmd);
                                    
  virtual void operator ()(const CmdbFSetMaSlaveB &cmd);
  virtual void operator ()(const CmdbFSetMaSlaveE &cmd);
                                    
  virtual void operator ()(const CmdbFGetMaSlaveB &cmd);
  virtual void operator ()(const CmdbFGetMaSlaveE &cmd);
                                    
  virtual void operator ()(const CmdbFSetBaudRateB &cmd);
  virtual void operator ()(const CmdbFSetBaudRateE &cmd);
                                    
  virtual void operator ()(const CmdbFGetTimeB &cmd);
  virtual void operator ()(const CmdbFGetTimeE &cmd);
                                    
  virtual void operator ()(const CmdbFSetTimeB &cmd);
  virtual void operator ()(const CmdbFSetTimeE &cmd);
                                    
  virtual void operator ()(const CmdbFGetSysValueE &cmd);
                                    
  virtual void operator ()(const CmdbFGetBckDataE &cmd);

  virtual void operator ()(const CmdbFBeepE &cmd);
  
  virtual void operator ()(const CmdbFTurnOffB &cmd);

 private:  
  virtual void operator ()(const TProtCmdPacket &pkt, TagFwd, CauseCmdUnparseable);
  virtual void operator ()(const TProtCmdPacket &pkt, TagFwd, CauseCmdUnfamiliar) ;
  
 private:
  TDateTimeSS GetTime() const;
  void SetTime(const TDateTimeSS &dt);
  
 private:  
  bool ScanNext(TByte b, bool &bEaten) {
    return ProtScanNext(b, bEaten, m_pkt, m_State, m_Data, m_Counts);
  }
  
  void Received();
  bool TryNext(TByte b);
  void Set(TByte b);

  void Return(const TProtCmdPacket &pkt);

 private:
  TProtCmdPacket     m_pkt;
  
  TProtScannerState  m_State;
  TProtScannerData   m_Data;
  TProtScannerCounts m_Counts;

 private:
  TMsgFrame m_mf;
  
  TBsCode m_bsc;
  bool m_bMaster;
  bool m_bHighSpeed;
};

#endif
