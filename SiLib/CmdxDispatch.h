#ifndef CmdxDispatch_h_already_included__02_04_2013__727BC68
#define CmdxDispatch_h_already_included__02_04_2013__727BC68
//
// SeVlaT, 02.04.2013
//

#include "CmdExchange.h"
#include "CmdVisitor.h"
#include "CmdTrxInfo.h"

template <typename OBSERVER>
class TCmdxDispatcher1 {
 private:
  template <typename DIR>
  class TOkVisitor {
   public:
    TOkVisitor(OBSERVER &Obs, OSysTime ot)
     : m_Obs(Obs), m_ot(ot) {}

   public:
    template <TCmdCode CC>
    void operator ()(const TCommandBase<CC, DIR> &cmd) const { m_Obs.OnOk(cmd, m_ot); }

   private:
    OSysTime m_ot;
    OBSERVER &m_Obs;
  };
  
  typedef TOkVisitor<TagFwd> TOkFVisitor;
  typedef TOkVisitor<TagBwd> TOkBVisitor;
  
 private:
  template <TCmdCode CCF>
  class TOkBFVisitor {
   public:
    TOkBFVisitor(      OBSERVER                  &Obs,
                 const TCommandBase<CCF, TagFwd> &cmdF,
                       OSysTime                   otF,
                       OSysTime                   otB)
     : m_Obs(Obs),
       m_otF(otF),
       m_cmdF(cmdF),
       m_otB(otB) {}

   public:
    template <TCmdCode CCB>
    void operator ()(const TCommandBase<CCB, TagBwd> &cmdB) const
     { 
       m_Obs.OnOk(m_cmdF, m_otF, cmdB, m_otB);
     }

    void operator ()(const TCommandBase<TCmdCdTraits<CCF>::ccB, TagBwd> &cmdB) const
     { 
       m_Obs.OnOk(m_cmdF, m_otF, cmdB, m_otB);
     }

   private:
    OBSERVER &m_Obs;

   private:
    const TCommandBase<CCF, TagFwd> &m_cmdF;
    OSysTime m_otF;
    OSysTime m_otB;
  };

  class TOkXVisitor {
   public:
    TOkXVisitor(      OBSERVER    &Obs,
                      OSysTime     otF,
                const IBCmdObject &BCmdo,
                      OSysTime     otB)
     : m_Obs(Obs), m_otF(otF), m_BCmdo(BCmdo), m_otB(otB) {}

   public:
    template <TCmdCode CCF>
    void operator ()(const TCommandBase<CCF, TagFwd> &cmdF) const
     { 
       TOkBFVisitor<CCF> Vis(m_Obs, cmdF, m_otF, m_otB);
       TCmdVisitorVRef<TOkBFVisitor<CCF>, TagBwd> VVis(Vis);
       m_BCmdo.Apply(VVis);
     }

    void operator ()(const CmdbFBeep &cmdFBeep) const  { }

   private:
    OSysTime m_otF;
    const IBCmdObject &m_BCmdo;
    OSysTime m_otB;
    OBSERVER &m_Obs;
  };

 private:
  class TFailedFVisitor {
   public:
    TFailedFVisitor(OBSERVER &Obs, OSysTime otF, TCmdxStatus Status)
     : m_Obs(Obs), m_otF(otF), m_Status(Status) {}

   public:
    template <TCmdCode CC>
    void operator ()(const TCommandBase<CC, TagFwd> &cmd) const { m_Obs.OnFailed(cmd, m_otF, m_Status); }

   private:
    OSysTime m_otF;
    TCmdxStatus m_Status;
    OBSERVER &m_Obs;
  };

 public:
  explicit TCmdxDispatcher1(OBSERVER &Observer)
   : m_Observer(Observer) {}

 public:
  void OnOk(const IFCmdObject &FCmdo,
                  OSysTime     otF,
            const IBCmdObject &BCmdo,
                  OSysTime     otB)
  {
    TOkXVisitor Vis(m_Observer, otF, BCmdo, otB);
    TCmdVisitorVRef<TOkXVisitor, TagFwd> VVis(Vis);
    FCmdo.Apply(VVis);
  }                  

  void OnOk(const IFCmdObject &FCmdo,
                  OSysTime     otF)
  {
    TOkFVisitor Vis(m_Observer, otF);
    TCmdVisitorVRef<TOkFVisitor, TagFwd> VVis(Vis);
    FCmdo.Apply(VVis);
  }                  

  void OnOk(const IBCmdObject &BCmdo,
                  OSysTime     otB)
  {
    TOkBVisitor Vis(m_Observer, otB);
    TCmdVisitorVRef<TOkBVisitor, TagBwd> VVis(Vis);
    BCmdo.Apply(VVis);
  }                  
                  
 public:
  void OnFailed(const IFCmdObject &FCmdo,
                      OSysTime     otF,
                      TCmdxStatus  Status)
  {
    TFailedFVisitor Vis(m_Observer, otF, Status);
    TCmdVisitorVRef<TFailedFVisitor, TagFwd> VVis(Vis);
    FCmdo.Apply(VVis);
  }                  
                      

  void OnStrange(const ICmdExch &cmdx)
  {
    m_Observer.OnStrange(cmdx);
  }                  

 private:
  OBSERVER &m_Observer;
};

////////////////////////////////////////////////////////////////////////////////

template <typename OBSERVER>
class TCmdxDispatcher {
 public:
  explicit TCmdxDispatcher(OBSERVER &Observer)
   : m_Observer(Observer) {}

 public:
  void operator()(const ICmdExch &cmdx)
  { if (!Try(cmdx)) m_Observer.OnStrange(cmdx); }
  
 private:
  bool Try(const ICmdExch &cmdx)
  {
    const IFCmdObject *pFCmd=cmdx.FCmd();
    const IBCmdObject *pBCmd=cmdx.BCmd();
    
    const TCmdxStatus Status=cmdx.Status();

    if ( pFCmd && pBCmd) {
      if (Status==ICmdExch::sOk) {
        m_Observer.OnOk(*pFCmd, cmdx.FInfo().ot,
                        *pBCmd, cmdx.BInfo().ot);
        return true;             
      }
    } else if (!pFCmd &&  pBCmd) {
      if (Status==ICmdExch::sOk) {
        m_Observer.OnOk(*pBCmd, cmdx.BInfo().ot);
        return true;             
      }
    } else if ( pFCmd && !pBCmd) {
      if (Status==ICmdExch::sOk) {
        m_Observer.OnOk(*pFCmd, cmdx.FInfo().ot);
        return true;             
      } else {
        m_Observer.OnFailed(*pFCmd, cmdx.FInfo().ot, Status);
        return true;             
      }
    }
    
    return false;
  }

 private:
  OBSERVER &m_Observer;
};

////////////////////////////////////////////////////////////////////////////////
template <typename OBSERVER>
void CmdxDispatch(const ICmdExch &cmdx, OBSERVER &Observer)
{
  typedef TCmdxDispatcher1<OBSERVER> TDisp1;
  TDisp1 Disp1(Observer);
  TCmdxDispatcher<TDisp1> Disp(Disp1);
  Disp(cmdx);
}


#endif
