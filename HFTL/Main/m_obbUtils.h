#ifndef m_obbUtils_h_already_included__02_12_2012__2DB343C0
#define m_obbUtils_h_already_included__02_12_2012__2DB343C0
//
// SeVlaT, 02.12.2012
//

#include "m_bbUtils.h"

#include "m_obbTypes.h"

namespace hftl {

// !!! Test it
template<typename VAL>
OByte SafeCastToByte(VAL v)
{
  if (v<0 || v>0xFF) return None;
  return static_cast<TByte>(v);
}

////////////////////////////////////////////////////////////////////////////////

inline OByte CharToByte(char ch)
{
  switch (ch) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 10;
    case 'b':
    case 'B': return 11;
    case 'c':
    case 'C': return 12;
    case 'd':
    case 'D': return 13;
    case 'e':
    case 'E': return 14;
    case 'f':
    case 'F': return 15;
  }

  return None;
}

inline OByte TwoCharToByte(char ch0, char ch1)
{
  const OByte ob0=CharToByte(ch0);
  if (!ob0) return None;

  const OByte ob1=CharToByte(ch1);
  if (!ob1) return None;
  
  return HFTL_MakeByte(*ob1, *ob0);
}

inline OByte StringToByte(const char *sz)
{
  if (!sz || !sz[0] || !sz[1]) return None;
  return TwoCharToByte(sz[0], sz[1]);
}

} // namespace hftl

#endif
