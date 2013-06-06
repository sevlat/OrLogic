// SeVlaT, 18.06.2012
#include "StdAfx.h"

#include "../CmdSerializeImpl.h"

#include "../Commands.h"

/*
  To make clear:
  If this file commented, program compiles and links. 
  But doesn't responds errors in CmdDataSerializeSpec. hWhy?
*/

template TCmdSerializer<CmdbFSetMaSlaveB>;
template TCmdSerializer<CmdbFSetMaSlaveE>;
                           
template TCmdSerializer<CmdbBSetMaSlaveB>;
template TCmdSerializer<CmdbBSetMaSlaveE>;
                           
                           
template TCmdSerializer<CmdbFSetBaudRateB>;
template TCmdSerializer<CmdbFSetBaudRateE>;
                           
template TCmdSerializer<CmdbBSetBaudRateB>;
template TCmdSerializer<CmdbBSetBaudRateE>;
                           
                           
template TCmdSerializer<CmdbFGetTimeB>;
template TCmdSerializer<CmdbFGetTimeE>;
                           
template TCmdSerializer<CmdbBGetTimeB>;
template TCmdSerializer<CmdbBGetTimeE>;
                           
                           
template TCmdSerializer<CmdbFSetTimeB>;
template TCmdSerializer<CmdbFSetTimeE>;
                           
template TCmdSerializer<CmdbBSetTimeB>;
template TCmdSerializer<CmdbBSetTimeE>;
                           
                           
template TCmdSerializer<CmdbFGetSysValueE>;
                           
template TCmdSerializer<CmdbBGetSysValueE>;
                           
template TCmdSerializer<CmdbFGetBckDataE>;
                           
template TCmdSerializer<CmdbBGetBckDataE>;
                           
template TCmdSerializer<CmdbFBeep>;
template TCmdSerializer<CmdbBNak>;
