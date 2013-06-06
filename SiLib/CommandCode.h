#ifndef CommandCode_h_already_included__23_06_2012__24170680
#define CommandCode_h_already_included__23_06_2012__24170680
//
// SeVlaT, 23.06.2012
//

#include "SiTypes.h"

// Command codes and descriptions 
// Retrieved from official documentation and
// open-source projects: LibSportIdent and Bosco

namespace CmdCd { 
  enum TValue {
    cNull        = 0x00,

//  Lite commands
    Beep         = 0x06,
    Nak          = 0x15,

// Base commands                  
    bSnC5        = 0x30,  //     BC_SET_CARDNO = '\x30'
    bGetC5       = 0x31,  //     BC_GET_SI5    = '\x31' # read out SI-card 5 data
                          //     BC_SI5_WRITE  = '\x43' # 02 43 (block: 0x30 to 0x37) (16 bytes) 03
    CardIns5RemB = 0x46,  //     BC_SI5_DET    = '\x46' # SI-card 5 inserted (46 49) or removed (46 4F)
    bCout        = 0x49,
    bPunch       = 0x53,  //     BC_TRANS_REC  = '\x53' # autosend timestamp (online control)
    bExtTT       = 0x54,  //     BC_TRANS_TIME = '\x54' # autosend timestamp (lightbeam trigger)
    bGetC6       = 0x61,  //     BC_GET_SI6    = '\x61' # read out SI-card 6 data
    CardIns6B    = 0x66,  //     BC_SI6_DET    = '\x66' # SI-card 6 inserted
    SetMaSlaveB  = 0x70,  //     BC_SET_MS     = '\x70' # \x4D="M"aster, \x53="S"lave
    GetMaSlaveB  = 0x71,  //     BC_GET_MS     = '\x71'
    bSetSys      = 0x72,  //     BC_SET_SYS_VAL= '\x72'
    bGetSys      = 0x73,  //     BC_GET_SYS_VAL= '\x73'
    bGetBck      = 0x74,  //     BC_GET_BDATA  = '\x74' # Note: response carries '\xC4'!
    bErsBck      = 0x75,  //     BC_ERASE_BDATA= '\x75'
    SetTimeB     = 0x76,  //     BC_SET_TIME   = '\x76'
    GetTimeB     = 0x77,  //     BC_GET_TIME   = '\x77'
    TurnOffB     = 0x78,  //     BC_OFF        = '\x78'
    bGBck2       = 0x7A,  //     BC_GET_BDATA2 = '\x7A' # Note: response carries '\xCA'!
    SetBaudRateB = 0x7E,  //     BC_SET_BAUD   = '\x7E' # 0=4800 baud, 1=38400 baud

// Extended commands                  
    GetBckDataE  = 0x81,  //     C_GET_BACKUP  = '\x81'
    eSetSys      = 0x82,  //     C_SET_SYS_VAL = '\x82'
    GetSysValueE = 0x83,  //     C_GET_SYS_VAL = '\x83'
                          //     C_SRR_WRITE   = '\xA2' # ShortRangeRadio - SysData write
                          //     C_SRR_READ    = '\xA3' # ShortRangeRadio - SysData read
                          //     C_SRR_QUERY   = '\xA6' # ShortRangeRadio - network device query
                          //     C_SRR_PING    = '\xA7' # ShortRangeRadio - heartbeat from linked devices, every 50 seconds
                          //     C_SRR_ADHOC   = '\xA8' # ShortRangeRadio - ad-hoc message, f.ex. from SI-ActiveCard
    eGetC5       = 0xB1,  //     C_GET_SI5     = '\xB1' # read out SI-card 5 data
    eGBck        = 0xC4,  
    eGBck2       = 0xCA,  
    ePunch       = 0xD3,  //     C_TRANS_REC   = '\xD3' # autosend timestamp (online control)
                          //     C_CLEAR_CARD  = '\xE0' # found on SI-dev-forum: 02 E0 00 E0 00 03 (http://www.sportident.com/en/forum/8/56#59)
    eGetC6       = 0xE1,  //     C_GET_SI6     = '\xE1' # read out SI-card 6 data block
    CardIns5E    = 0xE5,  //     C_SI5_DET     = '\xE5' # SI-card 5 inserted
    CardIns6E    = 0xE6,  //     C_SI6_DET     = '\xE6' # SI-card 6 inserted
    CardRemE     = 0xE7,  //     C_SI_REM      = '\xE7' # SI-card removed
    CardInsHE    = 0xE8,  //     C_SI9_DET     = '\xE8' # SI-card 8/9/10/11/p/t inserted
    eGetCH       = 0xEF,  //     C_GET_SI9     = '\xEF' # read out SI-card 8/9/10/11/p/t data block
    SetMaSlaveE  = 0xF0,  //     C_SET_MS      = '\xF0' # \x4D="M"aster, \x53="S"lave
    GetMaSlaveE  = 0xF1,  //     C_GET_MS      = '\xF1'
    eErsBck      = 0xF5,  //     C_ERASE_BDATA = '\xF5'
    SetTimeE     = 0xF6,  //     C_SET_TIME    = '\xF6'
    GetTimeE     = 0xF7,  //     C_GET_TIME    = '\xF7'
    eTurnOff     = 0xF8,  //     C_OFF         = '\xF8'
    BeepE        = 0xF9,  //     C_BEEP        = '\xF9' # 02 F9 (number of beeps) (CRC16) 03
    SetBaudRateE = 0xFE   //     C_SET_BAUD    = '\xFE' # \x00=4800 baud, \x01=38400 baud
  };
};

typedef CmdCd::TValue TCmdCode;

typedef TOptional<TCmdCode> OCmdCode;

inline TCmdCode Ccc(int nCc)
{ return static_cast<TCmdCode>(nCc); }

OCmdCode CmdCode(int n);

enum TCommandType {
  ctLite,
  ctBase,
  ctExt,
};
typedef TOptional<TCommandType> OCommandType;

struct TCommandInfo {
  TCommandType ct;
  
  OUInt onBSize;
  
  const char *szName;
  const char *szDescr;
  
  bool bUnknown;
  
  struct TTagUnknown {};
//  static const TTagUnknown Unknown;
  
  TCommandInfo(TCommandType act, OUInt aonBSize, const char *aszName, const char *aszDescr)
   : ct(act),
     onBSize(aonBSize),
     szName(aszName),
     szDescr(aszDescr),
     bUnknown(false) {}
   
  TCommandInfo(TCommandType act, const char *aszName, const char *aszDescr)
   : ct(act),
     szName(aszName),
     szDescr(aszDescr),
     bUnknown(false) {}

  TCommandInfo(TCommandType act, const char *aszName, const char *aszDescr, TTagUnknown)
   : ct(act),
     szName(aszName),
     szDescr(aszDescr),
     bUnknown(true) {}
};

const TCommandInfo* GetCommandInfoPtr(TCmdCode cc);
const TCommandInfo& GetCommandInfoRef(TCmdCode cc);

OCommandType GetCommandType(TCmdCode cc);
TCommandType GuessCommandType(TCmdCode cc);

OCmdCode LiteCmdCode(int n);


#endif
