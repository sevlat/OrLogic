#ifndef TimeTypes_h_already_included__17_11_2012__AEDC9C0
#define TimeTypes_h_already_included__17_11_2012__AEDC9C0
//
// SeVlaT, 17.11.2012
//

#include "Types.h"

#include <hftl/Main/m_Optional.h>

#include <hftl/Main/m_TimeUtils.h>

using boost::chrono::time_point;
using boost::chrono::duration;

using boost::chrono::nanoseconds;
using boost::chrono::microseconds;
using boost::chrono::milliseconds;
using boost::chrono::seconds;
using boost::chrono::minutes;
using boost::chrono::hours;

using boost::chrono::time_point_cast;
using boost::chrono::duration_cast;

const unsigned long c_nClockTick=32000; //LCM of 1000 and 256

BOOST_STATIC_ASSERT(c_nClockTick%256==0);
BOOST_STATIC_ASSERT(c_nClockTick%1000==0);

class TClock {
 public:
  typedef long rep; 
  typedef ratio<1, c_nClockTick> period;
  
  typedef duration<rep, period> duration;
  
  typedef time_point<TClock, duration> time_point;

  static const bool is_steady=false;
  
  time_point now() const; //?????
};

typedef TClock::duration   TSysSpan;
typedef TClock::time_point TSysTime;

TSysTime GetSysTime();

typedef TOptional<TSysSpan> OSysSpan;
typedef TOptional<TSysTime> OSysTime;

typedef duration<double>               TFloatSpan;
typedef time_point<TClock, TFloatSpan> TFloatTime;

////////////////////////////////////////////////////////////////////////////////
struct TNoonTime {
  TWord wDaySecond;

  int  Hour()   const { return hftl::DaySeconds2Hour(wDaySecond);   }
  int  Minute() const { return hftl::DaySeconds2Minute(wDaySecond); }
  int  Second() const { return hftl::DaySeconds2Second(wDaySecond); }

  explicit TNoonTime(TWord w)
   : wDaySecond(w) {}

  TNoonTime()
   : wDaySecond(0) {}
};

////////////////////////////////////////////////////////////////////////////////
struct TMoonTime: TNoonTime {
  TByte bWeekMidDay;
  
  bool Midday()  const { return HFTL_Bit1(bWeekMidDay, 0)!=0; }
  int  WeekDay() const { return HFTL_Bit3(bWeekMidDay, 1); }
  int  Week()    const { return HFTL_Bit2(bWeekMidDay, 4); }

  TMoonTime()
   : bWeekMidDay() {}

  explicit TMoonTime(TDWord dw)  // !!!!! To be checked
   : TNoonTime(HFTL_Get2WordL(dw)),
     bWeekMidDay(HFTL_Get4ByteHL(dw)) {}
};

////////////////////////////////////////////////////////////////////////////////
struct TMoonTimeSS: TMoonTime {
 public:
  TByte bSubSec;
  
 public:
  TMoonTimeSS()
   : bSubSec(0) {}

  TMoonTimeSS(const TMoonTime &t)
   : TMoonTime(t),
     bSubSec(0) {}
};

////////////////////////////////////////////////////////////////////////////////
struct TDate {
  TByte bYear;
  TByte bMonth;
  TByte bDay;
  
  TDate()
   : bYear (0),
     bMonth(0),
     bDay  (0) {}

  explicit TDate(TDWord dw) // !!!!! To be checked
   : bYear (HFTL_Get4ByteHL(dw)),
     bMonth(HFTL_Get4ByteLH(dw)),
     bDay  (HFTL_Get4ByteLL(dw))   {}
};

struct TDateTime: TDate, TMoonTime {
  TDateTime() {}

  TDateTime(const TDate     &d,
            const TMoonTime &t)
   : TDate(d),
     TMoonTime(t) {}
};

struct TDateTimeSS: TDate, TMoonTimeSS {
 public:
  TDateTime DateTime() const { return TDateTime(*this, *this); }

 public:
  TDateTimeSS() {}

  TDateTimeSS(const TDateTime &dt)
   : TMoonTimeSS(dt),
     TDate(dt) {}
};

////////////////////////////////////////////////////////////////////////////////
typedef TDateTime   TStationTime;     // !!!!!!!!!!!
typedef TDateTimeSS TStationTimeSS;   // !!!!!!!!!!!


typedef TDate     TBsMemDate;
typedef TMoonTime TBsMemTime;


#endif
