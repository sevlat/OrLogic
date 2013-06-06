#ifndef Types_h_already_included__18_05_2012__730B860
#define Types_h_already_included__18_05_2012__730B860
//
// SeVlaT, 18.05.2012
//

#include <hftl/Main/m_oTypes.h>
#include <hftl/Main/m_obbTypes.h>
#include <hftl/Main/m_bbArray.h>

#include <hftl/Main/m_stlUtils.h>
#include <hftl/Main/m_bbUtils.h>

#include <hftl/Main/m_SerNum.h>

#include <HFTL/Main/m_oiplSegPoint.h>

using hftl::TInd;
using hftl::TiSegmU;
using hftl::OiSegmU;

using hftl::TByte;
using hftl::TWord;
using hftl::TDWord;

using hftl::TOptional;
using hftl::None;
using hftl::OptFromPtr;
using hftl::OptFromOpt;

using hftl::OInt;
using hftl::OByte;
using hftl::OWord;
using hftl::ODWord;

using hftl::TByteArray;

using hftl::BoBe;
using hftl::BoLe;

using hftl::boBe;
using hftl::boLe;

using hftl::TNByte;

typedef unsigned int     TUInt;
typedef TOptional<TUInt> OUInt;
typedef TOptional<bool>  OBool;

////////////////////////////////////////////////////////////////////////////////
typedef std::deque<TByte>          TByteDeque;

typedef TByteDeque::const_iterator TByteDequeCIt;
typedef TByteDeque::iterator       TByteDequeIt;

using std::basic_string;
using std::wstring;
using std::string;

template <typename T>
struct ConstRef {
  typedef const T& type;
};

typedef hftl::TSerNumGen<TUInt> TSerNumGen;
typedef TSerNumGen::TSerNum     TSerNum;

using boost::ratio;

#endif
