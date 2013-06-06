#ifndef BsTypes_h_already_included__10_02_2013__1D566E8
#define BsTypes_h_already_included__10_02_2013__1D566E8
//
// SeVlaT, 10.02.2013
//

#include "StationTypes.h"
#include "TimeTypes.h"
#include "ByteBufAddress.h"

enum TBsModel {
  bsmlUnk,

  bsmlBSF3,
  
  bsmlBSF4,
  bsmlBSM4,
  
  bsmlBSF5,
  
  bsmlBSM6,
  bsmlBSF6,
  
  bsmlBSF7,
  bsmlBS7_SI_M,
  bsmlBSM7,
  bsmlBS7_S,
  bsmlBS7_P,
  bsmlBS7_GSM,
  
  bsmlBSF8,
  bsmlBS8_SI_M,
  bsmlBSM8,
  bsmlBS8_P,
};

struct TBsModelRaw {
  TBsModel Model;
  TDWord  dwModel;
  
  TBsModelRaw(TBsModel aModel, TDWord adwModel)
   : Model(aModel), dwModel(adwModel) {}
   
  TBsModelRaw()
   : Model(bsmlUnk), dwModel(0) {}
};

typedef TOptional<TBsModelRaw> OBsModelRaw;

template <typename CH>
basic_string<CH> GetConstName(TBsModelRaw bmr);


struct TBsModelInfo {
  int  nVer;
  bool bField;
  bool bMaster;
  
  TBsModelInfo()
   : nVer(0),
     bField(false),
     bMaster(false) {}   

  TBsModelInfo(int nV, bool bF, bool bM)
   : nVer(nV),
     bField(bF),
     bMaster(bM) {}   
};

TBsModelInfo GetBsModelInfo(TBsModel bm);

////////////////////////////////////////////////////////////////////////////////
enum TBsMode {
  bsmUnk,
  bsmControl,
  bsmStart,
  bsmFinish,
  bsmReadout,
  bsmClear,
  bsmCheck
}; 

struct TBsModeRaw {
  TBsMode Mode;
  TDWord  dwMode;
  
  TBsModeRaw(TBsMode aMode, TDWord adwMode)
   : Mode(aMode), dwMode(adwMode) {}
   
  TBsModeRaw()
   : Mode(bsmUnk), dwMode(0) {}
};

typedef TOptional<TBsModeRaw> OBsModeRaw;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename CH, bool PREF=false>
struct TBsConstName {
  static const CH* Get(TBsMode  bm, const CH *szDef);
  static const CH* Get(TBsMode  bm);
  static const CH* Get(TBsModel bm, const CH *szDef);
  static const CH* Get(TBsModel bm);

  static basic_string<CH> Get(TBsModeRaw  bmr);
  static basic_string<CH> Get(TBsModelRaw bmr);
};

typedef TBsConstName<wchar_t, false> TBsConstNameW;

////////////////////////////////////////////////////////////////////////////////
template<typename INT, int TAG>
class TIntLabel {
 public:
  TIntLabel(): m_n() {}
  explicit TIntLabel(INT n): m_n(n) {}
  
 public:
  INT Get() const { return m_n; }
  
 public:
  void Set(INT n) { m_n=n; }

 private:
  INT m_n; 
};

////////////////////////////////////////////////////////////////////////////////
typedef TIntLabel<TUInt, 'BsC'>  TBsCode;
typedef TIntLabel<TByte, 'BsCb'> TBsCodeB;
typedef TIntLabel<TWord, 'BsCw'> TBsCodeW;

typedef TIntLabel<TUInt, 'BsSn'> TBsSerNum;

typedef TOptional<TBsCode>   OBsCode;
typedef TOptional<TBsCodeB>  OBsCodeB;
typedef TOptional<TBsCodeW>  OBsCodeW;

typedef TOptional<TBsSerNum> OBsSerNum;

////////////////////////////////////////////////////////////////////////////////
struct TBsInfo {
  OBsSerNum  oSerNum;
  OBsCode    oCode;
  
  OBsModelRaw oModel; 
  OBsModeRaw  oMode;
  
  OUInt onMemSizeKiB;
  OBool obOverflow;
  OUInt onBackupPtr;
};

typedef TOptional<TBsInfo> OBsInfo;
////////////////////////////////////////////////////////////////////////////////

// Base station addresses retrieved from BOSCO

const TBbAddress2Be c_BsAdr_OLD_SERIAL    (0x00);  // 2 bytes - only up to BSx6, numbers < 65.536
const TBbAddress2Be c_BsAdr_OLD_CPU_ID    (0x02);  // 2 bytes - only up to BSx6, numbers < 65.536
const TBbAddress4Be c_BsAdr_SERIAL_NO     (0x00);  // 4 bytes - only after BSx7, numbers > 70.000
                                                   //   (if byte 0x00 > 0, better use OLD offsets)
const TBbAddress3Be c_BsAdr_FIRMWARE      (0x05);  // 3 bytes
const TBbAddress3Be c_BsAdr_BUILD_DATE    (0x08);  // 3 bytes - YYMMDD
const TBbAddress2Be c_BsAdr_MODEL_ID      (0x0B);  // 2 bytes:
const TBbAddress1   c_BsAdr_MEM_SIZE      (0x0D);  // 1 byte - in KB
const TBbAddress3Be c_BsAdr_BAT_DATE      (0x15);  // 3 bytes - YYMMDD
const TBbAddress2Be c_BsAdr_BAT_CAP       (0x19);  // 2 bytes - battery capacity in mAh (as multiples of 14.0625?!)

const TBbAddress4   c_BsAdr_BACKUP_PTR    (0x22, 0x21, 0x1D, 0x1C);

const TBbAddress1   c_BsAdr_SI6_CB        (0x33);  // 1 byte - bitfield defining which SI Card 6 blocks to read:
const TBbAddress1   c_BsAdr_MEM_OVERFLOW  (0x3D);  // 1 byte - memory overflow if != 0x00
const TBbAddress1   c_BsAdr_PROGRAM       (0x70);  // 1 byte - station program: xx0xxxxxb competition, xx1xxxxxb training
const TBbAddress1   c_BsAdr_MODE          (0x71);  // 1 byte - see SI station modes below
const TBbAddress1   c_BsAdr_STATION_CODE  (0x72);  // 1 byte
const TBbAddress1   c_BsAdr_PROTO         (0x74);  // 1 byte - protocol configuration, bit mask value:
const TBbAddress3Be c_BsAdr_WAKEUP_DATE   (0x75);  // 3 bytes - YYMMDD
const TBbAddress3Be c_BsAdr_WAKEUP_TIME   (0x78);  // 3 bytes - 1 byte day (see below), 2 bytes seconds after midnight/midday
const TBbAddress3Be c_BsAdr_SLEEP_TIME    (0x7B);  // 3 bytes - 1 byte day (see below), 2 bytes seconds after midnight/midday
                                                   //   xxxxxxx0b - seconds relative to midnight/midday: 0 = am, 1 = pm
                                                   //   xxxx000xb - day of week: 000 = Sunday, 110 = Saturday
                                                   //   xx00xxxxb - week counter 0..3, relative to programming date

  
              

#endif
