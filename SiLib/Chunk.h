#ifndef Chunk_h_already_included__17_03_2013__38B15240
#define Chunk_h_already_included__17_03_2013__38B15240
//
// SeVlaT, 17.03.2013
//

#include "TimeTypes.h"
#include "ByteBuffer.h"

class TTimeRange {
 public:
  TSysTime t0;
  TSysTime t1;
};
typedef TOptional<TTimeRange> OTimeRange;

class TChunk: public TTimeRange {
 public:
  TByteBuffer buf;
  TUInt nRequested;
};

#endif
