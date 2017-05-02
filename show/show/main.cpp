#include <atlbase.h>
#include <atlapp.h>
#include "MainFrame.h"
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;
    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD styleEx = WS_EX_APPWINDOW;
    if (wndMain.Create(NULL, CWindow::rcDefault, _T("MainFrame"), style, styleEx) == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

/** GDIPlush Token
*/
ULONG_PTR m_gdiplusToken;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartupOutput gdiplusStartupOutput;
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, &gdiplusStartupOutput);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));
	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	//AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls
    AtlInitCommonControls(ICC_WIN95_CLASSES | ICC_COOL_CLASSES | ICC_DATE_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES);
	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));
	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();

    Gdiplus::GdiplusShutdown(m_gdiplusToken);
	::CoUninitialize();

	return nRet;
}