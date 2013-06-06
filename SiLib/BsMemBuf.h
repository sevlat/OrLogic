#ifndef BsMemBuf_h_already_included__19_05_2013__121E4020
#define BsMemBuf_h_already_included__19_05_2013__121E4020
//
// SeVlaT, 19.05.2013
//

#include "ByteBuffer.h"


class TBsMemBuffer {
 public:
  bool Empty() const { return m_buf.empty(); }

 public:
  void AddEmpty(TUInt nAddr, TUInt nSize);
  void Add(const TBiasedByteBuffer &buf);

 public:
  bool Load(std::istream &is);
  bool Save(std::ostream &os) const;

 private:
   std::deque<TByte> m_buf;
};

#endif
