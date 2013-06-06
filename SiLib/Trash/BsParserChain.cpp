#include "StdAfx.h"

#include "../BsParserChain.h"

TBsParserChain::TBsParserChain()
 : m_bClosed(false)
{
}
  
bool TBsParserChain::Closed() const
{
  return m_bClosed;
}

/*
AddChar(ch);
New() - should return courrent result


AddChar(ch0);
AddChar(ch1);
AddChar(ch2);
AddChar(ch3);
AddChar(ch4);
AddChar(ch5);
AddChar(ch6);
AddChar(ch7);
AddChar(ch8);
AddChar(ch9);


-----------------------------------
  AddChar(ch0);           +   +  
                          
  AddChar(ch1); Etx       +=  =
                          
  New()                       
  AddChar(ch2); Ack       +=  =
                          
  New()                       
  AddChar(ch3);           +   +
                          
  AddChar(ch4); unexp Stx -   
  New()                       
  AddChar(ch4); Stx       +   +
                          
  AddChar(ch5);           +=  =
                          
  New()                       
  AddChar(ch6);           +   +
                          
  AddChar(ch7); unexp Ack -   
  New()                       
  AddChar(ch7); Ack           =
                          
  New()                       
  AddChar(ch8);               +
                          
  AddChar(ch9); Etx           =

  -----------------------------------
  AddChar(ch0);           +   +

  AddChar(ch1); last byte +   +

  AddChar(ch2); Etx       +=  =

  New()
  AddChar(ch3); Stx       +   +

  AddChar(ch4);           +   +

  AddChar(ch5); Etx       +=  =

  -----------------------------------
  AddChar(ch0);           +   +

  AddChar(ch1); last byte +   +
  
  AddChar(ch2); Stx       -=  =
  New()
  AddChar(ch2); Stx       +   +

  AddChar(ch3);           +   +

  AddChar(ch4); Etx       +=  =

  -----------------------------------
  AddChar(ch0);           +   +
  Get-
  New-

  AddChar(ch1); last byte +   +
  Get-
  New-
  
  AddChar(ch2); Ack       -=  =
  Get+
  New+
  Get-
* AddChar(ch2); Ack       +=  =
  Get+
  New-

  -----------------------------------
  AddChar(ch0);
  AddChar(ch1); Etx
  New()
  AddChar(ch2); Ack


  -----------------------------------
  AddChar(ch0);            +
  AddChar(ch1);            +
  AddChar(ch2); unexp Byte
  New()
  AddChar(ch2); unexp Byte
  Close()

  AddChar(ch3);
  AddChar(ch4);
  AddChar(ch5);
  AddChar(ch6);
  AddChar(ch7);
  AddChar(ch8);
  AddChar(ch9);
*/

/*
bool TBsParserChain::Add(TByte b)
{
  if (m_bClosed) return false;
}

bool TBsParserChain::Parsed() const
{
  if (m_bClosed) return false;
}

bool TBsParserChain::Continue()
{
}


bool TBsParserChain::DoNext(char ch)
{
  if (m_bClosed) return false;
  if (m_vec.empty()) return false;

  TBsParser &bspCur=m_vec.back();
  if (bspCur.IsFinished()) return false;
  if (bspCur.Next(ch)) return true;
  
  m_bClosed=true;
  return false;
}

void TBsParserChain::New()
{
  m_vec.push_back(TBsParser());
}

bool TBsParserChain::Next(char ch)
{
  if (DoNext(ch)) return true;
  if (m_bClosed) return false;
  if (DoNext(ch)) return true;
  return false;
}
*/