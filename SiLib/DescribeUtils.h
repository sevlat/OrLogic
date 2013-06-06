#ifndef DescribeUtils_h_already_included__24_02_2013__28BDB600
#define DescribeUtils_h_already_included__24_02_2013__28BDB600
//
// SeVlaT, 24.02.2013
//

#include "Types.h"
#include "Fwd.h"
#include "TimeTypes.h" //!!!!!
#include "CommandCode.h"

void DescribeBool(      std::ostream &os,
                  const char         *szFalse,
                  const char         *szTrue,
                        bool          b);
void DescribeBool(std::ostream &os, const char *szName, bool b);
void DescribeInt(std::ostream &os, const char *szName, int n);
void DescribeHex(std::ostream &os, const char *szName, unsigned long dw);

void DescribeNoonTime(std::ostream &os, const char *szName, const TNoonTime &t);
void DescribeMoonTime(std::ostream &os, const char *szName, const TMoonTime &t);
void DescribeMoonTimeSS(std::ostream &os, const char *szName, const TMoonTimeSS &t);
void DescribeDate(std::ostream &os, const char *szName, const TDate &d);
void DescribeDateTime(std::ostream &os, const char *szName, const TDateTime &t);
void DescribeDateTimeSS(std::ostream &os, const char *szName, const TDateTimeSS &t);

void DescribeBuf(std::ostream &os, const TByteBuffer &buf, int nMaxLength);
void DescribeBufLen(std::ostream &os, const TByteBuffer &buf, int nMaxLength);

void DescribeCmdCode(std::ostream &os, TCmdCode cc, const TCommandInfo *pci);

////////////////////////////////////////////////////////////////////////////////
class TDescriber {
 public:
  explicit TDescriber(std::ostream &os);
  
 public:
  void Bool(const char *szFalse,
            const char *szTrue,
                  bool  b);
  void Bool(const char *szName, bool b);

  void Int(const char *szName, int n);
  void Hex(const char *szName, unsigned long un);

  void Time(const char *szName, const TStationTime &st);
  void Time(const char *szName, const TStationTimeSS &st);

  void Buf(const TByteBuffer &buf, int nMaxLength);
  void BufLen(const TByteBuffer &buf, int nMaxLength);

  void CmdCode(TCmdCode cc, const TCommandInfo *pci);

 public:
  void operator()(const char *szName, bool b)                   { return Bool(szName, b);  }

  void operator()(const char *szName, int n)                    { return Int(szName, n);   }
  void operator()(const char *szName, unsigned long un)         { return Hex(szName, un);  }

  void operator()(const char *szName, const TStationTime &st)   { return Time(szName, st); }
  void operator()(const char *szName, const TStationTimeSS &st) { return Time(szName, st); }
 
 protected:
  std::ostream &m_os;
};

#endif
