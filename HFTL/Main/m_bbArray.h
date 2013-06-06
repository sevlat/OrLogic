#ifndef m_bbArray_h_already_included__23_04_2013__245BA100
#define m_bbArray_h_already_included__23_04_2013__245BA100
//
// SeVlaT, 23.04.2013
//

#include "m_bbUtils.h"
#include "m_Array.h"

namespace hftl { // Helpful template library

template<std::size_t N>
class TByteArray: public array<TByte, N> {
 public:
  TByteArray() {}
  explicit TByteArray(TByte b): array(b) {}

 public:
  template <size_type I>
  TByte Byte1() const { return at<I>(); }

  template <size_type IL, size_type IH>
  TWord Byte2() const { return HFTL_Make2Byte(at<IL>(),
                                              at<IH>()); }

  template <size_type ILL, size_type ILH, size_type IHL>
  TDWord Byte3() const { return HFTL_Make3Byte(at<ILL>(),
                                               at<ILH>(),
                                               at<IHL>()); }

  template <size_type ILL, size_type ILH, size_type IHL, size_type IHH>
  TDWord Byte4() const { return HFTL_Make4Byte(at<ILL>(),
                                               at<ILH>(),
                                               at<IHL>(),
                                               at<IHH>()); }

 public:
  template <size_type I, typename BO>
  TWord Byte2() const { return Make2Byte<BO>(at<I>(),
                                             at<I+1>()); }

  template <size_type I, typename BO>
  TDWord Byte3() const { return Make3Byte<BO>(at<I>(),
                                              at<I+1>(),
                                              at<I+2>()); }

  template <size_type I, typename BO>
  TDWord Byte4() const { return Make4Byte<BO>(at<I>(),
                                              at<I+1>(),
                                              at<I+2>(),
                                              at<I+3>()); }

 public:
  template <size_type I>
  void Set1(TByte b) { at<I>()=b; }

  template <size_type IL, size_type IH>
  void Set2(TWord w) { SplitNByte(w, at<IL>(),
                                     at<IH>()); }

  template <size_type ILL, size_type ILH, size_type IHL>
  void Set3(TDWord dw) { SplitNByte(dw, at<ILL>(),
                                        at<ILH>(),
                                        at<IHL>()); }

  template <size_type ILL, size_type ILH, size_type IHL, size_type IHH>
  void Set4(TDWord dw) { SplitNByte(dw, at<ILL>(),
                                        at<ILH>(),
                                        at<IHL>(),
                                        at<IHH>()); }

 public:
  template <size_type I, typename BO>
  void Set2(TWord w) { SplitNByte<BO>(w, at<I>(),
                                         at<I+1>()); }

  template <size_type I, typename BO>
  void Set3(TDWord dw) { SplitNByte<BO>(dw, at<I>(),
                                            at<I+1>(),
                                            at<I+2>()); }

  template <size_type I, typename BO>
  void Set4(TDWord dw) { SplitNByte<BO>(dw, at<I>(),
                                            at<I+1>(),
                                            at<I+2>(),
                                            at<I+3>()); }
};

}

#endif
