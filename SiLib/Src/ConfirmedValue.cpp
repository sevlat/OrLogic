// SeVlaT, 26.02.2013
#include "StdAfx.h"

#include "../ConfirmedValue.h"

 
TTimePlus::TTimePlus()
 : np(0)
{
}
  
bool TTimePlus::CompareV(const TTimePlus &tp, int &nRes) const
{
  return hftl::CompareV(ot, tp.ot, nRes) ||
         hftl::CompareV(np, tp.np, nRes);
}

bool TTimePlus::Equal(const TTimePlus &tp) const
{
  return tp.ot==ot && tp.np==np;
}

void TTimePlus::SetMax(const TOptional<TTimePlus> &aotp, OSysTime aot)
{
  if (aot) {
//    assert()
    ot=aot;
    np=0;
  } else {
    if (aotp) {
      int nRes=0;
      CompareV(*aotp, nRes);
      if (nRes<0) {
        ot=aotp->ot;
        np=aotp->np;
      }
    }
    ++np;
  }
}


////////////////////////////////////////////////////////////////////////////////
void TConfirmTime::Confirm(OSysTime ot, const OTimePlus &otpObscured)
{
  otpConfirmed.Set().SetMax(otpObscured, ot);
}

void TConfirmTime::Obscure(OSysTime ot, OTimePlus &otpObscured) const
{
  otpObscured.Set().SetMax(otpConfirmed, ot);
}
