// SeVlaT, 27.05.2013
#include "StdAfx.h"

#include "AboutDlg.h"

#include "Utils.h"

#include "resource.h"

// Message handler for about box.
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);
  
  switch (message) {
    case WM_INITDIALOG:
      SetDlgItemText(hDlg, IDC_VERSION_LABEL, GetVersionString(L"Ver. ", 4).c_str());
      return (INT_PTR)TRUE;

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
      }
      break;
  }
  
  return (INT_PTR)FALSE;
}

