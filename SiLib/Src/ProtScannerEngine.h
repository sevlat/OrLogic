#ifndef ProtScannerEngine_h_already_included__13_03_2013__2C8CDDC0
#define ProtScannerEngine_h_already_included__13_03_2013__2C8CDDC0
//
// SeVlaT, 13.03.2013
//

#include "../Types.h"

class TProtScannerState;
class TProtScannerOutput;
class TProtScannerCounts;


////////////////////////////////////////////////////////////////////////////////
class TProtScanner {
 public:
  TProtScanner(TProtScannerState  &State,
               TProtScannerOutput &Output,
               TProtScannerCounts &Counts);
  
 public:
  bool Next(TByte b) const;

 private:
  bool NextAtStart(TByte b) const;
  bool NextAtWUp  (TByte b) const;
  bool NextAtStx1 (TByte b) const;
  bool NextAtStx2 (TByte b) const;
  bool NextAtBData(TByte b) const;
  bool NextAtBDle (TByte b) const;
  bool NextAtECmd (TByte b) const;
  bool NextAtEData(TByte b) const;
  bool NextAtECrcH(TByte b) const;
  bool NextAtECrcL(TByte b) const;
  bool NextAtEnd  (TByte b) const;

 private:
  bool TakeUnexpected    (TByte b) const;
  bool TakeWakeUp        (TByte b) const;
  bool TakeFirstStx      (TByte b) const;
  bool TakeSecondStx     (TByte b) const;
  bool TakeLiteCmd       (TByte b) const;
  bool TakeCmd           (TByte b) const;
  bool TakeDle           (TByte b) const;
  bool TakeBUnescapedData(TByte b) const;
  bool TakeBEscapedData  (TByte b) const;
  bool TakeELen          (TByte b) const;
  bool TakeEData         (TByte b) const;
  bool TakeECrcH         (TByte b) const;
  bool TakeECrcLnCheck   (TByte b) const;
  bool TakeSuffix        (TByte b) const;
  
 private:
  TProtScannerState  &m_State;
  TProtScannerOutput &m_Output;
  TProtScannerCounts &m_Counts;
};

#endif
