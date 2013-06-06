// SeVlaT, 13.09.2012
#include "StdAfx.h"

#include "../PacketParseV.h"
#include "../ProtParser.h"

#include "../CmdSerializeImpl.h"

////////////////////////////////////////////////////////////////////////////////
void ParsePacketV(      IFCmdVisitor    &FVisitor,
                        IFRawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr)
{
  ProtParse(FVisitor, RVisitor, pkt, pErr);
}

////////////////////////////////////////////////////////////////////////////////
void ParsePacketV(      IBCmdVisitor    &BVisitor,
                        IBRawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr)
{
  ProtParse(BVisitor, RVisitor, pkt, pErr);
}

////////////////////////////////////////////////////////////////////////////////
void ParsePacketV(      IFCmdVisitor    &FVisitor,
                        IBCmdVisitor    &BVisitor,
                        IURawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr)
{
  ProtParse(FVisitor, BVisitor, RVisitor, pkt, pErr);
}                       


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TFPacketParser::TFPacketParser(IFCmdVisitor    &FVisitor,
                               IFRawPktVisitor &RVisitor)
 : m_FVisitor(FVisitor),
   m_RVisitor(RVisitor)   
{
} 
  
void TFPacketParser::operator ()(const TProtCmdPacket &pkt,
                                       TErrList       *pErr) const
{
  ParsePacketV(m_FVisitor, m_RVisitor, pkt, pErr);
} 

////////////////////////////////////////////////////////////////////////////////
TBPacketParser::TBPacketParser(IBCmdVisitor    &BVisitor,
                               IBRawPktVisitor &RVisitor)
 : m_BVisitor(BVisitor),
   m_RVisitor(RVisitor)
{
}

void TBPacketParser::operator ()(const TProtCmdPacket &pkt,
                                       TErrList       *pErr) const
{
  ParsePacketV(m_BVisitor, m_RVisitor, pkt, pErr);
}

////////////////////////////////////////////////////////////////////////////////
TFBPacketParser::TFBPacketParser(IFCmdVisitor    &FVisitor,
                                 IBCmdVisitor    &BVisitor,
                                 IURawPktVisitor &RVisitor)
 : m_FVisitor(FVisitor),
   m_BVisitor(BVisitor),
   m_RVisitor(RVisitor)
{
}
  
void TFBPacketParser::operator ()(const TProtCmdPacket &pkt,
                                        TErrList       *pErr) const
{
  ParsePacketV(m_FVisitor, m_BVisitor, m_RVisitor, pkt, pErr);
}                                       
                 

