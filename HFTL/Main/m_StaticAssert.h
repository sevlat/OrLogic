#ifndef m_StaticAssert_h_already_included__24_04_2013__18290BC0
#define m_StaticAssert_h_already_included__24_04_2013__18290BC0
//
// SeVlaT, 24.04.2013
//

// Borrowed from boost::static_assert

namespace hftl {
  namespace details {
    ///////////////////////////////////////////////////////////////////////////////
    // HP aCC cannot deal with missing names for template value parameters
    template <bool x> struct STATIC_ASSERTION_FAILURE;

    template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

    // HP aCC cannot deal with missing names for template value parameters
    template<int x> struct static_assert_test{};
  }
}

#define HFTL_STATIC_ASSERT( B ) \
   typedef ::hftl::details::static_assert_test<\
      sizeof(::hftl::details::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
      > hftl_static_assert_typedef_

#endif
