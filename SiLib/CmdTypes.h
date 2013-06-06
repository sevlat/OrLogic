#ifndef CmdTypes_h_already_included__07_02_2013__84236C0
#define CmdTypes_h_already_included__07_02_2013__84236C0
//
// SeVlaT, 07.02.2013
//

#include "CommandCode.h"

class CauseCmdUnparseable {};
class CauseCmdUnfamiliar {};

class TagUnk {};
class TagFwd {};
class TagBwd {};

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
struct TDirTraits;

template <>
struct TDirTraits<TagFwd> {
  typedef TagBwd TBwd;
  typedef TagBwd TCounterDir;
};

template <>
struct TDirTraits<TagBwd> {
  typedef TagFwd TFwd;
  typedef TagBwd TCounterDir;
};


////////////////////////////////////////////////////////////////////////////////
template <TCmdCode CC>
struct TCmdCdTraits {
  static const TCmdCode ccF=CC;
  static const TCmdCode ccB=CC;
  static const TCmdCode ccCounter=CC;
};

template <>
struct TCmdCdTraits<CmdCd::bGetBck> {
  static const TCmdCode ccF      =CmdCd::bGetBck;
  static const TCmdCode ccB      =CmdCd::eGBck;
  static const TCmdCode ccCounter=ccB;
};

template <>
struct TCmdCdTraits<CmdCd::eGBck> {
  static const TCmdCode ccF      =CmdCd::bGetBck;
  static const TCmdCode ccB      =CmdCd::eGBck;
  static const TCmdCode ccCounter=ccF;
};

template <>
struct TCmdCdTraits<CmdCd::bGBck2> {
  static const TCmdCode ccF      =CmdCd::bGBck2;
  static const TCmdCode ccB      =CmdCd::eGBck2;
  static const TCmdCode ccCounter=ccB;
};

template <>
struct TCmdCdTraits<CmdCd::eGBck2> {
  static const TCmdCode ccF      =CmdCd::bGBck2;
  static const TCmdCode ccB      =CmdCd::eGBck2;
  static const TCmdCode ccCounter=ccF;
};

#endif
