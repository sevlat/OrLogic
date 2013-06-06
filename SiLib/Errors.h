#ifndef Errors_h_already_included__21_05_2012__2DB174C0
#define Errors_h_already_included__21_05_2012__2DB174C0
//
// SeVlaT, 21.05.2012
//

class TGlobalErrorCode {
 public:
  explicit TGlobalErrorCode(int n)
   : m_n(n) {}
 
 public:
  int Get() const { return m_n; }
  
 private:
  int m_n;
};

class TError {
 public:
  explicit TError(TGlobalErrorCode nCode);
 
 public:
  TGlobalErrorCode Code() const { return m_nCode; }
  unsigned long SysError() const { return m_dwSysError; }

 private:
  TGlobalErrorCode m_nCode;
  unsigned long m_dwSysError;
};

class TErrList {
 public:
  void Push(TGlobalErrorCode nCode);
  bool Pop();
  void Reset();
  
 public:
  const TError* Top() const;
  const TError* Get(int n) const;

 private:
  typedef std::vector<TError> TErrList::*Bool;
  static Bool MakeBool(bool b) { return b? &TErrList::m_vec: 0; }
  
 public:
  operator Bool() const { return MakeBool(m_vec.empty()); }

  bool operator! () const { return !m_vec.empty(); }

 private:
  std::vector<TError> m_vec;
};

template<typename ERRCODE, int ELAST, int EBASE>
class TErrorDescription {
  typedef ERRCODE TErrorCode;
  
  enum {
    eLast=ELAST,
    c_nErrBase=EBASE
  };
  
 public: 
  static bool i2e(TGlobalErrorCode i, TErrorCode &e)
   { const int ne=i-c_nErrBase;
     if (ne<0 || ne>=eLast) return false; 
     e=static_cast<TErrorCode>(ne);
     return true;
   }
   
  static TGlobalErrorCode e2i(TErrorCode e)
   { return TGlobalErrorCode(c_nErrBase+e); }
   
  static void PushError(TErrList *pErr, TErrorCode ec)
  { if (pErr) pErr->Push(e2i(ec)); }
   
};

struct TExcept {
};

inline void ThrowExcept() { throw TExcept(); }

namespace PlatformSpecific {
  unsigned int GetCurrentSystemError();
}

#endif
