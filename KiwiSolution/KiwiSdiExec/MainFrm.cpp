
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "KiwiSdiExec.h"

#include "MainFrm.h"
#include "KiwiSdiExecDoc.h"
#include "KiwiSdiExecView.h"

#include "PersonalSummary.h"
#include "PersonalForm01.h"
#include "PersonalForm02.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(WM_CREATE_PERSONAL_FORM, OnCreatePersonalForm)
	ON_MESSAGE(WM_SHOW_PERSONAL_SUMMARY, &CMainFrame::OnShowPersonalSummary)
	ON_MESSAGE(WM_UPDATE_ORGNIZATION, &CMainFrame::OnUpdateOrgnization)
	ON_COMMAND(ID_TOOL_FULLSCREEN, &CMainFrame::OnToolFullscreen)
	ON_UPDATE_COMMAND_UI(ID_TOOL_FULLSCREEN, &CMainFrame::OnUpdateToolFullscreen)
	ON_MESSAGE(WM_SHOW_DEFAULT_SUMMARY, &CMainFrame::OnShowDefaultSummary)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	m_bFullscreen = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);

	CXTPDockingPane* paneOrgnization = m_paneManager.CreatePane(
		IDD_PANE_ORGNIZATION, CRect(0, 0, 240, 300), xtpPaneDockLeft);
	paneOrgnization->SetOptions(xtpPaneNoCloseable | xtpPaneNoFloatable | xtpPaneNoDockable | xtpPaneNoHideable);
	paneOrgnization->SetMaxTrackSize(CSize(240, 300)); paneOrgnization->SetMinTrackSize(CSize(240, 300));

	CXTPDockingPane* paneShortcut = m_paneManager.CreatePane(
		IDD_PANE_SHORTCUT, CRect(0, 0, 240, 100), xtpPaneDockBottom, paneOrgnization);
	paneShortcut->SetOptions(xtpPaneNoCloseable | xtpPaneNoFloatable | xtpPaneNoDockable | xtpPaneNoHideable);
	paneShortcut->SetMaxTrackSize(CSize(240, 100)); paneShortcut->SetMinTrackSize(CSize(240, 100));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

//
CView* CMainFrame::CreatePersonalForm(CRuntimeClass* pNewViewClass, int nID)
{
	CDocument* pDoc = GetActiveDocument();
	//GetActiveView()->DestroyWindow();
	GetActiveView()->ShowWindow(SW_HIDE);

	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = pDoc;
	CView* pNewView = (CView*)this->CreateView(&context);
	this->SetActiveView(pNewView);
	this->ShowWindow(SW_SHOW);
	RecalcLayout();

	return pNewView;
}

// CMainFrame 消息处理程序

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
			case IDD_PANE_ORGNIZATION:
				if (!::IsWindow(m_wndPaneOrgnization.m_hWnd))
				{
					m_wndPaneOrgnization.Create(IDD_PANE_ORGNIZATION, this);
				}
				pPane->Attach(&m_wndPaneOrgnization);
				break;
			case IDD_PANE_SHORTCUT:
				if (!::IsWindow(m_wndPaneShortcut.m_hWnd))
				{
					m_wndPaneShortcut.Create(IDD_PANE_SHORTCUT, this);
				}
				pPane->Attach(&m_wndPaneShortcut);
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}

afx_msg LRESULT CMainFrame::OnCreatePersonalForm(WPARAM wParam, LPARAM lParam)
{
	WORD id = LOWORD(wParam);
	switch (id) {
	case 1:
	{
		CPersonalForm01* pView = (CPersonalForm01*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm01), IDD_PERSONAL_FORM01);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;
	}
	case 2:
		CreatePersonalForm(RUNTIME_CLASS(CPersonalForm02), IDD_PERSONAL_FORM02);
		return 0;

	}


	return 0;
}


afx_msg LRESULT CMainFrame::OnShowPersonalSummary(WPARAM wParam, LPARAM lParam)
{
		CString *folder = (CString *)wParam, *file = (CString *)lParam;
		m_wndPaneShortcut.m_strCurrentFolder.Format(_T("%s"), *folder); //delete folder;
		m_wndPaneShortcut.m_strCurrentFile.Format(_T("%s"), *file); //delete file;

		CView* pView = CreatePersonalForm(RUNTIME_CLASS(CPersonalSummary), IDD_PERSONAL_SUMMARY);
		::PostMessage(pView->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, wParam, lParam);

		pView->OnInitialUpdate();		

	return 0;
}


afx_msg LRESULT CMainFrame::OnUpdateOrgnization(WPARAM wParam, LPARAM lParam)
{
	if (::IsWindow(m_wndPaneOrgnization.m_hWnd)) {
		::PostMessage(m_wndPaneOrgnization.m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
	}
	return 0;
}


void CMainFrame::OnToolFullscreen()
{
	// TODO:  在此添加命令处理程序代码
	if (!m_bFullscreen) {
				GetWindowRect(&m_rcMainFrame);

				ModifyStyle(WS_CAPTION, 0);
				// Now resize the main window
				int cxScrn = ::GetSystemMetrics(SM_CXSCREEN);
				int cyScrn = ::GetSystemMetrics(SM_CYSCREEN);
				int cxBorder = ::GetSystemMetrics(SM_CXBORDER);
				int cyBorder = ::GetSystemMetrics(SM_CYBORDER);
				SetWindowPos(NULL, -cxBorder, -cyBorder, cxScrn + cxBorder * 2,
					cyScrn + cyBorder * 2, SWP_NOZORDER);

				RecalcLayout(TRUE);
			}
	else {
		ModifyStyle(0, WS_CAPTION);
		MoveWindow(&m_rcMainFrame);

		RecalcLayout(TRUE);
	}

	m_bFullscreen = !m_bFullscreen;
}


void CMainFrame::OnUpdateToolFullscreen(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bFullscreen);

	
}


afx_msg LRESULT CMainFrame::OnShowDefaultSummary(WPARAM wParam, LPARAM lParam)
{
	CString *folder = (CString *)lParam;
	m_wndPaneShortcut.m_strCurrentFolder.Format(_T("%s"), *folder); //delete folder;

	CView* pView = CreatePersonalForm(RUNTIME_CLASS(CKiwiSdiExecView), IDD_KIWISDIEXEC_FORM);
	pView->OnInitialUpdate();

	return 0;
}
