#ifndef CmdTrxInfo_h_already_included__27_02_2013__295986C0
#define CmdTrxInfo_h_already_included__27_02_2013__295986C0
//
// SeVlaT, 27.02.2013
//

#include "TimeTypes.h"

////////////////////////////////////////////////////////////////////////////////
struct TChunkTxInfo {
  OSysTime ot;
  TUInt nSent;
  
  TChunkTxInfo()
   : nSent(0) {}
};
typedef TOptional<TChunkTxInfo> OChunkTxInfo;

////////////////////////////////////////////////////////////////////////////////
struct TBufTxInfo {
  OSysTime ot;
};
typedef TOptional<TBufTxInfo>   OBufTxInfo;

////////////////////////////////////////////////////////////////////////////////
struct TPktTxInfo {
  OSysTime ot;
};
typedef TOptional<TPktTxInfo>   OPktTxInfo;

////////////////////////////////////////////////////////////////////////////////
struct TCmdInfo {
  TSerNum  sn;
  OSysTime ot;
  
  TCmdInfo() {}
  explicit TCmdInfo(TSerNum asn): sn(asn) {}
  TCmdInfo(TSerNum asn, TSysTime t): sn(asn), ot(t) {}
};

struct TCmdTxInfo: TCmdInfo {
  TCmdTxInfo() {}
  explicit TCmdTxInfo(TSerNum asn): TCmdInfo(asn) {}
  TCmdTxInfo(TSerNum asn, TSysTime t): TCmdInfo(asn, t) {}
};

typedef TOptional<TCmdTxInfo> OCmdTxInfo;

struct TCmdRxInfo: TCmdInfo {
  TCmdRxInfo() {}
  explicit TCmdRxInfo(TSerNum asn): TCmdInfo(asn) {}
  TCmdRxInfo(TSerNum asn, TSysTime t): TCmdInfo(asn, t) {}
};

typedef TOptional<TCmdRxInfo> OCmdRxInfo;


#endif
