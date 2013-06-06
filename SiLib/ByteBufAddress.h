#ifndef ByteBufAddress_h_already_included__19_04_2013__27216000
#define ByteBufAddress_h_already_included__19_04_2013__27216000
//
// SeVlaT, 19.04.2013
//

#include "Types.h"

template <int SIZE>
struct TBbAddressSparse;

template <>
struct TBbAddressSparse<1> {
  static const int c_nSize=1;
  
  TInd i;
  
  TiSegmU Range() const { return TiSegmU(i, i+1); }
  
  explicit TBbAddressSparse(TInd ai): i(ai) {}
};


template <>
struct TBbAddressSparse<2> {
  static const int c_nSize=2;
  
  TInd iL;
  TInd iH;
  
  TiSegmU Range() const { return TiSegmU::MakeRange(iL, iH); }
  
  TBbAddressSparse(TInd aiL, TInd aiH): iL(aiL), iH(aiH) {}
};

template <>
struct TBbAddressSparse<3> {
  static const int c_nSize=3;
  
  TInd iLL;
  TInd iLH;
  TInd iHL;
  
  TiSegmU Range() const { return TiSegmU::MakeRange(iLL, iLH, iHL); }
  
  TBbAddressSparse(TInd aiLL, TInd aiLH, TInd aiHL): iLL(aiLL), iLH(aiLH), iHL(aiHL) {}
};

template <>
struct TBbAddressSparse<4> {
  static const int c_nSize=4;
  
  TInd iLL;
  TInd iLH;
  TInd iHL;
  TInd iHH;
  
  TiSegmU Range() const { return TiSegmU::MakeRange(iLL, iLH, iHL, iHH); }
  
  TBbAddressSparse(TInd aiLL, TInd aiLH, TInd aiHL, TInd aiHH)
   : iLL(aiLL), iLH(aiLH), iHL(aiHL), iHH(aiHH) {}
};

typedef TBbAddressSparse<1> TBbAddress1;
typedef TBbAddressSparse<2> TBbAddress2;
typedef TBbAddressSparse<3> TBbAddress3;
typedef TBbAddressSparse<4> TBbAddress4;


////////////////////////////////////////////////////////////////////////////////
template <int SIZE, typename BO>
struct TBbAddressSolid {
  static const int c_nSize=SIZE;
  typedef BO TBo;
  
  TInd i;
  
  TiSegmU Range() const { return TiSegmU(i, i+SIZE); }

  explicit TBbAddressSolid(TInd ai): i(ai) {}
};

typedef TBbAddressSolid<2, BoBe> TBbAddress2Be;
typedef TBbAddressSolid<2, BoLe> TBbAddress2Le;
                                            
typedef TBbAddressSolid<3, BoBe> TBbAddress3Be;
typedef TBbAddressSolid<3, BoLe> TBbAddress3Le;
                                            
typedef TBbAddressSolid<4, BoBe> TBbAddress4Be;
typedef TBbAddressSolid<4, BoLe> TBbAddress4Le;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <int SIZE, typename RESULT=typename TNByte<SIZE>::Type>
struct TBbAddrSparse;

template <typename RESULT>
struct TBbAddrSparse<1, RESULT>: TBbAddress1 {
  typedef RESULT TResult;
 
  explicit TBbAddrSparse(TInd ai): TBbAddress1(ai) {}
  explicit TBbAddrSparse(TBbAddress1 adr): TBbAddress1(adr) {}
};

////////////////////////////////////////////////////////////////////////////////
template <typename RESULT>
struct TBbAddrSparse<2, RESULT>: TBbAddress2 {
  typedef RESULT TResult;
  
  TBbAddrSparse(TInd aiL, TInd aiH): TBbAddress2(aiL, aiH) {}
  explicit TBbAddrSparse(TBbAddress2 adr): TBbAddress2(adr) {}
};


////////////////////////////////////////////////////////////////////////////////
template <typename RESULT>
struct TBbAddrSparse<3, RESULT>: TBbAddress3 {
  typedef RESULT TResult;
  
  TBbAddrSparse(TInd aiLL, TInd aiLH, TInd aiHL): TBbAddress3(aiLL, aiLH, aiHL) {}
  explicit TBbAddrSparse(TBbAddress3 adr): TBbAddress3(adr) {}
};

////////////////////////////////////////////////////////////////////////////////
template <typename RESULT>
struct TBbAddrSparse<4, RESULT>: TBbAddress4 {
  typedef RESULT TResult;
  
  TBbAddrSparse(TInd aiLL, TInd aiLH, TInd aiHL, TInd aiHH)
   : TBbAddress4(aiLL, aiLH, aiHL, aiHH) {}
  explicit TBbAddrSparse(TBbAddress4 adr): TBbAddress4(adr) {}
};

////////////////////////////////////////////////////////////////////////////////
typedef TBbAddrSparse<1, TByte>  TBbAdr1B;
typedef TBbAddrSparse<2, TWord>  TBbAdr2Dw;
typedef TBbAddrSparse<3, TDWord> TBbAdr3Dw;
typedef TBbAddrSparse<4, TDWord> TBbAddr4Dw;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <int SIZE, typename BO, typename RESULT=typename TNByte<SIZE>::Type>
struct TBbAddr: TBbAddressSolid<SIZE, BO> {
  typedef RESULT TResult;
  
  explicit TBbAddr(TInd ai): TBbAddressSolid(ai) {}
  explicit TBbAddr(TBbAddressSolid adr): TBbAddressSolid(adr) {}
};


typedef TBbAddr<2, BoBe, TWord>  TBbAdr2BeW;
typedef TBbAddr<2, BoLe, TWord>  TBbAdr2LeW;

typedef TBbAddr<3, BoBe, TDWord> TBbAdr3BeDw;
typedef TBbAddr<3, BoLe, TDWord> TBbAdr3LeDw;

typedef TBbAddr<4, BoBe, TDWord> TBbAddr4BeDw;
typedef TBbAddr<4, BoLe, TDWord> TBbAddr4LeDw;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename RESULT>
class IBbAddr {
 public:
  typedef RESULT TResult;

 public:
  virtual TiSegmU Range() const=0;
};

template <typename RESULT, typename BBADDR>
class TBbAddrV: public IBbAddr<RESULT> {
 public:
  static const int c_nSize=BBADDR::c_nSize;
  
 public:
  explicit TBbAddrV(const BBADDR &bbAddr)
   : m_bbAddr(bbAddr) {}
 
 public:
  virtual TiSegmU Range() const { return m_bbAddr.Range(); }
  
 public:
 private:
  const BBADDR m_bbAddr;
};

#endif
