
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
#include "PersonalForm03.h"
#include "PersonalForm04.h"
#include "PersonalForm05.h"
#include "PersonalForm06.h"
#include "PersonalForm07.h"
#include "PersonalForm08.h"
#include "PersonalForm09.h"
#include "PersonalForm10.h"
#include "PersonalForm11.h"
#include "PersonalForm12.h"
#include "PersonalForm13.h"
#include "PersonalForm14.h"
#include "PersonalForm15.h"
#include "PersonalForm16.h"
#include "PersonalForm17.h"
#include "PersonalForm18.h"
#include "PersonalForm19.h"
#include "PersonalForm20.h"

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
	{
		CPersonalForm02* pView = (CPersonalForm02*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm02), IDD_PERSONAL_FORM02);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 3:
	{
		PersonalForm03* pView = (PersonalForm03*)CreatePersonalForm(RUNTIME_CLASS(PersonalForm03), IDD_PERSONAL_FORM03);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 4:
	{
		CPersonalForm04* pView = (CPersonalForm04*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm04), IDD_PERSONAL_FORM04);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 5:
	{
		CPersonalForm05* pView = (CPersonalForm05*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm05), IDD_PERSONAL_FORM05);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 6:
	{
		CPersonalForm06* pView = (CPersonalForm06*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm06), IDD_PERSONAL_FORM06);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 7:
	{
		CPersonalForm07* pView = (CPersonalForm07*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm07), IDD_PERSONAL_FORM07);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 8:
	{
		CPersonalForm08* pView = (CPersonalForm08*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm08), IDD_PERSONAL_FORM08);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 9:
	{
		CPersonalForm09* pView = (CPersonalForm09*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm09), IDD_PERSONAL_FORM09);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 10:
	{
		CPersonalForm10* pView = (CPersonalForm10*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm10), IDD_PERSONAL_FORM10);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 11:
	{
		CPersonalForm11* pView = (CPersonalForm11*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm11), IDD_PERSONAL_FORM11);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 12:
	{
		CPersonalForm12* pView = (CPersonalForm12*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm12), IDD_PERSONAL_FORM12);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 13:
	{
		CPersonalForm13* pView = (CPersonalForm13*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm13), IDD_PERSONAL_FORM13);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 14:
	{
		CPersonalForm14* pView = (CPersonalForm14*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm14), IDD_PERSONAL_FORM14);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 15:
	{
		CPersonalForm15* pView = (CPersonalForm15*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm15), IDD_PERSONAL_FORM15);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 16:
	{
		CPersonalForm16* pView = (CPersonalForm16*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm16), IDD_PERSONAL_FORM16);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 17:
	{
		CPersonalForm17* pView = (CPersonalForm17*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm17), IDD_PERSONAL_FORM17);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 18:
	{
		CPersonalForm18* pView = (CPersonalForm18*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm18), IDD_PERSONAL_FORM18);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 19:
	{
		CPersonalForm19* pView = (CPersonalForm19*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm19), IDD_PERSONAL_FORM19);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 20:
	{
		CPersonalForm20* pView = (CPersonalForm20*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm20), IDD_PERSONAL_FORM20);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
		return 0;
	}
}


afx_msg LRESULT CMainFrame::OnShowPersonalSummary(WPARAM wParam, LPARAM lParam)
{
		CString *folder = (CString *)wParam, *file = (CString *)lParam;
		m_wndPaneShortcut.m_strCurrentFolder.Format(_T("%s"), *folder); //delete folder;
		m_wndPaneShortcut.m_strCurrentFile.Format(_T("%s"), *file); //delete file;

		CPersonalSummary* pView = (CPersonalSummary*)CreatePersonalForm(RUNTIME_CLASS(CPersonalSummary), IDD_PERSONAL_SUMMARY);
		pView->m_strCurrentFolder.Format(_T("%s"), *folder);
		pView->m_strCurrentFile.Format(_T("%s"), *file);
		//::PostMessage(pView->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, wParam, lParam);

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

	//////////////////////////////////////
	//考虑把其他的窗口的关闭,销毁

	return 0;
}
