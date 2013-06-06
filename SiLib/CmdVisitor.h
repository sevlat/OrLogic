#ifndef CmdVisitor_h_already_included__08_09_2012__F9B8040
#define CmdVisitor_h_already_included__08_09_2012__F9B8040
//
// SeVlaT, 08.09.2012
//

#include "Commands.h"

struct TProtCmdPacket;

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
class IRawPktVisitor {
 public:
  typedef DIR TDir;

 public:
  virtual void operator ()(const TProtCmdPacket &pkt, DIR, CauseCmdUnparseable)=0;
  virtual void operator ()(const TProtCmdPacket &pkt, DIR, CauseCmdUnfamiliar) =0;
};

typedef IRawPktVisitor<TagUnk> IURawPktVisitor;
typedef IRawPktVisitor<TagFwd> IFRawPktVisitor;
typedef IRawPktVisitor<TagBwd> IBRawPktVisitor;

////////////////////////////////////////////////////////////////////////////////
template<typename DIR>
class IRawCmdVisitor {
 public:
  typedef DIR TDir;

 public:
  virtual void operator ()(const TRawCommand_Base<DIR, CauseCmdUnparseable> &cmd)=0;
  virtual void operator ()(const TRawCommand_Base<DIR, CauseCmdUnfamiliar>  &cmd)=0;
  
  virtual void operator ()(const TCommSetup &cs)=0;
};

typedef IRawCmdVisitor<TagUnk> IURawCmdVisitor;
typedef IRawCmdVisitor<TagFwd> IFRawCmdVisitor;
typedef IRawCmdVisitor<TagBwd> IBRawCmdVisitor;

////////////////////////////////////////////////////////////////////////////////
template<typename DIR>
class ICmdVisitor;

////////////////////////////////////////////////////////////////////////////////
template<>
class ICmdVisitor<TagUnk> {
 public:
  typedef TagUnk TDir;
};

////////////////////////////////////////////////////////////////////////////////
template<>
class ICmdVisitor<TagFwd> {
 public:
  typedef TagFwd TDir;

 public:
  virtual void operator ()(const CmdbFBeep &cmd)=0;
                                    
  virtual void operator ()(const CmdbFSetMaSlaveB &cmd)=0;
  virtual void operator ()(const CmdbFSetMaSlaveE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFGetMaSlaveB &cmd)=0;
  virtual void operator ()(const CmdbFGetMaSlaveE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFSetBaudRateB &cmd)=0;
  virtual void operator ()(const CmdbFSetBaudRateE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFGetTimeB &cmd)=0;
  virtual void operator ()(const CmdbFGetTimeE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFSetTimeB &cmd)=0;
  virtual void operator ()(const CmdbFSetTimeE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFGetSysValueE &cmd)=0;
                                    
  virtual void operator ()(const CmdbFGetBckDataE &cmd)=0;

  virtual void operator ()(const CmdbFBeepE &cmd)=0;
  
  virtual void operator ()(const CmdbFTurnOffB &cmd)=0;
  
  template <typename CMD>
  void Apply(const CMD &cmd) { operator()(cmd); }

 private:
  template <typename T>
  void operator ()(const T&) {}
};

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
template<>
class ICmdVisitor<TagBwd> {
 public:
  typedef TagBwd TDir;

 public:
  virtual void operator ()(const CmdbBNak &cmd)=0;
                                    
  virtual void operator ()(const CmdbBSetMaSlaveB &cmd)=0;
  virtual void operator ()(const CmdbBSetMaSlaveE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBGetMaSlaveB &cmd)=0;
  virtual void operator ()(const CmdbBGetMaSlaveE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBSetBaudRateB &cmd)=0;
  virtual void operator ()(const CmdbBSetBaudRateE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBGetTimeB &cmd)=0;
  virtual void operator ()(const CmdbBGetTimeE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBSetTimeB &cmd)=0;
  virtual void operator ()(const CmdbBSetTimeE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBGetSysValueE &cmd)=0;
                                    
  virtual void operator ()(const CmdbBGetBckDataE &cmd)=0;
  
  virtual void operator ()(const CmdbBBeepE &cmd)=0;

  virtual void operator ()(const CmdbBTurnOffB &cmd)=0;
  
  virtual void operator ()(const CmdbBCardIns5RemB &cmd)=0;
  virtual void operator ()(const CmdbBCardIns6B &cmd)=0;
  virtual void operator ()(const CmdbBCardIns5E &cmd)=0;
  virtual void operator ()(const CmdbBCardIns6E &cmd)=0;
  virtual void operator ()(const CmdbBCardInsHE &cmd)=0;
  virtual void operator ()(const CmdbBCardRemE &cmd)=0;
  
  template <typename CMD>
  void Apply(const CMD &cmd) { operator()(cmd); }

 private:
  template <typename T>
  void operator ()(const T&) {}
};

typedef ICmdVisitor<TagUnk> IUCmdVisitor;
typedef ICmdVisitor<TagFwd> IFCmdVisitor;
typedef ICmdVisitor<TagBwd> IBCmdVisitor;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR, typename ARG, typename DIR> // Use partial specialization?
class TRawPktVisitorV: public IRawPktVisitor<DIR> {
 public:
  explicit TRawPktVisitorV(ARG arg)
   : m_Vis(arg) {}

 public:
  virtual void operator ()(const TProtCmdPacket &pkt, DIR, CauseCmdUnparseable) { m_Vis(pkt, DIR(), CauseCmdUnparseable()); }
  virtual void operator ()(const TProtCmdPacket &pkt, DIR, CauseCmdUnfamiliar)  { m_Vis(pkt, DIR(), CauseCmdUnfamiliar()); }

 protected:
  const VISITOR& Vis() const { return m_Vis; }
        VISITOR& Vis()       { return m_Vis; }

 private:
  VISITOR m_Vis;
};
   
////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR, typename ARG, typename DIR> // Use partial specialization?
class TRawCmdVisitorV: public IRawCmdVisitor<DIR> {
 public:
  explicit TRawCmdVisitorV(ARG arg)
   : m_Vis(arg) {}

 public:
  virtual void operator ()(const TRawCommand_Base<DIR, CauseCmdUnparseable> &cmd) { m_Vis(cmd); }
  virtual void operator ()(const TRawCommand_Base<DIR, CauseCmdUnfamiliar>  &cmd) { m_Vis(cmd); }
  
  virtual void operator ()(const TCommSetup &cs) { m_Vis(cs); }

 protected:
  const VISITOR& Vis() const { return m_Vis; }
        VISITOR& Vis()       { return m_Vis; }

 private:
  VISITOR m_Vis;
};

////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR, typename ARG, typename DIR>
class TCmdVisitorV_base;

template <typename VISITOR, typename ARG>
class TCmdVisitorV_base<VISITOR, ARG, TagFwd>: public IFCmdVisitor {
 protected:
  explicit TCmdVisitorV_base(ARG arg)
   : m_Vis(arg) {}
   
 public:
  virtual void operator ()(const CmdbFBeep &cmd)         { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFSetMaSlaveB &cmd)  { m_Vis(cmd); }
  virtual void operator ()(const CmdbFSetMaSlaveE &cmd)  { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFGetMaSlaveB &cmd)  { m_Vis(cmd); }
  virtual void operator ()(const CmdbFGetMaSlaveE &cmd)  { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFSetBaudRateB &cmd) { m_Vis(cmd); }
  virtual void operator ()(const CmdbFSetBaudRateE &cmd) { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFGetTimeB &cmd)     { m_Vis(cmd); }
  virtual void operator ()(const CmdbFGetTimeE &cmd)     { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFSetTimeB &cmd)     { m_Vis(cmd); }
  virtual void operator ()(const CmdbFSetTimeE &cmd)     { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFGetSysValueE &cmd) { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbFGetBckDataE &cmd)  { m_Vis(cmd); }

  virtual void operator ()(const CmdbFBeepE &cmd)        { m_Vis(cmd); }
  
  virtual void operator ()(const CmdbFTurnOffB &cmd)     { m_Vis(cmd); }

 protected:
  VISITOR m_Vis;
};

template <typename VISITOR, typename ARG>
class TCmdVisitorV_base<VISITOR, ARG, TagBwd>: public IBCmdVisitor {
 protected:
  explicit TCmdVisitorV_base(ARG arg)
   : m_Vis(arg) {}
   
 public:
  virtual void operator ()(const CmdbBNak &cmd)          { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBSetMaSlaveB &cmd)  { m_Vis(cmd); }
  virtual void operator ()(const CmdbBSetMaSlaveE &cmd)  { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBGetMaSlaveB &cmd)  { m_Vis(cmd); }
  virtual void operator ()(const CmdbBGetMaSlaveE &cmd)  { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBSetBaudRateB &cmd) { m_Vis(cmd); }
  virtual void operator ()(const CmdbBSetBaudRateE &cmd) { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBGetTimeB &cmd)     { m_Vis(cmd); }
  virtual void operator ()(const CmdbBGetTimeE &cmd)     { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBSetTimeB &cmd)     { m_Vis(cmd); }
  virtual void operator ()(const CmdbBSetTimeE &cmd)     { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBGetSysValueE &cmd) { m_Vis(cmd); }
                                    
  virtual void operator ()(const CmdbBGetBckDataE &cmd)  { m_Vis(cmd); }

  virtual void operator ()(const CmdbBBeepE &cmd)        { m_Vis(cmd); }

  virtual void operator ()(const CmdbBTurnOffB &cmd)     { m_Vis(cmd); }

  virtual void operator ()(const CmdbBCardIns5RemB &cmd) { m_Vis(cmd); }
  virtual void operator ()(const CmdbBCardIns6B &cmd)    { m_Vis(cmd); }
  virtual void operator ()(const CmdbBCardIns5E &cmd)    { m_Vis(cmd); }
  virtual void operator ()(const CmdbBCardIns6E &cmd)    { m_Vis(cmd); }
  virtual void operator ()(const CmdbBCardInsHE &cmd)    { m_Vis(cmd); }
  virtual void operator ()(const CmdbBCardRemE &cmd)     { m_Vis(cmd); }

 protected:
  VISITOR m_Vis;
};

////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR, typename ARG, typename DIR>
class TCmdVisitorV: public TCmdVisitorV_base<VISITOR, ARG, DIR>
{
 public:
  explicit TCmdVisitorV(ARG arg)
   : TCmdVisitorV_base<VISITOR, ARG, DIR>(arg) {}

 public:
  const VISITOR& Vis() const { return m_Vis; }
        VISITOR& Vis()       { return m_Vis; }
};

template <typename VISITOR, typename DIR>
class TCmdVisitorVRef: public TCmdVisitorV_base<VISITOR&, VISITOR&, DIR>
{
 public:
  explicit TCmdVisitorVRef(VISITOR& vis)
   : TCmdVisitorV_base<VISITOR&, VISITOR&, DIR>(vis) {}
};


#endif
