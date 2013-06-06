#ifndef Crc_h_already_included__12_06_2012__6A83CB8
#define Crc_h_already_included__12_06_2012__6A83CB8
//
// SeVlaT, 12.06.2012
//

#include "Types.h"
#include "ByteBuffer.h"

class TCrc {
 public:
  TCrc();
  explicit TCrc(int nReserve);

 public:
  void AddByte(TByte b);
  void AddBuf(const TByteBuffer &Buf);
  
 public:
  TWord Get() const;
  
 private:
  TByteBuffer m_Buf;
};

#endif
