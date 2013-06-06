// SeVlaT, 29.05.2012
#include "StdAfx.h"

#include "../StationTypes.h"

#include "../SiTypes.h"
#include "../Stream.h"
#include "../Errors.h"

////////////////////////////////////////////////////////////////////////////////
TMsgPrefix::TMsgPrefix()
 : bWakeUp(true),
   nStx(1)
{
}

TMsgPrefix::TMsgPrefix(bool  abWakeUp,
                       TUInt anStx)
 : bWakeUp(abWakeUp),
   nStx(anStx)
{
}

TMsgPrefix::TMsgPrefix(const TMsgPrefix    &wp,
                       const TPrefixParams &Params)
 : bWakeUp(Params.obWakeUp.Get(wp.bWakeUp)),
   nStx(Params.onStx.Get(wp.nStx))
{
}

TUInt TMsgPrefix::Size() const
{
  int nSize=0;
  if (bWakeUp) ++nSize;
  if (nStx==1) ++nSize;
  if (nStx==2) ++nSize;
  return nSize;
}

bool TMsgPrefix::Put(IOStream &os, TErrList *pErr) const
{
  if (bWakeUp)
    if (!NStreamUtils::Put1Byte(os, SpecByte::bWup, pErr)) return false;
    
  if (nStx>0)
    if (!NStreamUtils::Put1Byte(os, SpecByte::bStx, pErr)) return false;
    
  if (nStx>1)
    if (!NStreamUtils::Put1Byte(os, SpecByte::bStx, pErr)) return false;

  return true;
}

////////////////////////////////////////////////////////////////////////////////
void TMsgFrame::PutPrefix(IOStream &os, TErrList *pErr) const
{
  if (!Prefix.Put(os, pErr)) ThrowExcept();
}

void TMsgFrame::PutSuffix(IOStream &os, TErrList *pErr) const
{
  const TByte bSuffix=(Suffix==msNak)? SpecByte::bNak: SpecByte::bEtx;
  if (!NStreamUtils::Put1Byte(os, bSuffix, pErr)) ThrowExcept();
}

TUInt TMsgFrame::Size() const
{
  return Prefix.Size()+1;
}

