#ifndef CmdsPerform_h_already_included__23_03_2013__329C9F40
#define CmdsPerform_h_already_included__23_03_2013__329C9F40
//
// SeVlaT, 23.03.2013
//

#include "CmdsMake.h"
#include "CmdShpCast.h"
#include "CmdsExchange.h"
#include "CmdTransceive.h"

#include "../CmdProcs.h"

////////////////////////////////////////////////////////////////////////////////

template <TCmdCode FCC>
class TCmdsPerfRes {
 public:
  typedef TCommand<TCmdCdTraits<FCC>::ccB, TagBwd> TBCmd;
  typedef typename TBCmd::TBase                    TBCmdb;
  
  typedef typename TCmdShpTraits_Cmd<TBCmdb>::ShpCmd TBCmds;
  
  TCmdsPerfRes() {}
  
  explicit TCmdsPerfRes(const OCmdExch &ocmde)
   : m_ocmde(ocmde)
  {
    if (m_ocmde &&
        m_ocmde->Status()==TCmdExch::sOk) {
      m_BCmds=CmdShpCast<TBCmdb>(m_ocmde->BCmds());
    }
  }
 
 public:
  OCmdExch m_ocmde;
  TBCmds m_BCmds;

 public:
  typedef typename TBCmds::TBool TBool;

  operator TBool()  const { return  m_BCmds; }
  bool operator !() const { return !m_BCmds; }

 public:
  const TBCmdb& operator*()  const { return m_BCmds.operator *(); }
  const TBCmdb* operator->() const { return m_BCmds.operator ->(); }
};

////////////////////////////////////////////////////////////////////////////////
template <typename FCMD>
struct TCmdsPerfRet {
  typedef TCmdsPerfRes<FCMD::cc> TRes;
};

class TCmdsPerf: public TCmdProcSetF_tmpl<TCmdsPerf, TCmdsPerfRet> {
 public:
  TCmdsPerf(      TCmdTransceiver &Transceiver,
            const TPrefixParams   &PP,
                  TErrList        *pErr)
   : m_PP(PP),
     m_Transceiver(Transceiver),
     m_pErr(pErr) {}

 public:
// Why cannot use TCmdsPerfRes<FCMD::cc> ? !!!!!
  template <typename FCMD>
  typename TCmdsPerfRet<FCMD>::TRes Do()
  {
    return Do1<FCMD>(TCmdsMake<FCMD>()());
  }

  template <typename FCMD, typename ARG>
  typename TCmdsPerfRet<FCMD>::TRes Do(const ARG &a)
  {
    return Do1<FCMD>(TCmdsMake<FCMD>()(a));
  }

  template <typename FCMD, typename ARG0, typename ARG1>
  typename TCmdsPerfRet<FCMD>::TRes Do(const ARG0 &a0, const ARG1 &a1)
  {
    return Do1<FCMD>(TCmdsMake<FCMD>()(a0, a1));
  }

 private:
  template <typename FCMD>
  typename TCmdsPerfRet<FCMD>::TRes Do1(TCmdPtr<typename TCmdoGen<FCMD>::Type> cmds)
  {
    const OCmdExch ocmde=m_Transceiver.Transceive(cmds, &m_PP, m_pErr);
    TCmdsPerfRes<FCMD::cc> res(ocmde);
    return res;
  }

 private:
  const TPrefixParams m_PP;

 private:
  TCmdTransceiver &m_Transceiver;
  TErrList        *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
typedef TCmdsPerfRes<CmdCd::GetMaSlaveB > TCprGetMaSlaveB;
typedef TCmdsPerfRes<CmdCd::GetMaSlaveE > TCprGetMaSlaveE;
typedef TCmdsPerfRes<CmdCd::SetMaSlaveB > TCprSetMaSlaveB;
typedef TCmdsPerfRes<CmdCd::SetMaSlaveE > TCprSetMaSlaveE;
typedef TCmdsPerfRes<CmdCd::SetBaudRateB> TCprSetBaudRateB;
typedef TCmdsPerfRes<CmdCd::SetBaudRateE> TCprSetBaudRateE;
typedef TCmdsPerfRes<CmdCd::GetTimeB    > TCprGetTimeB;
typedef TCmdsPerfRes<CmdCd::GetTimeE    > TCprGetTimeE;
typedef TCmdsPerfRes<CmdCd::SetTimeB    > TCprSetTimeB;
typedef TCmdsPerfRes<CmdCd::SetTimeE    > TCprSetTimeE;
typedef TCmdsPerfRes<CmdCd::GetSysValueE> TCprGetSysValueE;
typedef TCmdsPerfRes<CmdCd::GetBckDataE > TCprGetBckDataE;

#endif
