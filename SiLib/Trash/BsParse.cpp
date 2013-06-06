/*
class TBsCmdReader {
 public:
  void Done();
  void Next(TByte b);
  TUInt Need() const;
  
 private:
  TBsParser m_bp;
};

class TBsPortReader {
 public:
  bool Read(TUInt nBytesToRead);
  
 private:
  IIStream     &m_is;
  TBsCmdReader  m_cr;

 private:
  mutable TByteBuffer m_bb; 
};

bool TBsPortReader::Read(TUInt nBytesToRead)
{
  TUInt nBytesRead=0;
  m_bb.resize(nBytesToRead);
  if (!m_is.GetRaw(m_bb.begin_ptr(), nBytesToRead, nBytesRead, 0, 0)) return false;
  
  for (TUInt i=0; i<nBytesRead; ++i) {
    m_cr.Next(m_bb[i]);
  }
}
*/

/*
  virtual bool GetRaw(void     *pBuf,
                      TUInt     nBytesToRead,
                      TUInt    &nBytesRead,
                      TErrList *pErr)=0;


bool TParserNew::TrySet(TByte b)
{
  const bool bEaten=m_bsp.Next(b);
  
  if (m_bsp.IsStalled()) {
    if (m_bsp.IsStalledOk()) {
      m_cd.Dispatch(m_bsp.GetMsg(), 0);
      std::cout << std::endl;
    } else if (m_bsp.IsStalledFail()) {
      std::cout << "!!Error" <<  std::endl;
    }
    
    ResetBsParser();
  }
  return bEaten;
}
*/
