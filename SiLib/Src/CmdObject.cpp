// SeVlaT, 01.03.2013
#include "StdAfx.h"

#include "../CmdObject.h"
#include "../CmdSerializeImpl.h"

class TPacketMakeVisitor {
 public:
  explicit TPacketMakeVisitor(TMsgFrame       mf,
                              TProtCmdPacket &pkt,
                              TErrList       *pErr)
   : m_pkt(pkt),
     m_mf(mf),
     m_pErr(pErr),
     m_bRes(false) {}
   
 public:
  template<typename CMD>
  void operator ()(const CMD &cmd) { m_bRes=MakePacket(cmd, m_mf, m_pkt, m_pErr); }

 public:
  bool Res() const { return m_bRes; }

 private:
  TProtCmdPacket &m_pkt;
  TMsgFrame       m_mf;
  TErrList       *m_pErr;
  bool            m_bRes;
};



template<typename DIR>
bool MakePacket_tmpl(const ICmdObject<DIR> &Cmdo,
                     const TMsgFrame       &mf,
                           TProtCmdPacket  &pkt,
                           TErrList        *pErr)
{
  TPacketMakeVisitor v(mf, pkt, pErr);
  TCmdVisitorVRef<TPacketMakeVisitor, TagFwd> vv(v);
  Cmdo.Apply(vv);
  return v.Res();
}                         

bool MakePacket(const IFCmdObject    &Cmdo,
                const TMsgFrame      &mf,
                      TProtCmdPacket &pkt,
                      TErrList       *pErr)
{
  return MakePacket_tmpl(Cmdo, mf, pkt, pErr);
}                         
