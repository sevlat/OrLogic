#ifndef Utils_h_already_included__18_05_2012__1DC86180
#define Utils_h_already_included__18_05_2012__1DC86180
//
// SeVlaT, 18.05.2012
//

#include "Types.h"

namespace PlatformSpecific {

void SleepMs(unsigned int nMs);

}

using PlatformSpecific::SleepMs;

////////////////////////////////////////////////////////////////////////////////
const char* DecIntConstName(const char *szName, int n, char szBuffer[32]);

const char* HexConstName(const char *szName, TDWord dw, char szBuffer[32]);
const char* HexBConstName(const char *szName, TByte b, char szBuffer[32]);
const char* HexWConstName(const char *szName, TWord w, char szBuffer[32]);
const char* HexDwConstName(const char *szName, TDWord dw, char szBuffer[32]);

////////////////////////////////////////////////////////////////////////////////
const wchar_t* DecIntConstName(const wchar_t *szName, int n, wchar_t szBuffer[32]);

const wchar_t* HexConstName(const wchar_t *szName, TDWord dw, wchar_t szBuffer[32]);
const wchar_t* HexBConstName(const wchar_t *szName, TByte b, wchar_t szBuffer[32]);
const wchar_t* HexWConstName(const wchar_t *szName, TWord w, wchar_t szBuffer[32]);
const wchar_t* HexDwConstName(const wchar_t *szName, TDWord dw, wchar_t szBuffer[32]);

////////////////////////////////////////////////////////////////////////////////
template<typename DERIVED, typename CH>
class ToStrEx_crtp {
 public:
  typedef std::basic_string<CH> TStr;
  
  TStr Dec(OInt  on)    const { if (!on)  return m_sDef;
                                          return Self().Dec(*on);   }
  TStr Dec(OUInt on)    const { if (!on)  return m_sDef;
                                          return Self().Dec(*on);   } 
  
  TStr Hex(ODWord odw)  const { if (!odw) return m_sDef;
                                          return Self().Hex(*odw);  }
  
  TStr Hex1(OByte ob)   const { if (!ob)  return m_sDef;
                                          return Self().Hex1(*ob);  }
  TStr Hex2(OWord ow)   const { if (!ow)  return m_sDef;
                                          return Self().Hex2(*ow);  }
  TStr Hex3(ODWord odw) const { if (!odw) return m_sDef;
                                          return Self().Hex3(*odw); }
  TStr Hex4(ODWord odw) const { if (!odw) return m_sDef;
                                          return Self().Hex4(*odw); }
  
 public:
  void SetDef(const TStr &s) { m_sDef=sDef; }
  void SetDef(const CH *szDef) { if (!szDef) m_sDef.clear(); m_sDef=szDef; }

 private:
  TStr m_sDef;

 private:
  DERIVED& Self() { return static_cast<DERIVED&>(*this); }
};

template<typename CH>
class ToStr: public ToStrEx_crtp<ToStr<CH>, CH> {
 public:
  typedef ToStrEx_crtp<ToStr<CH>, CH> TBase;
  typedef std::basic_string<CH> TStr;
  
 public:
  using TBase::Dec;
  using TBase::Hex;
  using TBase::Hex1;
  using TBase::Hex2;
  using TBase::Hex3;
  using TBase::Hex4;
  
 public:
  TStr Dec(int n) const;
  
  TStr Hex(TDWord dw) const;
  
  TStr Hex1(TByte b) const;
  TStr Hex2(TWord w) const;
  TStr Hex3(TDWord dw) const;
  TStr Hex4(TDWord dw) const;
};

typedef ToStr<char>    ToStrA;
typedef ToStr<wchar_t> ToStrW;


#endif
