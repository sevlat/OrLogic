// SeVlaT, 23.06.2012
#include "StdAfx.h"

#include "../CommandCode.h"

// Ensure that any byte can be converted to TCmdCode and vice versa
BOOST_STATIC_ASSERT(TCmdCode(0x00)==int(0x00));
BOOST_STATIC_ASSERT(TCmdCode(0xFF)==int(0xFF));


namespace {

template<TCmdCode cc, int ncc>
struct Value_Should_Be_Equal_To_Command_Code {
  int a[cc==ncc? 1: -1];
  enum { ccVal=cc };
};

struct TCommandInfoMap {
  TCmdCode     cc;
  TCommandInfo ci;
};

#ifdef COMCODE
  #error "Macro COMCODE should not be defined"
#endif

#define COMCODE(x, y) \
  TCmdCode(Value_Should_Be_Equal_To_Command_Code<(x), (y)>::ccVal)


#ifdef COMINF
  #error "Macro COMINF should not be defined"
#endif

#define COMINF TCommandInfo

using namespace CmdCd;  
  
const TCommandInfoMap c_SiCommands[]={

{ COMCODE(Beep,         0x06), COMINF(ctLite, -1,  "Beep",         "beep"   ) },
{ COMCODE(Nak,          0x15), COMINF(ctLite, -1,  "Nak",          "nak"    ) },
                                                
{ COMCODE(bSnC5,        0x30), COMINF(ctBase,   4, "bSnC5",        "set start number si 5"   ) },
{ COMCODE(bGetC5,       0x31), COMINF(ctBase, 130, "bGetC5",       "get data from si5"   ) },
{ COMCODE(CardIns5RemB, 0x46), COMINF(ctBase,      "CardIns5RemB", "si card detected (5) or removed (all)"   ) },
{ COMCODE(bCout,        0x49), COMINF(ctBase,      "bCout",        "si card removed"   ) },
{ COMCODE(bPunch,       0x53), COMINF(ctBase,      "bPunch",       "auto sent punch record"   ) },
{ COMCODE(bExtTT,       0x54), COMINF(ctBase,      "bExtTT",       "si external time trigger"   ) },
{ COMCODE(bGetC6,       0x61), COMINF(ctBase,      "bGetC6",       "get data from si 6"   ) },
{ COMCODE(CardIns6B,    0x66), COMINF(ctBase,      "CardIns6B",    "detected si 6"   ) },
{ COMCODE(SetMaSlaveB,  0x70), COMINF(ctBase,      "SetMaSlaveB",  "set main station mode to master or slave"   ) },
{ COMCODE(GetMaSlaveB,  0x71), COMINF(ctBase,      "GetMaSlaveB",  "get main station mode of master or slave"   ) },
{ COMCODE(bSetSys,      0x72), COMINF(ctBase,      "bSetSys",      "write system memory"   ) },
{ COMCODE(bGetSys,      0x73), COMINF(ctBase,      "bGetSys",      "read system memory"   ) },
{ COMCODE(bGetBck,      0x74), COMINF(ctBase,      "bGetBck",      "get backup data"   ) },
{ COMCODE(bErsBck,      0x75), COMINF(ctBase,   1, "bErsBck",      "erase backup pointer"   ) },
{ COMCODE(SetTimeB,     0x76), COMINF(ctBase,   7, "SetTimeB",     "set station time"   ) },
{ COMCODE(GetTimeB,     0x77), COMINF(ctBase,   0, "GetTimeB",     "get station time"   ) },
{ COMCODE(TurnOffB,     0x78), COMINF(ctBase,      "TurnOffB",     "switch station off"   ) },
{ COMCODE(bGBck2,       0x7A), COMINF(ctBase,      "bGBck2",       "get backup data with extended start and finish times"   ) },
{ COMCODE(SetBaudRateB, 0x7E), COMINF(ctBase,      "SetBaudRateB", "set baud rate" ) },

{ COMCODE(GetBckDataE,  0x81), COMINF(ctExt,       "GetBckDataE",  "get backup data"   ) },
{ COMCODE(eSetSys,      0x82), COMINF(ctExt,       "eSetSys",      "write system memory"   ) },
{ COMCODE(GetSysValueE, 0x83), COMINF(ctExt,       "GetSysValueE", "read system memory"   ) },
{ COMCODE(eGetC5,       0xB1), COMINF(ctExt,       "eGetC5",       "get data from si 5"   ) },
{ COMCODE(eGBck,        0xC4), COMINF(ctBase,      "eGBck",        "get backup data"   ) },
{ COMCODE(eGBck2,       0xCA), COMINF(ctBase,      "eGBck2",       "get backup data with extended start and finish times"   ) },
{ COMCODE(ePunch,       0xD3), COMINF(ctExt,       "ePunch",       "autosent punch record"   ) },
{ COMCODE(eGetC6,       0xE1), COMINF(ctExt,       "eGetC6",       "get data from si 6"   ) },
{ COMCODE(CardIns5E,    0xE5), COMINF(ctExt,       "CardIns5E",    "detected si 5"   ) },
{ COMCODE(CardIns6E,    0xE6), COMINF(ctExt,       "CardIns6E",    "detected si 6"   ) },
{ COMCODE(CardRemE,     0xE7), COMINF(ctExt,       "CardRemE",     "card removes"   ) },
{ COMCODE(CardInsHE,    0xE8), COMINF(ctExt,       "CardInsHE",    "detected htags (8,9,p-card,t-card)"   ) },
{ COMCODE(eGetCH,       0xEF), COMINF(ctExt,       "eGetCH",       "get data from htags"   ) },
{ COMCODE(SetMaSlaveE,  0xF0), COMINF(ctExt,       "SetMaSlaveE",  "set main station mode to master or slave"   ) },
{ COMCODE(GetMaSlaveE,  0xF1), COMINF(ctExt,       "GetMaSlaveE",  "get main station mode of master or slave"   ) },
{ COMCODE(eErsBck,      0xF5), COMINF(ctExt,       "eErsBck",      "erase backup pointer"   ) },
{ COMCODE(SetTimeE,     0xF6), COMINF(ctExt,       "SetTimeE",     "set station time"   ) },
{ COMCODE(GetTimeE,     0xF7), COMINF(ctExt,       "GetTimeE",     "get station time"   ) },
{ COMCODE(eTurnOff,     0xF8), COMINF(ctExt,       "eTurnOff",     "switch station off"   ) },
{ COMCODE(BeepE,        0xF9), COMINF(ctExt,       "BeepE",        "beep"   ) },
{ COMCODE(SetBaudRateE, 0xFE), COMINF(ctExt,       "SetBaudRateE", "set baud rate"   ) },

};

#undef COMINF

#undef COMCODE

template <int N>
const TCommandInfo* LookUpCommandInfo(const TCommandInfoMap (&SiCommands)[N],
                                            TCmdCode          cc)
{
  struct IsThis {
   public:
    explicit IsThis(TCmdCode cc): m_cc(cc) {}
    bool operator()(const TCommandInfoMap &cim) const { return m_cc==cim.cc; }
    
   private:
    TCmdCode m_cc;
  };
  
  const TCommandInfoMap *pBegin=SiCommands;
  const TCommandInfoMap *pEnd  =SiCommands+N;
  
  const TCommandInfoMap *pFound=std::find_if(pBegin, pEnd, IsThis(cc));
  if (pFound!=pEnd) return &pFound->ci;
  
  return 0;
}

TCommandType RoughGuessCommandType(TCmdCode cc)
{
  if (cc>=0x80) return ctExt;
  return ctBase;
}

} // namespace

const TCommandInfo* GetCommandInfoPtr(TCmdCode cc)
{
  return LookUpCommandInfo(c_SiCommands, cc);
}

const TCommandInfo& GetCommandInfoRef(TCmdCode cc)
{
  const TCommandInfo *pci=LookUpCommandInfo(c_SiCommands, cc);
  if (pci) return *pci;
  
  const TCommandType ct=RoughGuessCommandType(cc);
  
  if (ct==ctExt) {
    static const TCommandInfo c_UnknownExtCommandInfo
                            (ctExt, "eUnk",  "unknown", TCommandInfo::TTagUnknown());
     
    return c_UnknownExtCommandInfo;
  }

  static const TCommandInfo c_UnknownBaseCommandInfo
                            (ctBase, "bUnk",  "unknown", TCommandInfo::TTagUnknown());

  return c_UnknownBaseCommandInfo;
}

OCommandType GetCommandType(TCmdCode cc)
{
  const TCommandInfo *pci=LookUpCommandInfo(c_SiCommands, cc);
  if (!pci) return None;
  return pci->ct;
}

TCommandType GuessCommandType(TCmdCode cc)
{
  const OCommandType oct=GetCommandType(cc);
  if (oct) return *oct;
  
  return RoughGuessCommandType(cc);
}

OCmdCode CmdCode(int n)
{
  if (n<0 && n>=0x100) return None;

  const TByte b=static_cast<TByte>(n);
  if (b==SpecByte::bWup) return None;
  if (b==SpecByte::bStx) return None;
  if (b==SpecByte::bEtx) return None;
  if (b==SpecByte::bDle) return None;
  
  return static_cast<TCmdCode>(b);
}

OCmdCode LiteCmdCode(int n)
{
  const OCmdCode occ=CmdCode(n);
  if (occ) {  
    const OCommandType oct=GetCommandType(*occ);
    if (oct && (*oct==ctLite)) return occ;
  }

  return None;
}
