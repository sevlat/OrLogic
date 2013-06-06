#ifndef BsParserChain_h_already_included__04_12_2012__32BC8500
#define BsParserChain_h_already_included__04_12_2012__32BC8500
//
// SeVlaT, 04.12.2012
//

#include "BsParser.h"

typedef std::vector<TBsParser>       TBsParserVec;
typedef TBsParserVec::const_iterator TBsParserVecCIt;


class TBsParserChain {
 public:
  TBsParserChain();
  
 public:
  bool AddChar(char ch);
  bool Parsed() const;
  bool Continue();
  
 public:
  const TBsParser& Top() const { return m_vec.back(); }
  const TBsParser& Get(TUInt i) const { return m_vec[i]; }
  
  TUInt Count() const { return m_vec.size(); }

 public:
  bool Closed() const;

 private:
  TBsParserVec m_vec;
  
 private:
  bool m_bClosed;
};

#endif
