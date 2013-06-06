#ifndef SerialTypes_h_already_included__03_06_2012__19E6E000
#define SerialTypes_h_already_included__03_06_2012__19E6E000
//
// SeVlaT, 03.06.2012
//
#include "Types.h"

namespace SerSpecByte { 
  enum TValue {
    bStx = 0x02, // Start of text
    bEtx = 0x03, // End of text
    bAck = 0x06, // Positive handshake return
    bDle = 0x10, // Data Link Escape
    bNak = 0x15, // Negative handshake return
  };
};

typedef SerSpecByte::TValue TSerSpecByte;

struct TCommSetup {
  OUInt onBaudRate;
  
  TCommSetup() {}
  explicit TCommSetup(TUInt nBaudRate)
   : onBaudRate(nBaudRate) {}
};


#endif
