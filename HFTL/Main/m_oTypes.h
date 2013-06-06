#ifndef m_oTypes_h_already_included__20_09_2012__344ED240
#define m_oTypes_h_already_included__20_09_2012__344ED240
//
// SeVlaT, 20.09.2012
//

#include "m_Optional.h"

namespace hftl { // Helpful template library

typedef TOptional<char>             OChar;
typedef TOptional<int>              OInt;
typedef TOptional<long>             OLong;
                                 
typedef TOptional<unsigned char>    OUChar;
typedef TOptional<unsigned int>     OUInt;
typedef TOptional<unsigned long>    OULong;
                                 
typedef TOptional<bool>             OBool;
                                 
typedef TOptional<float>            OFloat;
typedef TOptional<double>           ODouble;

typedef TOptional<__int64>          OInt64;
typedef TOptional<unsigned __int64> OUInt64;

}

#endif
