#ifndef CmdsSender_h_already_included__17_05_2013__2C219F40
#define CmdsSender_h_already_included__17_05_2013__2C219F40
//
// SeVlaT, 17.05.2013
//

#include "../CmdTrxInfo.h"
#include "CmdShpObject.h"

class TPktSender;

class TCmdSender {
 public:
  explicit TCmdSender(TPktSender &ps,
                      TSerNumGen &sng)
   : m_ps(ps),
     m_sng(sng) {}

 public:
  OCmdTxInfo Send(const ShpFCmdObject &shpFCmd,
                  const TMsgFrame     &mf,
                        TErrList      *pErr);
  
 private:
  TPktSender &m_ps;
  
 private:
  TSerNumGen &m_sng;
};



#endif
