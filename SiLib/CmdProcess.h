// !!!!!!!! to be deleted

#ifndef CmdProcess_h_already_included__23_12_2012__32943300
#define CmdProcess_h_already_included__23_12_2012__32943300
//
// SeVlaT, 23.12.2012
//

#include "TimeTypes.h"

#include "CommandCode.h"

class TCmdProcess {
 public:
  enum TState {
    sStart,
    sReqSent,
    sRespGot,
    sNakGot,
    sTimeOut,
  };

 public:
  TCmdProcess(TCmdCode ccB, TSysSpan tsWait);
  
 public:
  void Sent(TSysTime t);
  bool Receive(TCmdCode cc, TSysTime t);
 
 public:
  bool IsWaiting()  const { return m_state==sReqSent; }
  bool IsOK()       const { return m_state==sRespGot; }
  bool IsNak()      const { return m_state==sNakGot;  }
  bool IsTimeOut()  const { return m_state==sTimeOut; }
  bool IsFinished() const { return m_state==sRespGot ||
                                   m_state==sNakGot  ||
                                   m_state==sTimeOut; }
   
 private:
  TState m_state;
 
 private:
  TCmdCode m_ccB;
  TSysSpan m_tsWait;
  TSysTime m_tLast;
};


#endif
