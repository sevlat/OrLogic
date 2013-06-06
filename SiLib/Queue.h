#ifndef Queue_h_already_included__06_03_2013__39D3D300
#define Queue_h_already_included__06_03_2013__39D3D300
//
// SeVlaT, 06.03.2013
//

#include "Types.h"

template<typename DERIVED, typename QUEUE, typename INDEX>
class TRangeQueue_crtp {
 public:
  typedef typename QUEUE        queue_type;
//  typedef typename DERIVED::queue_type        queue_type;
  
  typedef typename queue_type::size_type      size_type;
  typedef typename queue_type::value_type     value_type;
  typedef typename queue_type::const_iterator const_iterator;
  
  typedef INDEX index_type;
  
 protected:
  TRangeQueue_crtp()
   : m_nLast(0) {}  
   
  ~TRangeQueue_crtp() {}
  
 public:
  const_iterator begin() const { return Queue().begin(); }
  const_iterator end()   const { return Queue().end();   }
  
  bool empty() const { return Queue().empty(); }

 public:
  void push(const value_type &elem) { Queue().push_back(elem); ++m_nLast; }
  void pop() { Queue().pop_front(); }
  
 public:
  const value_type& get_first() const { return Queue().front(); }
  const value_type& get(index_type i)  { Queue()[i-first()]; }

  const value_type* check_get(index_type &i) const
    { if (i<first()) i=first();
      if (i>=last()) return 0;
      return &Queue()[i-first()]; }
  
 public:
  index_type first() const { return m_nLast-Queue().size(); }
  index_type last()  const { return m_nLast; }
  
 private:
  index_type m_nLast;
  
 private:
  queue_type& Queue()
   { return static_cast<DERIVED&>(*this).m_queue; }
  const queue_type& Queue() const
   { return static_cast<const DERIVED&>(*this).m_queue; }
};

////////////////////////////////////////////////////////////////////////////////
template<typename T, typename INDEX>
class TDequeRangeQueue: public TRangeQueue_crtp<TDequeRangeQueue<T, INDEX>,
                                                std::deque<T>,
                                                INDEX> {
 public:
  
 private:
  typedef std::deque<T> queue_type;

  friend class TRangeQueue_crtp<TDequeRangeQueue<T, INDEX>,
                                queue_type,
                                INDEX>;
  
  queue_type m_queue;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T, typename INDEX, unsigned int DEFCAP=64>
class TCircBufRangeQueue: public TRangeQueue_crtp<TCircBufRangeQueue<T, INDEX>,
                                                  boost::circular_buffer<T>,
                                                  INDEX> {
 public:
  TCircBufRangeQueue(size_type nCapacity=DEFCAP)
   : m_queue(nCapacity) {}
  
 private:
  typedef boost::circular_buffer<T> queue_type;

  friend class TRangeQueue_crtp<TCircBufRangeQueue<T, INDEX>,
                                queue_type,
                                INDEX>;
  
  queue_type m_queue;
};


#endif
