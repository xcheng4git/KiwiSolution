// DlgNewForm.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgNewForm.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include "MainFrm.h"

// CDlgNewForm 对话框

IMPLEMENT_DYNAMIC(CDlgNewForm, CDialogEx)

CDlgNewForm::CDlgNewForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewForm::IDD, pParent)
{

}

CDlgNewForm::~CDlgNewForm()
{
}

void CDlgNewForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FORM_TYPE, m_listFormType);
}


BEGIN_MESSAGE_MAP(CDlgNewForm, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewForm 消息处理程序


BOOL CDlgNewForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listFormType.DeleteAllItems();

	m_listFormType.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_listFormType.InsertColumn(1, _T("廉政档案名称"), LVCFMT_LEFT, 250);
	m_listFormType.InsertColumn(2, _T("说明"), LVCFMT_LEFT, 100);
	m_listFormType.InsertColumn(3, _T("ID"), LVCFMT_LEFT, 0);


	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select type_serial, type_name, type_description, type_id from form_type";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

	int iItem = 0;
	char *type_serial, *type_name, *type_description, *type_id;
	for (int r = 1; r <= row; r++) {
		type_serial = re[r*col + 0]; type_name = re[r*col + 1]; type_description = re[r*col + 2]; type_id = re[r*col + 3];
		m_listFormType.InsertItem(iItem, CA2W(type_serial, CP_UTF8));
		m_listFormType.SetItem(iItem, 1, LVIF_TEXT, CA2W(type_name, CP_UTF8), 0, NULL, NULL, NULL);
		m_listFormType.SetItem(iItem, 2, LVIF_TEXT, CA2W(type_description, CP_UTF8), 0, NULL, NULL, NULL);
		m_listFormType.SetItem(iItem, 3, LVIF_TEXT, CA2W(type_id, CP_UTF8), 0, NULL, NULL, NULL);

		iItem++;
	}

	help->closeDB();
	delete help;

	m_listFormType.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT | LVS_EX_FULLROWSELECT);
	m_listFormType.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	
	HWND hWndHeader = m_listFormType.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.FreezeColumn(3);
	m_header.SetTheme(new CXTPHeaderCtrlThemeOffice2003());

	//UpdateData(false);
	CString title; title.Format(_T("%s    -    \t新建廉政档案"), m_strCurrentFile);
	SetWindowText(title.GetBuffer());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgNewForm::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();

	int row = m_listFormType.GetNextItem(-1, LVIS_SELECTED);
	int type_id = _ttoi(m_listFormType.GetItemText(row, 3));

	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(type_id), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));

	CDialogEx::OnOK();
}
