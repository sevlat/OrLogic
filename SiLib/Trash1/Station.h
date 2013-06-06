// !!!!!!!! to be deleted

#ifndef Station_h_already_included__18_06_2012__15699EA0
#define Station_h_already_included__18_06_2012__15699EA0
//
// SeVlaT, 18.06.2012
//

#include "Stream.h"
#include "Commands.h"
#include "StationTypes.h"

#include "CmdSerialize.h"

#include "StationWrite.h"
#include "StationRead.h"

#include "CmdObject.h"
#include "CmdProcess.h"


////////////////////////////////////////////////////////////////////////////////
enum TReceiveResult {
  rrOK,
  rrNak,
  rrReceivingError,
  rrParcingError,
};

class ICmdTransmit: public IFCmdObject {
 public:
  virtual void Init(const TMsgFrame &mf, TErrList *pErr)=0;
  virtual bool Send(IOStream &os, TErrList *pErr)=0;
};

class ICmdReceive: public IBCmdObject {
 public:
  virtual TReceiveResult Receive(IIStream &is, TErrList *pErr)=0;
};

////////////////////////////////////////////////////////////////////////////////

template<typename CMD>
class TCmdTransmit: public ICmdTransmit {
 public:
  typedef CMD TFwd;
  typedef typename CMD::TData TFwdD;

 public:
  TCmdTransmit(const TFwdD &fwdd)
   : m_fwd(fwdd) {}

 public:
  void Init(const TMsgFrame &mf, TErrList *pErr)
  {
    m_osmw=TCmdSerializer<CMD>::Make(m_fwd.data, mf, pErr);
  }
  
  bool Send(IOStream &os, TErrList *pErr)
  {
    if (!m_osmw) {
      return false;
    }
    
    return StationWrite(os, *m_osmw, pErr);
  }

 public:
  virtual void Apply(IFCmdVisitor &v) { v(m_fwd); }

 private:
  const TFwd m_fwd;
  
 private:
  OStMessage m_osmw;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template<typename CMD>
class TCmdReceive: public ICmdReceive {
 public:
  typedef CMD TBwd;
  typedef typename CMD::TData TBwdD;

 public:
  TReceiveResult Receive(IIStream &is, TErrList *pErr)
  {
    TStMessage smr;
    if (!StationRead(is, smr, pErr)) return rrReceivingError;
    
    typedef TCmdSerializer<CMD> TCSer;

    CmddVoid cmddNak;
    if (TCmdSerializer<CmdBNak>::Parse(smr, cmddNak, pErr)) return rrNak;
    if (TCmdSerializer<CMD>::Parse(smr, m_oBwd.Set().data, pErr)) return rrOK;
    
    m_oBwd=None;
    return rrParcingError;
  }

  virtual void Apply(IBCmdVisitor &v) { if (m_oBwd) v(*m_oBwd); }

 protected:
  TOptional<TBwd> m_oBwd;
};

template<typename CMDPAIR>
class TCmdTransceive: public TCmdTransmit<typename CMDPAIR::TFwd>,
                      public TCmdReceive<typename CMDPAIR::TBwd> {
 public:
  TCmdTransceive(const TFwdD &fwdd)
   : TCmdTransmit<typename CMDPAIR::TFwd>(fwdd) {}
};

////////////////////////////////////////////////////////////////////////////////
class TSetMaSlaveB: public TCmdTransceive<CmdPSetMaSlaveB> {
 public:
  explicit TSetMaSlaveB(bool bMaster)
   : TCmdTransceive<CmdPSetMaSlaveB>(CmddFSetMaSlave(bMaster)) {}
};

class TSetMaSlaveE: public TCmdTransceive<CmdPSetMaSlaveE> {
 public:
  explicit TSetMaSlaveE(bool bMaster)
   : TCmdTransceive<CmdPSetMaSlaveE>(CmddFSetMaSlave(bMaster)) {}
};
 
////////////////////////////////////////////////////////////////////////////////
class TSetBaudRateB: public TCmdTransceive<CmdPSetBaudRateB> {
 public:
  explicit TSetBaudRateB(bool bHigh)
   : TCmdTransceive<CmdPSetBaudRateB>(CmddFSetBaudRate(bHigh)) {}
};

class TSetBaudRateE: public TCmdTransceive<CmdPSetBaudRateE> {
 public:
  explicit TSetBaudRateE(bool bHigh)
   : TCmdTransceive<CmdPSetBaudRateE>(CmddFSetBaudRate(bHigh)) {}
};

////////////////////////////////////////////////////////////////////////////////
enum TCmdResult {
  crOK,
  crNak,
  crTransmittingError,
  crReceivingError,
  crParcingError,
};

struct TCmdProcParams {
  TUInt nRepeteOnNakCount;
  
  TUInt nMsWaitAnswer;
  TUInt nMsWaitAnswerInc;

  TUInt nMsWaitOnNak;
  TUInt nMsWaitOnNakInc;
  
  TMsgPrefix Pref;
  
  TCmdProcParams()
   : nRepeteOnNakCount(0),
     nMsWaitAnswer(0),
     nMsWaitAnswerInc(0),
     nMsWaitOnNak(0),
     nMsWaitOnNakInc(0)  {}
};

class ICmdProcessor {
 public:
  virtual TCmdResult Do(ICmdTransmit &CmdT,
                        ICmdReceive  &CmdR,
                        IIStream     &is,
                        IOStream     &os,
                        TErrList     *pErr) const=0;
};

class TCmdProcessor: public ICmdProcessor {
 public:
  explicit TCmdProcessor(const TCmdProcParams &Params)
   : m_Params(Params) {}
  
 public:
  virtual TCmdResult Do(ICmdTransmit &CmdT,
                        ICmdReceive  &CmdR,
                        IIStream     &is,
                        IOStream     &os,
                        TErrList     *pErr) const;

 private:
  TCmdProcParams m_Params;
};

////////////////////////////////////////////////////////////////////////////////
class TStation {
 public:
  TStation(IIOStream &ios);
  
 public:
  TCmdResult Cmd(TSetMaSlaveB &cmd, const ICmdProcessor &proc, TErrList *pErr);
  TCmdResult Cmd(TSetMaSlaveE &cmd, const ICmdProcessor &proc, TErrList *pErr);

  TCmdResult Cmd(TSetBaudRateB &cmd, const ICmdProcessor &proc, TErrList *pErr);
  TCmdResult Cmd(TSetBaudRateE &cmd, const ICmdProcessor &proc, TErrList *pErr);

 private:
  template<typename TRANSCEIVER>
  TCmdResult DoCmd(TRANSCEIVER &trcv, const ICmdProcessor &proc, TErrList *pErr);
  
 private:
  IIStream &m_is;
  IOStream &m_os;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum TReceiveStatus {
  rsNone,
  rsNak,
  rsOK,
};

template<typename CMD>
class TCmdReceiver;

template<>
class TCmdReceiver<CmdFNone> {
 public:
  template<typename CMD>
  void operator ()(const CMD &cmd) const {}
};

template<typename CMD>
class TCmdReceiver {
 public:
  template<typename CMD1>
  void operator ()(const CMD1 &cmd) const {}

  void operator ()(const CmdBNak &cmd) const;
  void operator ()(const CMD &cmd) const;
  
 public:
  TReceiveStatus Status() const { return m_Status; }

 private:
  TReceiveStatus m_Status;
};

template<typename CMD>
class TCmdReceiverV: public TCmdVisitorV<TCmdReceiver<CMD>, int, TagBwd> { /// int - make it clear

 public:
  TReceiveStatus Status() const { return Vis().Status(); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename CMDPAIR>
class TCmdFB {
 public:
  typedef typename CMDPAIR::TFwd  TFwd;
  typedef typename CMDPAIR::TFwdD TFwdD;

  typedef typename CMDPAIR::TBwd  TBwd;
  typedef typename CMDPAIR::TBwdD TBwdD;
  
 public:
  explicit TCmdFB(const TFwd &fwd)
   : m_fwd(fwd) {
   }
 
 public:
  

 private:
  TFwd m_fwd;
  TBwd m_bwd;
};

////////////////////////////////////////////////////////////////////////////////

template<typename CMDP>
class TTranceiveCmd {
 public:
  typedef typename CMDP::TFwdD TFwdD;
  typedef typename CMDP::TFwd  TFwd;

  typedef typename CMDP::TBwdD TBwdD;
  typedef typename CMDP::TBwd  TBwd;
  
  static TOptional<TBwdD> Do(IIOStream &ios,
                             TFwdD      fwdD,
                             TErrList  *pErr)
  {
    TMsgFrame mf;
    
    const TProtCmdPacket cptx=TCmdSerializer<TFwd>::Make(fwdD, mf, pErr);
    const bool bWrite=StationWrite(ios, cptx, 0);
    if (!bWrite) return None;
    
    TCmdProcess cmdproc(CMDP::cc, TSysSpan(1000000));
    
    cmdproc.Sent(GetSysTime());
    while (cmdproc.IsWaiting()) {
      TProtCmdPacket cprx;
      const bool bRead=StationRead(ios, cprx, pErr);
      if (!bRead) return None;
    
      cmdproc.Receive(cprx.cc, GetSysTime());
      if (cmdproc.IsOK()) {
        TBwdD bwdD;
        if (TCmdSerializer<TBwd>::Parse(cprx, bwdD, pErr))
          return bwdD;
      }
      return None;
    }
    return None;
  }
};



#endif
