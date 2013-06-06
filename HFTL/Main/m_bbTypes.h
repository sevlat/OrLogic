#ifndef m_bbTypes_h_already_included__02_12_2012__29CF4D00
#define m_bbTypes_h_already_included__02_12_2012__29CF4D00
//
// SeVlaT, 02.12.2012
//

namespace hftl { // Helpful template library

typedef unsigned char  TByte;  // unsigned  8 bit
typedef unsigned short TWord;  // unsigned 16 bit
typedef unsigned long  TDWord; // unsigned 32 bit

template <int N>
struct TNByte;

template <> struct TNByte<1> {
  typedef TByte  Type;
  
  static bool Check(const TByte  &b)  { return true; }
  static bool Check(const TWord  &w)  { return (w  & 0xFFu)==w; }
  static bool Check(const TDWord &dw) { return (dw & 0xFFu)==dw; }
};

template <> struct TNByte<2> {
  typedef TWord  Type;
  
  static bool Check(const TWord  &w)  { return true; }
  static bool Check(const TDWord &dw) { return (dw & 0xFFFFu)==dw; }
};

template <> struct TNByte<3> {
  typedef TDWord Type;

  static bool Check(const TDWord &dw) { return (dw & 0xFFFFFFu)==dw; }
};

template <> struct TNByte<4> {
  typedef TDWord Type;

  static bool Check(const TDWord &dw) { return true; }
};

////////////////////////////////////////////////////////////////////////////////
// Byte Order clases and constants
class BoBe {};
class BoLe {};

const BoBe boBe;
const BoLe boLe;


}

#endif
