#ifndef CmdsParse_h_already_included__20_03_2013__28BAE7C0
#define CmdsParse_h_already_included__20_03_2013__28BAE7C0
//
// SeVlaT, 20.03.2013
//

#include "CmdShpObject.h"

#include "../StationTypes.h"
#include "../CmdDispatcher.h"
#include "../CmdSerialize.h"

template<typename CMD>
struct TCmdShpParse {

  typedef typename TCmdoGen<CMD>::Type TCmdObj;
  typedef TCmdPtr<TCmdObj>             ShpCmdObject;

  static ShpCmdObject Parse(const TProtCmdPacket &pkt, TErrList *pErr)
  {
    typedef TCmdSerializer<typename CMD::TBase> TCmdSer;
    TCmdObj *pCmd=new TCmdObj();
    ShpCmdObject shpCmd(pCmd);
    
    if (!TCmdSer::Parse(pkt, *pCmd, pErr)) return ShpCmdObject();
    return shpCmd;
  }
};


template <typename DIR>
struct TShpDispatchReader {
  typedef ICmdObject<DIR> ICmdObj;
  
  typedef TCmdPtr<ICmdObj> ShpCmdObject;
  
  explicit TShpDispatchReader(TErrList *pErr)
   : m_pErr(pErr) {}
  
  template <typename CMD>
  bool Try(const TProtCmdPacket &pkt)
  {
    shpCmd=TCmdShpParse<CMD>::Parse(pkt, m_pErr);
    return shpCmd; 
  }
  
  bool Unhandled(const TProtCmdPacket &pkt)
  {
    typedef TShpCmdRawObjectFactory<DIR, CauseCmdUnparseable> Factory;
    shpCmd=Factory::Create(pkt);
    return true;
  }

  void Unfamiliar(const TProtCmdPacket &pkt)
  {
    typedef TShpCmdRawObjectFactory<DIR, CauseCmdUnfamiliar> Factory;
    shpCmd=Factory::Create(pkt);
  }

  ShpCmdObject shpCmd;
  
 private:
  TErrList *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
template<typename DIR>
TCmdPtr<ICmdObject<DIR> > ShpParse(const TProtCmdPacket &pkt, TErrList *pErr)
{
  typedef TShpDispatchReader<DIR> TReader;
  typedef TPacketDisp<DIR, TReader, TReader> TDisp;
  
  TReader Reader(pErr);
  TDisp Disp(Reader, Reader, pkt);
  
  if (!EnumCmd(Disp)) Reader.Unfamiliar(pkt);

  return Reader.shpCmd;
}

ShpFCmdObject ShpFParse(const TProtCmdPacket &pkt, TErrList *pErr);
ShpBCmdObject ShpBParse(const TProtCmdPacket &pkt, TErrList *pErr);

////////////////////////////////////////////////////////////////////////////////


#endif
