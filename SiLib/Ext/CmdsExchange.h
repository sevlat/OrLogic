#ifndef CmdsExchange_h_already_included__02_04_2013__A6C08E0
#define CmdsExchange_h_already_included__02_04_2013__A6C08E0
//
// SeVlaT, 02.04.2013
//

#include "CmdShpObject.h"

#include "../CmdExchange.h"
#include "../CmdTrxInfo.h"

struct TFCmdTx {
  ShpFCmdObject shpCmd;
  TCmdTxInfo    cti;
  
  TFCmdTx() {}

  explicit TFCmdTx(ShpFCmdObject ashpCmd)
   : shpCmd(ashpCmd) {}

  TFCmdTx(ShpFCmdObject ashpCmd, const TCmdTxInfo &acti)
   : shpCmd(ashpCmd),
     cti(acti) {}
};

struct TBCmdRx {
  ShpBCmdObject shpCmd;
  TCmdRxInfo    cri;
  
  TBCmdRx() {}

  explicit TBCmdRx(ShpBCmdObject ashpCmd)
   : shpCmd(ashpCmd) {}
  
  TBCmdRx(ShpBCmdObject ashpCmd, const TCmdRxInfo &acri)
   : shpCmd(ashpCmd),
     cri(acri) {}
};

typedef TOptional<TBCmdRx> OBCmdRx;

////////////////////////////////////////////////////////////////////////////////
class TCmdExch: public ICmdExch {
 public:
   TCmdExch()
   : m_Status(sError) {}

  explicit TCmdExch(TFCmdTx aFCmdTx, TStatus aStatus=sOk)
   : m_FCmdTx(aFCmdTx),
     m_Status(aStatus) {}

  explicit TCmdExch(TBCmdRx aBCmdRx, TStatus aStatus=sOk)
   : m_BCmdRx(aBCmdRx),
     m_Status(aStatus) {}

  TCmdExch(TFCmdTx aFCmdTx, TBCmdRx aBCmdRx, TStatus aStatus=sOk)
   : m_FCmdTx(aFCmdTx),
     m_BCmdRx(aBCmdRx),
     m_Status(aStatus) {}
  
  TCmdExch(ShpFCmdObject aFCmds, ShpBCmdObject aBCmds, TStatus aStatus=sOk)
   : m_FCmdTx(aFCmds),
     m_BCmdRx(aBCmds),
     m_Status(aStatus) {}

 public:
  virtual TStatus Status() const { return m_Status; }
  
  virtual const IFCmdObject* FCmd() const { return m_FCmdTx.shpCmd.Get(); }
  virtual const TCmdTxInfo& FInfo() const { return m_FCmdTx.cti; }

  virtual const IBCmdObject* BCmd() const { return m_BCmdRx.shpCmd.Get(); }
  virtual const TCmdRxInfo& BInfo() const { return m_BCmdRx.cri; }
 
 public:
  const ShpFCmdObject& FCmds() const { return m_FCmdTx.shpCmd; }
  const ShpBCmdObject& BCmds() const { return m_BCmdRx.shpCmd; }

 private:
  TFCmdTx m_FCmdTx;
  TBCmdRx m_BCmdRx;
  
  TStatus m_Status;
};

typedef TOptional<TCmdExch> OCmdExch;

#endif
