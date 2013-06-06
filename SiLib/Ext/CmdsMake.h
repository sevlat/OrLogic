#ifndef CmdsMake_h_already_included__20_03_2013__2713F580
#define CmdsMake_h_already_included__20_03_2013__2713F580
//
// SeVlaT, 20.03.2013
//

#include "CmdShpObject.h"

#include "../CmdProcs.h"

////////////////////////////////////////////////////////////////////////////////
template <typename CMD>
struct TCmdsMakeRes {
  typedef typename TCmdoGen<CMD>::Type TCmdObj;
  typedef TCmdPtr<TCmdObj>             TRes;
};

struct TCmdsMake_base {
  template <typename CMD>
  TCmdPtr<typename TCmdoGen<CMD>::Type> Do()
  {
    return new typename TCmdoGen<CMD>::Type();  
  }

  template <typename CMD, typename ARG>
  TCmdPtr<typename TCmdoGen<CMD>::Type> Do(const ARG &a)
  {
    return new typename TCmdoGen<CMD>::Type(a);  
  }

  template <typename CMD, typename ARG0, typename ARG1>
  TCmdPtr<typename TCmdoGen<CMD>::Type> Do(const ARG0 &a0, const ARG1 &a1)
  {
    return new typename TCmdoGen<CMD>::Type(a0, a1);  
  }
};

////////////////////////////////////////////////////////////////////////////////
struct TCmdsMakeSet: TCmdProcSet_tmpl<TCmdsMakeSet, TCmdsMakeRes>,
                     TCmdsMake_base {};

////////////////////////////////////////////////////////////////////////////////
struct TCmdsMakeSetF: TCmdProcSetF_tmpl<TCmdsMakeSetF, TCmdsMakeRes>,
                     TCmdsMake_base {};

////////////////////////////////////////////////////////////////////////////////
template <typename CMD>
struct TCmdsMake: TCmdProc<TCmdsMake<CMD>, CMD, TCmdsMakeRes>,
                  TCmdsMake_base {

};

#endif
