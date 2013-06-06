#ifndef CmdDataSerializeImpl_h_already_included__18_10_2012__121EC4C0
#define CmdDataSerializeImpl_h_already_included__18_10_2012__121EC4C0
//
// SeVlaT, 18.10.2012
//

#include "CmdDataSerializeSpec.h"

////////////////////////////////////////////////////////////////////////////////
template <typename CMDD>
bool TCmdDataSerializer<CMDD>::Get(IIStream &is, CMDD &cmdD, TErrList *pErr)
{
  TSer<CMDD> Ser;
  return Ser.Get(is, cmdD, pErr);
}

template <typename CMDD>
bool TCmdDataSerializer<CMDD>::Put(IOStream &os, const CMDD &cmdD, TErrList *pErr)
{
  TSer<CMDD> Ser;
  return Ser.Put(os, cmdD, pErr);
}

template <typename CMDD>
bool TCmdDataSerializer<CMDD>::Count(int &nSize)
{
  TSer<CMDD> Ser;
  return Ser.Count(nSize);
}

////////////////////////////////////////////////////////////////////////////////
template<typename SER, typename CMDD>
bool TSerBase<SER, CMDD>::Get(IIStream &is, TCmdD &cmdD, TErrList *pErr) const
{
  const TDISerializer<TCmdD> Ser(is, cmdD, pErr);
  return SER().DoSerialize(Ser);
}

template<typename SER, typename CMDD>
bool TSerBase<SER, CMDD>::Put(IOStream &os, const TCmdD &cmdD, TErrList *pErr) const
{
  const TDOSerializer<TCmdD> Ser(os, cmdD, pErr);
  return SER().DoSerialize(Ser);
}

template<typename SER, typename CMDD>
bool TSerBase<SER, CMDD>::Count(int &nSize) const
{
  nSize=0;
  const TDCountSerializer<TCmdD> Ser(nSize);
  return SER().DoSerialize(Ser);
}

////////////////////////////////////////////////////////////////////////////////
template <typename CMDD>
bool CmdGet(IIStream &is, CMDD &cmdD, TErrList *pErr)
{
  return TCmdDataSerializer<CMDD>::Get(is, cmdD, pErr);
}

template <typename CMDD>
bool CmdPut(IOStream &os, const CMDD &cmdD, TErrList *pErr)
{
  return TCmdDataSerializer<CMDD>::Put(os, cmdD, pErr);
}



#endif
