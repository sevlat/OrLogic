#ifndef BsMasterConnect_h_already_included__14_12_2012__8493BE0
#define BsMasterConnect_h_already_included__14_12_2012__8493BE0
//
// SeVlaT, 14.12.2012
//

#include "SiTypes.h"
#include "BsTypes.h"
#include "CardTypes.h"
#include "TimeTypes.h"

#include "ConfirmedValue.h"

#include "CmdxObserver.h"

struct TCmdTxInfo;
struct TCmdRxInfo;

typedef TConfirmedValue<bool>       CVBool;
typedef TConfirmedValue<TBsModeRaw>    CVBsMode;
typedef TConfirmedValue<TBsModelRaw>   CVBsModel;
typedef TConfirmedValue<TBsCodeB>   CVBsCodeB;
typedef TConfirmedValue<TBsCodeW>   CVBsCodeW;
typedef TConfirmedValue<TBsSerNum>  CVBsSerNum;

typedef TConfirmedValue<TCardNum>   CVCardNum;
typedef TConfirmedValue<TCardModel> CVCardModel;

typedef TConfirmedValueO<bool>       CVBoolO;


struct TBsConnectData {
  OTimePlus otpObscured;
  
  CVBool     cvbPresent;
  CVBsCodeB  cvBsCodeB;
  CVBsCodeW  cvBsCodeW;
  CVBsSerNum cvBsSerNum;
  CVBsMode   cvBsMode;
  CVBsModel  cvBsModel;
  
  void Obscure(OSysTime ot);

  void ConfirmPresent(bool bPresent, OSysTime ot);
  void ConfirmBsCodeB(TBsCodeB bsCode, OSysTime ot);
  void ConfirmBsCodeW(TBsCodeW bsCode, OSysTime ot);
  void ConfirmBsSerNum(TBsSerNum bssn, OSysTime ot);
  void ConfirmBsMode(TBsModeRaw bsm, OSysTime ot);
  void ConfirmBsModel(TBsModelRaw bsml, OSysTime ot);
};


struct TMasterConnectData: TBsConnectData {
  CVBool cvbSupportHiSpeed;
  CVBool cvbSupportLoSpeed;
  CVBool cvbSupportProtBase;
  CVBool cvbSupportProtExt;
  
  void Obscure(OSysTime ot);

  void ConfirmSupportHiSpeed(bool bSupport, OSysTime ot);
  void ConfirmSupportLoSpeed(bool bSupport, OSysTime ot);
  void ConfirmSupportProtBase(bool bSupport, OSysTime ot);
  void ConfirmSupportProtExt(bool bSupport, OSysTime ot);
};

struct TSlaveConnectData: TBsConnectData {
};  

struct TCardConnectData {
  OTimePlus otpObscured;

  CVBool      cvbPresent;
  CVCardNum   cvNum;
  CVCardModel cvModel;

  void Obscure(OSysTime ot);

  void ConfirmCardPresent(TCardNum cn, OSysTime ot);
  void ConfirmCardNum(TCardNum cn, OSysTime ot);
  void ConfirmCardModel(TCardModel cm, OSysTime ot);
};

////////////////////////////////////////////////////////////////////////////////
class TBsMasterConnectObs {
 public:

 public:
  TBsMasterConnectObs();
  
 public: // GetMaSlave
  void OnOk(const CmdbFGetMaSlaveB &FCmd,
                  OSysTime          otF,
            const CmdbBGetMaSlaveB &BCmd,
                  OSysTime          otB);

  void OnOk(const CmdbFGetMaSlaveE &FCmd,
                  OSysTime          otF,
            const CmdbBGetMaSlaveE &BCmd,
                  OSysTime          otB);

 public:
  void OnFailed(const CmdbFGetMaSlaveB &FCmd,
                      OSysTime          otB,
                      TCmdxStatus       Status);

  void OnFailed(const CmdbFGetMaSlaveE &FCmd,
                      OSysTime          otB,
                      TCmdxStatus       Status);


 public: // SetMaSlave
  void OnOk(const CmdbFSetMaSlaveB &FCmd,
                  OSysTime          otF,
            const CmdbBSetMaSlaveB &BCmd,
                  OSysTime          otB);

  void OnOk(const CmdbFSetMaSlaveE &FCmd,
                  OSysTime          otF,
            const CmdbBSetMaSlaveE &BCmd,
                  OSysTime          otB);

 public:
  void OnFailed(const CmdbFSetMaSlaveB &FCmd,
                      OSysTime          otB,
                      TCmdxStatus       Status);

  void OnFailed(const CmdbFSetMaSlaveE &FCmd,
                      OSysTime          otB,
                      TCmdxStatus       Status);

 public: // GetTime
  void OnOk(const CmdbFGetTimeB &FCmd,
                  OSysTime       otF,
            const CmdbBGetTimeB &BCmd,
                  OSysTime       otB);

  void OnOk(const CmdbFGetTimeE &FCmd,
                  OSysTime       otF,
            const CmdbBGetTimeE &BCmd,
                  OSysTime       otB);

 public:
  void OnFailed(const CmdbFGetTimeB &FCmd,
                      OSysTime       otB,
                      TCmdxStatus    Status);

  void OnFailed(const CmdbFGetTimeE &FCmd,
                      OSysTime       otB,
                      TCmdxStatus    Status);

 public: // SetTime
  void OnOk(const CmdbFSetTimeB &FCmd,
                  OSysTime       otF,
            const CmdbBSetTimeB &BCmd,
                  OSysTime       otB);

  void OnOk(const CmdbFSetTimeE &FCmd,
                  OSysTime       otF,
            const CmdbBSetTimeE &BCmd,
                  OSysTime       otB);

 public:
  void OnFailed(const CmdbFSetTimeB &FCmd,
                      OSysTime       otB,
                      TCmdxStatus    Status);

  void OnFailed(const CmdbFSetTimeE &FCmd,
                      OSysTime       otB,
                      TCmdxStatus    Status);

 public: // SetTime
//   void OnOk(const CmdbFGetSysValueB &FCmd,
//                   OSysTime           otF,
//             const CmdbBGetSysValueB &BCmd,
//                   OSysTime           otB);

  void OnOk(const CmdbFGetSysValueE &FCmd,
                  OSysTime           otF,
            const CmdbBGetSysValueE &BCmd,
                  OSysTime           otB);

 public:
//   void OnFailed(const CmdbFGetSysValueB &FCmd,
//                       OSysTime           otB,
//                       TCmdxStatus        Status);

  void OnFailed(const CmdbFGetSysValueE &FCmd,
                      OSysTime           otB,
                      TCmdxStatus        Status);

 public:
  void OnStrange(const ICmdExch &cmdx);

 public: // Default template stubs
  template <TCmdCode CCF>
  void OnOk(const TCommandBase<CCF, TagFwd> &FCmd,
                  OSysTime                   otF) {}

  template <TCmdCode CCB>
  void OnOk(const TCommandBase<CCB, TagBwd> &BCmd,
                  OSysTime                   otB) {}

  template <TCmdCode CCF, TCmdCode CCB>
  void OnOk(const TCommandBase<CCF, TagFwd> &FCmd,
                  OSysTime                   otF,
            const TCommandBase<CCB, TagBwd> &BCmd,
                  OSysTime                   otB) {}

 public:
  template <TCmdCode CCF>
  void OnFailed(const TCommandBase<CCF, TagFwd> &FCmd,
                      OSysTime                   otF,
                      TCmdxStatus                Status) {}

 private:
  void ConfirmMasterBase(OSysTime ot, TByte bCN);
  void ConfirmMasterExt(OSysTime ot, TWord wCN);
  void ConfirmBase(OSysTime ot, TByte bCN);
  void ConfirmExt(OSysTime ot, TWord wCN);
  void ObscureAll(OSysTime ot);
  
 public:
  const CVBoolO&            MasterMode()        const { return m_cvbMasterMode; }
  
  const TMasterConnectData& MasterConnectData() const { return m_mcd; }
  const TSlaveConnectData&  SlaveConnectData()  const { return m_scd; }
  const TCardConnectData&   CardConnectData()   const { return m_ccd; }

 private:
  CVBoolO            m_cvbMasterMode;
  TMasterConnectData m_mcd;
  TSlaveConnectData  m_scd;
  TCardConnectData   m_ccd;

///////////////////////////////////////////////////////
};


#endif
