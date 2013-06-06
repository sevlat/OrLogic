#ifndef ByteBuffer_h_already_included__13_08_2012__2B87C64
#define ByteBuffer_h_already_included__13_08_2012__2B87C64
//
// SeVlaT, 13.08.2012
//

#include "ByteBufAddress.h"

////////////////////////////////////////////////////////////////////////////////
template <typename DERIVED>
class TByteBuffer_crtp {
 public:
  typedef std::vector<TByte>      TVector;

  typedef TVector::const_iterator const_iterator;
  typedef TVector::iterator       iterator;

  typedef TVector::size_type      size_type;

 protected:
  ~TByteBuffer_crtp() {}

 public:
  TByte operator [](size_type i) const { SelfIndex(i); return SelfData()[i]; }

  size_type size() const { return SelfData().size();  }
  bool empty() const     { return SelfData().empty(); }

 public:
        iterator begin()       { return SelfData().begin(); }
  const_iterator begin() const { return SelfData().begin(); }

        iterator end()         { return SelfData().end(); }
  const_iterator end() const   { return SelfData().end(); }

 public:
        TByte* begin_ptr()       { return hftl::begin_ptr(SelfData()); }
  const TByte* begin_ptr() const { return hftl::begin_ptr(SelfData()); }

        TByte* ptr(size_type i)       { SelfIndex(i); return &SelfData()[i]; }
  const TByte* ptr(size_type i) const { SelfIndex(i); return &SelfData()[i]; }

 public:
  void reserve(size_type nBytes) { SelfData().reserve(nBytes); }

 public:
  void Append(TByte b) { SelfData().push_back(b); }

  void Append(const void *pBuf, size_type nBytes)
   { const TByte *pbBuf=static_cast<const TByte*>(pBuf);
     TVector &Vec=SelfData();
     Vec.insert(Vec.end(), pbBuf, pbBuf+nBytes);
   }

  template<unsigned int N>
  void Append(const TByte(&b)[N])
   {
     TVector &Vec=SelfData();
     Vec.insert(Vec.end(), b, b+N);
   }

 public:
  OByte Byte1(size_type i) const
    { if (!SelfCheckIndex(i)) return None;
      const TVector &Vec=SelfData();
      return Vec[i]; }

  template <typename BO>
  OWord Byte2(size_type i) const
    { if (!SelfCheckIndex(i, 2)) return None;
      const TVector &Vec=SelfData();
      return hftl::Make2Byte<BO>(Vec[i], Vec[i+1]); }

  template <typename BO>
  ODWord Byte3(size_type i) const
    { if (!SelfCheckIndex(i, 3)) return None;
      const TVector &Vec=SelfData();
      return hftl::Make3Byte<BO>(Vec[i], Vec[i+1], Vec[i+2]); }

  template <typename BO>
  ODWord Byte4(size_type i) const
    { if (!SelfCheckIndex(i, 4)) return None;
      const TVector &Vec=SelfData();
      return hftl::Make4Byte<BO>(Vec[i], Vec[i+1], Vec[i+2], Vec[i+3]); }

 public:
  OWord Byte2(size_type iL,  size_type iH) const
    {
      if (!SelfCheckIndex(iL) ||
          !SelfCheckIndex(iH)) return None;

      const TVector &Vec=SelfData();
      return hftl::Make2Byte(Vec[iL], Vec[iH]);
    }

  ODWord Byte3(size_type iLL, size_type iLH, size_type iHL) const
    {
      if (!SelfCheckIndex(iLL) ||
          !SelfCheckIndex(iLH) ||
          !SelfCheckIndex(iHL)) return None;

      const TVector &Vec=SelfData();
      return hftl::Make3Byte(Vec[iLL], Vec[iLH], Vec[iHL]);
    }

  ODWord Byte4(size_type iLL, size_type iLH, size_type iHL, size_type iHH) const
    {
      if (!SelfCheckIndex(iLL) ||
          !SelfCheckIndex(iLH) ||
          !SelfCheckIndex(iHL) ||
          !SelfCheckIndex(iHH)) return None;

      const TVector &Vec=SelfData();
      return hftl::Make4Byte(Vec[iLL], Vec[iLH], Vec[iHL], Vec[iHH]);
    }

 public:
  OByte GetRaw(const TBbAddress1 &adr) const
   { return Byte1(adr.i); }

  OWord GetRaw(const TBbAddress2 &adr) const
   { return Byte2(adr.iL, adr.iH); }
  OWord GetRaw(const TBbAddress2Be &adr) const
   { return Byte2<BoBe>(adr.i); }
  OWord GetRaw(const TBbAddress2Le &adr) const
   { return Byte2<BoLe>(adr.i); }

  ODWord GetRaw(const TBbAddress3 &adr) const
   { return Byte3(adr.iLL, adr.iLH, adr.iHL); }
  ODWord GetRaw(const TBbAddress3Be &adr) const
   { return Byte3<BoBe>(adr.i); }
  ODWord GetRaw(const TBbAddress3Le &adr) const
   { return Byte3<BoLe>(adr.i); }

  ODWord GetRaw(const TBbAddress4 &adr) const
   { return Byte4(adr.iLL, adr.iLH, adr.iHL, adr.iHH); }
  ODWord GetRaw(const TBbAddress4Be &adr) const
   { return Byte4<BoBe>(adr.i); }
  ODWord GetRaw(const TBbAddress4Le &adr) const
   { return Byte4<BoLe>(adr.i); }

 public:
  template <int SIZE, typename RESULT>
  TOptional<RESULT> Get(const TBbAddrSparse<SIZE, RESULT> &adr) const
   { return GetRaw(adr).ToOpt<RESULT>(); }

  template <int SIZE, typename BO, typename RESULT>
  TOptional<RESULT> Get(const TBbAddr<SIZE, BO, RESULT> &adr) const
   { return GetRaw(adr).ToOpt<RESULT>(); }

 private:
  bool Check(size_type i)                   const { return i<SelfData().size(); }
  bool Check(size_type i0, size_type nSize) const { return Check(i0) && Check(i0+nSize-1); }

 private:
        DERIVED& Self()       { return static_cast<      DERIVED&>(*this); }
  const DERIVED& Self() const { return static_cast<const DERIVED&>(*this); }

        TVector& SelfData()       { return Self().Data(); }
  const TVector& SelfData() const { return Self().Data(); }

  void SelfIndex(size_type &i) const { Self().Index(i); }

  bool SelfCheckIndex(size_type &i)                  const { SelfIndex(i); return Check(i); }
  bool SelfCheckIndex(size_type &i, size_type nSize) const { SelfIndex(i); return Check(i, nSize); }

};

////////////////////////////////////////////////////////////////////////////////
class TByteBuffer: public TByteBuffer_crtp<TByteBuffer> {
  typedef TByteBuffer_crtp<TByteBuffer> TBase;

 public:
  void swap(TByteBuffer &bb) { m_data.swap(bb.m_data); }

 public:
  using TBase::Append;

  void Append(const TByteBuffer &Buf)
   { m_data.insert(m_data.end(), Buf.m_data.begin(), Buf.m_data.end()); }

 public:
  void resize(size_type nBytes)          { m_data.resize(nBytes); }
  void assign(size_type nBytes, TByte b) { m_data.assign(nBytes, b); }
  void clear()                           { m_data.clear(); }

 private:
        TVector& Data()       { return m_data; }
  const TVector& Data() const { return m_data; }

  void Index(size_type &i) const {}

 private:
  TVector m_data;

  friend class TBase;
  friend class TBiasedByteBuffer;
};


typedef TByteBuffer::const_iterator TByteBufferCIt;
typedef TByteBuffer::iterator       TByteBufferIt;

typedef TOptional<TByteBuffer>      OByteBuffer;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class TBiasedByteBuffer: public TByteBuffer_crtp<TBiasedByteBuffer> {
  typedef TByteBuffer_crtp<TBiasedByteBuffer> TBase;

 public:
  TBiasedByteBuffer()
   : m_nBase(0) {}
  
  explicit TBiasedByteBuffer(const TByteBuffer &buf, size_type nBase=0)
   : m_data(buf.m_data),
     m_nBase(nBase) {}

 public:
  void swap(TBiasedByteBuffer &bb)
   { m_data.swap(bb.m_data);
     std::swap(m_nBase, bb.m_nBase); }

 public:
  using TBase::Append;

 private:
        TVector& Data()       { return m_data; }
  const TVector& Data() const { return m_data; }

  void Index(size_type &i) const { i-=m_nBase; }

 public:
  size_type First() const { return m_nBase; }
  size_type Last()  const { return m_nBase+m_data.size(); }

 private:
  size_type m_nBase;

 private:
  TVector m_data;

  friend class TBase;
};


typedef TBiasedByteBuffer::const_iterator TBiasedByteBufferCIt;
typedef TBiasedByteBuffer::iterator       TBiasedByteBufferIt;

typedef TOptional<TBiasedByteBuffer>      OBiasedByteBuffer;

////////////////////////////////////////////////////////////////////////////////
class IByteBuffer {
 public:
  virtual OByte GetRaw(const TBbAddress1 &adr) const=0;

  virtual OWord GetRaw(const TBbAddress2 &adr) const=0;
  virtual OWord GetRaw(const TBbAddress2Be &adr) const=0;
  virtual OWord GetRaw(const TBbAddress2Le &adr) const=0;

  virtual ODWord GetRaw(const TBbAddress3 &adr) const=0;
  virtual ODWord GetRaw(const TBbAddress3Be &adr) const=0;
  virtual ODWord GetRaw(const TBbAddress3Le &adr) const=0;

  virtual ODWord GetRaw(const TBbAddress4 &adr) const=0;
  virtual ODWord GetRaw(const TBbAddress4Be &adr) const=0;
  virtual ODWord GetRaw(const TBbAddress4Le &adr) const=0;

 public:
  virtual TiSegmU Required(TInd iAdr, TInd iMaxSize) const=0;

 public:
  virtual ~IByteBuffer() {}
};

#endif
