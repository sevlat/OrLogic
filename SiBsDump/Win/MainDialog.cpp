// SeVlaT, 07.05.2013
#include "StdAfx.h"

#include "MainDialog.h"

#include "Utils.h"
#include "resource.h"

#include "../Engine.h"
#include "../Utils.h"

#include <SiLib/Utils.h>
#include <HFL/Utils.h>

const int c_nDelayMs=1000;


TMainDialog::TMainDialog(TEngine &Eng)
 : m_hDlg(0),
   m_Eng(Eng),
   m_IdEngineTimer(100)
{
}

void TMainDialog::SetHandle(HWND hDlg)
{
  assert(m_hDlg==0 || m_hDlg==hDlg);
  m_hDlg=hDlg;
}

void TMainDialog::OnInitDialog()
{
  SearchComPorts();
  SetTimer(m_hDlg, m_IdEngineTimer, c_nDelayMs, 0);
  
  UpdateUI();
}

void TMainDialog::OnDestroy()
{
  KillTimer(m_hDlg, m_IdEngineTimer);
}

void TMainDialog::OnDeviceChange()
{
  SearchComPorts();
}

bool TMainDialog::OnCommand(int cmd)
{
  assert(DebugCheckState());
  
  switch (cmd) {
    case IDOK:
    case IDCANCEL:
      DestroyWindow(m_hDlg);
      return true;

    case IDC_COMPORT_SEARCH:
      SearchComPorts();
      return true;

    case IDC_COMPORT_CONNECT:
      OnConnect();
      return true;

    case IDC_COMPORT_DISCONNECT:
      OnDisconnect();
      return true;
      
    case IDC_MASTER_DETECT:
      OnMasterDetect();
      return true;
      
    case IDC_MASTER_DUMP:
      OnMasterDump();
      return true;
      
    case IDC_SLAVE_DETECT:
      OnSlaveDetect();
      return true;
      
    case IDC_SLAVE_DUMP:
      OnSlaveDump();
      return true;

    case IDC_MASTER_DETECT_AUTO:
    case IDC_SLAVE_DETECT_AUTO:
    case IDC_SLAVE_DUMP_AUTO:
      OnParamsChanged();
      return true;

    case IDC_JOB_STOP:
      OnStopClicked();
  }
  
  return false;
}

void TMainDialog::OnTimer(int IdTimer)
{
  if (IdTimer==m_IdEngineTimer) OnEngineTimer();
}

void TMainDialog::OnEngineTimer()
{
  if (m_Eng.Do()) UpdateUI();
}

void TMainDialog::OnConnect()
{
  TCHAR szPort[256]=_T("");
  const int nRes=GetDlgItemText(m_hDlg, IDC_COMPORT_NAME, szPort, 256);

  m_Eng.Connect(szPort);
  UpdateUI();
}

void TMainDialog::OnDisconnect()
{
  m_Eng.Disconnect();
  UpdateUI();
}

void TMainDialog::OnMasterDetect()
{
  m_Eng.DetectMaster();
  UpdateUI();
}

void TMainDialog::OnMasterDump()
{
  m_Eng.StartDump(true);
  UpdateUI();
}

void TMainDialog::OnSlaveDetect()
{
  m_Eng.DetectSlave();
  UpdateUI();
}

void TMainDialog::OnSlaveDump()
{
  m_Eng.StartDump(false);
  UpdateUI();
}

void TMainDialog::OnStopClicked()
{
  m_Eng.Abort();
  UpdateUI();
}

void TMainDialog::OnParamsChanged()
{
  const bool bAutoDetectMasterEnabled=SendDlgItemMessage(m_hDlg,
                IDC_MASTER_DETECT_AUTO, BM_GETCHECK, 0, 0)==BST_CHECKED;
  const bool bAutoDetectSlaveEnabled=SendDlgItemMessage(m_hDlg,
                IDC_SLAVE_DETECT_AUTO, BM_GETCHECK, 0, 0)==BST_CHECKED;
  const bool bAutoDumpSlaveEnabled=SendDlgItemMessage(m_hDlg,
                IDC_SLAVE_DUMP_AUTO, BM_GETCHECK, 0, 0)==BST_CHECKED;

  m_Eng.SetParams(bAutoDetectMasterEnabled,
                  bAutoDetectSlaveEnabled,
                  bAutoDumpSlaveEnabled);
  UpdateUI();
}

void TMainDialog::EnableControl(int IdCtrl, bool bEnable)
{
  const HWND hCtrl=GetDlgItem(m_hDlg, IdCtrl);
  if (hCtrl) EnableWindow(hCtrl, bEnable);
}

void TMainDialog::ShowControl(int IdCtrl, bool bShow)
{
  const HWND hCtrl=GetDlgItem(m_hDlg, IdCtrl);
  if (!hCtrl) return;
  
  if (bShow) ShowWindow(hCtrl, SW_SHOW);
        else ShowWindow(hCtrl, SW_HIDE);
}

TString GetStringValue(const TBsModeRaw  &bmr) { return TBsConstNameW::Get(bmr); }
TString GetStringValue(const TBsModelRaw &bmr) { return TBsConstNameW::Get(bmr); }
TString GetStringValue(TUInt n) { return ToStrW().Dec(n); }

template<typename INT, int TAG>
TString GetStringValue(const TIntLabel<INT, TAG> &il) 
{
  wchar_t szBuf[256]={0};
  return DecIntConstName(0, il.Get(), szBuf);
}

TString GetStringValue(OSysSpan os)
{
  if (!os) return L"";
  
  return A2W(SysSpanToStr(*os));
}

template <typename VAL>
void TMainDialog::UpdateCtrl(      int      IdCtrl,
                                   int      IdTitle,
                             const OBsInfo &obsi,
                             TOptional<VAL> TBsInfo::*pOVal)
{
  EnableControl(IdTitle, obsi);
  
  TString sText;

  if (obsi) {
    const TOptional<VAL> &oVal=(*obsi).*pOVal;
    EnableControl(IdCtrl, oVal);
    
    if (oVal) sText=GetStringValue(*oVal);
  } else {
    EnableControl(IdCtrl, false);
  }
  SetDlgItemText(m_hDlg, IdCtrl, sText.c_str());
}

void TMainDialog::UpdateUI()
{
  const TEngineState &State=m_Eng.State();
  
  {
    EnableControl(IDC_COMPORT_SEARCH,     !State.osConnected);
    EnableControl(IDC_COMPORT_CONNECT,     State.CanConnect());
    EnableControl(IDC_COMPORT_DISCONNECT,  State.CanDisconnect());

    if (State.osConnected) {
      const TString sText=L"Connected "+*State.osConnected;
      SetDlgItemText(m_hDlg, IDC_COMPORT_STATUS, sText.c_str());
    } else {
      SetDlgItemText(m_hDlg, IDC_COMPORT_STATUS, L"");
    }
  } 
 
  {
    UpdateCtrl(IDC_MASTER_CODE,     IDC_MASTER_CODE_TITLE,
               State.obsiMaster,   &TBsInfo::oCode);
    UpdateCtrl(IDC_MASTER_MODE,     IDC_MASTER_MODE_TITLE,
               State.obsiMaster,   &TBsInfo::oMode);
    UpdateCtrl(IDC_MASTER_MODEL,    IDC_MASTER_MODEL_TITLE,
               State.obsiMaster,   &TBsInfo::oModel);
    UpdateCtrl(IDC_MASTER_SERNUM,   IDC_MASTER_SERNUM_TITLE,
               State.obsiMaster,   &TBsInfo::oSerNum);
    UpdateCtrl(IDC_MASTER_BCKPTR,   IDC_MASTER_BCKPTR_TITLE,
               State.obsiMaster,   &TBsInfo::onBackupPtr);
    UpdateCtrl(IDC_MASTER_OVERFLOW, IDC_MASTER_OVERFLOW_TITLE,
               State.obsiMaster,   &TBsInfo::obOverflow);
    
    EnableControl(IDC_MASTER_DUMP,   m_Eng.CanStartDump(true));
    EnableControl(IDC_MASTER_DETECT, State.osConnected);
  }
  
  {
    UpdateCtrl(IDC_SLAVE_CODE,      IDC_SLAVE_CODE_TITLE,
               State.obsiSlave,    &TBsInfo::oCode);
    UpdateCtrl(IDC_SLAVE_MODE,      IDC_SLAVE_MODE_TITLE,
               State.obsiSlave,    &TBsInfo::oMode);
    UpdateCtrl(IDC_SLAVE_MODEL,     IDC_SLAVE_MODEL_TITLE,
               State.obsiSlave,    &TBsInfo::oModel);
    UpdateCtrl(IDC_SLAVE_SERNUM,    IDC_SLAVE_SERNUM_TITLE,
               State.obsiSlave,    &TBsInfo::oSerNum);
    UpdateCtrl(IDC_SLAVE_BCKPTR,    IDC_SLAVE_BCKPTR_TITLE,
               State.obsiSlave,    &TBsInfo::onBackupPtr);
    UpdateCtrl(IDC_SLAVE_OVERFLOW,  IDC_SLAVE_OVERFLOW_TITLE,
               State.obsiSlave,    &TBsInfo::obOverflow);

    EnableControl(IDC_SLAVE_DUMP,   m_Eng.CanStartDump(false));
    EnableControl(IDC_SLAVE_DETECT, State.osConnected);
  }
  
  EnableControl(IDC_SLAVE_DETECT_AUTO, false);
  EnableControl(IDC_MASTER_DETECT_AUTO, false);
  EnableControl(IDC_SLAVE_DUMP_AUTO, false);

  EnableControl(IDC_JOB_STOP, m_Eng.IsReading());
  
  {
    const TDumpJobInfo *pJobInfo=m_Eng.Job();
    if (pJobInfo) {
      const TDumpJobInfo &JobInfo=*pJobInfo;
      
      const TString sTextLong=JobInfo.GetStatusText();
      
      TString sTextShort;
      if (JobInfo.bMaster) sTextShort=L"Master";
                      else sTextShort=L"Slave";

      SetDlgItemText(m_hDlg, IDC_JOB_STATUS_SHORT, sTextShort.c_str());
      SetDlgItemText(m_hDlg, IDC_JOB_STATUS_LONG,  sTextLong.c_str());
      
      if (m_Eng.IsReading()) {
        SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETRANGE32,
                           0x100, JobInfo.nMaxAddr); //!!!!
        SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETPOS,
                           JobInfo.nCurAddr, 0);
      } else {
        SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETRANGE32, 0, 0);
        SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETPOS, 0, 0);
      }                           
                
    } else {
      SetDlgItemText(m_hDlg, IDC_JOB_STATUS_SHORT, L"");
      SetDlgItemText(m_hDlg, IDC_JOB_STATUS_LONG,  L"");

      SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETRANGE32, 0, 0);
      SendDlgItemMessage(m_hDlg, IDC_PROGRESS, PBM_SETPOS, 0, 0);
    }
    
    if (!m_Eng.IsIdle() && pJobInfo) {
      EnableControl(IDC_JOB,              true);
      EnableControl(IDC_JOB_STATUS_SHORT, true);
      EnableControl(IDC_JOB_STATUS_LONG,  true);

      ShowControl(IDC_TIME_TITLE,         true);
      ShowControl(IDC_TIME_TOTAL_TITLE,   true);
      ShowControl(IDC_TIME_LEFT_TITLE,    true);
      ShowControl(IDC_TIME_ELAPSED_TITLE, true);

      ShowControl(IDC_TIME_TOTAL,         true);
      ShowControl(IDC_TIME_LEFT,          true);
      ShowControl(IDC_TIME_ELAPSED,       true);

      const TTimeEstimator &te=pJobInfo->m_TimeEstimator;

      SetDlgItemText(m_hDlg, IDC_TIME_TOTAL,   GetStringValue(te.Total()).c_str());
      SetDlgItemText(m_hDlg, IDC_TIME_LEFT,    GetStringValue(te.Rest()).c_str());
      SetDlgItemText(m_hDlg, IDC_TIME_ELAPSED, GetStringValue(te.Spent()).c_str());

    } else {
      EnableControl(IDC_JOB,              false);
      EnableControl(IDC_JOB_STATUS_SHORT, false);
      EnableControl(IDC_JOB_STATUS_LONG,  false);

      ShowControl(IDC_TIME_TITLE,         false);
      ShowControl(IDC_TIME_TOTAL_TITLE,   false);
      ShowControl(IDC_TIME_LEFT_TITLE,    false);
      ShowControl(IDC_TIME_ELAPSED_TITLE, false);

      ShowControl(IDC_TIME_TOTAL,         false);
      ShowControl(IDC_TIME_LEFT,          false);
      ShowControl(IDC_TIME_ELAPSED,       false);

      SetDlgItemText(m_hDlg, IDC_TIME_TOTAL,   L"");
      SetDlgItemText(m_hDlg, IDC_TIME_LEFT,    L"");
      SetDlgItemText(m_hDlg, IDC_TIME_ELAPSED, L"");
    }
  }
}

bool TMainDialog::OnNotify(int msg, int idCtrl, HWND hCtrl)
{
  assert(DebugCheckState());

  switch (idCtrl) {
    case IDC_COMPORT_LIST:
      if (msg==LBN_DBLCLK) return OnComportListDblClk(hCtrl);
      break;
  }
  
  return false;
}

bool TMainDialog::OnComportListDblClk(HWND hList)
{
  const int nCur=SendMessage(hList, LB_GETCURSEL, 0, 0);
  if (nCur==LB_ERR) return true;
  if (nCur<0) return true;

  const int nLen=SendMessage(hList, LB_GETTEXTLEN, nCur, 0);
  if (nLen==LB_ERR) return true;
  if (nLen<0 || nLen>=100) return true;//!!!!! 100

  TCHAR szItem[256]=_T("");
  const int nRes=SendMessage(hList, LB_GETTEXT, nCur, WStr2LParam(szItem));
  if (nRes==LB_ERR) return true;
  
  SetDlgItemText(m_hDlg, IDC_COMPORT_NAME, szItem);
  return true;
}

void TMainDialog::SearchComPorts()
{
  std::vector<std::wstring> CpVec;
  EnumComPorts(CpVec);
  UpdateComPortList(CpVec);
  if (CpVec.size()==1) {
    TCHAR szPort[256]=_T("");
    const int nRes=GetDlgItemText(m_hDlg, IDC_COMPORT_NAME, szPort, 256);
    if (szPort[0]==0) {
      SetDlgItemText(m_hDlg, IDC_COMPORT_NAME, CpVec.front().c_str());
    }
  }
}

void TMainDialog::UpdateComPortList(const std::vector<std::wstring> &CpVec)
{
  if (!m_hDlg) return;
  const HWND hList=GetDlgItem(m_hDlg, IDC_COMPORT_LIST);
  
  if (!hList) return;
  SendMessage(hList, LB_RESETCONTENT, 0, 0);
  if (CpVec.empty()) {
    SendMessage(hList, LB_ADDSTRING, 0, CWStr2LParam(_T("not found")));
    EnableWindow(hList, FALSE);
  } else {
    EnableWindow(hList, TRUE);
    typedef std::vector<std::wstring>::const_iterator TCIt;
    for (TCIt I=CpVec.begin(); I!=CpVec.end(); ++I) {
      SendMessage(hList, LB_ADDSTRING, 0, CWStr2LParam(I->c_str()));
    }
  }
}

bool TMainDialog::DebugCheckState() const
{
  if (!IsWindow(m_hDlg)) return false;
  
  return true;
}

