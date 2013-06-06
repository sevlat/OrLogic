#ifndef CmdDataSerialize_h_already_included__18_10_2012__1FE39EE0
#define CmdDataSerialize_h_already_included__18_10_2012__1FE39EE0
//
// SeVlaT, 18.10.2012
//

#include "CmdItemSerialize.h"

template <typename SER, typename CMDD>
struct TSerBase  {
  typedef CMDD TCmdD;

  bool Get(IIStream &is, TCmdD &cmdD, TErrList *pErr) const;
  bool Put(IOStream &os, const TCmdD &cmdD, TErrList *pErr) const;
  bool Count(int &nSize) const;
};

template <typename CMDD>
struct TSer;

////////////////////////////////////////////////////////////////////////////////
template <typename CMDD>
struct TCmdDataSerializer {
  static bool Get(IIStream &is, CMDD &cmdD, TErrList *pErr);
  static bool Put(IOStream &os, const CMDD &cmdD, TErrList *pErr);
  static bool Count(int &nSize);
};

////////////////////////////////////////////////////////////////////////////////
template <typename CMDD>
bool CmdGet(IIStream &is, CMDD &cmdD, TErrList *pErr);

template <typename CMDD>
bool CmdPut(IOStream &os, const CMDD &cmdD, TErrList *pErr);

#endif
