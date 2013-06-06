#ifndef m_SegPoint_h_already_included__16_03_2011__1B0D9707
#define m_SegPoint_h_already_included__16_03_2011__1B0D9707
//
// Taimanov Sergei, 16.03.2011
//

#include "m_MinMax.h"

namespace hftl {

enum TAlignment {
 aBegin,
 aCenter,
 aEnd
};

// Point- point
// Segm - segment (couple of points)
// U - unidimensional
// B - bidimensional

///////////////////////////////////////////////////////////////////////////////
// Segment span
template<typename VAL>
struct TSegmU {  // prefix 'ss'
 public:
  VAL B;
  VAL E;

 public:
  TSegmU()
   : B(VAL()), E(VAL()) {}
  TSegmU(VAL aB, VAL aE)
   : B(aB), E(aE) {}

 public:
  static TSegmU MakeBS(VAL aB, VAL aS) { return TSegmU(aB, aB+aS); }
  static TSegmU MakeSE(VAL aS, VAL aE) { return TSegmU(aE-aS, aE); }
  static TSegmU MakeCS(VAL aC, VAL aS) { return MakeBS(aC-aS/2, aS); }

  static TSegmU MakeI(VAL aB) { return TSegmU(aB, aB+1); }

  // !!!! MakeRange probably may be more effective
  static TSegmU MakeRange(VAL a0, VAL a1)
   { return TSegmU(Min(a0, a1), Max(a0, a1)+1); }

  static TSegmU MakeRange(VAL a0, VAL a1, VAL a2)
   { return TSegmU(Min(a0, a1, a2), Max(a0, a1, a2)+1); }

  static TSegmU MakeRange(VAL a0, VAL a1, VAL a2, VAL a3)
   { return TSegmU(Min(a0, a1, a2, a3), Max(a0, a1, a2, a3)+1); }

 public:
  VAL Size() const { return E-B; }
  VAL C()    const { return (B+E)/2; }

 public:
  TSegmU EB() const { return TSegmU(E, B); }

  TSegmU BB() const { return TSegmU(B, B); }
  TSegmU BC() const { return TSegmU(B, C()); }
  TSegmU CB() const { return TSegmU(C(), B); }

  TSegmU CC() const { const VAL c=C(); return TSegmU(c, c); }
  TSegmU CE() const { return TSegmU(C(), E); }
  TSegmU EC() const { return TSegmU(E, C()); }

  TSegmU EE() const { return TSegmU(E, E); }

 public:
  TSegmU BO() { return TSegmU(B, 0); }
  TSegmU OB() { return TSegmU(0, B); }

  TSegmU EO() { return TSegmU(E, 0); }
  TSegmU OE() { return TSegmU(0, E); }

 public:
  TSegmU NormI() const { return E<B? TSegmU(E, B): *this; }

 public:
  TSegmU& NormB() { if (E<B) B=E; return *this; }
  TSegmU& NormE() { if (E<B) E=B; return *this; }

 public:
//   Объединяет отрезки A и B, если это возможно. 
//   Если отрезки пересекаются или касаются, то возвращает true и устанавливает A
//   в объединение A и B.
//   Предполагается, что В - ненулевой правильный отрезок (Begin<End)

/*
  bool Eat(TSegmU su) {
  // Особо обрабатываем случай, когда отрезок A - пустой.
    if (B>=E) {  *this=su;  return true; }

    // Понятная, но неэффективная реализация

    // Если отрезки A и B пересекаются или касаются,
  //   if (Max(B, su.B)<=Min(E, su.E)) {
  //     B = Min(B, su.B);           // то объединяем их
  //     E   = Max(E,   su.E);
  //     return true;
  //   }
  //   return false;

  // То же самое, но эффективнее (3 сравнения + 0-2 присваивания)
    if (B<su.B) {         // => Max=su.B, Min=B
      if (E<su.E) {       // => Max=su.E,   Min=E
        if (su.B<=E) { 
          E = su.E;
          return true;
        }
      } else {             // => Max=E,   Min=su.E
        if (su.B<=su.E) {
          return true;
        }
      }
    } else {               // => Max=B, Min=su.B
      if (E<su.E) {        // => Max=su.E,   Min=E
        if (B<=E) {
          *this=su;
          return true;
        }
      } else {             // => Max=E,   Min=su.E
        if (B<=su.E) {
          B = su.B;
          return true;
        }
      }
    }

    return false;
  }
*/

 public:
  TSegmU Align(TAlignment a, VAL vSize) const
  { switch (a) {
      case aCenter: return MakeCS(C(), vSize);
      case aEnd:    return MakeSE(vSize, E);
                    return MakeBS(B, vSize); //case aBegin
    }
  }

 public:
  VAL PutIn(VAL v) const
   { if (v<B) v=B; if (E<v) v=E; return v; }

 public:
  bool Has(const TSegmU &sg) const { return !(sg.B<B) && !(E<sg.E); }
  bool Has(VAL v) const  { return Has(TSegmU(v, v)); }
  bool HasI(VAL v) const { return Has(TSegmU(v, v+1)); }

 public:
  TSegmU const& operator + () const { return *this; }
  TSegmU        operator - () const { return TSegmU(-B, -E); }

 public:
  TSegmU& operator += (const TSegmU &su)
    { B+=su.B; E+=su.E; return *this; }
  TSegmU& operator -= (const TSegmU &su)
    { B-=su.B; E-=su.E; return *this; }

  TSegmU& operator += (VAL v)
    { B+=v; E+=v; return *this; }
  TSegmU& operator -= (VAL v)
    { B-=v; E-=v; return *this; }

 public:
  template<typename NUM> TSegmU& operator *= (NUM n)
    { B*=n; E*=n; return *this; }
  template<typename NUM> TSegmU& operator /= (NUM n)
    { B/=n; E/=n; return *this; }
};


///////////////////////////////////////////////////////////////////////////////
// Operations on segments
template<typename VAL>
bool operator == (const TSegmU<VAL> &su0, const TSegmU<VAL> &su1)
  { return (su0.B==su1.B) && (su0.E==su1.E); }

template<typename VAL>
bool operator != (const TSegmU<VAL> &su0, const TSegmU<VAL> &su1)
  { return !(su0==su1); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmU<VAL> operator + (TSegmU<VAL> su0, const TSegmU<VAL> &su1)
  { return su0+=su1; }

template<typename VAL>
TSegmU<VAL> operator - (TSegmU<VAL> su0, const TSegmU<VAL> &su1)
  { return su0-=su1; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmU<VAL> operator + (TSegmU<VAL> su, VAL v)
  { return su+=v; }

template<typename VAL>
TSegmU<VAL> operator - (TSegmU<VAL> su, VAL v)
  { return su-=v; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmU<VAL> operator + (VAL v, TSegmU<VAL> su)
  { return su+=v; }

template<typename VAL>
TSegmU<VAL> operator - (VAL v, TSegmU<VAL> su)
  { return su-=v; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL, typename NUM>
TSegmU<VAL> operator * (TSegmU<VAL> su, NUM n)
{ return su*=n; }

template<typename VAL, typename NUM>
TSegmU<VAL> operator * (NUM n, TSegmU<VAL> su)
{ return su*=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL, typename NUM>
TSegmU<VAL> operator / (TSegmU<VAL> su, NUM n)
{ return su/=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmU<VAL> Intersect(const TSegmU<VAL> &su0, const TSegmU<VAL> &su1)
  { return TSegmU<VAL>(MaxRef(su0.B, su1.B), MinRef(su0.E, su1.E)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmU<VAL> Hull(const TSegmU<VAL> &su, const VAL &v)
  { return TSegmU<VAL>(MinRef(su.B, v), MaxRef(su.E, v)); }

template<typename VAL>
TSegmU<VAL> Hull(const TSegmU<VAL> &su0, const TSegmU<VAL> &su1)
  {  return TSegmU<VAL>(MinRef(su0.B, su1.B), MaxRef(su0.E, su1.E)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
VAL BCenter(const TSegmU<VAL> &su, VAL Size) {  return su.C()-Size/2; }

template<typename VAL>
VAL ECenter(const TSegmU<VAL> &su, VAL Size) {  return su.C()+Size/2; }

template<typename VAL>
TSegmU<VAL> Center(const TSegmU<VAL> &su, VAL Size)
  {  const VAL vB=BCenter(su, Size); return TSegmU<VAL>(vB, vB+Size); }

///////////////////////////////////////////////////////////////////////////////

// Point-span - difference between two points
template<typename VAL>
struct TPointB { // prefix 'ps'
 public:
  VAL X;
  VAL Y;

 public:
  TPointB()
   : X(VAL()), Y(VAL()) {}
  TPointB(VAL aX, VAL aY)
   : X(aX), Y(aY) {}

 public:
  template<typename V>
  TPointB<V> LF(TPointB<V> pb) const { return TPointB<V>(pb.X*X, pb.Y*Y); }

 public:
  TPointB<VAL> YX() const { return TPointB(Y, X); }

 public:
  TPointB<VAL> Abs() const { return TPointB<VAL>(hftl::Abs(X), hftl::Abs(Y)); }
  double SqMod() const { return X*X+Y*Y; }

 public:
  TPointB const& operator + () const { return *this; }
  TPointB        operator - () const { return TPointB(-X, -Y); }

  TPointB& operator += (const TPointB &ps)
    { X+=ps.X; Y+=ps.Y; return *this; }
  TPointB& operator -= (const TPointB &ps)
    { X-=ps.X; Y-=ps.Y; return *this; }

  template<typename NUM> TPointB& operator *= (NUM n)
    { X*=n; Y*=n; return *this; }
  template<typename NUM> TPointB& operator /= (NUM n)
    { X/=n; Y/=n; return *this; }
};

///////////////////////////////////////////////////////////////////////////////
// Comparation
template<typename VAL>
bool operator == (const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
{ return (pb0.X==pb1.X) && (pb0.Y==pb1.Y); }

template<typename VAL>
bool operator != (const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
{ return !(pb0==pb1); }

///////////////////////////////////////////////////////////////////////////////
// Addition/Subtraction
template<typename VAL>
TPointB<VAL> operator + (TPointB<VAL> pb0, const TPointB<VAL> &pb1)
  { return pb0+=pb1; }

template<typename VAL>
TPointB<VAL> operator - (TPointB<VAL> pb0, const TPointB<VAL> &pb1)
  { return pb0-=pb1; }

///////////////////////////////////////////////////////////////////////////////
// Product/Division
template<typename VAL, typename NUM>
TPointB<VAL> operator * (TPointB<VAL> pb, NUM n)
{ return pb*=n; }

template<typename VAL, typename NUM>
TPointB<VAL> operator * (NUM n, TPointB<VAL> pb)
{ return pb*=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL, typename NUM>
TPointB<VAL> operator / (TPointB<VAL> pb, NUM n)
{ return pb/=n; }

///////////////////////////////////////////////////////////////////////////////
// Scalar product
///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
VAL ScalarProd(const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
  { return pb0.X*pb1.X + pb0.Y*pb1.Y; }

template<typename VAL>
VAL operator * (const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
  { return ScalarProd(pb0, pb1); }

///////////////////////////////////////////////////////////////////////////////
// Vector product
///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
VAL VectorProd(const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
  { return pb0.X*pb1.Y - pb0.Y*pb1.X; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TPointB<VAL> MaxSize(const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
 {  return TPointB<VAL>(Max(pb0.X, pb1.X), Max(pb0.Y, pb1.Y)); }

template<typename VAL>
TPointB<VAL> MinSize(const TPointB<VAL> &pb0, const TPointB<VAL> &pb1)
 {  return TPointB<VAL>(Min(pb0.X, pb1.X), Min(pb0.Y, pb1.Y)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
struct TSegmB { // prefix 'rs'
 public:
  TSegmU<VAL> X;
  TSegmU<VAL> Y;

 public:
  TSegmB()
    {}
  TSegmB(VAL aXB, VAL aYB, VAL aXE, VAL aYE)
    : X(aXB, aXE), Y(aYB, aYE) {}
  TSegmB(const TSegmU<VAL> &assX, const TSegmU<VAL> &assY)
    : X(assX), Y(assY) {}
  TSegmB(const TPointB<VAL> &apsB, const TPointB<VAL> &apsE)
    : X(apsB.X, apsE.X), Y(apsB.Y, apsE.Y) {}

 public:
  TSegmB(VAL v, const TPointB<VAL> &apbSize)
    : X(v, apbSize.X), Y(v, apbSize.Y) {}

 public:
  static TSegmB MakeBS(TPointB<VAL> pbB, TPointB<VAL> pbS)
    { return TSegmB(pbB, pbB+pbS); }

  static TSegmB MakeSE(TPointB<VAL> pbS, TPointB<VAL> pbE)
    { return TSegmB(pbE-pbS, pbE); }

  static TSegmB MakeI(TPointB<VAL> pbB)
    { return TSegmB(pbB.X, pbB.Y, pbB.X+1, pbB.Y+1); }

 public:
  TPointB<VAL> Size() const { return TPointB<VAL>(X.Size(), Y.Size()); }

 public:
  TPointB<VAL> PutIn(const TPointB<VAL> &pb) const
   { return TPointB<VAL>(X.PutIn(pb.X), Y.PutIn(pb.Y)); }

 public:
  TSegmB NormI() const { return TSegmB(X.NormI(), Y.NormI()); }

 public:
  TSegmB const& operator + () const { return *this; }
  TSegmB        operator - () const { return TSegmB<VAL>(-X, -Y); }

 public:
  template<typename NUM> TSegmB& operator *= (NUM n)
    { X*=n; Y*=n; return *this; }
  template<typename NUM> TSegmB& operator /= (NUM n)
    { X/=n; Y/=n; return *this; }

 public:
  TPointB<VAL> B() const { return TPointB<VAL>(X.B,   Y.B);   }
  TPointB<VAL> E() const { return TPointB<VAL>(X.E,   Y.E);   }
  TPointB<VAL> C() const { return TPointB<VAL>(X.C(), Y.C()); }

  TPointB<VAL> BC() const { return TPointB<VAL>(X.B,   Y.C()); }
  TPointB<VAL> BE() const { return TPointB<VAL>(X.B,   Y.E);   }
  TPointB<VAL> CB() const { return TPointB<VAL>(X.C(), Y.B);   }
  TPointB<VAL> CE() const { return TPointB<VAL>(X.C(), Y.E);   }
  TPointB<VAL> EB() const { return TPointB<VAL>(X.E,   Y.B);   }
  TPointB<VAL> EC() const { return TPointB<VAL>(X.E,   Y.C()); }

 public:
  bool Has(const TSegmB &arc)  const
    { return X.Has(arc.X) && Y.Has(arc.Y); }
  bool Has(const TPointB<VAL> &pb)  const
    { return X.Has(pb.X) && Y.Has(pb.Y); }
  bool HasI(const TPointB<VAL> &pb)  const
    { return Has(TSegmB(pb, pb+TPointB<VAL>(1,1))); }

 public:
  TSegmB& AtMost(const TPointB<VAL> &pt)
   { X.AtMost(pt.X); Y.AtMost(pt.Y); return *this; }
  TSegmB& AtLeast(const TPointB<VAL> &pt)
   { X.AtLeast(pt.X); Y.AtLeast(pt.Y); return *this; }

 public:
  TSegmB& NormB() { X.NormB(); Y.NormB(); return *this; }
  TSegmB& NormE() { X.NormE(); Y.NormE(); return *this; }

 public:
  TSegmB& operator +=(const TSegmB<VAL> &rs) 
    { X+=rs.X; Y+=rs.Y; return *this; }

  TSegmB& operator -=(const TSegmB<VAL> &rs) 
    { X-=rs.X; Y-=rs.Y; return *this; }

 public:
  TSegmB& operator +=(const TPointB<VAL> &pb) 
    { X+=pb.X; Y+=pb.Y; return *this; }

  TSegmB& operator -=(const TPointB<VAL> &pb) 
    { X-=pb.X; Y-=pb.Y; return *this; }
};

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
bool operator == (const TSegmB<VAL> &sb0, const TSegmB<VAL> &sb1)
  { return (sb0.X==sb1.X) && (sb0.X==sb1.X); }

template<typename VAL>
bool operator != (const TSegmB<VAL> &sb0, const TSegmB<VAL> &sb1)
  { return !(sb0==sb1); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmB<VAL> operator + (TSegmB<VAL> sb0, const TSegmB<VAL> &sb1)
  { return sb0+=sb1; }

template<typename VAL>
TSegmB<VAL> operator - (TSegmB<VAL> sb0, const TSegmB<VAL> &sb1)
  { return sb0-=sb1; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmB<VAL> operator + (TSegmB<VAL> sb, const TPointB<VAL> &pb)
  { return sb+=pb; }

template<typename VAL>
TSegmB<VAL> operator - (TSegmB<VAL> sb, const TPointB<VAL> &pb)
  { return sb-=pb; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmB<VAL> operator + (const TPointB<VAL> &pb, TSegmB<VAL> sb)
  { return sb+=pb; }

template<typename VAL>
TSegmB<VAL> operator - (const TPointB<VAL> &pb, TSegmB<VAL> sb)
  { return sb-=pb; }

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmB<VAL> Intersect(const TSegmB<VAL> &sb0, const TSegmB<VAL> &sb1)
  { return TSegmB<VAL>(Intersect(sb0.X, sb1.X),
                       Intersect(sb0.Y, sb1.Y)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmB<VAL> Hull(const TSegmB<VAL> &sb0, const TSegmB<VAL> &sb1)
  { return TSegmB<VAL>(Hull(sb0.X, sb1.X), Hull(sb0.Y, sb1.Y)); }

template<typename VAL>
TSegmB<VAL> Hull(const TSegmB<VAL> &sb, const TPointB<VAL> &pb)
  { return TSegmB<VAL>(Hull(sb.X, pb.X), Hull(sb.Y, pb.Y)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TPointB<VAL> BCenter(TSegmB<VAL> sb, TPointB<VAL> pbSize)
{
  return TPointB<VAL>(BCenter(sb.X, pbSize.X), BCenter(sb.Y, pbSize.Y));
}

template<typename VAL>
TPointB<VAL> ECenter(TSegmB<VAL> sb, TPointB<VAL> pbSize)
{
  return TPointB<VAL>(ECenter(sb.X, pbSize.X), ECenter(sb.Y, pbSize.Y));
}

template<typename VAL>
TSegmB<VAL> Center(TSegmB<VAL> sb, TPointB<VAL> pbSize)
{
  return TSegmB<VAL>(Center(sb.X, pbSize.X), Center(sb.Y, pbSize.Y));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template<typename VAL>
struct TPointT { // prefix 'pt'
 public:
  VAL X;
  VAL Y;
  VAL Z;

 public:
  TPointT()
   : X(VAL()), Y(VAL()), Z(VAL()) {}
  TPointT(VAL aX, VAL aY, VAL aZ)
   : X(aX), Y(aY), Z(aZ) {}

 public:
  static TPointT MakeX(VAL aX) { return TPointT(aX, 0,  0); }
  static TPointT MakeY(VAL aY) { return TPointT(0, aY,  0); }
  static TPointT MakeZ(VAL aZ) { return TPointT(0,  0, aZ); }

 public:
  template<typename V>
  TPointT<V> LF(TPointT<V> pb) const { return TPointT<V>(pb.X*X, pb.Y*Y, pb.Z*Z); }

 public:
  TPointT<VAL> GetPositive() const { return TPointT<VAL>(Abs(X), Abs(Y), Abs(Z));  } // !!!!! Need?
  double SqMod() const { return X*X+Y*Y+Z*Z; }

  TPointT<VAL> ShiftX(VAL aX) const { return TPointT<VAL>(X+aX, Y,    Z);    } 
  TPointT<VAL> ShiftY(VAL aY) const { return TPointT<VAL>(X,    Y+aY, Z);    } 
  TPointT<VAL> ShiftZ(VAL aZ) const { return TPointT<VAL>(X,    Y,    Z+aZ); } 

 public:
  TPointT const& operator + () const { return *this; }
  TPointT        operator - () const { return TPointT(-X, -Y, -Z); }

  TPointT& operator += (const TPointT &pt)
    { X+=pt.X; Y+=pt.Y; Z+=pt.Z; return *this; }
  TPointT& operator -= (const TPointT &pt)
    { X-=pt.X; Y-=pt.Y; Z-=pt.Z; return *this; }

  template<typename NUM> TPointT& operator *= (NUM n)
    { X*=n; Y*=n; Z*=n; return *this; }
  template<typename NUM> TPointT& operator /= (NUM n)
    { X/=n; Y/=n; Z/=n; return *this; }
};

///////////////////////////////////////////////////////////////////////////////
// Comparation
template<typename VAL>
bool operator == (const TPointT<VAL> &pt0, const TPointT<VAL> &pt1)
{ return (pt0.X==pt1.X) && (pt0.Y==pt1.Y) && (pt0.Z==pt1.Z); }

template<typename VAL>
bool operator != (const TPointT<VAL> &pt0, const TPointT<VAL> &pt1)
{ return !(pb0==pb1); }

///////////////////////////////////////////////////////////////////////////////
// Addition/Subtraction
template<typename VAL>
TPointT<VAL> operator + (TPointT<VAL> pt0, const TPointT<VAL> &pt1)
  { return pt0+=pt1; }

template<typename VAL>
TPointT<VAL> operator - (TPointT<VAL> pt0, const TPointT<VAL> &pt1)
  { return pt0-=pt1; }

///////////////////////////////////////////////////////////////////////////////
// Product/Division
template<typename VAL, typename NUM>
TPointT<VAL> operator * (TPointT<VAL> pt, NUM n)
{ return pt*=n; }

template<typename VAL, typename NUM>
TPointT<VAL> operator * (NUM n, TPointT<VAL> pt)
{ return pt*=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL, typename NUM>
TPointT<VAL> operator / (TPointT<VAL> pt, NUM n)
{ return pt/=n; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
VAL ScalarProd (const TPointT<VAL> &pt0, const TPointT<VAL> &pt1)
  { return pt0.X*pt1.X + pt0.Y*pt1.Y + pt0.Z*pt1.Z; }

template<typename VAL>
VAL operator * (const TPointT<VAL> &pt0, const TPointT<VAL> &pt1)
  { return ScalarProd(pt0, pt1); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TPointT<VAL> VectorProd(const TPointT<VAL> &pt0, const TPointT<VAL> &pt1)
  { return TPointT<VAL>(pt0.Y*pt1.Z - pt0.Z*pt1.Y,
                        pt0.Z*pt1.X - pt0.X*pt1.Z,
                        pt0.X*pt1.Y - pt0.Y*pt1.X); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
struct TSegmT { // prefix 'st'
 public:
  TSegmU<VAL> X;
  TSegmU<VAL> Y;
  TSegmU<VAL> Z;

 public:
  TSegmT()
    {}
  TSegmT(VAL aXB, VAL aYB, VAL aZB,
         VAL aXE, VAL aYE, VAL aZE)
    : X(aXB, aXE), Y(aYB, aYE), Z(aZB, aZE) {}

  TSegmT(const TSegmU<VAL> &asuX,
         const TSegmU<VAL> &asuY,
         const TSegmU<VAL> &asuZ)
    : X(asuX), Y(asuY), Z(asuZ) {}
  TSegmT(const TPointT<VAL> &aptB, const TPointT<VAL> &aptE)
    : X(aptB.X, aptE.X), Y(aptB.Y, aptE.Y), Z(aptB.Z, aptE.Z) {}

 public:
  TSegmT(VAL v, const TPointT<VAL> &apbSize)
    : X(v, apbSize.X), Y(v, apbSize.Y), Z(v, apbSize.Z) {}

 public:
  static TSegmT MakeBS(TPointT<VAL> pbB, TPointT<VAL> pbS)
    { return TSegmT(pbB, pbB+pbS); }

  static TSegmT MakeSE(TPointT<VAL> pbS, TPointT<VAL> pbE)
    { return TSegmT(pbE-pbS, pbE); }

  static TSegmT MakeCR(TPointT<VAL> pbC, VAL vRadius)
    { return TSegmT(pbC.X-vRadius, pbC.X+vRadius,
                    pbC.Y-vRadius, pbC.Y+vRadius,
                    pbC.Z-vRadius, pbC.Z+vRadius); }

  static TSegmT MakeI(TPointT<VAL> pbB)
    { return TSegmT(pbB.X, pbB.Y, pbB.Z, pbB.X+1, pbB.Y+1, pbB.Z+1); }

 public:
  TPointT<VAL> Size() const { return TPointT<VAL>(X.Size(), Y.Size(), Z.Size()); }

 public:
  TSegmT NormI() const { return TSegmT(X.NormI(), Y.NormI(), Z.NormI()); }

 public:
  TSegmB<VAL> XY() const { return TSegmB<VAL>(X, Y); }

 public:
  TSegmT const& operator + () const { return *this; }
  TSegmT        operator - () const { return TSegmT<VAL>(-X, -Y, -Z); }

 public:
  template<typename NUM> TSegmT& operator *= (NUM n)
    { X*=n; Y*=n; Z*=n; return *this; }
  template<typename NUM> TSegmT& operator /= (NUM n)
    { X/=n; Y/=n; Z/=n; return *this; }

 public:
  TPointT<VAL> B() const { return TPointT<VAL>(X.B,   Y.B,   Z.B);   }
  TPointT<VAL> E() const { return TPointT<VAL>(X.E,   Y.E,   Z.E);   }
  TPointT<VAL> C() const { return TPointT<VAL>(X.C(), Y.C(), ZC()); }

 public:
  bool Has(const TSegmT &arc)  const
    { return X.Has(arc.X) && Y.Has(arc.Y) && Z.Has(arc.Z); }
  bool Has(const TPointT<VAL> &pb)  const
    { return X.Has(pb.X) && Y.Has(pb.Y) && Z.Has(pb.Z); }
  bool HasI(const TPointT<VAL> &pb)  const
    { return Has(TSegmT(pb, pb+TPointT<VAL>(1,1,1))); }

 public:
  TSegmT& operator +=(const TSegmT<VAL> &rs) 
    { X+=rs.X; Y+=rs.Y; Z+=rs.Z; return *this; }

  TSegmT& operator -=(const TSegmT<VAL> &rs) 
    { X-=rs.X; Y-=rs.Y; Z-=rs.Z; return *this; }

 public:
  TSegmT& operator +=(const TPointT<VAL> &pb) 
    { X+=pb.X; Y+=pb.Y; Z+=pb.Z; return *this; }

  TSegmT& operator -=(const TPointT<VAL> &pb) 
    { X-=pb.X; Y-=pb.Y; Z-=pb.Z; return *this; }
};

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
bool operator == (const TSegmT<VAL> &sb0, const TSegmT<VAL> &sb1)
  { return (sb0.X==sb1.X) && (sb0.Y==sb1.Y) && (sb0.Z==sb1.Z); }

template<typename VAL>
bool operator != (const TSegmT<VAL> &sb0, const TSegmT<VAL> &sb1)
  { return !(sb0==sb1); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmT<VAL> operator + (TSegmT<VAL> sb0, const TSegmT<VAL> &sb1)
  { return sb0+=sb1; }

template<typename VAL>
TSegmT<VAL> operator - (TSegmT<VAL> sb0, const TSegmT<VAL> &sb1)
  { return sb0-=sb1; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmT<VAL> operator + (TSegmT<VAL> sb, const TPointT<VAL> &pb)
  { return sb+=pb; }

template<typename VAL>
TSegmT<VAL> operator - (TSegmT<VAL> sb, const TPointT<VAL> &pb)
  { return sb-=pb; }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmT<VAL> operator + (const TPointT<VAL> &pb, TSegmT<VAL> sb)
  { return sb+=pb; }

template<typename VAL>
TSegmT<VAL> operator - (const TPointT<VAL> &pb, TSegmT<VAL> sb)
  { return sb-=pb; }

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmT<VAL> Intersect(const TSegmT<VAL> &sb0, const TSegmT<VAL> &sb1)
  { return TSegmT<VAL>(Intersect(sb0.X, sb1.X),
                       Intersect(sb0.Y, sb1.Y),
                       Intersect(sb0.Z, sb1.Z)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TSegmT<VAL> Hull(const TSegmT<VAL> &sb0, const TSegmT<VAL> &sb1)
  { return TSegmT<VAL>(Hull(sb0.X, sb1.X),
                       Hull(sb0.Y, sb1.Y),
                       Hull(sb0.Z, sb1.Z)); }

template<typename VAL>
TSegmT<VAL> Hull(const TSegmT<VAL> &sb, const TPointT<VAL> &pb)
  { return TSegmT<VAL>(Hull(sb.X, pb.X),
                       Hull(sb.Y, pb.Y),
                       Hull(sb.Z, pb.Z)); }

///////////////////////////////////////////////////////////////////////////////
template<typename VAL>
TPointT<VAL> BCenter(TSegmT<VAL> sb, TPointT<VAL> pbSize)
{
  return TPointT<VAL>(BCenter(sb.X, pbSize.X),
                      BCenter(sb.Y, pbSize.Y),
                      BCenter(sb.Z, pbSize.Z));
}

template<typename VAL>
TPointT<VAL> ECenter(TSegmT<VAL> sb, TPointT<VAL> pbSize)
{
  return TPointT<VAL>(ECenter(sb.X, pbSize.X),
                      ECenter(sb.Y, pbSize.Y),
                      ECenter(sb.Z, pbSize.Z));
}

template<typename VAL>
TSegmT<VAL> Center(TSegmT<VAL> sb, TPointT<VAL> pbSize)
{
  return TSegmT<VAL>(Center(sb.X, pbSize.X),
                     Center(sb.Y, pbSize.Y),
                     Center(sb.Z, pbSize.Z));
}

} // namespace hftl

#endif
