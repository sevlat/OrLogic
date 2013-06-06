#ifndef CmdData_h_already_included__08_09_2012__2A9A7A00
#define CmdData_h_already_included__08_09_2012__2A9A7A00
//
// SeVlaT, 08.09.2012
//

#include "Types.h"
#include "Fwd.h"

#include "ByteBuffer.h"

#include "TimeTypes.h"

class TagSet {};
class TagGet {};

struct CmddVoid {
 protected: ~CmddVoid() {}
};

struct CmddRaw {
  TByteBuffer data;
  
 protected:
  CmddRaw() {}
  CmddRaw(const TByteBuffer &abuf): data(abuf) {}
  ~CmddRaw() {}
};

////////////////////////////////////////////////////////////////////////////////
// Setting master/slave
////////////////////////////////////////////////////////////////////////////////
struct CmddFSetMaSlave {
  bool bMaster;
  
 protected:
  CmddFSetMaSlave();
  explicit CmddFSetMaSlave(bool bM);
   ~CmddFSetMaSlave() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddBMaSlaveB {
  bool bMaster;
  TByte bCN;
  
 protected:
  CmddBMaSlaveB();
  CmddBMaSlaveB(bool abMaster, TByte abCN);
   ~CmddBMaSlaveB() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddBMaSlaveE {
  bool bMaster;
  TWord wCN;
  
 protected:
  CmddBMaSlaveE();
  CmddBMaSlaveE(bool abMaster, TWord awCN);
   ~CmddBMaSlaveE() {}
};

////////////////////////////////////////////////////////////////////////////////
// Setting baud rate
////////////////////////////////////////////////////////////////////////////////
struct CmddFSetBaudRate {
  bool bHigh;
  
 protected:
  CmddFSetBaudRate();
  explicit CmddFSetBaudRate(bool abHigh);
   ~CmddFSetBaudRate() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddBSetBaudRateB {
  bool  bHigh;
  TByte bCN;
  
 protected:
  CmddBSetBaudRateB();
  CmddBSetBaudRateB(bool abHigh, TByte abCN);
   ~CmddBSetBaudRateB() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddBSetBaudRateE {
  bool  bHigh;
  TWord wCN;
  
 protected:
  CmddBSetBaudRateE();
  CmddBSetBaudRateE(bool abHigh, TWord awCN);
   ~CmddBSetBaudRateE() {}
};

////////////////////////////////////////////////////////////////////////////////
// Station time templates
////////////////////////////////////////////////////////////////////////////////
template <typename TAG>
struct CBTimeB {
  TStationTime t;
  TByte bCN;
  
 protected:
  CBTimeB()
    : bCN(0) {}

  CBTimeB(const TDateTime &at, TByte abCN)
    : t(at), bCN(abCN) {}

   ~CBTimeB() {}
};

////////////////////////////////////////////////////////////////////////////////
template <typename TAG>
struct CBTimeE {
  TStationTimeSS t;
  TWord wCN;
  
 protected:
  CBTimeE()
    : wCN(0) {}

  CBTimeE(const TDateTimeSS &at, TWord awCN)
    : t(at), wCN(awCN) {}

   ~CBTimeE() {}
};

////////////////////////////////////////////////////////////////////////////////
// Setting station time
////////////////////////////////////////////////////////////////////////////////
struct CmddFSetTimeB {
  TDateTime t;
  
 protected:
  CmddFSetTimeB();
  explicit CmddFSetTimeB(const TDateTime &at);
   ~CmddFSetTimeB() {}
};

struct CmddFSetTimeE {
  TStationTimeSS t;

 protected:
  CmddFSetTimeE();
  explicit CmddFSetTimeE(const TDateTimeSS &at);
   ~CmddFSetTimeE() {}
};

typedef CBTimeB<TagGet> CmddBGetTimeB;
typedef CBTimeB<TagSet> CmddBSetTimeB;
typedef CBTimeE<TagGet> CmddBGetTimeE;
typedef CBTimeE<TagSet> CmddBSetTimeE;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct CmddFGetSysValueE {
  TByte bAddr;
  TByte bLen;
  
 protected:
  CmddFGetSysValueE();
  CmddFGetSysValueE(TByte abAddr, TByte abLen);
   ~CmddFGetSysValueE() {}
};

struct CmddBGetSysValueE {
  TByte bAddr;
  TWord wCN;
  
  TByteBuffer data;
  
 protected:
  CmddBGetSysValueE();
  CmddBGetSysValueE(TByte abAddr, TWord awCN);
   ~CmddBGetSysValueE() {}
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct CmddFGetBckDataE {
  TDWord dwAddr;
  TByte  bLen;
  
 protected:
  CmddFGetBckDataE();
  CmddFGetBckDataE(TDWord adwAddr, TByte abLen);
   ~CmddFGetBckDataE() {}
};

struct CmddBGetBckDataE {
  TDWord dwAddr;
  TWord  wCN;
  
  TByteBuffer data;

 protected:
  CmddBGetBckDataE();
  CmddBGetBckDataE(TDWord adwAddr, TWord awCN);
   ~CmddBGetBckDataE() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddFBeepE {
  TByte bBeeps;

 protected:
  CmddFBeepE();
  explicit CmddFBeepE(TByte abBeeps);
   ~CmddFBeepE() {}
};

struct CmddBBeepE {
  TByte bBeeps;
  TWord  wCN;

 protected:
  CmddBBeepE();
  CmddBBeepE(TByte abBeeps, TWord awCN);
   ~CmddBBeepE() {}
};

////////////////////////////////////////////////////////////////////////////////
struct CmddFTurnOffB {
  TByte bUnknown;

 protected:
  CmddFTurnOffB();
  explicit CmddFTurnOffB(TByte abUnknown);
   ~CmddFTurnOffB() {}
};

struct CmddBTurnOffB {
  TByte bUnknown;
  TByte bCN;

 protected:
  CmddBTurnOffB();
  CmddBTurnOffB(TByte abUnknown, TByte abCN);
   ~CmddBTurnOffB() {}
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
struct CmddBCardIns5RemB
struct CmddBCardIns6B
struct CmddBCardIns5E
struct CmddBCardIns6E
struct CmddBCardInsHE
struct CmddBCardRemE

struct CmddBCardIns5RemB
struct CmddBCardIns6B
struct CmddBCardInsRemE
*/

struct CmddBCardIns5RemB
{
  bool bInsert;
  
 protected:
  CmddBCardIns5RemB();
  explicit CmddBCardIns5RemB(bool abInsert);
   ~CmddBCardIns5RemB() {}
};

struct CmddBCardIns6B
{
  TByte  bCN;
  TByte  bTI;
  TByte  bTP;
  TDWord dwCardN;

 protected:
  CmddBCardIns6B();
  CmddBCardIns6B(TByte abCN, TByte abTI, TByte abTP, TDWord adwCardN);
   ~CmddBCardIns6B() {}
};

struct CmddBCardInsRemE
{
  TWord  wCN;
  TByte  bCardType;
  TDWord dwCardN;

 protected:
  CmddBCardInsRemE();
  CmddBCardInsRemE(TWord awCN, TByte abCardType, TDWord adwCardN);
   ~CmddBCardInsRemE() {}
};


#endif
