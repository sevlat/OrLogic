#ifndef m_bbUtils_h_already_included__02_12_2012__20713BC0
#define m_bbUtils_h_already_included__02_12_2012__20713BC0
//
// SeVlaT, 02.12.2012
//

#include "m_bbTypes.h"

////////////////////////////////////////////////////////////////////////////////
// Make byte from digits 0x_Xh_Xl
#define HFTL_MakeByte(Xl, Xh)                                                \
    ((hftl::TByte)(((hftl::TByte)((((hftl::TByte)(Xl))&0x0Fu)<<0))        |  \
                   ((hftl::TByte)((((hftl::TByte)(Xh))&0x0Fu)<<4))))

////////////////////////////////////////////////////////////////////////////////
// Make 2-byte word 0x_XH_XL
#define HFTL_Make2Byte(XL, XH)                                               \
    ((hftl::TWord)(((hftl::TWord)((((hftl::TByte)(XL))&0xFFu)<<0))        |  \
                   ((hftl::TWord)((((hftl::TByte)(XH))&0xFFu)<<8))))

// Make 3-byte double word 0x_XHL_XLH_XLL
#define HFTL_Make3Byte(XLL, XLH, XHL)                                        \
    ((hftl::TDWord)(((hftl::TDWord)((((hftl::TByte)(XLL))&0xFFu)<<0))     |  \
                    ((hftl::TDWord)((((hftl::TByte)(XLH))&0xFFu)<<8))     |  \
                    ((hftl::TDWord)((((hftl::TByte)(XHL))&0xFFu)<<16))))

// Make 4-byte double word 0x_XHH_XHL_XLH_XLL
#define HFTL_Make4Byte(XLL, XLH, XHL, XHH)                                   \
    ((hftl::TDWord)(((hftl::TDWord)((((hftl::TByte)(XLL))&0xFFu)<<0))     |  \
                    ((hftl::TDWord)((((hftl::TByte)(XLH))&0xFFu)<<8))     |  \
                    ((hftl::TDWord)((((hftl::TByte)(XHL))&0xFFu)<<16))    |  \
                    ((hftl::TDWord)((((hftl::TByte)(XHH))&0xFFu)<<24))))


// Make 4-byte double word 0x_XH_XL
#define HFTL_Make2Word(XL, XH)                                               \
    ((hftl::TDWord)(((hftl::TDWord)((((hftl::TWord)(XL))&0xFFFFu)<<0))    |  \
                    ((hftl::TDWord)((((hftl::TWord)(XH))&0xFFFFu)<<16))))

////////////////////////////////////////////////////////////////////////////////
#define HFTL_Get2ByteL(W)   ((hftl::TByte)((((hftl::TWord)(W))>>0) &0xFFu))
#define HFTL_Get2ByteH(W)   ((hftl::TByte)((((hftl::TWord)(W))>>8) &0xFFu))

#define HFTL_Get3ByteLL(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>0) &0xFFu))
#define HFTL_Get3ByteLH(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>8) &0xFFu))
#define HFTL_Get3ByteHL(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>16)&0xFFu))

#define HFTL_Get4ByteLL(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>0) &0xFFu))
#define HFTL_Get4ByteLH(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>8) &0xFFu))
#define HFTL_Get4ByteHL(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>16)&0xFFu))
#define HFTL_Get4ByteHH(DW) ((hftl::TByte)((((hftl::TDWord)(DW))>>24)&0xFFu))

                  
#define HFTL_Get2WordL(DW)  ((hftl::TWord)((((hftl::TDWord)(DW))>>0) &0xFFFFu))
#define HFTL_Get2WordM(DW)  ((hftl::TWord)((((hftl::TDWord)(DW))>>8) &0xFFFFu))
#define HFTL_Get2WordH(DW)  ((hftl::TWord)((((hftl::TDWord)(DW))>>16)&0xFFFFu))

////////////////////////////////////////////////////////////////////////////////
#define HFTL_Is1Byte(X)   ((((hftl::TWord)(X)) && 0xFF)      ==((hftl::TWord)(X)))
#define HFTL_Is2Byte(X)   ((((hftl::TWord)(X)) && 0xFFFF)    ==((hftl::TWord)(X)))
#define HFTL_Is3Byte(X)   ((((hftl::TWord)(X)) && 0xFFFFFF)  ==((hftl::TWord)(X)))
#define HFTL_Is4Byte(X)   ((((hftl::TWord)(X)) && 0xFFFFFFFF)==((hftl::TWord)(X)))

////////////////////////////////////////////////////////////////////////////////
// Little endian macros
//
// Make 2-byte word 0x_X1_X0
#define HFTL_Make2ByteLe(X0, X1)            HFTL_Make2Byte(X0, X1)

// Make 3-byte double word 0x_X2_X1_X0
#define HFTL_Make3ByteLe(X0, X1, X2)        HFTL_Make3Byte(X0, X1, X2)

// Make 4-byte double word 0x_X3_X2_X1_X0
#define HFTL_Make4ByteLe(X0, X1, X2, X3)    HFTL_Make4Byte(X0, X1, X2, X3)


// Make 4-byte double word 0x_X1_X0
#define HFTL_Make2WordLe(X0, X1)            HFTL_Make2Word(X0, X1) 


////////////////////////////////////////
#define HFTL_Get2ByteLe0(W)                 HFTL_Get2ByteL(W)
#define HFTL_Get2ByteLe1(W)                 HFTL_Get2ByteH(W)

#define HFTL_Get3ByteLe0(DW)                HFTL_Get3ByteLL(DW)
#define HFTL_Get3ByteLe1(DW)                HFTL_Get3ByteLH(DW)
#define HFTL_Get3ByteLe2(DW)                HFTL_Get3ByteHL(DW)
                               
#define HFTL_Get4ByteLe0(DW)                HFTL_Get4ByteLL(DW)
#define HFTL_Get4ByteLe1(DW)                HFTL_Get4ByteLH(DW)
#define HFTL_Get4ByteLe2(DW)                HFTL_Get4ByteHL(DW)
#define HFTL_Get4ByteLe3(DW)                HFTL_Get4ByteHH(DW)

                                                     
#define HFTL_Get2WordLe0(DW)                HFTL_Get2WordL(DW)
#define HFTL_Get2WordLe1(DW)                HFTL_Get2WordH(DW)

////////////////////////////////////////////////////////////////////////////////
// Big endian macros
//
// Make 2-byte word 0x_X0_X1
#define HFTL_Make2ByteBe(X0, X1)            HFTL_Make2Byte(X1, X0)

// Make 3-byte double word 0x_X0_X1_X2
#define HFTL_Make3ByteBe(X0, X1, X2)        HFTL_Make3Byte(X2, X1, X0)

// Make 4-byte double word 0x_X0_X1_X2_X3
#define HFTL_Make4ByteBe(X0, X1, X2, X3)    HFTL_Make4Byte(X3, X2, X1, X0)


// Make 4-byte double word 0x_X0_X1
#define HFTL_Make2WordBe(X0, X1)            HFTL_Make2Word(X1, X0) 


////////////////////////////////////////
#define HFTL_Get2ByteBe0(W)                 HFTL_Get2ByteH(W)
#define HFTL_Get2ByteBe1(W)                 HFTL_Get2ByteL(W)

#define HFTL_Get3ByteBe0(DW)                HFTL_Get3ByteHL(DW)
#define HFTL_Get3ByteBe1(DW)                HFTL_Get3ByteLH(DW)
#define HFTL_Get3ByteBe2(DW)                HFTL_Get3ByteLL(DW)
                                
#define HFTL_Get4ByteBe0(DW)                HFTL_Get4ByteHH(DW)
#define HFTL_Get4ByteBe1(DW)                HFTL_Get4ByteHL(DW)
#define HFTL_Get4ByteBe2(DW)                HFTL_Get4ByteLH(DW)
#define HFTL_Get4ByteBe3(DW)                HFTL_Get4ByteLL(DW)

                                                     
#define HFTL_Get2WordBe0(DW)                HFTL_Get2WordH(DW)
#define HFTL_Get2WordBe1(DW)                HFTL_Get2WordL(DW)

////////////////////////////////////////////////////////////////////////////////
namespace hftl {

inline TWord  Make2Byte(TByte bl, TByte bh)
  { return HFTL_Make2Byte(bl, bh); }
  
inline TDWord Make3Byte(TByte bll, TByte blh, TByte bhl)
  { return HFTL_Make3Byte(bll, blh, bhl); }
  
inline TDWord Make4Byte(TByte bll, TByte blh, TByte bhl, TByte bhh)
  { return HFTL_Make4Byte(bll, blh, bhl, bhh); }


inline TDWord Make2Word(TWord wl, TWord wh)
  { return HFTL_Make2Word(wl, wh); }
  

inline TByte Get2ByteL(TWord w)    { return HFTL_Get2ByteL(w); }
inline TByte Get2ByteH(TWord w)    { return HFTL_Get2ByteH(w); }

inline TByte Get3ByteLL(TDWord dw) { return HFTL_Get3ByteLL(dw); }
inline TByte Get3ByteLH(TDWord dw) { return HFTL_Get3ByteLH(dw); }
inline TByte Get3ByteHL(TDWord dw) { return HFTL_Get3ByteHL(dw); }

inline TByte Get4ByteLL(TDWord dw) { return HFTL_Get4ByteLL(dw); }
inline TByte Get4ByteLH(TDWord dw) { return HFTL_Get4ByteLH(dw); }
inline TByte Get4ByteHL(TDWord dw) { return HFTL_Get4ByteHL(dw); }
inline TByte Get4ByteHH(TDWord dw) { return HFTL_Get4ByteHH(dw); }

                                                    
inline TWord Get2WordL(TDWord dw)  { return HFTL_Get2WordL(dw); }
inline TWord Get2WordH(TDWord dw)  { return HFTL_Get2WordH(dw); }
inline TWord Get2WordM(TDWord dw)  { return HFTL_Get2WordM(dw); }


////////////////////////////////////////////////////////////////////////////////
template <typename BO> TWord  Make2Byte(TByte b0, TByte b1);
template <typename BO> TDWord Make3Byte(TByte b0, TByte b1, TByte b2);
template <typename BO> TDWord Make4Byte(TByte b0, TByte b1, TByte b2, TByte b3);

template <typename BO> TDWord Make2Word(TWord w0, TWord w1);


template <typename BO> TByte Get2Byte0(TWord w);
template <typename BO> TByte Get2Byte1(TWord w);
                                    
template <typename BO> TByte Get3Byte0(TDWord dw);
template <typename BO> TByte Get3Byte1(TDWord dw);
template <typename BO> TByte Get3Byte2(TDWord dw);
                                    
template <typename BO> TByte Get4Byte0(TDWord dw);
template <typename BO> TByte Get4Byte1(TDWord dw);
template <typename BO> TByte Get4Byte2(TDWord dw);
template <typename BO> TByte Get4Byte3(TDWord dw);

                                          
template <typename BO> TWord Get2Word0(TDWord dw);
template <typename BO> TWord Get2Word1(TDWord dw);

////////////////////////////////////////////////////////////////////////////////
template<> inline TWord  Make2Byte<BoLe>(TByte b0,  TByte b1)
  { return HFTL_Make2ByteLe(b0, b1); }
  
template<> inline TDWord Make3Byte<BoLe>(TByte b0, TByte b1, TByte b2)
  { return HFTL_Make3ByteLe(b0, b1, b2); }
  
template<> inline TDWord Make4Byte<BoLe>(TByte b0, TByte b1, TByte b2, TByte b3)
  { return HFTL_Make4ByteLe(b0, b1, b2, b3); }


template<> inline TDWord Make2Word<BoLe>(TWord w0, TWord w1)
  { return HFTL_Make2WordLe(w0, w1); }
  

template<> inline TByte Get2Byte0<BoLe>(TWord w)   { return HFTL_Get2ByteLe0(w); }
template<> inline TByte Get2Byte1<BoLe>(TWord w)   { return HFTL_Get2ByteLe1(w); }
                     
template<> inline TByte Get3Byte0<BoLe>(TDWord dw) { return HFTL_Get3ByteLe0(dw); }
template<> inline TByte Get3Byte1<BoLe>(TDWord dw) { return HFTL_Get3ByteLe1(dw); }
template<> inline TByte Get3Byte2<BoLe>(TDWord dw) { return HFTL_Get3ByteLe2(dw); }
                     
template<> inline TByte Get4Byte0<BoLe>(TDWord dw) { return HFTL_Get4ByteLe0(dw); }
template<> inline TByte Get4Byte1<BoLe>(TDWord dw) { return HFTL_Get4ByteLe1(dw); }
template<> inline TByte Get4Byte2<BoLe>(TDWord dw) { return HFTL_Get4ByteLe2(dw); }
template<> inline TByte Get4Byte3<BoLe>(TDWord dw) { return HFTL_Get4ByteLe3(dw); }

                                            
template<> inline TWord Get2Word0<BoLe>(TDWord dw) { return HFTL_Get2WordLe0(dw); }
template<> inline TWord Get2Word1<BoLe>(TDWord dw) { return HFTL_Get2WordLe1(dw); }

////////////////////////////////////////////////////////////////////////////////
template<> inline TWord  Make2Byte<BoBe>(TByte b0, TByte b1)
  { return HFTL_Make2ByteBe(b0, b1); }
  
template<> inline TDWord Make3Byte<BoBe>(TByte b0, TByte b1, TByte b2)
  { return HFTL_Make3ByteBe(b0, b1, b2); }
  
template<> inline TDWord Make4Byte<BoBe>(TByte b0, TByte b1, TByte b2, TByte b3)
  { return HFTL_Make4ByteBe(b0, b1, b2, b3); }

template<> inline TDWord Make2Word<BoBe>(TWord w0, TWord w1)
  { return HFTL_Make2WordBe(w0, w1); }


template<> inline TByte Get2Byte0<BoBe>(TWord w)   { return HFTL_Get2ByteBe0(w); }
template<> inline TByte Get2Byte1<BoBe>(TWord w)   { return HFTL_Get2ByteBe1(w); }
                                                             
template<> inline TByte Get3Byte0<BoBe>(TDWord dw) { return HFTL_Get3ByteBe0(dw); }
template<> inline TByte Get3Byte1<BoBe>(TDWord dw) { return HFTL_Get3ByteBe1(dw); }
template<> inline TByte Get3Byte2<BoBe>(TDWord dw) { return HFTL_Get3ByteBe2(dw); }
                                                             
template<> inline TByte Get4Byte0<BoBe>(TDWord dw) { return HFTL_Get4ByteBe0(dw); }
template<> inline TByte Get4Byte1<BoBe>(TDWord dw) { return HFTL_Get4ByteBe1(dw); }
template<> inline TByte Get4Byte2<BoBe>(TDWord dw) { return HFTL_Get4ByteBe2(dw); }
template<> inline TByte Get4Byte3<BoBe>(TDWord dw) { return HFTL_Get4ByteBe3(dw); }

                                                              
template<> inline TWord Get2Word0<BoBe>(TDWord dw) { return HFTL_Get2WordBe0(dw); }
template<> inline TWord Get2Word1<BoBe>(TDWord dw) { return HFTL_Get2WordBe1(dw); }


////////////////////////////////////////////////////////////////////////////////
inline bool Is1Byte(TDWord dw) { return HFTL_Is1Byte(dw); }
inline bool Is2Byte(TDWord dw) { return HFTL_Is2Byte(dw); }
inline bool Is3Byte(TDWord dw) { return HFTL_Is3Byte(dw); }
inline bool Is4Byte(TDWord dw) { return HFTL_Is4Byte(dw); }

////////////////////////////////////////////////////////////////////////////////
template <typename BO> 
TWord  MakeNByte(const TByte (&b)[2])
  { return Make2Byte<BO>(b[0], b[1]); }

template <typename BO> 
TDWord MakeNByte(const TByte (&b)[3])
  { return Make3Byte<BO>(b[0], b[1], b[2]); }

template <typename BO> 
TDWord MakeNByte(const TByte (&b)[4])
  { return Make4Byte<BO>(b[0], b[1], b[2], b[3]); }


////////////////////////////////////////////////////////////////////////////////
template <typename BO> 
void SplitNByte(TWord w, TByte &b0, TByte &b1)
  { b0=Get2Byte0<BO>(w);
    b1=Get2Byte1<BO>(w); }

template <typename BO> 
void SplitNByte(TDWord dw, TByte &b0, TByte &b1, TByte &b2)
  { b0=Get3Byte0<BO>(dw);
    b1=Get3Byte1<BO>(dw);
    b2=Get3Byte2<BO>(dw); }

template <typename BO> 
void SplitNByte(TDWord dw, TByte &b0, TByte &b1, TByte &b2, TByte &b3)
  { b0=Get4Byte0<BO>(dw);
    b1=Get4Byte1<BO>(dw);
    b2=Get4Byte2<BO>(dw);
    b3=Get4Byte3<BO>(dw); }

////////////////////////////////////////////////////////////////////////////////
template <typename BO> 
void SplitNByte(TWord w, TByte (&b)[2])
  { SplitNByte<BO>(w, b[0], b[1]); }

template <typename BO> 
void SplitNByte(TDWord dw, TByte (&b)[3])
  { SplitNByte<BO>(dw, b[0], b[1], b[2]); }

template <typename BO> 
void SplitNByte(TDWord dw, TByte (&b)[4])
  { SplitNByte<BO>(dw, b[0], b[1], b[2], b[3]); }
  
////////////////////////////////////////////////////////////////////////////////
inline void SplitNByte(TWord w, TByte &bl, TByte &bh)
  { bl=Get2ByteH(w);
    bh=Get2ByteL(w); }

inline void SplitNByte(TDWord dw, TByte &bll, TByte &blh, TByte &bhl)
  { bll=Get3ByteLL(dw);
    blh=Get3ByteLH(dw);
    bhl=Get3ByteHL(dw); }

inline void SplitNByte(TDWord dw, TByte &bll, TByte &blh, TByte &bhl, TByte &bhh)
  { bll=Get4ByteLL(dw);
    blh=Get4ByteLH(dw);
    bhl=Get4ByteHL(dw);
    bhh=Get4ByteHH(dw); }


////////////////////////////////////////////////////////////////////////////////
#define HFTL_Bit1(X, N) ((((TDWord)(X))>>(N))&0x1u)
#define HFTL_Bit2(X, N) ((((TDWord)(X))>>(N))&0x3u)
#define HFTL_Bit3(X, N) ((((TDWord)(X))>>(N))&0x7u)


} // namespace hftl

#endif
