#ifndef ComPort_h_already_included__09_04_2013__21046B80
#define ComPort_h_already_included__09_04_2013__21046B80
//
// SeVlaT, 09.04.2013
//

#include "Types.h"

#include "Stream.h"
#include "Errors.h"

class IComPort: public IIOStream {
 public:
  virtual ~IComPort() {}

 public:
  virtual bool Valid(TErrList *pErr) const=0;
                             
 public:
  virtual bool Open(const wstring &sPort, TErrList *pErr)=0;
  virtual void Close(TErrList *pErr)=0;

  virtual const wstring& GetPortName() const=0;

 public:
  virtual bool SetBaudRate(TUInt nBaudRate, TErrList *pErr)=0;
  virtual OUInt GetBaudRate(TErrList *pErr) const=0;
};

////////////////////////////////////////////////////////////////////////////////
namespace NComPortErrors {
  enum TErrorCode {
    eUnknown,
 
    eComPortError,

    eComPortReadingFailed,
    eComPortWritingFailed,
    eComPortIsNotOpen,
    eComPortAlreadyOpen,
    eCannotGetComPortState,
    eCannotSetComPortState,
    eCannotGetComPortTimeouts,
    eCannotSetComPortTimeouts,

    eLast
  };
  
  typedef TErrorDescription<TErrorCode, eLast, 300> TErrorDescr;
  
  inline void PushError(TErrList *pErr, TErrorCode ec)
  { TErrorDescr::PushError(pErr, ec); }
}

////////////////////////////////////////////////////////////////////////////////
namespace PlatformSpecific {

void EnumComPorts(std::vector<std::wstring> &CpVec);

////////////////////////////////////////////////////////////////////////////////
IComPort* CreateComPort();
void DeleteComPort(IComPort* pCp);

}

using PlatformSpecific::EnumComPorts;

#endif
