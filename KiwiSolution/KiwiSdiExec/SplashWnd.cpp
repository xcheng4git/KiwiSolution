// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "SplashWnd.h"
#include "resource.h"

CSplashWnd* CSplashWnd::c_pSplashWnd;

BOOL CSplashWnd::c_bShowSplashWnd;
// CSplashWnd

IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)

CSplashWnd::CSplashWnd()
{

}

CSplashWnd::~CSplashWnd()
{
	ASSERT(c_pSplashWnd == this);

	c_pSplashWnd = NULL;

	m_bitmap.DeleteObject();
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()

	ON_WM_TIMER()

	ON_WM_PAINT()
END_MESSAGE_MAP()



// CSplashWnd 消息处理程序

void CSplashWnd::EnableSplashScreen(BOOL bEnable/* = TRUE*/)

{

	c_bShowSplashWnd = bEnable;

}





void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd/* = NULL*/)

{

	//如果不要显示SplashScreen或SplashWnd对象已经被创建则返回

	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)

	{

		return;

	}



	c_pSplashWnd = new CSplashWnd;



	if (!c_pSplashWnd->Create(pParentWnd))

	{

		delete c_pSplashWnd;

	}

	else

	{

		c_pSplashWnd->UpdateWindow();

	}

}





BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)

{

	if (c_pSplashWnd == NULL)

		return FALSE;



	if (pMsg->message == WM_KEYDOWN

		|| pMsg->message == WM_SYSKEYDOWN

		|| pMsg->message == WM_LBUTTONDOWN

		|| pMsg->message == WM_RBUTTONDOWN

		|| pMsg->message == WM_MBUTTONDOWN

		|| pMsg->message == WM_NCLBUTTONDOWN

		|| pMsg->message == WM_NCRBUTTONDOWN

		|| pMsg->message == WM_NCMBUTTONDOWN)

	{

		c_pSplashWnd->HideSplashScreen();

		return TRUE;

	}



	return FALSE;

}





void CSplashWnd::PostNcDestroy()

{

	delete this;

}





int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)

{

	if (CWnd::OnCreate(lpCreateStruct) == -1)

		return -1;



	// TODO:  Add your specialized creation code here

	CenterWindow();



	SetTimer(1, 2000, NULL);



	return 0;

}





void CSplashWnd::OnTimer(UINT_PTR nIDEvent)

{

	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == 1)

	{

		HideSplashScreen();

	}



	/*CWnd::OnTimer(nIDEvent);*/

}





void CSplashWnd::OnPaint()

{

	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CWnd::OnPaint() for painting messages

	CDC dcImg;

	if (!dcImg.CreateCompatibleDC(&dc))

	{

		return;

	}



	BITMAP bm;

	m_bitmap.GetBitmap(&bm);

	// paint the image

	CBitmap* pOldBit = dcImg.SelectObject(&m_bitmap);

	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImg, 0, 0, SRCCOPY);

	dcImg.SelectObject(pOldBit);

}





BOOL CSplashWnd::Create(CWnd* pParentWnd)

{
	
	if (!m_bitmap.LoadBitmap(IDB_BMP_SPLASH))
	//if (!m_bitmap.LoadBitmap(IDB_SPLASH))
	{

		return FALSE;

	}



	BITMAP bm;

	m_bitmap.GetBitmap(&bm);



	return CreateEx(0,

		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),

		NULL,

		WS_POPUP | WS_VISIBLE,

		0,

		0,

		bm.bmWidth,

		bm.bmHeight,

		pParentWnd->GetSafeHwnd(),

		NULL);

}





void CSplashWnd::HideSplashScreen(void)

{

	DestroyWindow();

	AfxGetMainWnd()->UpdateWindow();

}
