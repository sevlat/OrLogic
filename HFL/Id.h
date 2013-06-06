#ifndef Id_h_already_included__18_10_2011__3AE75009
#define Id_h_already_included__18_10_2011__3AE75009
//
// SeVlaT, 18.10.2011
// SeVlaT, 28.05.2011
// SeVlaT, 27.03.2011
//

class TIdData {
 public:
  TIdData();

 public:
  void Generate();
  bool IsNull() const { return m_n==0 && m_t==0; }

 public: 
  bool IsEqual(TIdData idd) const { return idd.m_n==m_n && idd.m_t==m_t; }

  bool LessThan(TIdData idd) const
  {
    if (m_n<idd.m_n) return false;
    if (m_n>idd.m_n) return true;
    return m_t>idd.m_t;
  }

 public: 
  unsigned int Display() const { return (unsigned int)m_n; }

 private:
  int m_n;
  int m_t;
};

class TIdLabel {
  enum { c_nBufSize=8 };

 public:
  TIdLabel();

 public:
  void Set(const char *sz);
  const char* Get() const { return m_sz; }
  
 private:
  char m_sz[c_nBufSize];
};

template <typename TAG>
class TIdt {
  class ZeroPtr {
    TAG* Dummi;
  };

 public:
  TIdt() {}
  TIdt(const ZeroPtr*) {}

 public:
  bool operator == (TIdt id) const { return  m_idd.IsEqual(id.m_idd); }
  bool operator != (TIdt id) const { return !m_idd.IsEqual(id.m_idd); }

 public:
  bool IdLessThan(TIdt idt) const
  { return m_idd.LessThan(idt.m_idd); }

  bool IdIsEqual(TIdt idt) const
  { return m_idd.IsEqual(idt.m_idd); }

  struct TIdCmp {
    bool operator ()(TIdt id0, TIdt id1) const
    { return id0.IdLessThan(id1); }
  };

  struct TIdEq {
    bool operator ()(TIdt id0, TIdt id1) const
    { return id0.IdIsEqual(id1); }
  };

 public:
  operator const void*() const { return m_idd.IsNull()? 0: &m_idd; }
  bool operator !() const { return m_idd.IsNull(); }

 public: 
  unsigned int Display() const { return m_idd.Display(); }

 protected:
  void GenerateId() { m_idd.Generate(); }

 private:
  TIdData m_idd;

#ifdef _DEBUG
 public:
  void SetLabel(const char *sz) { m_Label.Set(sz); }
  const char* GetLabel() const { return m_Label.Get(); }
  
 private:
  TIdLabel m_Label;
#else
 public:
  void SetLabel(const char *sz) {}
  const char* GetLabel() const { static char ch=0; return &ch; }
#endif
};

////////////////////////////////////////////////////////////////////////////////
template <typename TAG>
class TIdObject: protected TIdt<TAG> {
 public:
  typedef TIdt<TAG> TId;

 public:
  bool IdLessThan(const TIdObject &ido) const { return TIdt<TAG>::IdLessThan(ido); }
  using TId::IdIsEqual;

  struct TIdCmp {
    bool operator ()(const TIdObject &ido0, const TIdObject &ido1) const
    { return ido0.IdLessThan(ido1); }
  };

  struct TIdEq {
    bool operator ()(const TIdObject &ido0, const TIdObject &ido1) const
    { return ido0.IdIsEqual(ido1); }
  };

  struct TSmartPtrIdCmp {
    template <typename SMART_PTR>
    bool operator ()(const SMART_PTR &sp0, const SMART_PTR &sp1) const
    { return Id(sp0).IdLessThan(Id(sp1)); }

    template <typename SMART_PTR>
    TId Id(const SMART_PTR &sp) const
    { if (!sp) return 0; return *sp; }
  };


  struct TIdEqU: public std::unary_function<const TIdObject &, bool> {
    explicit TIdEqU(const TId &id)
     : m_id(id) {}

    bool operator ()(const TIdObject &ido) const
    { return ido.IdIsEqual(m_id); }

    TId m_id;
  };

 public:
  TId Id() const { return *this; }

 public:
  void SetDescr(const char    *sz);
  void SetDescr(const wchar_t *wsz);

 protected:
  TIdObject() { GenerateId(); }
  ~TIdObject() {}
};

#endif
