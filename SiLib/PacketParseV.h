#ifndef PacketParseV_h_already_included__25_02_2013__157A2800
#define PacketParseV_h_already_included__25_02_2013__157A2800
//
// SeVlaT, 25.02.2013
//

#include "CmdVisitor.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ParsePacketV(      IFCmdVisitor    &FVisitor,
                        IFRawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr);

////////////////////////////////////////////////////////////////////////////////
void ParsePacketV(      IBCmdVisitor    &BVisitor,
                        IBRawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr);

////////////////////////////////////////////////////////////////////////////////
                    
void ParsePacketV(      IFCmdVisitor    &FVisitor,
                        IBCmdVisitor    &BVisitor,
                        IURawPktVisitor &RVisitor,
                  const TProtCmdPacket  &pkt,
                        TErrList        *pErr);
                      
////////////////////////////////////////////////////////////////////////////////
class IPacketParser {
 public:
  virtual void operator ()(const TProtCmdPacket &pkt,
                                 TErrList       *pErr) const=0;
};

////////////////////////////////////////////////////////////////////////////////
class TFPacketParser: public IPacketParser {
 public:
  TFPacketParser(IFCmdVisitor    &FVisitor,
                 IFRawPktVisitor &RVisitor);
  
 public:
  virtual void operator ()(const TProtCmdPacket &pkt,
                                 TErrList       *pErr) const;

 private:
  IFCmdVisitor    &m_FVisitor;
  IFRawPktVisitor &m_RVisitor;
};

////////////////////////////////////////////////////////////////////////////////
class TBPacketParser: public IPacketParser {
 public:
  TBPacketParser(IBCmdVisitor    &BVisitor,
                 IBRawPktVisitor &RVisitor);
  
 public:
  virtual void operator ()(const TProtCmdPacket &pkt,
                                 TErrList       *pErr) const;

 private:
  IBCmdVisitor    &m_BVisitor;
  IBRawPktVisitor &m_RVisitor;
};

////////////////////////////////////////////////////////////////////////////////
class TFBPacketParser: public IPacketParser {
 public:
  TFBPacketParser(IFCmdVisitor    &FVisitor,
                  IBCmdVisitor    &BVisitor,
                  IURawPktVisitor &RVisitor);
  
 public:
  virtual void operator ()(const TProtCmdPacket &pkt,
                                 TErrList       *pErr) const;

 private:
  IFCmdVisitor    &m_FVisitor;
  IBCmdVisitor    &m_BVisitor;
  IURawPktVisitor &m_RVisitor;
};

#endif
