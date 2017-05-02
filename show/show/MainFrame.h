#pragma once
#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>

namespace Gdiplus{
    class Bitmap;
}

class CPopWindow :
	public CWindowImpl<CPopWindow>
{
public:
	DECLARE_WND_CLASS(_T("CPopWindow"))

	CPopWindow();
	~CPopWindow();

	BEGIN_MSG_MAP(CPopWindow)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
	END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    

    Gdiplus::Bitmap* m_pBitmap;
};

class CMainFrame :
	public CWindowImpl<CMainFrame, CWindow/*, CFrameWinTraits*/>,
	public CMessageFilter, 
	public CIdleHandler
{
public:
	DECLARE_WND_CLASS_EX(_T("MainFrame"), /*CS_DROPSHADOW | CS_VREDRAW |*/ CS_DBLCLKS, COLOR_WINDOW)
	CMainFrame();
	~CMainFrame();

	BOOL PreTranslateMessage(MSG* pMsg);

	BOOL OnIdle();

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnMovied)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnMovied(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CPopWindow _popWindow;
   
    Gdiplus::Bitmap* m_pBitmap;

    CButton m_btn;
};

