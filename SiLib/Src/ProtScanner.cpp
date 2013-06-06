// SeVlaT, 13.03.2013
#include "StdAfx.h"

#include "../ProtScanner.h"

#include "ProtScannerEngine.h"

////////////////////////////////////////////////////////////////////////////////
using namespace ProtScannerState;

bool ProtScanNext(TByte               b,
                  bool               &bEaten,
                  TProtCmdPacket     &pkt,
                  TProtScannerState  &State,
                  TProtScannerData   &Data,
                  TProtScannerCounts &Counts)
{
  TProtScannerOutput Output(pkt, Data);

  const TProtScanner Scanner(State, Output, Counts);
  bEaten=Scanner.Next(b);
  return true;
}                   
