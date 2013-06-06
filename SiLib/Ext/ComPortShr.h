#ifndef ComPortShr_h_already_included__09_04_2013__22A29600
#define ComPortShr_h_already_included__09_04_2013__22A29600
//
// SeVlaT, 09.04.2013
//

#include "Types.h"

#include "../ComPort.h"

class TComPortShr {
 public:
  explicit TComPortShr(bool bEmulator=false);

 public:
  IComPort &get() const { return *m_shp; }

 public:
  typedef shared_ptr<IComPort> TShp;
  
  TShp m_shp;
};

#endif
