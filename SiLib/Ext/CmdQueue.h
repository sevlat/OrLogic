#ifndef CmdQueue_h_already_included__18_01_2013__118C928
#define CmdQueue_h_already_included__18_01_2013__118C928
//
// SeVlaT, 18.01.2013
//

#include "CmdsExchange.h"

#include "../Queue.h"
#include "../CmdTrxInfo.h"
#include "../CmdxDispatch.h"


class TFCmdQueue {
 public:
  void Push(ShpFCmdObject shpF, const TCmdTxInfo &cti);
  
 public:
  typedef std::deque<TFCmdTx>    TQueue;
  typedef TQueue::const_iterator TCIt;
  
  const TQueue& Get() const { return m_data; }
  
 private:
  TQueue m_data;
};

class TBCmdQueue {
 public:
  void Push(ShpBCmdObject shpB, const TCmdRxInfo &cri);
  
 public:
  typedef std::deque<TBCmdRx>    TQueue;
  typedef TQueue::const_iterator TCIt;
  
  const TQueue& Get() const { return m_data; }
  
 private:
  TQueue m_data;
};


////////////////////////////////////////////////////////////////////////////////
class TCmdQueue {
 public: // Forward
  void Push(TFCmdTx fctx);
  void Push(TCmdTxInfo cti);

 public: // Backward
  void Push(TBCmdRx bcrx);
  void Push(TCmdRxInfo cri);

 public:
  void Flush(TCmdRxInfo cri);

 public: // Output (pop)
  const TCmdExch& Get() const;
  const TCmdExch* GetPtr() const;
  void Pop();

 public: // Output (observe)
  const TCmdExch* GetCurOutput(TUInt &nIndex) const
    { return m_q.check_get(nIndex); }

 public:
  TSerNumGen& Sng() { return m_sng; }

 public:
  bool InputEmpty() const;
  bool OutputEmpty() const;

 public:
  typedef std::deque<TFCmdTx>     TFQueue;
  typedef TFQueue::const_iterator TFCIt;

  typedef std::deque<TBCmdRx>     TBQueue;
  typedef TBQueue::const_iterator TBCIt;

  typedef TCircBufRangeQueue<TCmdExch, TUInt> TOQueue;
  typedef TOQueue::const_iterator    TOCIt;
  
 private:
  void Process();
  bool DoProcess();

 private:
  TCmdTxInfo m_cti;
  TCmdRxInfo m_cri;
  
  TFQueue m_fq;
  TBQueue m_bq;

  TOQueue m_q;
  
  TSerNumGen m_sng;
};

////////////////////////////////////////////////////////////////////////////////
template <typename OBSERVER>
class TCmdQueueObserver {
 public:
  TCmdQueueObserver(OBSERVER &Obs)
   : m_Obs(Obs),
     m_nIndex(0) {}
   
 public:
  void operator()(const TCmdQueue &Queue)
  {
    for (const TCmdExch *pCmdExch=Queue.GetCurOutput(m_nIndex); 
                         pCmdExch;
                         pCmdExch=Queue.GetCurOutput(++m_nIndex)) {
      CmdxDispatch(*pCmdExch, m_Obs);
    }
  }
  
 private:
  TUInt m_nIndex;
  
 private:
  OBSERVER &m_Obs;
};

/*
  TUInt nIndex=0;
    
*/

#endif
