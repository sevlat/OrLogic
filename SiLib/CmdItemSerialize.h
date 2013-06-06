#ifndef CmdItemSerialize_h_already_included__05_10_2012__208CCD40
#define CmdItemSerialize_h_already_included__05_10_2012__208CCD40
//
// SeVlaT, 05.10.2012
//

#include "Types.h"
#include "Fwd.h"
#include "ByteBuffer.h"
#include "TimeTypes.h"

namespace NCmdItemSerializeErrors {

  enum TErrorCode {
    eUnknown,
    
    eIncorrectMaSlaveData,
    eIncorrectInOutData,
    eIncorrectBaudRateData,
 
    eLast
  };
}

////////////////////////////////////////////////////////////////////////////////
class TSerializerErrorBase {
 protected:
  explicit TSerializerErrorBase(TErrList *pErr)
   : m_pErr(pErr) {}

 protected:
  typedef NCmdItemSerializeErrors::TErrorCode TErrorCode;

 protected:
  void PushError(TErrorCode ec) const;

 protected:
  TErrList *m_pErr;
};

////////////////////////////////////////////////////////////////////////////////
class TISerializer: protected TSerializerErrorBase {
 public:
  TISerializer(IIStream &is, TErrList *pErr)
   : TSerializerErrorBase(pErr),
     m_is(is) {}

 public:
  bool B1Byte  (TByte          &b)       const;
  bool B2ByteBE(TWord          &w)       const;
  bool B3ByteBE(TDWord         &dw)      const;
  bool B4ByteBE(TDWord         &dw)      const;
  bool MaSlave (bool           &bMaster) const;
  bool InOut   (bool           &bIn)     const;
  bool BaudRate(bool           &bHigh)   const;
  bool Time    (TStationTime   &st)      const;
  bool TimeSS  (TStationTimeSS &st)      const;
  bool Buffer  (TByteBuffer    &buf)     const;

 private:
  bool Bool(TByte       bTrue,
            TByte       bFalse,
            bool       &b,
            TErrorCode  ec) const;

 private:
  IIStream &m_is; 
};

////////////////////////////////////////////////////////////////////////////////
class TOSerializer: protected TSerializerErrorBase {
 public:
  TOSerializer(IOStream &os, TErrList *pErr)
   : TSerializerErrorBase(pErr),
     m_os(os) {}

 public:
  bool B1Byte  (      TByte           b)       const;
  bool B2ByteBE(      TWord           w)       const;
  bool B3ByteBE(      TDWord          dw)      const;
  bool B4ByteBE(      TDWord          dw)      const;
  bool MaSlave (      bool            bMaster) const;
  bool InOut   (      bool            bIn)     const;
  bool BaudRate(      bool            bHigh)   const;
  bool Time    (const TStationTime   &st)      const;
  bool TimeSS  (const TStationTimeSS &st)      const;
  bool Buffer  (const TByteBuffer    &buf)     const;

 protected:
  bool Bool(TByte     bTrue,
            TByte     bFalse,
            bool      b) const;
            
 private:
  IOStream &m_os; 
};

////////////////////////////////////////////////////////////////////////////////
class TCountSerializer {
 public:
  TCountSerializer(int &nMinSize, int &nMaxSize);
   
 public:
  void B1Byte  () const;
  void B2ByteBE() const;
  void B3ByteBE() const;
  void B4ByteBE() const;
  void MaSlave () const;
  void InOut   () const;
  void BaudRate() const;
  void Time    () const;
  void TimeSS  () const;
  void Buffer  () const;

 private:
  void Bool() const;

 private:
  void Add(int n) const;
  void Add(int nMin, int nMax) const;

 private:
  int &m_nMinSize; 
  int &m_nMaxSize; 
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename DATA>
class TDISerializer {
 public:
  TDISerializer(IIStream &is, DATA &Data, TErrList *pErr)
   : m_Ser(is, pErr),
     m_Data(Data) {}

 public:
  template<TByte          DATA::*pmb>       bool B1Byte  () const { return m_Ser.B1Byte  (m_Data.*pmb)      ; }
  template<TWord          DATA::*pmw>       bool B2ByteBE() const { return m_Ser.B2ByteBE(m_Data.*pmw)      ; }
  template<TDWord         DATA::*pmt>       bool B3ByteBE() const { return m_Ser.B3ByteBE(m_Data.*pmt)      ; }
  template<TDWord         DATA::*pmdw>      bool B4ByteBE() const { return m_Ser.B4ByteBE(m_Data.*pmdw)     ; }
  template<bool           DATA::*pmbMaster> bool MaSlave () const { return m_Ser.MaSlave (m_Data.*pmbMaster); }
  template<bool           DATA::*pmbIn>     bool InOut   () const { return m_Ser.InOut   (m_Data.*pmbIn)    ; }
  template<bool           DATA::*pmbHigh>   bool BaudRate() const { return m_Ser.BaudRate(m_Data.*pmbHigh)  ; }
  template<TStationTime   DATA::*pmst>      bool Time    () const { return m_Ser.Time    (m_Data.*pmst)     ; } 
  template<TStationTimeSS DATA::*pmst>      bool TimeSS  () const { return m_Ser.TimeSS  (m_Data.*pmst)     ; } 
  template<TByteBuffer    DATA::*pbuf>      bool Buffer  () const { return m_Ser.Buffer  (m_Data.*pbuf)     ; } 

 private:
  TISerializer m_Ser; 
  DATA &m_Data;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DATA>
class TDOSerializer {
 public:
  TDOSerializer(IOStream &os, const DATA &Data, TErrList *pErr)
   : m_Ser(os, pErr),
     m_Data(Data) {}

 public:
  template<TByte          DATA::*pmb>       bool B1Byte  () const { return m_Ser.B1Byte  (m_Data.*pmb)      ; }
  template<TWord          DATA::*pmw>       bool B2ByteBE() const { return m_Ser.B2ByteBE(m_Data.*pmw)      ; }
  template<TDWord         DATA::*pmt>       bool B3ByteBE() const { return m_Ser.B3ByteBE(m_Data.*pmt)      ; }
  template<TDWord         DATA::*pmdw>      bool B4ByteBE() const { return m_Ser.B4ByteBE(m_Data.*pmdw)     ; }
  template<bool           DATA::*pmbMaster> bool MaSlave () const { return m_Ser.MaSlave (m_Data.*pmbMaster); }
  template<bool           DATA::*pmbIn>     bool InOut   () const { return m_Ser.InOut   (m_Data.*pmbIn)    ; }
  template<bool           DATA::*pmbHigh>   bool BaudRate() const { return m_Ser.BaudRate(m_Data.*pmbHigh)  ; }
  template<TStationTime   DATA::*pmst>      bool Time    () const { return m_Ser.Time    (m_Data.*pmst)     ; } 
  template<TStationTimeSS DATA::*pmst>      bool TimeSS  () const { return m_Ser.TimeSS  (m_Data.*pmst)     ; } 
  template<TByteBuffer    DATA::*pbuf>      bool Buffer  () const { return m_Ser.Buffer  (m_Data.*pbuf)     ; } 

 private:
  TOSerializer m_Ser; 
  const DATA &m_Data;
};

////////////////////////////////////////////////////////////////////////////////
template <typename DATA>
class TDCountSerializer {
 public:
  explicit TDCountSerializer(int &nSize)
   : m_Ser(nSize) {}
   
 public:
  template<TByte          DATA::*pmb>       bool B1Byte  () const { m_Ser.B1Byte  (); return true; }
  template<TWord          DATA::*pmw>       bool B2ByteBE() const { m_Ser.B2ByteBE(); return true; }
  template<TDWord         DATA::*pmt>       bool B3ByteBE() const { m_Ser.B3ByteBE(); return true; }
  template<TDWord         DATA::*pmdw>      bool B4ByteBE() const { m_Ser.B4ByteBE(); return true; }
  template<bool           DATA::*pmbMaster> bool MaSlave () const { m_Ser.MaSlave (); return true; }
  template<bool           DATA::*pmbIn>     bool InOut   () const { m_Ser.InOut   (); return true; }
  template<bool           DATA::*pmbHigh>   bool BaudRate() const { m_Ser.BaudRate(); return true; }
  template<TStationTime   DATA::*pmst>      bool Time    () const { m_Ser.Time    (); return true; } 
  template<TStationTimeSS DATA::*pmst>      bool TimeSS  () const { m_Ser.TimeSS  (); return true; } 
  template<TByteBuffer    DATA::*pbuf>      bool Buffer  () const { m_Ser.Buffer  (); return true; } 

 private:
  TCountSerializer m_Ser; 
};

////////////////////////////////////////////////////////////////////////////////
template <typename DATA, typename RNDGEN>
class TDRandomSerializer {
 public:
  explicit TDRandomSerializer(DATA &Data, RNDGEN RndGen)
   : m_RndGen(RndGen),
     m_Data(Data) {}

 public:
  template<TByte          DATA::*pmb>       bool B1Byte  () const { m_RngGen(m_Data.*pmb)      ; return true; }
  template<TWord          DATA::*pmw>       bool B2ByteBE() const { m_RngGen(m_Data.*pmw)      ; return true; }
  template<TDWord         DATA::*pmt>       bool B3ByteBE() const { m_RngGen(m_Data.*pmt)      ; return true; }
  template<TDWord         DATA::*pmdw>      bool B4ByteBE() const { m_RngGen(m_Data.*pmdw)     ; return true; }
  template<bool           DATA::*pmbMaster> bool MaSlave () const { m_RngGen(m_Data.*pmbMaster); return true; }
  template<bool           DATA::*pmbIn>     bool InOut   () const { m_RngGen(m_Data.*pmbIn)    ; return true; }
  template<bool           DATA::*pmbHigh>   bool BaudRate() const { m_RngGen(m_Data.*pmbHigh)  ; return true; }
  template<TStationTime   DATA::*pmst>      bool Time    () const { m_RngGen(m_Data.*pmst)     ; return true; } 
  template<TStationTimeSS DATA::*pmst>      bool TimeSS  () const { m_RngGen(m_Data.*pmst)     ; return true; } 
  template<TByteBuffer    DATA::*pbuf>      bool Buffer  () const { m_RngGen(m_Data.*pbuf)     ; return true; } 

 private:
  RNDGEN m_RndGen; 
  DATA &m_Data;
};
#endif
