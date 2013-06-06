#ifndef CmdCast_h_already_included__10_02_2013__17707700
#define CmdCast_h_already_included__10_02_2013__17707700
//
// SeVlaT, 10.02.2013
//

#include "CmdObject.h"
#include "CmdVisitor.h"

template<typename CMD>
class TCmdCastVisitor {
 public:
  TCmdCastVisitor()
   : m_pCmd(0) {}
   
  explicit TCmdCastVisitor(int nDummi)
   : m_pCmd(0) {}
   
 public:
  void operator ()(const CMD &cmd) { m_pCmd=&cmd; }

  template<typename CMD1>
  void operator ()(const CMD1 &cmd) { m_pCmd=0; }
  
 public:
  const CMD* Get() const { return m_pCmd; }

 private:
  const CMD *m_pCmd;
};

template<typename CMD>
const CMD* CmdCast(const ICmdObject<typename CMD::TDir> &cmdo)
{
  typedef typename CMD::TDir TDir;
  
  typedef TCmdCastVisitor<CMD>                  TCastVisitor;
  typedef TCmdVisitorV<TCastVisitor, int, TDir> TCastVisitorV;
  
  TCastVisitorV v(0);
  
  cmdo.Apply(v);
  return v.Vis().Get();
}

#endif
