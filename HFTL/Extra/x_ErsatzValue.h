#ifndef x_ErsatzValue_h_already_included__05_02_2012__35FE4E4F
#define x_ErsatzValue_h_already_included__05_02_2012__35FE4E4F
//
// SeVlaT, 05.02.2012
//

namespace hftl {

template<typename PUB, typename PRIV>
class TErsatzValue {
 public:
  TErsatzValue(PUB v): m_val(v) {}

 public:
  operator PUB() const { return m_val; }

 private:
  operator PRIV() const { return m_val; }

 private:
  PUB m_val;
};

}

#endif
