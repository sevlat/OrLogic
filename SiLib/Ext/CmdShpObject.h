#ifndef CmdShpObject_h_already_included__20_01_2013__35F309C0
#define CmdShpObject_h_already_included__20_01_2013__35F309C0
//
// SeVlaT, 20.01.2013
//

#include "Types.h"

#include "../CmdObject.h"

template <class CMDOBJ>
class TCmdPtr
{
 public:
  typedef typename CMDOBJ::TDir TDir;

 public:
  typedef shared_ptr<CMDOBJ> TShp;

 public:
  TCmdPtr(CMDOBJ *pCmdObj=0)
   : m_shp(pCmdObj) {}

  TCmdPtr(const TShp &shp)
   : m_shp(shp) {}

  template <class CMDOBJ1>
  TCmdPtr(const TCmdPtr<CMDOBJ1> &pkt)
   : m_shp(pkt.m_shp) {}

 public:
  struct StaticCastTag {};
  
  template <class CMDOBJ1>
  TCmdPtr(const TCmdPtr<CMDOBJ1> &pkt, StaticCastTag)
    : m_shp(boost::static_pointer_cast<CMDOBJ>(pkt.m_shp)) {}

 public:
  typedef typename TShp::unspecified_bool_type TBool;

  operator TBool()  const { return  m_shp; }
  bool operator !() const { return !m_shp; }

 public:
  const CMDOBJ* Get() const { return m_shp.get(); }

 public:
  const CMDOBJ& operator*() const { return *m_shp; }
  const CMDOBJ* operator->() const { return m_shp.operator->(); }

 public:
  CMDOBJ* Get_nc() { Detach(); return m_shp.get(); }

 public:
  CMDOBJ* GetW() { if (m_shp.unique()) return m_shp.get(); return 0; }

 private:
  void Detach()
  {
    T *p=m_shp.get();
    if ((p!=0) && !m_shp.unique()) m_shp=TShp(new T(*p));
  }

 private:
  template<class Y> friend class TCmdPtr;

  TShp m_shp;
};

/*
ShpCmd
ShpICmd
ShpIFCmd
ShpIBCmd
*/

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
struct TShpCmdTraits_Dir {
  typedef DIR              TDir;
  typedef ICmdObject<TDir> ICmdObj;
  
  typedef TCmdPtr<ICmdObj> ShpICmd;
};

template <typename CMD>
struct TCmdShpTraits_Cmd: public TShpCmdTraits_Dir<typename CMD::TDir> {

  typedef typename TCmdoGen<CMD>::Type TCmdObj;
  typedef TCmdPtr<TCmdObj>             ShpCmd;
};

template <typename CMD>
struct TCmdShpTraits: public TCmdShpTraits_Cmd<CMD> {
};

typedef TShpCmdTraits_Dir<TagFwd>::ShpICmd ShpFCmd;
typedef TShpCmdTraits_Dir<TagBwd>::ShpICmd ShpBCmd;

typedef TCmdPtr<IFCmdObject> ShpFCmdObject; // !!!! Remove?
typedef TCmdPtr<IBCmdObject> ShpBCmdObject; // !!!! Remove?


////////////////////////////////////////////////////////////////////////////////
template<typename CMD>
struct TShpCmdObjectFactory {
  typedef typename CMD::TDir TDir;

  typedef ICmdObject<TDir>             ICmdObj;
  typedef typename TCmdoGen<CMD>::Type TCmdObj;
  
  typedef TCmdPtr<ICmdObj> ShpCmdObject;

  static ShpCmdObject Create() { return new TCmdObj(); }
  
};

template <typename DIR, typename CAUSE>
struct TShpCmdRawObjectFactory {
  typedef DIR TDir;

  typedef TRawCommand<DIR, CAUSE> TCmd;

  typedef ICmdObject<TDir> ICmdObj;
  typedef TCmdRawObject<DIR, CAUSE> TCmdObj;
  
  typedef TCmdPtr<ICmdObj> ShpCmdObject;

  static ShpCmdObject Create(const TProtCmdPacket &cp)
  {
    return new TCmdObj(cp.cc, cp.buf);
  }
};

#endif
