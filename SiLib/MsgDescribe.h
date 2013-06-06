#ifndef MsgDescribe_h_already_included__24_10_2012__34D06600
#define MsgDescribe_h_already_included__24_10_2012__34D06600
//
// SeVlaT, 24.10.2012
//

#include "CmdVisitor.h"
#include "DescribeUtils.h"
#include "CmdDataDescribe.h"

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
inline void DescribeDir(std::ostream &os);

template <>
inline void DescribeDir<TagFwd>(std::ostream &os) { os << " >>"; }

template <>
inline void DescribeDir<TagBwd>(std::ostream &os) { os << "<< "; }

template <>
inline void DescribeDir<TagUnk>(std::ostream &os) { os << "<?>"; }

////////////////////////////////////////////////////////////////////////////////
template <typename CAUSE>
inline void DescribeCause(std::ostream &os);

template <>
inline void DescribeCause<CauseCmdUnparseable>(std::ostream &os) { os << " unP"; }
template <>               
inline void DescribeCause<CauseCmdUnfamiliar> (std::ostream &os) { os << " unF"; }

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
void DescribeDirCmdCode(std::ostream &os, TCmdCode cc, const TCommandInfo *pci)
{
  DescribeDir<DIR>(os);
  os << " ";
  DescribeCmdCode(os, cc, pci);
}

template <typename DIR>
void DescribeCommSetup(std::ostream &os, const TCommSetup &cs)
{
  DescribeDir<DIR>(os);
  os << "Communication set up.";
}

template <TCmdCode CC, typename DIR>
void DescribeCmd(std::ostream &os, const TCommandBase<CC, DIR> &cmd)
{
  DescribeDirCmdCode<DIR>(os, CC, cmd.GetInfoPtr());
  
  os << ": ";
  DescribeCmdd(os, cmd);
}

template <typename DIR, typename CAUSE>
void DescribeCmd(std::ostream &os, const TRawCommand_Base<DIR, CAUSE> &cmd)
{
  DescribeDirCmdCode<DIR>(os, cmd.cc, cmd.GetInfoPtr());
  DescribeCause<CAUSE>(os);
  
  os << ": ";
  DescribeCmdd(os, cmd);
}

template <typename DIR, typename CAUSE>
void DescribePacket(std::ostream &os, const TProtCmdPacket &pkt)
{
  DescribeDirCmdCode<DIR>(os, pkt.cc, GetCommandInfoPtr(pkt.cc));
  DescribeCause<CAUSE>(os);
  
  os << ": ";
  DescribeBufLen(os, pkt.buf, 12);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class TDescrRawCmdVisitor {
 public:
  explicit TDescrRawCmdVisitor(std::ostream &os): m_os(os) {}

 public:
  template <typename DIR, typename CAUSE>
  void operator ()(const TRawCommand_Base<DIR, CAUSE> &cmd) const
   { DescribeCmd(m_os, cmd); }

  void operator ()(const TCommSetup &cs) const { DescribeCommSetup<TagUnk/*!!!!!*/>(m_os, cs); }

 private:
  std::ostream &m_os;
};

typedef TRawCmdVisitorV<TDescrRawCmdVisitor, std::ostream&, TagFwd> TFDescrRawCmdVisitorV;
typedef TRawCmdVisitorV<TDescrRawCmdVisitor, std::ostream&, TagBwd> TBDescrRawCmdVisitorV;
typedef TRawCmdVisitorV<TDescrRawCmdVisitor, std::ostream&, TagUnk> TUDescrRawCmdVisitorV;

////////////////////////////////////////////////////////////////////////////////
class TDescrRawPktVisitor {
 public:
  explicit TDescrRawPktVisitor(std::ostream &os): m_os(os) {}

 public:
  template <typename DIR, typename CAUSE>
  void operator ()(const TProtCmdPacket &pkt, DIR, CAUSE) const
   { DescribePacket<DIR, CAUSE>(m_os, pkt); }

 private:
  std::ostream &m_os;
};

typedef TRawPktVisitorV<TDescrRawPktVisitor, std::ostream&, TagFwd> TFDescrRawPktVisitorV;
typedef TRawPktVisitorV<TDescrRawPktVisitor, std::ostream&, TagBwd> TBDescrRawPktVisitorV;
typedef TRawPktVisitorV<TDescrRawPktVisitor, std::ostream&, TagUnk> TUDescrRawPktVisitorV;

////////////////////////////////////////////////////////////////////////////////
class TDescrCmdVisitor {
 public:
  explicit TDescrCmdVisitor(std::ostream &os): m_os(os) {}

 public:
// Delete it?
//  template <typename DIR, typename CAUSE>
//  void operator ()(const TRawCommand<DIR, CAUSE> &cmd) const { DescribeCmd(m_os, cmd); }
  
  template <TCmdCode CC, typename DIR>
  void operator ()(const TCommandBase<CC, DIR> &cmd) const { DescribeCmd(m_os, cmd); }

 private:
  std::ostream &m_os;
};

typedef TCmdVisitorV<TDescrCmdVisitor, std::ostream&, TagFwd> TFDescrCmdVisitorV;
typedef TCmdVisitorV<TDescrCmdVisitor, std::ostream&, TagBwd> TBDescrCmdVisitorV;

#endif
