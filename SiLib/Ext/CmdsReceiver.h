#ifndef CmdsReceiver_h_already_included__17_05_2013__1B98FD40
#define CmdsReceiver_h_already_included__17_05_2013__1B98FD40
//
// SeVlaT, 17.05.2013
//

#include "CmdsExchange.h"

class TPktReceiver;

class TCmdReceiver {
 public:
  TCmdReceiver(TPktReceiver &PktReceiver,
               TSerNumGen   &sng)
   : m_PktReceiver(PktReceiver),
     m_sng(sng) {}

 public:
  void Receive(TErrList *pErr);
 
  const OBCmdRx& Get() const { return m_oCmdRx; }
  
 private:
  TPktReceiver &m_PktReceiver;

 private:
  OBCmdRx m_oCmdRx;
  
 private:
  TSerNumGen &m_sng;
};


#endif
