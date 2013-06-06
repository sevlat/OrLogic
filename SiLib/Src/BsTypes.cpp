// SeVlaT, 10.02.2013
#include "StdAfx.h"

#include "../BsTypes.h"

#include "../Utils.h"

namespace {
////////////////////////////////////////////////////////////////////////////////
  template <typename CH>
  const CH* Aw_String(const char *sz, const wchar_t *wsz);

  template <>
  const char* Aw_String<char>(const char *sz, const wchar_t *wsz)
   { return sz; }

  template <>
  const wchar_t* Aw_String<wchar_t>(const char *sz, const wchar_t *wsz)
   { return wsz; }

////////////////////////////////////////////////////////////////////////////////
  template <typename CH, bool PREF>
  const CH* Aw_String(const char *szp, const wchar_t *wszp,
                      const char *sz,  const wchar_t *wsz);

  template <>
  const char* Aw_String<char, false>(const char *sz,  const wchar_t *wsz,
                                     const char *szp, const wchar_t *wszp)
   { return sz; }

  template <>
  const wchar_t* Aw_String<wchar_t, false>(const char *sz,  const wchar_t *wsz,
                                           const char *szp, const wchar_t *wszp)
   { return wsz; }

  template <>
  const char* Aw_String<char, true>(const char *sz,  const wchar_t *wsz,
                                    const char *szp, const wchar_t *wszp)
   { return szp; }

  template <>
  const wchar_t* Aw_String<wchar_t, true>(const char *sz,  const wchar_t *wsz,
                                          const char *szp, const wchar_t *wszp)
   { return wszp; }
}


#define AW_STRING(x) Aw_String<CH>(#x, L#x)

#define CASE_RETURN(x) case (x): return AW_STRING(x);
#define CASE_RETURNP(p, n) case (p##n): return Aw_String<CH, PREF>(#n, L#n, #p #n, L#p L#n);

////////////////////////////////////////////////////////////////////////////////
template <typename CH, bool PREF>
const CH* TBsConstName<CH, PREF>::Get(TBsMode  bm, const CH *szDef)
{
  switch (bm) {
    CASE_RETURNP(bsm, Unk);
    CASE_RETURNP(bsm, Control);
    CASE_RETURNP(bsm, Start);
    CASE_RETURNP(bsm, Finish);
    CASE_RETURNP(bsm, Readout);
    CASE_RETURNP(bsm, Clear);
    CASE_RETURNP(bsm, Check);
  }

  return szDef;
}

template <typename CH, bool PREF>
const CH* TBsConstName<CH, PREF>::Get(TBsMode bm)
{
  return Get(bm, AW_STRING(Unk));
}

template <typename CH, bool PREF>
const CH* TBsConstName<CH, PREF>::Get(TBsModel bm, const CH *szDef)
{
  switch (bm) {
    CASE_RETURNP(bsml, Unk);
    CASE_RETURNP(bsml, BSF3);
    CASE_RETURNP(bsml, BSF4);
    CASE_RETURNP(bsml, BSM4);
    CASE_RETURNP(bsml, BSF5);
    CASE_RETURNP(bsml, BSM6);
    CASE_RETURNP(bsml, BSF6);
    CASE_RETURNP(bsml, BSF7);
    CASE_RETURNP(bsml, BS7_SI_M);
    CASE_RETURNP(bsml, BSM7);
    CASE_RETURNP(bsml, BS7_S);
    CASE_RETURNP(bsml, BS7_P);
    CASE_RETURNP(bsml, BS7_GSM);
    CASE_RETURNP(bsml, BSF8);
    CASE_RETURNP(bsml, BS8_SI_M);
    CASE_RETURNP(bsml, BSM8);
    CASE_RETURNP(bsml, BS8_P);
  }
  
  return szDef;
}

template <typename CH, bool PREF>
const CH* TBsConstName<CH, PREF>::Get(TBsModel bm)
{
  return Get(bm, AW_STRING(Unk));
}

template <typename CH, bool PREF>
basic_string<CH> TBsConstName<CH, PREF>::Get(TBsModeRaw  bmr)
{
  const CH *szName=Get(bmr.Mode, 0);
  if (szName) return szName;
  
  CH szBuffer[256];

  basic_string<CH> s=AW_STRING(Unk);
  s+=CH(' ');
  s+=HexBConstName(0, bmr.dwMode, szBuffer);
  
  return s;
}

template <typename CH, bool PREF>
basic_string<CH> TBsConstName<CH, PREF>::Get(TBsModelRaw bmr)
{
  const CH *szName=Get(bmr.Model, 0);
  if (szName) return szName;
  
  CH szBuffer[256];

  basic_string<CH> s=AW_STRING(Unk);
  s+=CH(' ');
  s+=HexBConstName(0, bmr.dwModel, szBuffer);
  
  return s;
}


////////////////////////////////////////////////////////////////////////////////
template TBsConstName<char, false>;
template TBsConstName<char, true>;

template TBsConstName<wchar_t, false>;
template TBsConstName<wchar_t, true>;


////////////////////////////////////////////////////////////////////////////////

TBsModelInfo GetBsModelInfo(TBsModel bm)
{
  typedef TBsModelInfo Bmi;
  
  switch (bm) {
    case bsmlBSF3:     return Bmi(3, true,  false);
    case bsmlBSF4:     return Bmi(4, true,  false);
    case bsmlBSM4:     return Bmi(4, false, true);
    case bsmlBSF5:     return Bmi(5, true,  false);
    case bsmlBSM6:     return Bmi(6, false, true);
    case bsmlBSF6:     return Bmi(6, true,  false);
    case bsmlBSF7:     return Bmi(7, true,  false);
    case bsmlBS7_SI_M: return Bmi(7, true,  false);
    case bsmlBSM7:     return Bmi(7, false, true);
    case bsmlBS7_S:    return Bmi(7, false, false);
    case bsmlBS7_P:    return Bmi(7, false, false);
    case bsmlBS7_GSM:  return Bmi(7, false, false);
    case bsmlBSF8:     return Bmi(8, true,  false);
    case bsmlBS8_SI_M: return Bmi(8, false, false);
    case bsmlBSM8:     return Bmi(8, false, true);
    case bsmlBS8_P:    return Bmi(8, false, false);
  }
  
  return Bmi();
}

