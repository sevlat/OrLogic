#ifndef m_stlUtils_h_already_included__21_08_2012__17168C80
#define m_stlUtils_h_already_included__21_08_2012__17168C80
//
// SeVlaT, 21.08.2012
//

namespace hftl { // Helpful template library

template<typename T, typename A>
const T* begin_ptr(const std::vector<T, A> &v)
{ 
  return v.empty()? 0: &(*v.begin());
}

template<typename T, typename A>
T* begin_ptr(std::vector<T, A> &v)
{ 
  return v.empty()? 0: &(*v.begin());
}

/////////////////////////////////////////////////////////////////////////////////
template<typename T, typename A>
const T* elem_ptr(const std::vector<T, A> &v, unsigned int i)
{ 
  return v.empty()? 0: &(v[i]);
}

template<typename T, typename A>
T* elem_ptr(std::vector<T, A> &v, unsigned int i)
{ 
  return v.empty()? 0: &(v[i]);
}

}

#endif
