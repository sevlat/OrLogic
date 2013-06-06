#ifndef CmdObject_h_already_included__18_01_2013__35715B40
#define CmdObject_h_already_included__18_01_2013__35715B40
//
// SeVlaT, 18.01.2013
//

#include "CmdVisitor.h"

#include "StationTypes.h"

////////////////////////////////////////////////////////////////////////////////
template<typename DIR>
class ICmdObject {
 public:
  typedef DIR TDir;

 public:
  virtual TCmdCode CmdCode() const=0;
  virtual void Apply(ICmdVisitor<TDir> &v)  const=0;
  virtual void Apply(IRawCmdVisitor<TDir> &rv) const=0;
  
  virtual ~ICmdObject() {}
};

typedef ICmdObject<TagUnk> IUCmdObject; // !!! Not used?
typedef ICmdObject<TagFwd> IFCmdObject;
typedef ICmdObject<TagBwd> IBCmdObject;

////////////////////////////////////////////////////////////////////////////////

template <typename CMD>
class TCmdoGen {
  static const TCmdCode cc=CMD::cc;
  
  typedef typename CMD::TDir  TDir;
  typedef typename CMD::TData TData;
  typedef typename CMD::TCmdb TCmdb;

  template <typename DERIVED>
  class CrtpType: public ICmdObject<typename CMD::TDir> {
   public:
    virtual TCmdCode CmdCode() const { return cc; } 
    
    virtual void Apply(ICmdVisitor<TDir> &v)    const { v.Apply(Cmdb()); }
    virtual void Apply(IRawCmdVisitor<TDir>&) const { }
    
   private:
   public:
    const DERIVED& Self() const { return static_cast<const DERIVED&>(*this); }   
    const TCmdb& Cmdb()   const { return static_cast<const TCmdb&>(Self()); }   
  };
  
 public:
  typedef TCmdAncestor<TData, TCommandBase<cc, TDir>, CrtpType> Type;
};


////////////////////////////////////////////////////////////////////////////////
template <typename DIR, typename CAUSE>
class TCmdRawObject: public ICmdObject<DIR>,
                     public TRawCommand_Base<DIR, CAUSE> {
 public:
  typedef TRawCommand_Base<DIR, CAUSE> TBase;
  typedef DIR TDir;

 public:
  TCmdRawObject() {}
  TCmdRawObject(TCmdCode acc, const TByteBuffer &buf): TBase(acc, buf) {}
  explicit TCmdRawObject(const TProtCmdPacket &pkt): TBase(pkt.cc, pkt.buf) {}

 public:
  virtual TCmdCode CmdCode() const { return cc; } 
  
  virtual void Apply(ICmdVisitor<TDir> &v)    const { }
  virtual void Apply(IRawCmdVisitor<TDir> &v) const { v(*this); }
};

////////////////////////////////////////////////////////////////////////////////
template <typename DIR>
class TCommSetupCmdObject: public ICmdObject<DIR> {
 public:
  TCommSetupCmdObject() {}
  
 public:
  virtual TCmdCode CmdCode() const { return CmdCd::cNull; } 

  virtual void Apply(ICmdVisitor<TDir> &v)    const { }
  virtual void Apply(IRawCmdVisitor<TDir> &v) const { v(m_cs); }
  
 public:
  const TCommSetup& CommSetup() { return m_cs; }

 private:
  TCommSetup m_cs;
};



////////////////////////////////////////////////////////////////////////////////
// !!!!!!!! Move it to another header file
bool MakePacket(const IFCmdObject    &Cmdo,
                const TMsgFrame      &mf,
                      TProtCmdPacket &pkt,
                      TErrList       *pErr);

#endif
