// SeVlaT, 12.06.2012
#include "StdAfx.h"

#include "../Crc.h"

#include "crc529.h"

TCrc::TCrc()
{
}

TCrc::TCrc(int nReserve)
{
  m_Buf.reserve(nReserve);
}

void TCrc::AddByte(TByte b)
{
  m_Buf.Append(b);
}

void TCrc::AddBuf(const TByteBuffer &Buf)
{
  m_Buf.Append(Buf);
}

TWord TCrc::Get() const
{
  const TDWord dwCrc=crc(m_Buf.size(), m_Buf.begin_ptr());
  return hftl::Get2WordL(dwCrc);
}
