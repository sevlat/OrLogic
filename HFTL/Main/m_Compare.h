#ifndef m_Compare_h_already_included__22_10_2011__3AE83CDE
#define m_Compare_h_already_included__22_10_2011__3AE83CDE
//
// SeVlaT, 22.10.2011
//

namespace hftl { // HelpFul useful template library

////////////////////////////////////////////////////////////////////////////////
// Functions for comparing values
// CompareX
// X - mode of comparizons: 
//   V-Value.   Uses operator <.
//   B-Boolean. Uses operator !. Assumptions: false<true, true=true, false=false
//   Z-Zero.    Uses operator !. Assumptions: Zero<NonZero, Zero=Zero, NonZero?NonZero
//

// Compares values. Require operator <
template<typename L, typename R>
int CompareV(const L &lhs, const R &rhs)
{
  if (lhs<rhs) return -1;
  if (rhs<lhs) return  1;
               return  0; 
}

// Return true if operands are not equals
// Return false otherwise
template<typename L, typename R>
bool CompareV(const L &lhs, const R &rhs, int &nRes)
{
  nRes=CompareV(lhs, rhs);
  return nRes!=0;
}

template<typename L, typename R>
bool LessV(const L &lhs, const R &rhs, int &nRes)
{
  if (lhs<rhs) { nRes=-1; return true;  }
                 nRes= 0; return false;
}

////////////////////////////////////////////////////////////////////////////////
// Compares boolean values. Require operator !
// Return TRUE if operands are NOT EQUALS
// Return false otherwise
template<typename L, typename R>
bool CompareB(const L &lhs, const R &rhs, int &nRes)
{ // (!A && B) => (A<B)
  if (!lhs) {
    if (!rhs) { nRes= 0; return false; } // l==false && r==false
              { nRes=-1; return true;  } // l==false && r==true
  } 
  if (!rhs)   { nRes= 1; return true;  } // l==true  && r==false
                nRes= 0; return false;   // l==true  && r==true
}

// Compares values as booleans. Require operator !
// Return TRUE if operands are NOT EQUALS or BOTH ZERO
// Return false otherwise
template<typename L, typename R>
bool CompareZ(const L &lhs, const R &rhs, int &nRes)
{ // (!A && B) => (A<B)
  if (!lhs) {
    if (!rhs) { nRes= 0; return true;  } // l==0 && r==0
              { nRes=-1; return true;  } // l==0 && r!=0
  } 
  if (!rhs)   { nRes= 1; return true;  } // l!=0 && r==0
                nRes= 0; return false;   // l!=0 && r!=0
}

template<typename L, typename R>
bool CompareZ(const L &lhs, const R &rhs)
{
  return !lhs || !rhs;
}

}

#endif
