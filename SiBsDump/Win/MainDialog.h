#ifndef MainDialog_h_already_included__07_05_2013__13C22160
#define MainDialog_h_already_included__07_05_2013__13C22160
//
// SeVlaT, 07.05.2013
//

#include <SiLib/BsTypes.h>

class TEngine;

class TMainDialog
{
 public:
  explicit TMainDialog(TEngine &Eng);
 
 public:
  void SetHandle(HWND hDlg);
  
 public:
  void OnInitDialog();
  void OnDestroy();
  
 public:
  bool OnCommand(int cmd);
  bool OnNotify(int msg, int idCtrl, HWND hCtrl);
  
  bool OnComportListDblClk(HWND hList);

  void OnDeviceChange();

 public:
  void OnConnect();
  void OnDisconnect();
  
  void OnMasterDetect();
  void OnMasterDump();

  void OnSlaveDetect();
  void OnSlaveDump();

  void OnParamsChanged();

  void OnStopClicked();

 public:
  void OnTimer(int IdTimer);

  void OnEngineTimer();

 public:
  void EnableControl(int IdCtrl, bool bEnable);
  void ShowControl(int IdCtrl, bool bShow);

 private:
  void SearchComPorts();
  void UpdateComPortList(const std::vector<std::wstring> &CpVec);

  template <typename VAL>
  void UpdateCtrl(      int      IdCtrl,
                        int      IdTitle,
                  const OBsInfo &obsi,
                  TOptional<VAL> TBsInfo::*pOVal);

  void UpdateUI();

 private:
  bool DebugCheckState() const;

 private:
  HWND m_hDlg;
  int m_IdEngineTimer;
  
 private:
  TEngine &m_Eng;
};

#endif
