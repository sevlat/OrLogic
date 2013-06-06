#ifndef Types_h_already_included__08_05_2013__2A758880
#define Types_h_already_included__08_05_2013__2A758880
//
// SeVlaT, 08.05.2013
//

#include <SiLib/BsTypes.h>
#include <SiLib/ComPort.h>

using std::string;
using std::wstring;

typedef wstring            TString;
typedef TOptional<TString> OString;

struct TFlag {
  TFlag(bool &b): m_b(b) { m_b=true; }
  ~TFlag()  { m_b=false; }

  bool &m_b;
};


#endif
