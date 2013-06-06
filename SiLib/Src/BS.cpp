// SeVlaT, 15.11.2012
#include "StdAfx.h"

#include "../Bs.h"

#include "../Errors.h"

TBsMode BsModeFromByte(TByte b)
{
  switch(b) {
    case 0x02: return bsmControl;
    case 0x03: return bsmStart;
    case 0x04: return bsmFinish;
    case 0x05: return bsmReadout;
    case 0x06:                     // ????
    case 0x07: return bsmClear;
    case 0x0A: return bsmCheck;
  }
  
  return bsmUnk;
}

/*
 # 2 bytes:
 #   8003: BSF3 (serial numbers > 1.000)
 #   8004: BSF4 (serial numbers > 10.000)
 #   8084: BSM4-RS232
 #   8086: BSM6-RS232 / BSM6-USB
 #   8146: BSF6 (serial numbers > 30.000)
 #   8115: BSF5 (serial numbers > 50.000)
 #   8117: BSF7 (serial no. 70.000...70.521, 72.002...72.009)
 #   8118: BSF8 (serial no. 70.000...70.521, 72.002...72.009)
 #   8187: BS7-SI-Master
 #   8188: BS8-SI-Master
 #   8197: BSF7 (serial numbers > 71.000, apart from 72.002...72.009)
 #   8198: BSF8 (serial numbers > 80.000)
 #   9197: BSM7-RS232, BSM7-USB
 #   9198: BSM8-USB, BSM8-SRR
 #   9199: unknown
 #   9597: BS7-S
 #   B197: BS7-P 
 #   B198: BS8-P
 #   B897: BS7-GSM
*/

TBsModel BsModelFromWord(TWord w) // address \x0B
{
  switch (w) {
    case 0x8003: return bsmlBSF3;
    case 0x8004: return bsmlBSF4;
    case 0x8084: return bsmlBSM4;
    case 0x8086: return bsmlBSM6;
    case 0x8146: return bsmlBSF6;
    case 0x8115: return bsmlBSF5;
    case 0x8117: return bsmlBSF7;
    case 0x8118: return bsmlBSF8;
    case 0x8187: return bsmlBS7_SI_M;
    case 0x8188: return bsmlBS8_SI_M;
    case 0x8197: return bsmlBSF7;
    case 0x8198: return bsmlBSF8;
    case 0x9197: return bsmlBSM7;
    case 0x9198: return bsmlBSM8;
    case 0x9597: return bsmlBS7_S;
    case 0xB197: return bsmlBS7_P;
    case 0xB198: return bsmlBS8_P;
    case 0xB897: return bsmlBS7_GSM;
  }
  
  return bsmlUnk;
}

