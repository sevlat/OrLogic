#ifndef CmdProcs_h_already_included__21_03_2013__A7BA130
#define CmdProcs_h_already_included__21_03_2013__A7BA130
//
// SeVlaT, 21.03.2013
//

#include "Commands.h"

template<typename DERIVED, template <typename CMD> class RES>
struct TCmdProcSetFB_tmpl {
  typename RES<CmdFSetMaSlaveB >::TRes SetMaSlaveB (bool bMaster)                     { return Self().Do<CmdFSetMaSlaveB >(bMaster);      }
  typename RES<CmdFGetMaSlaveB >::TRes GetMaSlaveB ()                                 { return Self().Do<CmdFGetMaSlaveB >();             }
  typename RES<CmdFSetBaudRateB>::TRes SetBaudRateB(bool bHigh)                       { return Self().Do<CmdFSetBaudRateB>(bHigh);        }
  typename RES<CmdFSetTimeB    >::TRes SetTimeB    (const TDateTime t)                { return Self().Do<CmdFSetTimeB    >(t);            }
  typename RES<CmdFGetTimeB    >::TRes GetTimeB    ()                                 { return Self().Do<CmdFGetTimeB    >();             }
  
 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};                                                                                    
                                                                                      
template<typename DERIVED, template <typename CMD> class RES>                           
struct TCmdProcSetFE_tmpl {                                                           
  typename RES<CmdFSetMaSlaveE >::TRes SetMaSlaveE (bool bMaster)                     { return Self().Do<CmdFSetMaSlaveE >(bMaster);      }
  typename RES<CmdFGetMaSlaveE >::TRes GetMaSlaveE ()                                 { return Self().Do<CmdFGetMaSlaveE >();             }
  typename RES<CmdFSetBaudRateE>::TRes SetBaudRateE(bool bHigh)                       { return Self().Do<CmdFSetBaudRateE>(bHigh);        }
  typename RES<CmdFSetTimeE    >::TRes SetTimeE    (const TDateTimeSS t)              { return Self().Do<CmdFSetTimeE    >(t);            }
  typename RES<CmdFGetTimeE    >::TRes GetTimeE    ()                                 { return Self().Do<CmdFGetTimeE    >();             }
  typename RES<CmdFGetSysValueE>::TRes GetSysValueE(TByte bAddr, TByte bLen)          { return Self().Do<CmdFGetSysValueE>(bAddr, bLen);  }
  typename RES<CmdFGetBckDataE >::TRes GetBckDataE (TDWord dwAddr, TByte bLen)        { return Self().Do<CmdFGetBckDataE >(dwAddr, bLen); }
  
 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};             

template<typename DERIVED, template <typename CMD> class RES>
struct TCmdProcSetBB_tmpl {
  typename RES<CmdBSetMaSlaveB >::TRes BSetMaSlaveB (bool bMaster, TByte bCN)         { return Self().Do<CmdBSetMaSlaveB >(bMaster, bCN); }
  typename RES<CmdBGetMaSlaveB >::TRes BGetMaSlaveB (bool bMaster, TByte bCN)         { return Self().Do<CmdBGetMaSlaveB >(bMaster, bCN); }
  typename RES<CmdBSetBaudRateB>::TRes BSetBaudRateB(bool bHigh, TByte bCN)           { return Self().Do<CmdBSetBaudRateB>(bHigh, bCN);   }
  typename RES<CmdBSetTimeB    >::TRes BSetTimeB    (const TDateTime &t, TByte bCN)   { return Self().Do<CmdBSetTimeB    >(t, bCN);       }
  typename RES<CmdBGetTimeB    >::TRes BGetTimeB    (const TDateTime &t, TByte bCN)   { return Self().Do<CmdBGetTimeB    >(t, bCN);       }
  
 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};             
               
template<typename DERIVED, template <typename CMD> class RES>
struct TCmdProcSetBE_tmpl {
  typename RES<CmdBSetMaSlaveE >::TRes BSetMaSlaveE (bool bMaster, TWord wCN)         { return Self().Do<CmdBSetMaSlaveE >(bMaster, wCN); }
  typename RES<CmdBGetMaSlaveE >::TRes BGetMaSlaveE (bool bMaster, TWord wCN)         { return Self().Do<CmdBGetMaSlaveE >(bMaster, wCN); }
  typename RES<CmdBSetBaudRateE>::TRes BSetBaudRateE(bool bHigh, TWord wCN)           { return Self().Do<CmdBSetBaudRateE>(bHigh, wCN);   }
  typename RES<CmdBSetTimeE    >::TRes BSetTimeE    (const TDateTimeSS &t, TWord wCN) { return Self().Do<CmdBSetTimeE    >(t, wCN);       }
  typename RES<CmdBGetTimeE    >::TRes BGetTimeE    (const TDateTimeSS &t, TWord wCN) { return Self().Do<CmdBGetTimeE    >(t, wCN);       }
  typename RES<CmdBGetSysValueE>::TRes BGetSysValueE(TByte bAddr, TWord wCN)          { return Self().Do<CmdBGetSysValueE>(bAddr, wCN);   }
  typename RES<CmdBGetBckDataE >::TRes BGetBckDataE (TDWord dwAddr, TWord wCN)        { return Self().Do<CmdBGetBckDataE >(dwAddr, wCN);  }
  
 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};

template<typename DERIVED, template <typename CMD> class RES>
struct TCmdProcSet_tmpl: TCmdProcSetFB_tmpl<DERIVED, RES>,
                         TCmdProcSetFE_tmpl<DERIVED, RES>,
                         TCmdProcSetBB_tmpl<DERIVED, RES>,
                         TCmdProcSetBE_tmpl<DERIVED, RES> {};

template<typename DERIVED, template <typename CMD> class RES>
struct TCmdProcSetF_tmpl: TCmdProcSetFB_tmpl<DERIVED, RES>,
                          TCmdProcSetFE_tmpl<DERIVED, RES> {};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template<typename DERIVED, typename CMD, template <typename CMD1> class RES>
struct TCmdProc;

template<typename DERIVED, typename CMD, template <typename CMD1> class RES>
struct TCmdProc_base {
  typedef typename RES<CMD >::TRes TRes;

  TRes DoC() { return Self().Do<CMD>(); }

  template <typename ARG>
  TRes DoC(const ARG &a) { return Self().Do<CMD>(a); }
  
  template <typename ARG0, typename ARG1>
  TRes DoC(const ARG0 &a0, const ARG1 &a1) { return Self().Do<CMD>(a0, a1); }

 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};

////////////////////////////////////////////////////////////////////////////////
#define CMD_PROC_HEAD(CMD)                                         \
  template<typename DERIVED, template <typename CMD1> class RES>   \
  struct TCmdProc<DERIVED, CMD, RES>:                              \
    TCmdProc_base<DERIVED, CMD, RES> 

////////////////////////////////////////////////////////////////////////////////
CMD_PROC_HEAD(CmdFSetMaSlaveB ) { TRes operator ()(bool bMaster)                    { return DoC(bMaster);      } };
CMD_PROC_HEAD(CmdFSetBaudRateB) { TRes operator ()(bool bHigh)                      { return DoC(bHigh);        } };
CMD_PROC_HEAD(CmdFSetTimeB    ) { TRes operator ()(const TDateTime t)               { return DoC(t);            } };
CMD_PROC_HEAD(CmdFGetTimeB    ) { TRes operator ()()                                { return DoC();             } };

CMD_PROC_HEAD(CmdFSetMaSlaveE ) { TRes operator ()(bool bMaster)                    { return DoC(bMaster);      } };
CMD_PROC_HEAD(CmdFGetMaSlaveE ) { TRes operator ()()                                { return DoC();             } };
CMD_PROC_HEAD(CmdFSetBaudRateE) { TRes operator ()(bool bHigh)                      { return DoC(bHigh);        } };
CMD_PROC_HEAD(CmdFSetTimeE    ) { TRes operator ()(const TDateTimeSS t)             { return DoC(t);            } };
CMD_PROC_HEAD(CmdFGetTimeE    ) { TRes operator ()()                                { return DoC();             } };
CMD_PROC_HEAD(CmdFGetSysValueE) { TRes operator ()(TByte bAddr, TByte bLen)         { return DoC(bAddr, bLen);  } };
CMD_PROC_HEAD(CmdFGetBckDataE ) { TRes operator ()(TDWord dwAddr, TByte bLen)       { return DoC(dwAddr, bLen); } };

CMD_PROC_HEAD(CmdBSetMaSlaveB ) { TRes operator ()(bool bMaster, TByte bCN)         { return DoC(bMaster, bCN); } };
CMD_PROC_HEAD(CmdBGetMaSlaveB ) { TRes operator ()(bool bMaster, TByte bCN)         { return DoC(bMaster, bCN); } };
CMD_PROC_HEAD(CmdBSetBaudRateB) { TRes operator ()(bool bHigh, TByte bCN)           { return DoC(bHigh, bCN);   } };
CMD_PROC_HEAD(CmdBSetTimeB    ) { TRes operator ()(const TDateTime &t, TByte bCN)   { return DoC(t, bCN);       } };
CMD_PROC_HEAD(CmdBGetTimeB    ) { TRes operator ()(const TDateTime &t, TByte bCN)   { return DoC(t, bCN);       } };

CMD_PROC_HEAD(CmdBSetMaSlaveE ) { TRes operator ()(bool bMaster, TWord wCN)         { return DoC(bMaster, wCN); } };
CMD_PROC_HEAD(CmdBGetMaSlaveE ) { TRes operator ()(bool bMaster, TWord wCN)         { return DoC(bMaster, wCN); } };
CMD_PROC_HEAD(CmdBSetBaudRateE) { TRes operator ()(bool bHigh, TWord wCN)           { return DoC(bHigh, wCN);   } };
CMD_PROC_HEAD(CmdBSetTimeE    ) { TRes operator ()(const TDateTimeSS &t, TWord wCN) { return DoC(t, wCN);       } };
CMD_PROC_HEAD(CmdBGetTimeE    ) { TRes operator ()(const TDateTimeSS &t, TWord wCN) { return DoC(t, wCN);       } };
CMD_PROC_HEAD(CmdBGetSysValueE) { TRes operator ()(TByte bAddr, TWord wCN)          { return DoC(bAddr, wCN);   } };
CMD_PROC_HEAD(CmdBGetBckDataE ) { TRes operator ()(TDWord dwAddr, TWord wCN)        { return DoC(dwAddr, wCN);  } };

#undef CMD_PROC_HEAD

#endif
