#ifndef CardTypes_h_already_included__20_02_2013__13DA9CC0
#define CardTypes_h_already_included__20_02_2013__13DA9CC0
//
// SeVlaT, 20.02.2013
//

#include "Types.h"

enum TCardModel {
  cdmlUnk
};

const char* GetConstName(TCardModel cm);

////////////////////////////////////////////////////////////////////////////////
class TCardNum {
 public:
  TUInt Get() const { return m_n; }
  
 private:
  TUInt m_n; 
};

////////////////////////////////////////////////////////////////////////////////
struct TCardInfo {
  TCardNum  SerNum;
  
  TWord      wModel; // ? Remove it?
  TCardModel Model; 
  
  TCardInfo()
   : wModel(0),
     Model(cdmlUnk)  {}
};

#endif
