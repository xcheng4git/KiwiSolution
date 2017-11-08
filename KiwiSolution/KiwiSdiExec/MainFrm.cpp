
// MainFrm.cpp : CMainFrame ���ʵ��
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
#include "PersonalForm21.h"
#include "PersonalForm22.h"
#include "PersonalForm23.h"
#include "PersonalForm24.h"
#include "PersonalForm25.h"
#include "PersonalForm26.h"
#include "PersonalForm27.h"
#include "PersonalForm28.h"
#include "PersonalForm29.h"
#include "PersonalForm30.h"
#include "PersonalForm31.h"

#include "SplashWnd.h"

#include "DlgQueryBy.h"
#include "QueryByFolder.h"
#include "DlgBackupDatabase.h"
#include "DlgNewUser.h"

#include "SQLiteHelper.h"
#include <sstream>
using namespace std;


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
	//ON_COMMAND(ID_QUERY_BY_FOLDER, &CMainFrame::OnQueryByFolder)
	ON_MESSAGE(WM_MODIFY_PERSONAL_FORM, &CMainFrame::OnModifyPersonalForm)
	ON_COMMAND(ID_DATABASE_INITIAL, &CMainFrame::OnDatabaseInitial)
	ON_COMMAND(ID_DATABASE_BACKUP, &CMainFrame::OnDatabaseBackup)
	ON_COMMAND(ID_TOOL_NEW_USER, &CMainFrame::OnToolNewUser)
	ON_COMMAND(ID_QUERY_BY_POSITION, &CMainFrame::OnQueryByPosition)
	ON_COMMAND(ID_QUERY_BY_PARTY, &CMainFrame::OnQueryByParty)
	ON_COMMAND(ID_QUERY_BY_HANDIN_FORM, &CMainFrame::OnQueryByHandinForm)
	ON_COMMAND(ID_QUERY_BY_FORM, &CMainFrame::OnQueryByForm)
	ON_COMMAND(ID_QUERY_BY_PUNISH, &CMainFrame::OnQueryByPunish)
	ON_COMMAND(ID_QUERY_BY_DEGREE, &CMainFrame::OnQueryByDegree)
	ON_COMMAND(ID_QUERY_BY_AGE, &CMainFrame::OnQueryByAge)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
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
		IDD_PANE_ORGNIZATION, CRect(0, 0, 240, 380), xtpPaneDockLeft);
	paneOrgnization->SetOptions(xtpPaneNoCloseable | xtpPaneNoFloatable | xtpPaneNoDockable | xtpPaneNoHideable);
	paneOrgnization->SetMaxTrackSize(CSize(240, 380)); paneOrgnization->SetMinTrackSize(CSize(240, 380));
	paneOrgnization->SetTitle(_T("������֯��������"));

	CXTPDockingPane* paneShortcut = m_paneManager.CreatePane(
		IDD_PANE_SHORTCUT, CRect(0, 0, 240, 100), xtpPaneDockBottom, paneOrgnization);
	paneShortcut->SetOptions(xtpPaneNoCloseable | xtpPaneNoFloatable | xtpPaneNoDockable | xtpPaneNoHideable);
	paneShortcut->SetMaxTrackSize(CSize(240, 100)); paneShortcut->SetMinTrackSize(CSize(240, 100));
	paneShortcut->SetTitle(_T("������ݲ˵�����"));
	
	return 0;
}

CKiwiSdiExecDoc* CMainFrame::GetDocument()
{
	POSITION pos = theApp.GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = theApp.GetNextDocTemplate(pos);
	pos = pDocTemplate->GetFirstDocPosition();
	CKiwiSdiExecDoc* pDoc = (CKiwiSdiExecDoc*)pDocTemplate->GetNextDoc(pos);

	return pDoc;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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

// CMainFrame ��Ϣ�������

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
	case 21:
	{
		CPersonalForm21* pView = (CPersonalForm21*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm21), IDD_PERSONAL_FORM21);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 22:
	{
		CPersonalForm22* pView = (CPersonalForm22*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm22), IDD_PERSONAL_FORM22);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 23:
	{
		CPersonalForm23* pView = (CPersonalForm23*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm23), IDD_PERSONAL_FORM23);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 24:
	{
		CPersonalForm24* pView = (CPersonalForm24*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm24), IDD_PERSONAL_FORM24);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	case 25:
	{
		CPersonalForm25* pView = (CPersonalForm25*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm25), IDD_PERSONAL_FORM25);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 26:
	{
		CPersonalForm26* pView = (CPersonalForm26*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm26), IDD_PERSONAL_FORM26);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 27:
	{
		CPersonalForm27* pView = (CPersonalForm27*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm27), IDD_PERSONAL_FORM27);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 28:
	{
		CPersonalForm28* pView = (CPersonalForm28*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm28), IDD_PERSONAL_FORM28);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 29:
	{
		CPersonalForm29* pView = (CPersonalForm29*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm29), IDD_PERSONAL_FORM29);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 30:
	{
		CPersonalForm30* pView = (CPersonalForm30*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm30), IDD_PERSONAL_FORM30);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}	case 31:
	{
		CPersonalForm31* pView = (CPersonalForm31*)CreatePersonalForm(RUNTIME_CLASS(CPersonalForm31), IDD_PERSONAL_FORM31);
		pView->SetCurrentFile(*(CString *)lParam); delete (CString *)lParam;
		pView->OnInitialUpdate();
		return 0;

	}
	}

	return 0;
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
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_bFullscreen);

	
}


afx_msg LRESULT CMainFrame::OnShowDefaultSummary(WPARAM wParam, LPARAM lParam)
{
	if (lParam != NULL) {
		CString *folder = (CString *)lParam;
		m_wndPaneShortcut.m_strCurrentFolder.Format(_T("%s"), *folder); //delete folder;
		m_wndPaneShortcut.m_strCurrentFile.ReleaseBuffer();
		m_wndPaneShortcut.m_strCurrentFile = _T("");
	}
	CView* pView = CreatePersonalForm(RUNTIME_CLASS(CKiwiSdiExecView), IDD_KIWISDIEXEC_FORM);
	pView->OnInitialUpdate();

	//////////////////////////////////////
	//���ǰ������Ĵ��ڵĹر�,����

	return 0;
}


void CMainFrame::OnQueryByFolder()
{
	//CView* pView = CreatePersonalForm(RUNTIME_CLASS(CQueryByFolder), IDD_DIALOG_QUERY_BYFOLDER);
	//pView->OnInitialUpdate();

	//////////////////////////////////////
	//���ǰ������Ĵ��ڵĹر�,����
}


afx_msg LRESULT CMainFrame::OnModifyPersonalForm(WPARAM wParam, LPARAM lParam)
{
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	stringstream ss;
	ss << "select file_name, folder_name from orgnization_file where file_id=" << int(lParam) << ";";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�

	if (row < 1)
		return 0;

	CString folder; folder.Format(_T("%s"), CA2W(re[1 * col + 1], CP_UTF8));
	CString file; file.Format(_T("%s"), CA2W(re[1 * col + 0], CP_UTF8));
	::PostMessage(this->m_hWnd, WM_CREATE_PERSONAL_FORM, wParam, LPARAM(new CString(folder + _T("/") + file)));

	help->closeDB(); delete help;
	return 0;
}


void CMainFrame::OnDatabaseInitial()
{
	// TODO:  �ڴ���������������
	CKiwiSdiExecDoc* pDoc = GetDocument();
	if (pDoc->m_currentUserGroup != 0) {
		MessageBox(_T("�Բ����㲻�ǹ���Ա������ʹ�ø����"), _T("��������������ϵͳ��"), MB_ICONSTOP);
		return;
	}

	int ok1 = MessageBox(_T("��ȷ�ϳ�ʼ�����ݿ�ǰ���Ѿ����ݵ�ǰ���ݿ⣡"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION | IDOK);
	if (ok1 = IDOK) {
		int ok2 = MessageBox(_T("���ٴ�ȷ�ϳ�ʼ�����ݿ�ǰ���Ѿ����ݵ�ǰ���ݿ⣡"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION | IDOK);
		if (ok2 != IDOK)
			return;
		BOOL bRtc1 = DeleteFile(_T("kiwi.db3.temp")); BOOL bRtc2 = CopyFile(_T("kiwi.db3"), _T("kiwi.db3.temp"), FALSE);
		BOOL bRtc3 = DeleteFile(_T("kiwi.db3"));
		if (CopyFile(_T("kiwi.db3.init"), _T("kiwi.db3"), FALSE)) {
			MessageBox(_T("���ݿ��Ѿ���ʼ����"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);

			::PostMessage(this->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
		}
		else {
			if (bRtc3 && bRtc2) {
				MessageBox(_T("���ݿ��ʼ��ʧ�ܣ�ȷ�ϻָ����ݿ⣡"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
				if (CopyFile(_T("kiwi.db3.temp"), _T("kiwi.db3"), FALSE)) {
					MessageBox(_T("���ݿ�ָ��ɹ���"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
				} else
					MessageBox(_T("���ݿ�ָ�ʧ�ܣ����ֹ��ָ����ݿ⣬����ѯ����Ա��"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
			}
		}

	}
	else
		return;


	
}


void CMainFrame::OnDatabaseBackup()
{
	// TODO:  �ڴ���������������
	CDlgBackupDatabase dlgBackup;
	dlgBackup.DoModal();
}


void CMainFrame::OnToolNewUser()
{
	// TODO:  �ڴ���������������
	CKiwiSdiExecDoc* pDoc = GetDocument();
	if (pDoc->m_currentUserGroup != 0) {
		MessageBox(_T("�Բ����㲻�ǹ���Ա������ʹ�ø����"), _T("��������������ϵͳ��"), MB_ICONSTOP);
		return;
	}

	CDlgNewUser dlgUser;
	dlgUser.DoModal();
}


void CMainFrame::OnQueryByPosition()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_RANK;

	dlgQuery.DoModal();
}


void CMainFrame::OnQueryByParty()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_PARTY;

	dlgQuery.DoModal();
}


void CMainFrame::OnQueryByHandinForm()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_HANDIN_FORM;

	dlgQuery.DoModal();
}


void CMainFrame::OnQueryByForm()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_FORM;

	dlgQuery.DoModal();
}


void CMainFrame::OnQueryByPunish()
{
	// TODO:  �ڴ���������������

}


void CMainFrame::OnQueryByDegree()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_DEGREE;

	dlgQuery.DoModal();
}


void CMainFrame::OnQueryByAge()
{
	// TODO:  �ڴ���������������
	CDlgQueryBy dlgQuery;
	dlgQuery.m_queryType = CDlgQueryBy::QUERY_BY_AGE;

	dlgQuery.DoModal();
}
