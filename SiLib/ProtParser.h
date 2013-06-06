#ifndef ProtParser_h_already_included__25_02_2013__2B72BF80
#define ProtParser_h_already_included__25_02_2013__2B72BF80
//
// SeVlaT, 25.02.2013
//

#include "CmdDispatcher.h"

#include "StationTypes.h"
#include "CmdSerialize.h"


////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR>
struct TPacketParser {
  TPacketParser(VISITOR  &Visitor,
                TErrList *pErr)
   : m_Visitor(Visitor),
     m_pErr(pErr) {}
  
  template <typename CMD>
  bool Try(const TProtCmdPacket &pkt) const
  {
    if (CMD::cc!=pkt.cc) return false;

    typedef TCmdSerializer<typename CMD::TBase> TCmdSer;
    
//    class TCmd: public CMDB {};
    CMD Cmd;
    typename CMD::TBase &Cmdb=Cmd;
    
    if (TCmdSer::Parse(pkt, Cmdb, m_pErr)) {
      m_Visitor(Cmdb);
      return true;
    }
    
    return false;
  }

 private:
  VISITOR  &m_Visitor;
  TErrList *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
template <typename VISITOR>
struct TRawHandler {
  TRawHandler(VISITOR  &Visitor)
   : m_Visitor(Visitor) {}
  
  bool Unhandled(const TProtCmdPacket &pkt) const
  {
    m_Visitor(pkt, VISITOR::TDir(), CauseCmdUnparseable());
    return true;
  }

 private:
  VISITOR &m_Visitor;
};
  
template<typename VISITOR, typename RVISITOR>
void ProtParse(      VISITOR        &Visitor,
                     RVISITOR       &RVisitor,
               const TProtCmdPacket &pkt,
                     TErrList       *pErr)
{
  typedef TPacketParser<VISITOR> TParser;
  typedef TRawHandler<RVISITOR>  TRHandler;
  typedef VISITOR::TDir          TDir;
  
  typedef TPacketDisp<TDir, TParser, TRHandler> TDisp;
  
  TParser Parser(Visitor, pErr);
  TRHandler RHandler(RVisitor);
  
  TDisp Disp(Parser, RHandler, pkt);
  
  if (!EnumCmd(Disp)) RVisitor(pkt, TDir(), CauseCmdUnfamiliar());
}

template<typename FVISITOR, typename BVISITOR, typename RVISITOR>
void ProtParse(     FVISITOR       &FVisitor,
                    BVISITOR       &BVisitor,
                    RVISITOR       &RVisitor,
              const TProtCmdPacket &pkt,
                    TErrList       *pErr)
{
  typedef TPacketParser<FVISITOR> TFParser;
  typedef TPacketParser<BVISITOR> TBParser;
  typedef TRawHandler<RVISITOR>   TRHandler;
  
  typedef TPacketDispFB<TFParser, TBParser, TRHandler> TDisp;
  
  TFParser FParser(FVisitor, pErr);
  TBParser BParser(BVisitor, pErr);
  TRHandler RHandler(RVisitor);
  
  TDisp Disp(FParser, BParser, RHandler, pkt);
  
  if (!EnumCmd(Disp)) RVisitor(pkt, TagUnk(), CauseCmdUnfamiliar());
}


////////////////////////////////////////////////////////////////////////////////
#endif
