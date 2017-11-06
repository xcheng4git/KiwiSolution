// PaneOrgnization.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PaneOrgnization.h"
#include "afxdialogex.h"

#include "MainFrm.h"

#include "SQLiteHelper.h"

static UINT treeIcons[] =
{
	IDI_MY_DOCUMENTS,
	IDI_CONTACTS
};

// CPaneOrgnization 对话框

IMPLEMENT_DYNAMIC(CPaneOrgnization, CDialogEx)

CPaneOrgnization::CPaneOrgnization(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaneOrgnization::IDD, pParent)
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK | ILC_COLOR32, 1, 1);

	for (int i = 0; i < _countof(treeIcons); i++)
	{


		HICON hIcon = AfxGetApp()->LoadIcon(treeIcons[i]);
		ASSERT(hIcon);

		m_ilTreeIcons.Add(hIcon);
	}

	m_strCurrentFile.Empty(); m_strCurrentFolder.Empty(); m_bClicked = false;
}

CPaneOrgnization::~CPaneOrgnization()
{
}

void CPaneOrgnization::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ORGNIZATION, m_treeOrignization);
}


BEGIN_MESSAGE_MAP(CPaneOrgnization, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ORGNIZATION, &CPaneOrgnization::OnSelchangedTreeOrgnization)
	ON_MESSAGE(WM_UPDATE_ORGNIZATION, &CPaneOrgnization::OnUpdateOrgnization)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ORGNIZATION, &CPaneOrgnization::OnClickTreeOrgnization)
	ON_BN_CLICKED(IDC_BUTTON_TEST_FORM, &CPaneOrgnization::OnClickedButtonTestForm)
END_MESSAGE_MAP()


// CPaneOrgnization 消息处理程序

BOOL CPaneOrgnization::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// TODO:  在此添加额外的初始化
	m_treeOrignization.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);
	//HTREEITEM hItem = m_treeOrignization.InsertItem(_T("部门1"), 0, 0);
	//m_treeOrignization.InsertItem(_T("张三"), 1, 1, hItem);
	//m_treeOrignization.Expand(hItem, TVE_EXPAND);

	//hItem = m_treeOrignization.InsertItem(_T("部门2"), 0, 0);
	//m_treeOrignization.InsertItem(_T("李四"), 1, 1, hItem);

	OnUpdateOrgnization(0l, 0l);

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("黑体"), 3); lf.lfWeight = 400;
	CFont font1; font1.CreateFontIndirect(&lf);
	m_treeOrignization.SetFont(&font1); 
	
	//m_treeOrignization.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	GetDlgItem(IDC_STATIC_CURSELECTION)->SetFont(&font1);
	font1.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPaneOrgnization::OnSelchangedTreeOrgnization(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	if (!m_bClicked) return;
	HTREEITEM hItem = m_treeOrignization.GetSelectedItem();
	HTREEITEM hItemParent = m_treeOrignization.GetParentItem(hItem);
	if (hItemParent != NULL) {
		m_strCurrentFolder = m_treeOrignization.GetItemText(hItemParent);
		m_strCurrentFile = m_treeOrignization.GetItemText(hItem); m_bClicked = false;
		CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

		GetDlgItem(IDC_STATIC_CURSELECTION)->SetWindowText(m_strCurrentFolder + _T("\\") + m_strCurrentFile);
	}
	else
	{
		m_strCurrentFolder = m_treeOrignization.GetItemText(hItem);
		m_strCurrentFile.Empty(); m_bClicked = false;
		CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));

		GetDlgItem(IDC_STATIC_CURSELECTION)->SetWindowText(m_strCurrentFolder + _T("\\*"));
	}
}


afx_msg LRESULT CPaneOrgnization::OnUpdateOrgnization(WPARAM wParam, LPARAM lParam)
{
	m_treeOrignization.DeleteAllItems(); m_bClicked = false;

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select * from orgnization_folder where del_status=0";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

	char *folder_id, *folder_name;
	for (int r = 1; r <= row; r++) {
		folder_id = re[r*col + 0]; folder_name = re[r*col + 1];
		m_treeOrignization.InsertItem(CA2W(folder_name, CP_UTF8), 0, 0);
	}

	char sql2[500];
	HTREEITEM hItemParent = m_treeOrignization.GetFirstVisibleItem();
	while (hItemParent != NULL) {
		USES_CONVERSION;
		sprintf_s(sql2, 500, "select * from orgnization_file where folder_name='%s' and del_status=0", G2U(W2A(m_treeOrignization.GetItemText(hItemParent))));
		re = help->rawQuery(sql2, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		char *file_id, *file_name;
		for (int r = 1; r <= row; r++) {
			file_id = re[r*col + 0]; file_name = re[r*col + 1];

			m_treeOrignization.InsertItem(CA2W(file_name, CP_UTF8), 1, 1, hItemParent);
		}

		hItemParent = m_treeOrignization.GetNextVisibleItem(hItemParent);
	}

	help->closeDB();
	delete help;

	if (!m_strCurrentFolder.IsEmpty()) {
		HTREEITEM hItemParent = m_treeOrignization.FindItem(m_strCurrentFolder.GetBuffer());
		if (hItemParent != NULL) {
			m_treeOrignization.SelectItem(hItemParent);
			m_treeOrignization.Expand(hItemParent, TVE_EXPAND);
		}

	}
	return 0;
}


void CPaneOrgnization::OnClickTreeOrgnization(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	m_bClicked = true;

	CRect rt;
	HTREEITEM hItem = m_treeOrignization.GetSelectedItem();
	HTREEITEM hItemParent = m_treeOrignization.GetParentItem(hItem);
	if (hItemParent != NULL) {
		m_treeOrignization.GetItemRect(hItem, &rt, FALSE);
		CPoint pt; GetCursorPos(&pt); m_treeOrignization.ScreenToClient(&pt);
		//UINT uFlags;  HTREEITEM hClickedItem = m_treeOrignization.HitTest(pt, &uFlags);
		if (rt.PtInRect(pt)) {
			m_strCurrentFolder = m_treeOrignization.GetItemText(hItemParent);
			m_strCurrentFile = m_treeOrignization.GetItemText(hItem); m_bClicked = false;
			CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));
		}
	}
}



void CPaneOrgnization::OnClickedButtonTestForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, 1l, LPARAM(new CString(_T("天下为公/孙中山"))));
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, 8, LPARAM(new CString(_T("天下为公/孙中山"))));
}
