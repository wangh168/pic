#include "MainFrame.h"

#include <string>
#include <vector>
#include <stdint.h>

#include <gdiplus.h>
#include <FreeImagePlus.h>

extern CAppModule _Module;

CPopWindow::CPopWindow()
{

}

CPopWindow::~CPopWindow()
{

}

std::wstring GetDlgFile(HWND hWnd)
{
    std::wstring filePath;
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;

    ofn.lpstrFilter = _T("ALL\0*.*\0\0");
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;

    uint32_t bufSize = MAX_PATH;
    TCHAR* pBuf = new TCHAR[bufSize];
    if (pBuf == NULL)
    {
        return filePath;
    }
    memset(pBuf, 0, bufSize);
    ofn.nMaxFile = bufSize;
    ofn.lpstrFile = pBuf;
    bool isOk = GetOpenFileName(&ofn) ? true : false;
    if (!isOk)
    {
        delete[] pBuf;
        return filePath;
    }

    TCHAR* fileName = ofn.lpstrFile + ofn.nFileOffset;
    if (*(fileName - 1))
    {
        filePath = ofn.lpstrFile;
    }

    return filePath;
}


fipWinImage* g_pFipImage = NULL;
LRESULT CPopWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);
    CRect rect;
    GetClientRect(rect);
    {
        bool adpt = false;
        adpt = true;
        CMemoryDC memDc(dc.m_hDC, dc.m_ps.rcPaint);
        Gdiplus::Graphics g(memDc.m_hDC);
        g.Clear(Gdiplus::Color(255, 178, 178, 178));

        if (g_pFipImage != NULL && g_pFipImage->isValid())
        {

            int32_t x, y, width, height;
            int32_t ox, oy, owidth, oheight;

            uint32_t imageW = g_pFipImage->getWidth();
            uint32_t imageH = g_pFipImage->getHeight();
                // 适应窗口显示
            if (adpt)
            {
                float fx = imageW * 1.0f / rect.Width();
                float fy = imageH * 1.0f / rect.Height();
                float factor = max(fx, fy);
                if (factor > 1.0f)
                {
                    width = imageW / factor;
                    height = imageH / factor;
                }
                else
                {
                    width = imageW;
                    height = imageH;
                }

                x = (rect.Width() - width) / 2;
                y = (rect.Height() - height) / 2;

                ox = oy = 0;
                owidth = imageW;
                oheight = imageH;
            }
            else
            {
                x = 0; 
                y = 0;
                width = imageW;
                height = imageH;

                if (imageW > rect.Width())
                {
                    width = rect.Width();
                    ox = (imageW - rect.Width()) / 2;
                }
                else
                {
                    width = imageW;
                    ox = 0;
                }

                if (imageH > rect.Height())
                {
                    height = rect.Height();
                    oy = (imageH - rect.Height()) / 2;
                }
                else
                {
                    height = imageH;
                    oy = 0;
                }

                owidth =  width;
                oheight = height;
                x = (rect.Width() - width) / 2;
                y = (rect.Height() - height) / 2;
                
            }


            RECT sRect = { ox, oy, ox + owidth, oy + oheight };
            RECT dRect = { x, y, x + width, y + height };
           
            g_pFipImage->drawEx(memDc.m_hDC, dRect, sRect);
        }

        //if (m_pBitmap != NULL)
        //{
        //    // 适应窗口显示
        //    float fx = m_pBitmap->GetWidth() * 1.0f / rect.Width();
        //    float fy = m_pBitmap->GetHeight() * 1.0f / rect.Height();
        //    float factor = max(fx, fy);

        //    int32_t width = m_pBitmap->GetWidth() / factor;
        //    int32_t height = m_pBitmap->GetHeight() / factor;

        //    g.DrawImage(m_pBitmap, Gdiplus::RectF((rect.Width() - width) / 2, (rect.Height() - height) / 2, width, height), 0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight(), Gdiplus::UnitPixel);
        //}
    }
   
	return 0L;
}

LRESULT CPopWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;

    ::InvalidateRect(m_hWnd, NULL, FALSE);
    return 0;
}

//////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
{
    m_pBitmap = NULL;
}

CMainFrame::~CMainFrame()
{
    if (m_pBitmap != NULL)
    {
        delete m_pBitmap;
        m_pBitmap = NULL;
    }

    if (g_pFipImage != NULL)
    {
        delete g_pFipImage;
    }
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return  FALSE;
}

BOOL CMainFrame::OnIdle()
{
	return TRUE;
}

LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rect;
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	pLoop->AddIdleHandler(this);

    GetClientRect(&rect);
    rect.left += 10;
    rect.top += 10;
    rect.right -= 10;
    rect.bottom -= 10;

    std::wstring filePath = L"f:/66666.CR2";
    if (1)
    {
        filePath = GetDlgFile(NULL);
    }

    if (!filePath.empty())
    {
        _popWindow.m_pBitmap = m_pBitmap;
        g_pFipImage = new fipWinImage();
        g_pFipImage->loadU(filePath.c_str(), RAW_PREVIEW);
    }

    _popWindow.Create(m_hWnd, &rect, NULL, WS_CHILD);
    _popWindow.ShowWindow(SW_SHOW);
     

	return 0L;
}

LRESULT CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	pLoop->RemoveIdleHandler(this);
	::PostQuitMessage(0);

	bHandled = FALSE;

	return 1L;
}

LRESULT CMainFrame::OnMovied(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    RECT rect;
    GetClientRect(&rect);
    rect.left += 10;
    rect.top += 10;
    rect.right -= 10;
    rect.bottom -= 10;

    _popWindow.MoveWindow(&rect);

    return 0;
}