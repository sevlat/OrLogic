#ifndef Random_h_already_included__08_12_2012__C515520
#define Random_h_already_included__08_12_2012__C515520
//
// SeVlaT, 08.12.2012
//

#include "Types.h"
#include "Fwd.h"

struct TStationTime;
struct TStationTimeSS;

class TRandom {
 public:
  void operator()(TByte &b) const;
  void operator()(TWord &w) const;
  void operator()(bool &bMaster) const;
  void operator()(TStationTime &st) const;
  void operator()(TStationTimeSS &st) const;
  void operator()(TByteBuffer &buf) const;
};

#endif
