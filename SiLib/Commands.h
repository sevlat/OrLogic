#ifndef Commands_h_already_included__05_10_2012__1005A320
#define Commands_h_already_included__05_10_2012__1005A320
//
// SeVlaT, 05.10.2012
//

// 
#include "CmdTypes.h"
#include "CmdData.h"

#include "CommandCode.h"

template <TCmdCode CC, typename DIR>
struct TCcDirTraits_base;

#define DECL_CMDF_TRAITS(CCF, CMDDF)       \
template <>                                \
struct TCcDirTraits_base<CCF, TagFwd> {    \
  typedef CMDDF TCmdd;                     \
};

#define DECL_CMDB_TRAITS(CCB, CMDDB)       \
template <>                                \
struct TCcDirTraits_base<CCB, TagBwd> {    \
  typedef CMDDB TCmdd;                     \
};

#define DECL_CMDP_TRAITS(CC, CMDDF, CMDDB)  DECL_CMDF_TRAITS(TCmdCdTraits<CC>::ccF, CMDDF) \
                                            DECL_CMDB_TRAITS(TCmdCdTraits<CC>::ccB, CMDDB)

DECL_CMDF_TRAITS(CmdCd::Beep,         CmddVoid)

DECL_CMDB_TRAITS(CmdCd::Nak,          CmddVoid)

DECL_CMDP_TRAITS(CmdCd::GetMaSlaveB,  CmddVoid,          CmddBMaSlaveB     )
DECL_CMDP_TRAITS(CmdCd::GetMaSlaveE,  CmddVoid,          CmddBMaSlaveE     )

DECL_CMDP_TRAITS(CmdCd::SetMaSlaveB,  CmddFSetMaSlave,   CmddBMaSlaveB     )
DECL_CMDP_TRAITS(CmdCd::SetMaSlaveE,  CmddFSetMaSlave,   CmddBMaSlaveE     )

DECL_CMDP_TRAITS(CmdCd::SetBaudRateB, CmddFSetBaudRate,  CmddBSetBaudRateB )
DECL_CMDP_TRAITS(CmdCd::SetBaudRateE, CmddFSetBaudRate,  CmddBSetBaudRateE )

DECL_CMDP_TRAITS(CmdCd::GetTimeB,     CmddVoid,          CmddBGetTimeB     )
DECL_CMDP_TRAITS(CmdCd::GetTimeE,     CmddVoid,          CmddBGetTimeE     )

DECL_CMDP_TRAITS(CmdCd::SetTimeB,     CmddFSetTimeB,     CmddBSetTimeB     )
DECL_CMDP_TRAITS(CmdCd::SetTimeE,     CmddFSetTimeE,     CmddBSetTimeE     )

DECL_CMDP_TRAITS(CmdCd::GetSysValueE, CmddFGetSysValueE, CmddBGetSysValueE )

DECL_CMDP_TRAITS(CmdCd::GetBckDataE,  CmddFGetBckDataE,  CmddBGetBckDataE  )

DECL_CMDP_TRAITS(CmdCd::BeepE,        CmddFBeepE,        CmddBBeepE        )
DECL_CMDP_TRAITS(CmdCd::TurnOffB,     CmddFTurnOffB,     CmddBTurnOffB     )

DECL_CMDB_TRAITS(CmdCd::CardIns5RemB, CmddBCardIns5RemB)
DECL_CMDB_TRAITS(CmdCd::CardIns6B,    CmddBCardIns6B)
DECL_CMDB_TRAITS(CmdCd::CardIns5E,    CmddBCardInsRemE)
DECL_CMDB_TRAITS(CmdCd::CardIns6E,    CmddBCardInsRemE)
DECL_CMDB_TRAITS(CmdCd::CardRemE ,    CmddBCardInsRemE)
DECL_CMDB_TRAITS(CmdCd::CardInsHE,    CmddBCardInsRemE)

#undef DECL_CMDB_TRAITS
#undef DECL_CMDF_TRAITS
#undef DECL_CMDP_TRAITS


template <typename CMDD,
          typename BASE,
          template <typename DERIVED> class CRTP_BASE>
class TCmdAncestor;

// Macro definition
// !!! Note! Macro contain an open "{" bracket
#define DECL_CMD_ANC(CMDD)                                                     \
  template <typename BASE,                                                     \
            template <typename DERIVED> class CRTP_BASE>                       \
  class TCmdAncestor<CMDD, BASE, CRTP_BASE>:                                   \
                     public BASE,                                              \
                     public CRTP_BASE<TCmdAncestor<CMDD, BASE, CRTP_BASE> > {  \
    typedef CRTP_BASE<TCmdAncestor<CMDD, BASE, CRTP_BASE> > TCrtpBase;         \
   public:                                                                     \
    typedef BASE TBase;                                                        \
    typedef CMDD TData;                                                        \
    typedef typename TCrtpBase::TDir TDir;                                     \
   public:                                                                     \
    TCmdAncestor() {}                                                          \
   public:                                                                     \

#define DECL_CMD_ANCX(CMDD)  DECL_CMD_ANC(CMDD) explicit

DECL_CMD_ANC (CmddVoid)                                                                                         };
DECL_CMD_ANCX(CmddRaw)           TCmdAncestor(const TByteBuffer &abuf)          : TBase(abuf)            {} };
DECL_CMD_ANCX(CmddFSetMaSlave)   TCmdAncestor(bool abMaster)                    : TBase(abMaster)        {} };
DECL_CMD_ANC (CmddBMaSlaveB)     TCmdAncestor(bool abMaster, TByte abCN)        : TBase(abMaster, abCN)  {} };
DECL_CMD_ANC (CmddBMaSlaveE)     TCmdAncestor(bool abMaster, TWord awCN)        : TBase(abMaster, awCN)  {} };
DECL_CMD_ANCX(CmddFSetBaudRate)  TCmdAncestor(bool abHigh)                      : TBase(abHigh)          {} };
DECL_CMD_ANC (CmddBSetBaudRateB) TCmdAncestor(bool abHigh, TByte abCN)          : TBase(abHigh, abCN)    {} };
DECL_CMD_ANC (CmddBSetBaudRateE) TCmdAncestor(bool abHigh, TWord awCN)          : TBase(abHigh, awCN)    {} };
DECL_CMD_ANCX(CmddFSetTimeB)     TCmdAncestor(const TDateTime   &at)            : TBase(at)             {} };
DECL_CMD_ANC (CmddBSetTimeB)     TCmdAncestor(const TDateTime   &at, TByte abCN): TBase(at, abCN)       {} };
DECL_CMD_ANC (CmddBGetTimeB)     TCmdAncestor(const TDateTime   &at, TByte abCN): TBase(at, abCN)       {} };
DECL_CMD_ANCX(CmddFSetTimeE)     TCmdAncestor(const TDateTimeSS &at)            : TBase(at)             {} };      
DECL_CMD_ANC (CmddBSetTimeE)     TCmdAncestor(const TDateTimeSS &at, TWord awCN): TBase(at, awCN)       {} };
DECL_CMD_ANC (CmddBGetTimeE)     TCmdAncestor(const TDateTimeSS &at, TWord awCN): TBase(at, awCN)       {} };
DECL_CMD_ANC (CmddFGetSysValueE) TCmdAncestor(TByte abAddr, TByte abLen)        : TBase(abAddr, abLen)   {} };
DECL_CMD_ANC (CmddBGetSysValueE) TCmdAncestor(TByte abAddr, TWord awCN)         : TBase(abAddr, awCN)    {} };
DECL_CMD_ANC (CmddFGetBckDataE)  TCmdAncestor(TDWord adwAddr, TByte abLen)      : TBase(adwAddr, abLen)  {} };
DECL_CMD_ANC (CmddBGetBckDataE)  TCmdAncestor(TDWord adwAddr, TWord awCN)       : TBase(adwAddr, awCN)   {} };
DECL_CMD_ANCX(CmddFBeepE)        TCmdAncestor(TByte abBeeps)                    : TBase(abBeeps)         {} };   
DECL_CMD_ANC (CmddBBeepE)        TCmdAncestor(TByte abBeeps, TWord awCN)        : TBase(abBeeps, awCN)   {} };
DECL_CMD_ANCX(CmddFTurnOffB)     TCmdAncestor(TByte abUnknown)                  : TBase(abUnknown)       {} };
DECL_CMD_ANC (CmddBTurnOffB)     TCmdAncestor(TByte abUnknown, TWord awCN)      : TBase(abUnknown, awCN) {} };

DECL_CMD_ANCX(CmddBCardIns5RemB) TCmdAncestor(bool abInsert)                    : TBase(abInsert)  {} };
DECL_CMD_ANC (CmddBCardIns6B)    TCmdAncestor(TByte abCN, TByte abTI, TByte abTP, TDWord adwCardN) : TBase(abCN, abTI, abTP, adwCardN)  {} };
DECL_CMD_ANC (CmddBCardInsRemE)  TCmdAncestor(TWord awCN, TByte abCardType, TDWord adwCardN)      : TBase(awCN, abCardType, adwCardN)  {} };

#undef DECL_CMD_ANCX
#undef DECL_CMD_ANC

////////////////////////////////////////////////////////////////////////////////
template <TCmdCode CC, typename DIR>
class TCommandBase: public TCcDirTraits_base<CC, DIR>::TCmdd
{
//  typedef CMDD TBase;
  typedef typename TCcDirTraits_base<CC, DIR>::TCmdd TBase;
 public:
  static const TCmdCode cc=CC;
  
  typedef TCommandBase TCmdb;
  typedef TBase TData;
  typedef DIR   TDir;
  
  static const TCommandInfo* GetInfoPtr() { return GetCommandInfoPtr(cc); }
  static const TCommandInfo& GetInfoRef() { return GetCommandInfoRef(cc); }

 public:
  const TCommandBase& Cmdb() const { return *this; }
  
 protected:
  TCommandBase() {}

  template <typename ARG>
  TCommandBase(const ARG &a): TBase(a) {}
  
  template <typename ARG0, typename ARG1>
  TCommandBase(const ARG0 &a0, const ARG1 &a1): TBase(a0, a1) {}

  template <typename ARG0, typename ARG1, typename ARG2>
  TCommandBase(const ARG0 &a0, const ARG1 &a1, const ARG2 &a2): TBase(a0, a1, a2) {}

  template <typename ARG0, typename ARG1, typename ARG2, typename ARG3>
  TCommandBase(const ARG0 &a0, const ARG1 &a1, const ARG2 &a2, const ARG3 &a3): TBase(a0, a1, a2, a3) {}

  ~TCommandBase() {}
};

////////////////////////////////////////////////////////////////////////////////
template <TCmdCode CC, typename DIR, typename CMDD=typename TCcDirTraits_base<CC, DIR>::TCmdd>
struct TCommand;

// Macro definition
// !!! Note! Macro contain an open "{" bracket
#define DECL_CMD_SPEC(CMDD)                                                    \
  template <TCmdCode CC, typename DIR>                                         \
  class TCommand<CC, DIR, CMDD>: public TCommandBase<CC, DIR> {                \
   public:                                                                     \
    typedef TCommandBase<CC, DIR> TBase;                                       \
   public:                                                                     \
    TCommand() {}                                                         

#define DECL_CMD_SPECX(CMDD)  DECL_CMD_SPEC(CMDD) explicit

DECL_CMD_SPEC (CmddVoid)                                                                                 };
DECL_CMD_SPECX(CmddFSetMaSlave)   TCommand(bool abMaster)                    : TBase(abMaster)        {} };
DECL_CMD_SPEC (CmddBMaSlaveB)     TCommand(bool abMaster, TByte abCN)        : TBase(abMaster, abCN)  {} };
DECL_CMD_SPEC (CmddBMaSlaveE)     TCommand(bool abMaster, TWord awCN)        : TBase(abMaster, awCN)  {} };
DECL_CMD_SPECX(CmddFSetBaudRate)  TCommand(bool abHigh)                      : TBase(abHigh)          {} };
DECL_CMD_SPEC (CmddBSetBaudRateB) TCommand(bool abHigh, TByte abCN)          : TBase(abHigh, abCN)    {} };
DECL_CMD_SPEC (CmddBSetBaudRateE) TCommand(bool abHigh, TWord awCN)          : TBase(abHigh, awCN)    {} };
DECL_CMD_SPECX(CmddFSetTimeB)     TCommand(const TDateTime   &at)            : TBase(at)              {} };
DECL_CMD_SPEC (CmddBSetTimeB)     TCommand(const TDateTime   &at, TByte abCN): TBase(at, abCN)        {} };
DECL_CMD_SPEC (CmddBGetTimeB)     TCommand(const TDateTime   &at, TByte abCN): TBase(at, abCN)        {} };
DECL_CMD_SPECX(CmddFSetTimeE)     TCommand(const TDateTimeSS &at)            : TBase(at)              {} };      
DECL_CMD_SPEC (CmddBSetTimeE)     TCommand(const TDateTimeSS &at, TWord awCN): TBase(at, awCN)        {} };
DECL_CMD_SPEC (CmddBGetTimeE)     TCommand(const TDateTimeSS &at, TWord awCN): TBase(at, awCN)        {} };
DECL_CMD_SPEC (CmddFGetSysValueE) TCommand(TByte abAddr, TByte abLen)        : TBase(abAddr, abLen)   {} };
DECL_CMD_SPEC (CmddBGetSysValueE) TCommand(TByte abAddr, TWord awCN)         : TBase(abAddr, awCN)    {} };
DECL_CMD_SPEC (CmddFGetBckDataE)  TCommand(TDWord adwAddr, TByte abLen)      : TBase(adwAddr, abLen)  {} };
DECL_CMD_SPEC (CmddBGetBckDataE)  TCommand(TDWord adwAddr, TWord awCN)       : TBase(adwAddr, awCN)   {} };
DECL_CMD_SPECX(CmddFBeepE)        TCommand(TByte abBeeps)                    : TBase(abBeeps)         {} };   
DECL_CMD_SPEC (CmddBBeepE)        TCommand(TByte abBeeps, TWord awCN)        : TBase(abBeeps, awCN)   {} };
DECL_CMD_SPECX(CmddFTurnOffB)     TCommand(TByte abUnknown)                  : TBase(abUnknown)       {} };
DECL_CMD_SPEC (CmddBTurnOffB)     TCommand(TByte abUnknown, TWord awCN)      : TBase(abUnknown, awCN) {} };

DECL_CMD_SPEC (CmddBCardIns5RemB) TCommand(bool abInsert)                    : TBase(abInsert) {} };
DECL_CMD_SPEC (CmddBCardIns6B)    TCommand(TByte abCN, TByte abTI, TByte abTP, TDWord adwCardN): TBase(abCN, abTI, abTP, adwCardN) {} };
DECL_CMD_SPEC (CmddBCardInsRemE)  TCommand(TWord awCN, TByte abCardType, TDWord adwCardN)      : TBase(awCN, abCardType, adwCardN) {} };

#undef DECL_CMD_SPECX
#undef DECL_CMD_SPEC

template <TCmdCode CC, typename DIR>
struct TCcDirTraits: TCcDirTraits_base<CC, DIR> {
  typedef typename TCcDirTraits_base<CC, DIR>::TCmdd TCmdd;

  typedef TCommand<CC, DIR, TCmdd> TCmd;
  typedef typename TCmd::TBase     TCmdb;
};

template <typename CMD>
struct TCmdTraits{
  typedef typename CMD::TDir                     TDir;
  typedef typename TDirTraits<TDir>::TCounterDir TCounterDir;
  
  typedef TCommand<CMD::cc, TCounterDir>        TCounterCmd;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DIR, typename CAUSE>
class TRawCommand_Base: public CmddRaw {
 public:                   
  typedef CmddRaw TData;
  typedef DIR     TDir;
  typedef CAUSE   TCause;
  
 public:                   
  const TCommandInfo* GetInfoPtr() const { return GetCommandInfoPtr(cc); }
  const TCommandInfo& GetInfoRef() const { return GetCommandInfoRef(cc); }

 public:                   
  TCmdCode cc;

 protected:
  TRawCommand_Base()
   : cc(CmdCd::cNull) {}
   
  TRawCommand_Base(TCmdCode acc, const TByteBuffer &buf)
   : cc(acc), CmddRaw(buf) {}
                   
  ~TRawCommand_Base() {}
};

template <typename DIR, typename CAUSE>
struct TRawCommand: public TRawCommand_Base<DIR, CAUSE> {
 public:
  typedef TRawCommand_Base<DIR, CAUSE> TBase;

 public:                   
  TRawCommand() {}
  TRawCommand(      TCmdCode     acc,
              const TByteBuffer &buf): TRawCommand_Base(acc, buf) {}
};

////////////////////////////////////////////////////////////////////////////////

template <TCmdCode CC>
struct TCmdPair {
  static const TCmdCode ccF=TCmdCdTraits<CC>::ccF;
  static const TCmdCode ccB=TCmdCdTraits<CC>::ccB;
  
  typedef typename TCcDirTraits<ccF, TagFwd> TFCcDirTraits;
  typedef typename TCcDirTraits<ccB, TagBwd> TBCcDirTraits;
  
  typedef typename TFCcDirTraits::TCmdd TFCmdd;
  typedef typename TBCcDirTraits::TCmdd TBCmdd;

  typedef typename TFCcDirTraits::TCmdb TFCmdb;
  typedef typename TBCcDirTraits::TCmdb TBCmdb;

  typedef typename TFCcDirTraits::TCmd  TFCmd;
  typedef typename TBCcDirTraits::TCmd  TBCmd;
};

////////////////////////////////////////////////////////////
template <typename DIR, typename CMDP>
struct TCmdPairTraits;                      // !!!!! Not used!

template <typename CMDP>
struct TCmdPairTraits<TagFwd, CMDP> {
  typedef typename CMDP::TFCmd  TCmd;
  typedef typename CMDP::TFCmdD TCmdData;
};

template <typename CMDP>
struct TCmdPairTraits<TagBwd, CMDP> {
  typedef typename CMDP::TBCmd  TCmd;
  typedef typename CMDP::TBCmdD TCmdData;
};

////////////////////////////////////////////////////////////
typedef struct {} CmdFNone;

////////////////////////////////////////////////////////////
typedef TRawCommand<TagFwd, CauseCmdUnparseable> CmdFRUnparseable;
typedef TRawCommand<TagBwd, CauseCmdUnparseable> CmdBRUnparseable;
typedef TRawCommand<TagUnk, CauseCmdUnparseable> CmdURUnparseable;

typedef TRawCommand<TagFwd, CauseCmdUnfamiliar>  CmdFRUnfamiliar;
typedef TRawCommand<TagBwd, CauseCmdUnfamiliar>  CmdBRUnfamiliar;
typedef TRawCommand<TagUnk, CauseCmdUnfamiliar>  CmdURUnfamiliar;

////////////////////////////////////////////////////////////
typedef TCommand<CmdCd::Beep, TagFwd> CmdFBeep;

typedef TCommand<CmdCd::Nak,  TagBwd> CmdBNak;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::GetMaSlaveB> CmdPGetMaSlaveB;

typedef CmdPGetMaSlaveB::TFCmd  CmdFGetMaSlaveB;
typedef CmdPGetMaSlaveB::TBCmd  CmdBGetMaSlaveB;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::GetMaSlaveE> CmdPGetMaSlaveE;

typedef CmdPGetMaSlaveE::TFCmd CmdFGetMaSlaveE;
typedef CmdPGetMaSlaveE::TBCmd CmdBGetMaSlaveE;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::SetMaSlaveB> CmdPSetMaSlaveB;

typedef CmdPSetMaSlaveB::TFCmd CmdFSetMaSlaveB;
typedef CmdPSetMaSlaveB::TBCmd CmdBSetMaSlaveB;

////////////////////////////////////////
typedef TCmdPair<CmdCd::SetMaSlaveE> CmdPSetMaSlaveE;

typedef CmdPSetMaSlaveE::TFCmd CmdFSetMaSlaveE;
typedef CmdPSetMaSlaveE::TBCmd CmdBSetMaSlaveE;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::SetBaudRateB> CmdPSetBaudRateB;

typedef CmdPSetBaudRateB::TFCmd CmdFSetBaudRateB;
typedef CmdPSetBaudRateB::TBCmd CmdBSetBaudRateB;

////////////////////////////////////////
typedef TCmdPair<CmdCd::SetBaudRateE> CmdPSetBaudRateE;

typedef CmdPSetBaudRateE::TFCmd CmdFSetBaudRateE;
typedef CmdPSetBaudRateE::TBCmd CmdBSetBaudRateE;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::GetTimeB> CmdPGetTimeB;

typedef CmdPGetTimeB::TFCmd CmdFGetTimeB;
typedef CmdPGetTimeB::TBCmd CmdBGetTimeB;

////////////////////////////////////////
typedef TCmdPair<CmdCd::GetTimeE> CmdPGetTimeE;

typedef CmdPGetTimeE::TFCmd CmdFGetTimeE;
typedef CmdPGetTimeE::TBCmd CmdBGetTimeE;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::SetTimeB> CmdPSetTimeB;

typedef CmdPSetTimeB::TFCmd CmdFSetTimeB;
typedef CmdPSetTimeB::TBCmd CmdBSetTimeB;

////////////////////////////////////////
typedef TCmdPair<CmdCd::SetTimeE> CmdPSetTimeE;

typedef CmdPSetTimeE::TFCmd CmdFSetTimeE;
typedef CmdPSetTimeE::TBCmd CmdBSetTimeE;

////////////////////////////////////////////////////////////
typedef TCmdPair<CmdCd::GetSysValueE> CmdPGetSysValueE;

typedef CmdPGetSysValueE::TFCmd CmdFGetSysValueE;
typedef CmdPGetSysValueE::TBCmd CmdBGetSysValueE;

////////////////////////////////////////
typedef TCmdPair<CmdCd::GetBckDataE> CmdPGetBckDataE;

typedef CmdPGetBckDataE::TFCmd CmdFGetBckDataE;
typedef CmdPGetBckDataE::TBCmd CmdBGetBckDataE;

////////////////////////////////////////
typedef TCmdPair<CmdCd::BeepE> CmdPBeepE;

typedef CmdPBeepE::TFCmd CmdFBeepE;
typedef CmdPBeepE::TBCmd CmdBBeepE;

////////////////////////////////////////
typedef TCmdPair<CmdCd::TurnOffB> CmdPTurnOffB;

typedef CmdPTurnOffB::TFCmd CmdFTurnOffB;
typedef CmdPTurnOffB::TBCmd CmdBTurnOffB;

////////////////////////////////////////
typedef TCommand<CmdCd::CardIns5RemB, TagBwd> CmdBCardIns5RemB;
typedef TCommand<CmdCd::CardIns6B,    TagBwd> CmdBCardIns6B;
typedef TCommand<CmdCd::CardIns5E,    TagBwd> CmdBCardIns5E;
typedef TCommand<CmdCd::CardIns6E,    TagBwd> CmdBCardIns6E;
typedef TCommand<CmdCd::CardRemE ,    TagBwd> CmdBCardRemE;
typedef TCommand<CmdCd::CardInsHE,    TagBwd> CmdBCardInsHE;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef CmdFSetMaSlaveB::TBase     CmdbFSetMaSlaveB;
typedef CmdBSetMaSlaveB::TBase     CmdbBSetMaSlaveB; 

typedef CmdFSetMaSlaveE::TBase     CmdbFSetMaSlaveE; 
typedef CmdBSetMaSlaveE::TBase     CmdbBSetMaSlaveE; 
                       
typedef CmdFGetMaSlaveB::TBase     CmdbFGetMaSlaveB; 
typedef CmdBGetMaSlaveB::TBase     CmdbBGetMaSlaveB; 
                       
typedef CmdFGetMaSlaveE::TBase     CmdbFGetMaSlaveE; 
typedef CmdBGetMaSlaveE::TBase     CmdbBGetMaSlaveE; 
                             
typedef CmdFSetBaudRateB::TBase    CmdbFSetBaudRateB; 
typedef CmdBSetBaudRateB::TBase    CmdbBSetBaudRateB; 
                       
typedef CmdFSetBaudRateE::TBase    CmdbFSetBaudRateE; 
typedef CmdBSetBaudRateE::TBase    CmdbBSetBaudRateE; 
                             
typedef CmdFGetTimeB::TBase        CmdbFGetTimeB; 
typedef CmdBGetTimeB::TBase        CmdbBGetTimeB; 
                             
typedef CmdFGetTimeE::TBase        CmdbFGetTimeE; 
typedef CmdBGetTimeE::TBase        CmdbBGetTimeE; 
                             
typedef CmdFSetTimeB::TBase        CmdbFSetTimeB; 
typedef CmdBSetTimeB::TBase        CmdbBSetTimeB; 
                       
typedef CmdFSetTimeE::TBase        CmdbFSetTimeE; 
typedef CmdBSetTimeE::TBase        CmdbBSetTimeE; 
                             
typedef CmdFGetSysValueE::TBase    CmdbFGetSysValueE; 
typedef CmdBGetSysValueE::TBase    CmdbBGetSysValueE; 
                             
typedef CmdFGetBckDataE::TBase     CmdbFGetBckDataE; 
typedef CmdBGetBckDataE::TBase     CmdbBGetBckDataE; 
                             
typedef CmdFBeepE::TBase           CmdbFBeepE; 
typedef CmdBBeepE::TBase           CmdbBBeepE; 

typedef CmdFTurnOffB::TBase        CmdbFTurnOffB; 
typedef CmdBTurnOffB::TBase        CmdbBTurnOffB; 

typedef CmdFBeep::TBase            CmdbFBeep; 

typedef CmdBNak::TBase             CmdbBNak; 

typedef CmdBCardIns5RemB::TBase    CmdbBCardIns5RemB;
typedef CmdBCardIns6B::TBase       CmdbBCardIns6B;
typedef CmdBCardIns5E::TBase       CmdbBCardIns5E;
typedef CmdBCardIns6E::TBase       CmdbBCardIns6E;
typedef CmdBCardRemE::TBase        CmdbBCardRemE;
typedef CmdBCardInsHE::TBase       CmdbBCardInsHE;

////////////////////////////////////////////////////////////////////////////////
template<typename DISPATCHER>
static bool EnumCmd(DISPATCHER &Disp)
{
  return Disp.Try<CmdPSetMaSlaveB>()  ||
         Disp.Try<CmdPSetMaSlaveE>()  ||
         Disp.Try<CmdPGetMaSlaveB>()  ||
         Disp.Try<CmdPGetMaSlaveE>()  ||
         Disp.Try<CmdPSetBaudRateB>() ||
         Disp.Try<CmdPSetBaudRateE>() ||
         Disp.Try<CmdPGetTimeB>()     ||
         Disp.Try<CmdPGetTimeE>()     ||
         Disp.Try<CmdPSetTimeB>()     ||
         Disp.Try<CmdPSetTimeE>()     ||
         Disp.Try<CmdPGetSysValueE>() ||
         Disp.Try<CmdPGetBckDataE>()  ||
         Disp.Try<CmdPBeepE>()        ||
         Disp.Try<CmdPTurnOffB>()     ||
         Disp.Try<CmdFBeep>()         ||
         Disp.Try<CmdBNak>()          ||
         Disp.Try<CmdBCardIns5RemB>() ||
         Disp.Try<CmdBCardIns6B>()    ||
         Disp.Try<CmdBCardIns5E>()    ||
         Disp.Try<CmdBCardIns6E>()    ||
         Disp.Try<CmdBCardRemE>()     ||
         Disp.Try<CmdBCardInsHE>();
}


#endif
