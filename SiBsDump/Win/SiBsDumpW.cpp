// SiBsDumpW.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "SiBsDumpW.h"

#include "MainDialog.h"
#include "AboutDlg.h"

#include "Utils.h"

#include "../Engine.h"

#define MAX_LOADSTRING 100

// Global Variables:
TCHAR szTitle[MAX_LOADSTRING];          // The title bar text
HICON g_hIcon;

HINSTANCE g_hInstance;

TEngine g_Eng;
TMainDialog g_Dlg(g_Eng);

HINSTANCE HInstance() { return g_hInstance; }

void InitComCtrl()
{
  INITCOMMONCONTROLSEX icce={0};
  icce.dwSize=sizeof(icce);
  icce.dwICC=ICC_PROGRESS_CLASS;
  
  InitCommonControlsEx(&icce);
}

// Forward declarations of functions included in this code module:
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // Initialize global strings
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	g_hIcon=LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIBSDUMPW));
// wcex.hIconSm=LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  InitComCtrl();

  HWND hDlg=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINDLG), 0, DlgProc);

  if (!hDlg) return FALSE;

  ShowWindow(hDlg, nCmdShow);
  UpdateWindow(hDlg);

  HACCEL hAccelTable=LoadAccelerators(hInstance,
                                      MAKEINTRESOURCE(IDC_SIBSDUMPW));

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) &&
        !IsDialogMessage(hDlg, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int) msg.wParam;
}

BOOST_STATIC_ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
BOOST_STATIC_ASSERT(IDM_ABOUTBOX < 0xF000);

void InitSysMenu(HWND hDlg)
{
  const HMENU hMenu=GetSystemMenu(hDlg, FALSE);
  if (!hMenu) return;

	AppendMenu(hMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hMenu, MF_STRING, IDM_ABOUTBOX, L"About");
}

void InitDlgTitle(HWND hDlg)
{
  const int nBufSize=256;
  WCHAR szBuf[nBufSize]={0};
  GetWindowText(hDlg, szBuf, nBufSize);
  std::wstring sTitle(szBuf);
  SetWindowText(hDlg, GetVersionString(sTitle+L" Ver. ", 2).c_str());
}

INT_PTR OnSysMenu(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
  if ((wParam & 0xFFF0) == IDM_ABOUTBOX) {
    DialogBox(HInstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, AboutDlgProc);
    return (INT_PTR)TRUE;
  }
  
  return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  g_Dlg.SetHandle(hDlg);

  UNREFERENCED_PARAMETER(lParam);
  switch (message){
    case WM_INITDIALOG:
      InitSysMenu(hDlg);
      InitDlgTitle(hDlg);
      g_Dlg.OnInitDialog();
      return (INT_PTR)TRUE;

    case WM_DESTROY:
      g_Dlg.OnDestroy();
      PostQuitMessage(0);
      return (INT_PTR)TRUE;

    case WM_COMMAND:
      {
        const WORD wCode=HIWORD(wParam);
        const WORD wId  =LOWORD(wParam);
        
        if (wCode==0 || wCode==1) {
          if (g_Dlg.OnCommand(wId)) return (INT_PTR)TRUE;
        } else {
          const HWND hCtrl=(HWND)lParam;
          if (g_Dlg.OnNotify(wCode, wId, hCtrl)) return (INT_PTR)TRUE;
        }
      }
      break;

    case WM_SYSCOMMAND:
      return OnSysMenu(hDlg, wParam, lParam);

    case WM_TIMER:
      g_Dlg.OnTimer(wParam);
      return (INT_PTR)TRUE;

    case WM_DEVICECHANGE:
      g_Dlg.OnDeviceChange();
      return (INT_PTR)TRUE;
  
    case WM_ERASEBKGND:
      if (IsIconic(hDlg) && g_hIcon) {
        SendMessage(hDlg, WM_ICONERASEBKGND, wParam, 0L );
        return TRUE;
      }
      break;

    case WM_QUERYDRAGICON:
      return (INT_PTR)(g_hIcon);

    case WM_PAINT:
      {
        PAINTSTRUCT ps;

        BeginPaint(hDlg, &ps );

        if (IsIconic(hDlg)) {
          if (g_hIcon) {
            RECT rect;

            //center the icon correctly...
            GetClientRect(hDlg, &rect) ;
            rect.left = (rect.right - GetSystemMetrics(SM_CXICON))
                         >> 1;
            rect.top = (rect.bottom - GetSystemMetrics(SM_CYICON))
                        >> 1;
            DrawIcon( ps.hdc, rect.left, rect.top, g_hIcon );
          }
        }
        EndPaint(hDlg, &ps);
      }
      break;
  }
  
  return (INT_PTR)FALSE;
}
