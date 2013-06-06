#ifndef CmdDispatcher_h_already_included__19_01_2013__731FC38
#define CmdDispatcher_h_already_included__19_01_2013__731FC38
//
// SeVlaT, 19.01.2013
//

#include "Types.h"
#include "Commands.h"

struct TProtCmdPacket;

///////////////////////////////////////////////////////////////////////////////
template<typename DERIVED>
class TSplitDisp {
 public:
  template<typename C>
  bool Try()
  {
    return Try((const C*)0);
  }
  
 private:
  template <TCmdCode CC>
  bool Try(const TCommandBase<CC, TagFwd>*)
  {
    return Self().CheckCode(CC) && 
           Self().TryF<TCommand<CC, TagFwd> >();
  }

  template <TCmdCode CC>
  bool Try(const TCommandBase<CC, TagBwd>*)
  {
    return Self().CheckCode(CC) && 
           Self().TryB<TCommand<CC, TagBwd> >();
  }

  template <TCmdCode CC>
  bool Try(const TCmdPair<CC>*)
  {
    return CheckCode(TCmdPair<CC>::ccF,
                     TCmdPair<CC>::ccB) && 
           Self().TryP<TCmdPair<CC> >();
  }

 private:
  bool CheckCode(TCmdCode cc)
  { return Self().CheckCode(cc); }

  bool CheckCode(TCmdCode ccF, TCmdCode ccB)
  { if (ccF==ccB) return Self().CheckCode(ccF);
    return Self().CheckCode(ccF) || Self().CheckCode(ccB); }

  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename FHANDLER,
         typename BHANDLER,
         typename RHANDLER>
class TPacketDispFB: public TSplitDisp<TPacketDispFB<FHANDLER, BHANDLER, RHANDLER> > {
 public:
  explicit TPacketDispFB(      FHANDLER       &FHandler,
                               BHANDLER       &BHandler,
                               RHANDLER       &RHandler,
                         const TProtCmdPacket &pkt)
   : m_FHandler(FHandler),
     m_BHandler(BHandler),
     m_RHandler(RHandler),
     m_pkt(pkt) {}
  
  bool CheckCode(TCmdCode cc) const
  {
    return m_pkt.cc==cc;
  }

  template <typename CMDP>
  bool TryP() const
  {
    return m_FHandler.Try<CMDP::TFCmd>(m_pkt) ||
           m_BHandler.Try<CMDP::TBCmd>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryF() const
  {
    return m_FHandler.Try<CMD>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryB() const
  {
    return m_BHandler.Try<CMD>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

 private:
  FHANDLER &m_FHandler;
  BHANDLER &m_BHandler;
  RHANDLER &m_RHandler;

 private:
  const TProtCmdPacket &m_pkt;
};

////////////////////////////////////////////////////////////////////////////////
template<typename DIR, typename HANDLER, typename RHANDLER>
class TPacketDisp;

template<typename FHANDLER, typename RHANDLER>
class TPacketDisp<TagFwd, FHANDLER, RHANDLER>: public TSplitDisp<TPacketDisp<TagFwd, FHANDLER, RHANDLER> > {
 public:
  explicit TPacketDisp(      FHANDLER       &FHandler,
                             RHANDLER       &RHandler,
                       const TProtCmdPacket &pkt)
   : m_FHandler(FHandler),
     m_RHandler(RHandler),
     m_pkt(pkt) {}
  
  bool CheckCode(TCmdCode cc) const
  {
    return m_pkt.cc==cc;
  }

  template <typename CMDP>
  bool TryP() const
  {
    return m_FHandler.Try<CMDP::TFCmd>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryF() const
  {
    return m_FHandler.Try<CMD>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryB() const
  {
    return m_RHandler.Unhandled(m_pkt);
  }

 private:
  FHANDLER &m_FHandler;
  RHANDLER &m_RHandler;

 private:
  const TProtCmdPacket &m_pkt;
};


////////////////////////////////////////////////////////////////////////////////
template<typename BHANDLER, typename RHANDLER>
class TPacketDisp<TagBwd, BHANDLER, RHANDLER>: public TSplitDisp<TPacketDisp<TagBwd, BHANDLER, RHANDLER> > {
 public:
  explicit TPacketDisp(      BHANDLER       &BHandler,
                             RHANDLER       &RHandler,
                       const TProtCmdPacket &pkt)
   : m_BHandler(BHandler),
     m_RHandler(RHandler),
     m_pkt(pkt) {}
  
  bool CheckCode(TCmdCode cc) const
  {
    return m_pkt.cc==cc;
  }

  template <typename CMDP>
  bool TryP() const
  {
    return m_BHandler.Try<CMDP::TBCmd>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryF() const
  {
    return m_RHandler.Unhandled(m_pkt);
  }

  template <typename CMD>
  bool TryB() const
  {
    return m_BHandler.Try<CMD>(m_pkt) ||
           m_RHandler.Unhandled(m_pkt);
  }

 private:
  BHANDLER &m_BHandler;
  RHANDLER &m_RHandler;

 private:
  const TProtCmdPacket &m_pkt;
};

////////////////////////////////////////////////////////////////////////////////
#endif
