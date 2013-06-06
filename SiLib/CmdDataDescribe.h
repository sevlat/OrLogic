#ifndef CmdDataDescribe_h_already_included__20_10_2012__2A5A5BC0
#define CmdDataDescribe_h_already_included__20_10_2012__2A5A5BC0
//
// SeVlaT, 20.10.2012
//

#include "CmdData.h"

void DescribeCmdd(std::ostream &os, const CmddVoid          &cmdd);

void DescribeCmdd(std::ostream &os, const CmddRaw           &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFSetMaSlave   &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBMaSlaveB     &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBMaSlaveE     &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFSetBaudRate  &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBSetBaudRateB &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBSetBaudRateE &cmdd);

void DescribeCmdd(std::ostream &os, const CmddBGetTimeB     &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBGetTimeE     &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFSetTimeB     &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBSetTimeB     &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFSetTimeE     &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBSetTimeE     &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFGetSysValueE &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBGetSysValueE &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFGetBckDataE  &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBGetBckDataE  &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFBeepE        &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBBeepE        &cmdd);

void DescribeCmdd(std::ostream &os, const CmddFTurnOffB     &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBTurnOffB     &cmdd);

void DescribeCmdd(std::ostream &os, const CmddBCardIns5RemB &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBCardIns6B    &cmdd);
void DescribeCmdd(std::ostream &os, const CmddBCardInsRemE  &cmdd);

#endif
