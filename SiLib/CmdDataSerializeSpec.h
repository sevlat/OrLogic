#ifndef CmdDataSerializeSpec_h_already_included__18_10_2012__34D414C0
#define CmdDataSerializeSpec_h_already_included__18_10_2012__34D414C0
//
// SeVlaT, 18.10.2012
//

#include "CmdData.h"

#include "CmdDataSerialize.h"

////////////////////////////////////////////////////////////////////////////////

struct TSerVoid {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return true;
  };
};

template <>
struct TSer<CmddVoid>: TSerBase<TSerVoid, CmddVoid> {};

////////////////////////////////////////////////////////////////////////////////
// Setting master/slave
////////////////////////////////////////////////////////////////////////////////
struct TSerFSetMaSlave {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.MaSlave<&CmddFSetMaSlave::bMaster>();
  };
};

template <>
struct TSer<CmddFSetMaSlave>: TSerBase<TSerFSetMaSlave, CmddFSetMaSlave> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBSetMaSlaveB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte <&CmddBMaSlaveB::bCN>() &&
           Ser.MaSlave<&CmddBMaSlaveB::bMaster>();
  };
};

template <>
struct TSer<CmddBMaSlaveB>: TSerBase<TSerBSetMaSlaveB, CmddBMaSlaveB> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBSetMaSlaveE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBMaSlaveE::wCN>() &&
           Ser.MaSlave <&CmddBMaSlaveE::bMaster>();
  };
};

template <>
struct TSer<CmddBMaSlaveE>: TSerBase<TSerBSetMaSlaveE, CmddBMaSlaveE> {};

////////////////////////////////////////////////////////////////////////////////
// Setting baud rate
////////////////////////////////////////////////////////////////////////////////
struct TSerFSetBaudRate {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.BaudRate<&CmddFSetBaudRate::bHigh>();
  };
};

template <>
struct TSer<CmddFSetBaudRate>: TSerBase<TSerFSetBaudRate, CmddFSetBaudRate> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBSetBaudRateB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte  <&CmddBSetBaudRateB::bCN>() &&
           Ser.BaudRate<&CmddBSetBaudRateB::bHigh>();
  };
};

template <>
struct TSer<CmddBSetBaudRateB>: TSerBase<TSerBSetBaudRateB, CmddBSetBaudRateB> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBSetBaudRateE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBSetBaudRateE::wCN>() &&
           Ser.BaudRate<&CmddBSetBaudRateE::bHigh>();
  };
};

template <>
struct TSer<CmddBSetBaudRateE>: TSerBase<TSerBSetBaudRateE, CmddBSetBaudRateE> {};


////////////////////////////////////////////////////////////////////////////////
// Getting/Setting station time
////////////////////////////////////////////////////////////////////////////////
struct TSerFSetTimeB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.Time<&CmddFSetTimeB::t>();
  };
};

template <>
struct TSer<CmddFSetTimeB>: TSerBase<TSerFSetTimeB, CmddFSetTimeB> {};

////////////////////////////////////////////////////////////////////////////////

struct TSerFSetTimeE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.TimeSS<&CmddFSetTimeE::t>();
  };
};

template <>
struct TSer<CmddFSetTimeE>: TSerBase<TSerFSetTimeE, CmddFSetTimeE> {};

////////////////////////////////////////////////////////////////////////////////


template <typename TAG>
struct TSerBTime {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    typedef CBTimeB<TAG> CmddTime;
    
    return Ser.B1Byte<&CmddTime::bCN>() &&
           Ser.Time  <&CmddTime::t>();
  };
};

template <>
struct TSer<CmddBGetTimeB>: TSerBase<TSerBTime<TagGet>, CmddBGetTimeB> {};
template <>
struct TSer<CmddBSetTimeB>: TSerBase<TSerBTime<TagSet>, CmddBSetTimeB> {};

////////////////////////////////////////////////////////////////////////////////
template <typename TAG>
struct TSerBTimeE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    typedef CBTimeE<TAG> CmddTime;

    return Ser.B2ByteBE<&CmddTime::wCN>() &&
           Ser.TimeSS  <&CmddTime::t>();
  };
};

template <>
struct TSer<CmddBGetTimeE>: TSerBase<TSerBTimeE<TagGet>, CmddBGetTimeE> {};
template <>                                     
struct TSer<CmddBSetTimeE>: TSerBase<TSerBTimeE<TagSet>, CmddBSetTimeE> {};

////////////////////////////////////////////////////////////////////////////////
// Getting system value
////////////////////////////////////////////////////////////////////////////////
struct TSerFGetSysValueE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte<&CmddFGetSysValueE::bAddr>() &&
           Ser.B1Byte<&CmddFGetSysValueE::bLen>();
  };
};

template <>
struct TSer<CmddFGetSysValueE>: TSerBase<TSerFGetSysValueE, CmddFGetSysValueE> {};


////////////////////////////////////////////////////////////////////////////////
struct TSerBGetSysValueE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBGetSysValueE::wCN>() &&
           Ser.B1Byte  <&CmddBGetSysValueE::bAddr>() &&
           Ser.Buffer  <&CmddBGetSysValueE::data>();
  };
};

template <>
struct TSer<CmddBGetSysValueE>: TSerBase<TSerBGetSysValueE, CmddBGetSysValueE> {};

////////////////////////////////////////////////////////////////////////////////
// Getting backup data
////////////////////////////////////////////////////////////////////////////////
struct TSerFGetBckDataE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B3ByteBE<&CmddFGetBckDataE::dwAddr>() &&
           Ser.B1Byte  <&CmddFGetBckDataE::bLen>();
  };
};

template <>
struct TSer<CmddFGetBckDataE>: TSerBase<TSerFGetBckDataE, CmddFGetBckDataE> {};


////////////////////////////////////////////////////////////////////////////////
struct TSerBGetBckDataE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBGetBckDataE::wCN>() &&
           Ser.B3ByteBE<&CmddBGetBckDataE::dwAddr>() &&
           Ser.Buffer  <&CmddBGetBckDataE::data>();
  };
};

template <>
struct TSer<CmddBGetBckDataE>: TSerBase<TSerBGetBckDataE, CmddBGetBckDataE> {};


////////////////////////////////////////////////////////////////////////////////
struct TSerFBeepE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte<&CmddFBeepE::bBeeps>();
  };
};

template <>
struct TSer<CmddFBeepE>: TSerBase<TSerFBeepE, CmddFBeepE> {};


struct TSerBBeepE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBBeepE::wCN>() &&
           Ser.B1Byte  <&CmddBBeepE::bBeeps>();
  };
};

template <>
struct TSer<CmddBBeepE>: TSerBase<TSerBBeepE, CmddBBeepE> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerFTurnOffB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte<&CmddFTurnOffB::bUnknown>();
  };
};

template <>
struct TSer<CmddFTurnOffB>: TSerBase<TSerFTurnOffB, CmddFTurnOffB> {};


struct TSerBTurnOffB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte<&CmddBTurnOffB::bCN>() &&
           Ser.B1Byte<&CmddBTurnOffB::bUnknown>();
  };
};

template <>
struct TSer<CmddBTurnOffB>: TSerBase<TSerBTurnOffB, CmddBTurnOffB> {};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct TSerBCardIns5RemB {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.InOut<&CmddBCardIns5RemB::bInsert>();
  };
};

template <>
struct TSer<CmddBCardIns5RemB>: TSerBase<TSerBCardIns5RemB, CmddBCardIns5RemB> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBCardIns6B {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B1Byte  <&CmddBCardIns6B::bCN>() &&
           Ser.B1Byte  <&CmddBCardIns6B::bTI>() &&
           Ser.B1Byte  <&CmddBCardIns6B::bTP>() &&
           Ser.B4ByteBE<&CmddBCardIns6B::dwCardN>();
  };
};

template <>
struct TSer<CmddBCardIns6B>: TSerBase<TSerBCardIns6B, CmddBCardIns6B> {};

////////////////////////////////////////////////////////////////////////////////
struct TSerBCardInsRemE {
  template <typename SERIALIZER>
  bool DoSerialize(const SERIALIZER &Ser) const
  {
    return Ser.B2ByteBE<&CmddBCardInsRemE::wCN>() &&
           Ser.B1Byte  <&CmddBCardInsRemE::bCardType>() &&
           Ser.B3ByteBE<&CmddBCardInsRemE::dwCardN>();
  };
};

template <>
struct TSer<CmddBCardInsRemE>: TSerBase<TSerBCardInsRemE, CmddBCardInsRemE> {};


#endif
