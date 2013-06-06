#ifndef BsParseEngine_h_already_included__17_01_2013__34EB2C80
#define BsParseEngine_h_already_included__17_01_2013__34EB2C80
//
// SeVlaT, 17.01.2013
//

#include "../BsParser.h"

#include "Types.h"

typedef shared_ptr<TBsParser> shpBsParser;

class TBsParseEngine {
 public:
  TBsParseEngine();
  
 public:
  shpBsParser AddByte(TByte b, bool &bEaten);
  
 private:
  shpBsParser m_shpBsp;
};

#endif
