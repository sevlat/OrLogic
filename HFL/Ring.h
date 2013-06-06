#ifndef Ring_h_already_included__23_05_2013__2DB8F3C0
#define Ring_h_already_included__23_05_2013__2DB8F3C0
//
// SeVlaT, 23.05.2013
//

template <typename ITERATOR>
class TRingImpl {
 protected:
  TRingImpl(const ITERATOR &iFirst, const ITERATOR &iLast)
   : m_iFirst(iFirst), m_iLast(iLast) {}

 protected:
  void Inc(ITERATOR &i) { ++i; if (i==m_iLast) i=m_iFirst; }
  void Dec(ITERATOR &i) { if (i==m_iFirst) i=m_iLast; --i; }

  const ITERATOR& First() const { return m_iFirst; }
  const ITERATOR& Last()  const { return m_iLast; }

 private:
  ITERATOR m_iFirst, m_iLast;
};

template <typename VALUE, typename ITERATOR>
class TRing: private TRingImpl<ITERATOR> {
 public:
  TRing(const ITERATOR &iFirst, const ITERATOR &iLast)
   : TRingImpl<ITERATOR>(iFirst, iLast),
     m_iBegin(iFirst), m_iEnd(iFirst) {}

 public:
  void clear() { m_iBegin=First(); m_iEnd=First(); }
  void push(const VALUE &v)
   { *m_iEnd=v; Inc(m_iEnd); if (m_iBegin==m_iEnd) Inc(m_iBegin); }

 public:
  bool empty() const { return m_iBegin!=m_iEnd; }
  const VALUE& top() const { ITERATOR iTop=m_iEnd; Dec(iTop); return *iTop; }

 public:
  struct const_iterator: private TRingImpl<ITERATOR> {
    const_iterator(const TRingImpl<ITERATOR> &RingImpl,
                   const ITERATOR &i)
     : TRingImpl<ITERATOR>(RingImpl),
       m_i(i) {}

    const VALUE& operator*() const { return *m_i; }
    ITERATOR operator->() const    { return m_i; }

    const_iterator& operator++()   { Inc(m_i); return *this; }
		const_iterator& operator--()   { Dec(m_i); return *this; }

		const_iterator operator++(int)
      { const_iterator I=*this; Inc(m_i); return I; }
		const_iterator operator--(int)
      { const_iterator I=*this; Dec(m_i); return I; }

    bool operator == (const const_iterator& I) const { return I.m_i==m_i; }
    bool operator != (const const_iterator& I) const { return I.m_i!=m_i; }

   private:
    ITERATOR m_i;
  };

 public:
  const_iterator begin() const { return const_iterator(*this, m_iBegin); }
  const_iterator end() const   { return const_iterator(*this, m_iEnd); }

 private:
  ITERATOR m_iBegin, m_iEnd;
};

template <typename VALUE, size_t SIZE>
class TRingArray: public TRing<VALUE, VALUE*> {
 public:
  TRingArray(): TRing<VALUE, VALUE*>(m_Array, m_Array+SIZE+1) {}

 private:
  TRingArray(const TRingArray &ra);
  void operator =(const TRingArray &ra);

 private:
  VALUE m_Array[SIZE+1];
};

template <typename STREAM, typename VALUE, typename ITERATOR>
STREAM& operator << (STREAM &stream, const TRing<VALUE, ITERATOR> &ring)
{
  typename TRing<VALUE, ITERATOR>::const_iterator iB=ring.begin(), iE=ring.end();

  for ( ; iB!=iE; ++iB) { stream << *iB; }
  return stream;
}

#endif
