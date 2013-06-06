#ifndef m_Memory_h_already_included__22_07_2011__14DEC798
#define m_Memory_h_already_included__22_07_2011__14DEC798
//
// SeVT, 22.07.2011
//

namespace hftl {

// a-la boost

template<typename T>
class TScopedPtr {
 private:
  TScopedPtr(TScopedPtr const &);
  TScopedPtr & operator=(TScopedPtr const &);

 public:
  explicit TScopedPtr(T *ptr=0) : m_ptr(ptr) {}
  ~TScopedPtr() { delete m_ptr; }

  T* Get() const { return m_ptr; }
  T& operator*() const { return *m_ptr; }

  bool operator !() const { return m_ptr==0; }

  void Reset(T *ptr=0) { delete m_ptr; m_ptr=ptr; }

 private:
  T *m_ptr;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TScopedArray {
 private:
  TScopedArray(TScopedArray const &);
  TScopedArray & operator=(TScopedArray const &);

 public:
  explicit TScopedArray(T *ptr=0) : m_ptr(ptr) {}
  ~TScopedArray() { delete [] m_ptr; }

  T* Get() const { return m_ptr; }

  bool operator !() const { return m_ptr==0; }

 private:
  T *m_ptr;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TIntrusivePtr_base {
 protected:
  explicit TIntrusivePtr_base(T *pVal)
   : m_p(pVal)    { DoAddRef(); } 

  TIntrusivePtr_base(TIntrusivePtr_base &ptr)
   : m_p(ptr.m_p) { DoAddRef(); } 

  ~TIntrusivePtr_base()
   { DoRelease(); } 

 protected:
  TIntrusivePtr_base& operator=(const TIntrusivePtr_base &ptr)
   { TIntrusivePtr_base(ptr).swap(*this); return *this; } 

 public:
  void Swap(TIntrusivePtr_base &ptr)
   { T *p=m_p; m_p=ptr.m_p; ptr.m_p=p; }

 public:
  const T* GetPtr() const { return m_p; }
        T* GetPtr()       { return m_p; }

 public: // implicit conversion to "bool"
  typedef const T* TIntrusivePtr_base::*Bool;

  operator Bool() const
  { return m_p? &TIntrusivePtr_base::m_p: 0; }

  bool operator! () const { return m_p==0; }

 private:
	void DoAddRef()  const { if (m_p) m_p->AddRef(); }
	void DoRelease() const { if (m_p) m_p->Release(); }

 private:
  T *m_p;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TIntrusiveRef: public TIntrusivePtr_base<T> {
  typedef TIntrusivePtr_base<T> TBase;

 public:
  explicit TIntrusiveRef(T &Val): TBase(&Val) {  } 

 public:
  const T& Get() const { return *GetPtr(); }
        T& Get()       { return *GetPtr(); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TIntrusivePtr: public TIntrusivePtr_base<T> {
  typedef TIntrusivePtr_base<T> TBase;

 public:
  explicit TIntrusivePtr(T *pVal): TBase(pVal) {  } 
  explicit TIntrusivePtr(T &Val) : TBase(&Val) {  } 

  TIntrusivePtr(const TBase &ptr): TBase(ptr) {}

 public:
  const T* Get() const { return GetPtr(); }
};

////////////////////////////////////////////////////////////////////////////////
template <typename DERIVED>
class TIntrusivePointee_crtp {
 public:
  TIntrusivePointee_crtp(): m_nRefCount(0) {}

 protected:
  ~TIntrusivePointee_crtp() { }

 public:
  void AddRef()  { ++m_nRefCount; }
  void Release() { --m_nRefCount; if (m_nRefCount==0) delete SelfPtr(); }

 private:
  DERIVED* SelfPtr() { return static_cast<DERIVED*>(this); }

 protected:
  int Service_GetCount() const { return m_nRefCount; }

 private:
  unsigned int m_nRefCount;
};

////////////////////////////////////////////////////////////////////////////////
class TIntrusivePointee_base {
 public:
  TIntrusivePointee_base(): m_nRefCount(0) {}
  virtual ~TIntrusivePointee_base() {}

 private:
  TIntrusivePointee_base(const TIntrusivePointee_base&);
  TIntrusivePointee_base& operator=(const TIntrusivePointee_base&);

 public:
  void AddRef()  { ++m_nRefCount; }
  void Release() { --m_nRefCount; if (m_nRefCount==0) delete this; }

 protected:
  int Service_GetCount() const { return m_nRefCount; }

 private:
  int m_nRefCount;
};

////////////////////////////////////////////////////////////////////////////////

template <typename DERIVED>
void intrusive_ptr_add_ref(TIntrusivePointee_crtp<DERIVED> *p)
 { if (p) p->AddRef(); } 

template <typename DERIVED>
void intrusive_ptr_release(TIntrusivePointee_crtp<DERIVED> *p)
 { if (p) p->Release(); } 




}

#endif
