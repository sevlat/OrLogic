#ifndef m_Array_h_already_included__02_09_2012__201AC880
#define m_Array_h_already_included__02_09_2012__201AC880
//
// SeVlaT, 02.09.2012
//

#include "m_StaticAssert.h"

// Borrowed from boost::array

# pragma warning(push)  
# pragma warning(disable:4996) // 'std::equal': Function call with parameters that may be unsafe
# pragma warning(disable:4510) // boost::array<T,N>' : default constructor could not be generated 
# pragma warning(disable:4610) // warning C4610: class 'boost::array<T,N>' can never be instantiated - user defined constructor required 


// #include <cstddef>
// #include <stdexcept>
// #include <boost/assert.hpp>
// #include <boost/swap.hpp>
// 
// // Handles broken standard libraries better than <iterator>
// #include <boost/detail/iterator.hpp>
// #include <boost/throw_exception.hpp>
// #include <algorithm>
// 
// // FIXES for broken compilers
// #include <boost/config.hpp>

namespace hftl {

    template<class T, std::size_t N>
    class array {
      public:
       array()
        {}
       explicit array(const T& value)
        { fill(value); }
        
      public:
        T elems[N];    // fixed-size array of elements of type T

      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        // iterator support
        iterator        begin()       { return elems; }
        const_iterator  begin() const { return elems; }
        const_iterator cbegin() const { return elems; }
        
        iterator        end()       { return elems+N; }
        const_iterator  end() const { return elems+N; }
        const_iterator cend() const { return elems+N; }

        // operator[]
        reference operator[](size_type i) 
        { 
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i];
        }
        
        const_reference operator[](size_type i) const 
        {     
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i]; 
        }

        // at() with range check
        reference at(size_type i) { rangecheck(i); return elems[i]; }
        const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

        template <unsigned int I>
        reference at() { HFTL_STATIC_ASSERT(I<N); return elems[I]; }

        template <unsigned int I>
        const_reference at() const { HFTL_STATIC_ASSERT(I<N); return elems[I]; }
    
        // front() and back()
        reference front() 
        { 
            HFTL_STATIC_ASSERT(N>0)
            return elems[0]; 
        }
        
        const_reference front() const 
        {
            HFTL_STATIC_ASSERT(N>0)
            return elems[0];
        }
        
        reference back() 
        { 
            HFTL_STATIC_ASSERT(N>0)
            return elems[N-1]; 
        }
        
        const_reference back() const 
        { 
            HFTL_STATIC_ASSERT(N>0)
            return elems[N-1]; 
        }

        // size is constant
        static size_type size() { return N; }
        static bool empty() { return false; }
        static size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (array<T,N>& y) {
            for (size_type i = 0; i < N; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }
        T* data() { return elems; }

        // use array as C array (direct read/write access to data)
        T* c_array() { return elems; }

        // assignment with type conversion
        template <typename T2>
        array<T,N>& operator= (const array<T2,N>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value) { fill ( value ); }    // A synonym for fill
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static void rangecheck (size_type i) {
            if (i >= size()) {
                std::out_of_range e("array<>: index out of range");
                boost::throw_exception(e);
            }
        }

    };

    // comparisons
    template<class T, std::size_t N>
    bool operator== (const array<T,N>& x, const array<T,N>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, std::size_t N>
    bool operator< (const array<T,N>& x, const array<T,N>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, std::size_t N>
    bool operator!= (const array<T,N>& x, const array<T,N>& y) {
        return !(x==y);
    }
    template<class T, std::size_t N>
    bool operator> (const array<T,N>& x, const array<T,N>& y) {
        return y<x;
    }
    template<class T, std::size_t N>
    bool operator<= (const array<T,N>& x, const array<T,N>& y) {
        return !(y<x);
    }
    template<class T, std::size_t N>
    bool operator>= (const array<T,N>& x, const array<T,N>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, std::size_t N>
    inline void swap (array<T,N>& x, array<T,N>& y) {
        x.swap(y);
    }

// Specific for boost::array: simply returns its elems data member.
    template <typename T, std::size_t N>
    T(&get_c_array(array<T,N>& arg))[N]
    {
        return arg.elems;
    }
    
    // Const version.
    template <typename T, std::size_t N>
    const T(&get_c_array(const array<T,N>& arg))[N]
    {
        return arg.elems;
    }
}

#endif
