#ifndef CmdVisitorParam_h_already_included__25_12_2012__6949148
#define CmdVisitorParam_h_already_included__25_12_2012__6949148
//
// SeVlaT, 25.12.2012
//

#include "CmdVisitor.h"

////////////////////////////////////////////////////////////////////////////////
template<typename PARAM>
struct CmdVisit {

  //////////////////////////////////////////////////////////////////////////////
  class IC {
   public:
    // unrecognized
    virtual void operator ()(const TStMessage &sm, PARAM Param) const=0;
    virtual void Unrecognised(const TStMessage &sm, PARAM Param) const=0;
  };

  class IF {
   public:
    virtual void operator ()(const CmdFBeep &cmd, PARAM Param) const=0;

    virtual void operator ()(const CmdFSetMaSlaveB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdFSetMaSlaveE &cmd, PARAM Param) const=0;

    virtual void operator ()(const CmdFSetBaudRateB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdFSetBaudRateE &cmd, PARAM Param) const=0;

    virtual void operator ()(const CmdFGetTimeB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdFGetTimeE &cmd, PARAM Param) const=0;

    virtual void operator ()(const CmdFSetTimeB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdFSetTimeE &cmd, PARAM Param) const=0;
  };

  class ICF: public IC,
             public IF
  {
  };

  //////////////////////////////////////////////////////////////////////////////
  class IB {
   public:
    virtual void operator ()(const CmdBNak &cmd, PARAM Param) const=0;
                                    
    virtual void operator ()(const CmdBSetMaSlaveB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdBSetMaSlaveE &cmd, PARAM Param) const=0;
                                    
    virtual void operator ()(const CmdBSetBaudRateB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdBSetBaudRateE &cmd, PARAM Param) const=0;
                                    
    virtual void operator ()(const CmdBGetTimeB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdBGetTimeE &cmd, PARAM Param) const=0;
                                    
    virtual void operator ()(const CmdBSetTimeB &cmd, PARAM Param) const=0;
    virtual void operator ()(const CmdBSetTimeE &cmd, PARAM Param) const=0;
  };

  class ICB: public IC,
             public IB
  {
  };

  class ICFB: public IC,
              public IF,
              public IB
  {
  };
                    
  //////////////////////////////////////////////////////////////////////////////
  template<typename CMD>
  void AddParam(const IF &FVisitor, const CMD &cmd, PARAM Param)
    { FVisitor(cmd, Param); }

  template<typename CMD>
  void AddParam(const IB &BVisitor, const CMD &cmd, PARAM Param)
    { BVisitor(cmd, Param); }

  class TFAddParam {
   public:
    TFAddParam(const IF &FVisitor, PARAM Param)
     : m_FVisitor(FVisitor),
       m_Param(Param) {}

   public:
    template<typename CMD>
    void operator ()(const CMD &cmd) { m_FVisitor(cmd, m_Param); }
    
   private:
    const IB &m_FVisitor;
    PARAM m_Param;
  };

  class TFAddParamV: public TFCmdVisitorV<TFAddParam> {
   public:
    TFAddParamV(const IF &FVisitor, PARAM Param)
     : TFCmdVisitorV<TFAddParam>(TFAddParam(FVisitor, Param)) {}
  };

  //////////////////////////////////////////////////////////////////////////////
  class TBAddParam {
   public:
    TBAddParam(const IB &BVisitor, PARAM Param)
     : m_BVisitor(BVisitor),
       m_Param(Param) {}

   public:
    template<typename CMD>
    void operator ()(const CMD &cmd) { m_BVisitor(cmd, m_Param); }
    
   private:
    const IB &m_BVisitor;
    PARAM m_Param;
  };

  class TBAddParamV: public TBCmdVisitorV<TFAddParam> {
   public:
    TBAddParamV(const IB &BVisitor, PARAM Param)
     : TBCmdVisitorV<TBAddParam>(TBAddParam(BVisitor, Param)) {}
  };

  //////////////////////////////////////////////////////////////////////////////
  class TCAddParam: public ICCmdVisitor {
   public:
    TCAddParam(const IC &CVisitor, PARAM Param)
     : m_CVisitor(CVisitor),
       m_Param(Param) {}

   public:
    virtual void operator ()(const TStMessage &sm, PARAM Param) const
     { m_CVisitor(sm, m_Param); };
    virtual void UnknownCmd(const TStMessage &sm, PARAM Param) const
     { m_CVisitor.Unrecognised(sm, m_Param); };
    
   private:
    const IC &m_CVisitor;
    PARAM m_Param;
  };

  //////////////////////////////////////////////////////////////////////////////
  static void Dispatch(const TStMessage &msg,
                       const IC         &CVisitor,
                       const IF         &FVisitor,
                             PARAM       Param,
                             TErrList   *pErr)
   { ParsePacketV(msg,
                 TCAddParam(CVisitor, Param),
                 TFAddParam(FVisitor, Param),
                 pErr);
   }

  static void Dispatch(const TStMessage &msg,
                       const ICF        &Visitor,
                             PARAM       Param,
                             TErrList   *pErr);

  static void Dispatch(const TStMessage &msg,
                       const IC         &CVisitor,
                       const IB         &BVisitor,
                             PARAM       Param,
                             TErrList   *pErr)
   { ParsePacketV(msg,
                 TCAddParam(CVisitor, Param),
                 TBAddParam(BVisitor, Param),
                 pErr);
   }

  static void Dispatch(const TStMessage &msg,
                       const ICB        &Visitor,
                             PARAM       Param,
                             TErrList   *pErr);

  //////////////////////////////////////////////////////////////////////////////
  static void Dispatch(const TStMessage &msg,
                       const IC         &CVisitor,
                       const IF         &FVisitor,
                       const IB         &BVisitor,
                             PARAM       Param,
                             TErrList   *pErr)
   { ParsePacketV(msg,
                 TCAddParam(CVisitor, Param),
                 TFAddParam(FVisitor, Param),
                 TBAddParam(BVisitor, Param),
                 pErr);
   }

  static void Dispatch(const TStMessage &msg,
                       const ICFB       &Visitor,
                             PARAM       Param,
                             TErrList   *pErr);
                      
  //////////////////////////////////////////////////////////////////////////////
  class IDispatcher {
   public:
    virtual void Dispatch(const TStMessage &msg,
                                TErrList   *pErr) const=0;
  };

  //////////////////////////////////////////////////////////////////////////////
  class TCFDispatcher: public IDispatcher {
   public:
    TCFDispatcher(const IC &CVisitor,
                  const IF &FVisitor);                   
    
    explicit TCFDispatcher(const ICF &Visitor);

   public:
    virtual void Dispatch(const TStMessage &msg,
                                TErrList   *pErr) const;

   private:
    const IC &m_CVisitor;
    const IF &m_FVisitor;
  };

  //////////////////////////////////////////////////////////////////////////////
  class TCBDispatcher: public IDispatcher {
   public:
    TCBDispatcher(const IC &CVisitor,
                  const IB &BVisitor);
    
    explicit TCBDispatcher(const ICB &Visitor);

   public:
    virtual void Dispatch(const TStMessage &msg,
                                TErrList   *pErr) const;

   private:
    const IC &m_CVisitor;
    const IB &m_BVisitor;
  };

  //////////////////////////////////////////////////////////////////////////////
  class TCFBDispatcher: public IDispatcher {
   public:
    TCFBDispatcher(const IC &CVisitor,
                   const IF &FVisitor,
                   const IB &BVisitor);
    
    explicit TCFBDispatcher(const ICFB &Visitor);

   public:
    virtual void Dispatch(const TStMessage &msg,
                                TErrList   *pErr) const;

   private:
    const IC &m_CVisitor;
    const IF &m_FVisitor;
    const IB &m_BVisitor;
  };

};

#endif
