#ifndef ProtScanner_h_already_included__08_02_2013__4F8A968
#define ProtScanner_h_already_included__08_02_2013__4F8A968
//
// SeVlaT, 08.02.2013
//

#include "StationTypes.h"

////////////////////////////////////////////////////////////////////////////////
class TByteCount {
 public:
  explicit TByteCount(TUInt n);
  
 public:
  void Dec();
  void Set(TUInt n);

 public:
  void AssertNonNegative() const;

 public:
  TUInt Get() const { return m_nPos>m_nNeg? (m_nPos-m_nNeg): 0; }

 private:
  TUInt m_nPos;
  TUInt m_nNeg;
};

typedef TOptional<TByteCount> OByteCount;

////////////////////////////////////////////////////////////////////////////////
class TProtScannerCounts {
 public:
  TProtScannerCounts();
     
 public:
  OUInt GetMin() const;
  OUInt GetMax() const;
  
 public:
  void NeedEnd();
  void ReadCmdLite();
  void ReadCmdBase(OUInt onMin, OUInt onMax);
  void ReadCmdExt();
  void ReadLen(TByte bLen);
  void ReadData();
  void ReadCrc();
  void ReadEnd();

 public:
  void AssertNonNegative() const;
  void AssertZeroCounts() const;
  
 private:
  int GetWithoutData() const;

 private:
  TByteCount m_bcLen;
  TByteCount m_bcCmd;
  TByteCount m_bcCrc;
  TByteCount m_bcEnd;

  OByteCount m_obcDataMin;
  OByteCount m_obcDataMax;
};

////////////////////////////////////////////////////////////////////////////////
namespace ProtScannerState {
  enum TState {
    sStart,
    sWUp,
    sStx1,
    sStx2,

    sbData,
    sbDle,

    seCmd,
    seData,
    seCrcH,
    seCrcL,

    sEnd,
  };
  
  static const char* GetStateName(TState s);
}

class TProtScannerState {
 public:
  typedef ProtScannerState::TState TState;
  
 public:
  TProtScannerState();

 public:
  bool IsAtStart() const;
  bool IsRunning() const;
  bool IsStalled() const;
  bool IsStalledOk() const;
  bool IsStalledFail() const;

 public:
  TState GetState() const { return m_State; }

 public:
  void SetState(TState s);
  void SetError();
  
 private:
  bool CheckState() const;
  
 private:
  TState m_State;
  bool   m_bErr;
};

////////////////////////////////////////////////////////////////////////////////
class TProtScannerMessage {
 public:
  explicit TProtScannerMessage(TProtCmdPacket &pkt);

 public:
  void SetPrefixWakeUp();
  void SetPrefixStx1();
  void SetPrefixStx2();
  void SetSuffixEndNak();
  void SetSuffixEndEtx();

 protected:
  void AddDataByte(TByte b);
  void SetCommand(TCmdCode cc);

 protected:
  TWord CalcCrc() const;
  TUInt GetSize() const;

 private:
  TProtCmdPacket &m_pkt;
};

////////////////////////////////////////////////////////////////////////////////
struct TProtScannerData {
  OCommandType oct;

  OByte obUnexp;
  OByte obCrcH;
  OByte obCrcL;
  OByte obELen;

  OBool obCrcOk;
  
 public:
  void CheckCrc(TWord wCalculatedCrc);
  void SetCommandType(TCommandType ct);
  void SetELen(TByte b);
  void SetUnexpectedByte(TByte b);
  void SetCrcH(TByte b);
  void SetCrcL(TByte b);
};

////////////////////////////////////////////////////////////////////////////////
class TProtScannerOutput: public TProtScannerMessage {
 public:
  TProtScannerOutput(TProtCmdPacket   &pkt,
                     TProtScannerData &Data);

 public:
  void AddBDataByte(TByte b);
  bool AddEDataByte(TByte b);
  
  void SetELen(TByte b);

  void SetCrcH(TByte b);
  void SetCrcL(TByte b);
  void CheckCrc();

  void SetCommand(TCmdCode cc, TCommandType ct);
  void SetUnexpectedByte(TByte b);

 private:
  void AddDataByte(TByte b);
  void SetCommand(TCmdCode cc);

 private:
  TProtScannerData &m_Data;
};

////////////////////////////////////////////////////////////////////////////////
bool ProtScanNext(TByte               b,
                  bool               &bEaten,
                  TProtCmdPacket     &pkt,
                  TProtScannerState  &State,
                  TProtScannerData   &Data,
                  TProtScannerCounts &Counts);

#endif