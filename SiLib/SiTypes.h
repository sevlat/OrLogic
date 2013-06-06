#ifndef SiTypes_h_already_included__29_05_2012__12C7D400
#define SiTypes_h_already_included__29_05_2012__12C7D400
//
// SeVlaT, 29.05.2012
//

#include "SerialTypes.h"
#include "Types.h"

namespace SpecByte { 
  enum TValue {
    bStx = SerSpecByte::bStx,
    bEtx = SerSpecByte::bEtx,
    bAck = SerSpecByte::bAck,
    bDle = SerSpecByte::bDle,
    bNak = SerSpecByte::bNak,
    bWup = 0xFF,     // Wake up
  };
}

inline bool NeedDle(TByte b)
{  return b<0x20; }

////////////////////////////////////////////////////////////////////////////////
namespace BsSpeed {
  enum TValue {
    sLow,
    sHigh    
  };  
}
typedef BsSpeed::TValue     TBsSpeed;
typedef TOptional<TBsSpeed> OBsSpeed;

////////////////////////////////////////////////////////////////////////////////
namespace BsProtocol {
  enum TValue {
    pBase,
    pExt    
  };  
}
typedef BsProtocol::TValue     TBsProtocol;
typedef TOptional<TBsProtocol> OBsProtocol;


#endif
