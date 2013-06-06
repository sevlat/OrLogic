#ifndef ConfirmedValue_h_already_included__26_02_2013__2720C500
#define ConfirmedValue_h_already_included__26_02_2013__2720C500
//
// SeVlaT, 26.02.2013
//

#include "TimeTypes.h"

struct TTimePlus {
  OSysTime ot;
  TUInt    np;
  
  TTimePlus();
  
  void SetMax(const TOptional<TTimePlus> &aotp, OSysTime aot);

  bool CompareV(const TTimePlus &tp, int &nRes) const;
  bool Equal(const TTimePlus &tp) const;
};

inline bool CompareV(const TTimePlus &tp0, const TTimePlus &tp1, int &nRes)
{
  return tp0.CompareV(tp1, nRes);
}

inline bool operator ==(const TTimePlus &tp0, const TTimePlus &tp1)
{
  return tp0.Equal(tp1);
}

inline bool operator !=(const TTimePlus &tp0, const TTimePlus &tp1)
{
  return !tp0.Equal(tp1);
}

typedef TOptional<TTimePlus> OTimePlus;

////////////////////////////////////////////////////////////////////////////////
struct TConfirmTime {
  OTimePlus otpConfirmed;

  void Confirm(OSysTime ot, const OTimePlus &otpObscured);
  void Obscure(OSysTime ot, OTimePlus &otpObscured) const;
};

struct TConfirmTimeO: TConfirmTime {
  OTimePlus otpObscured;

  void Confirm(OSysTime ot) { TConfirmTime::Confirm(ot, otpObscured); }
  void Obscure(OSysTime ot) { TConfirmTime::Confirm(ot, otpObscured); }
};

template <typename VAL>
struct TConfirmedValue: TConfirmTime {
  TOptional<VAL> oVal;
  
  void Set(const VAL &v, OSysTime ot, const OTimePlus &otpObscured)
    { oVal=v; Confirm(ot, otpObscured); }
    
  void Cancel(TSysTime ot, const OTimePlus &otpObscured)
    { oVal=None; Confirm(ot, otpObscured); }
};

template <typename VAL>
struct TConfirmedValueO: TConfirmTimeO {
  TOptional<VAL> oVal;
  
  void Set(const VAL &v, OSysTime ot)
    { oVal=v; Confirm(ot); }
    
  void Cancel(TSysTime ot)
    { oVal=None; Confirm(ot); }
};

#endif
