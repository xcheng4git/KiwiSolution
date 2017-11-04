// PaneShortcut.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "KiwiSdiExec.h"
#include "PaneShortcut.h"
#include "afxdialogex.h"

#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

#include "DlgNewFolder.h"
#include "DlgNewFile.h"
#include "DlgNewForm.h"

// CPaneShortcut 对话框
static UINT listIcons[] =
{
	IDI_MY_DOCUMENTS,
	IDI_CONTACTS,
	IDI_NOTES,
	IDI_DELETED_ITEMS
};

IMPLEMENT_DYNAMIC(CPaneShortcut, CDialogEx)

CPaneShortcut::CPaneShortcut(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaneShortcut::IDD, pParent)
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK | ILC_COLOR32, 1, 1);

	for (int i = 0; i < _countof(listIcons); i++)
	{


		HICON hIcon = AfxGetApp()->LoadIcon(listIcons[i]);
		ASSERT(hIcon);

		m_ilTreeIcons.Add(hIcon);
	}

	m_strCurrentFolder.Empty(); m_strCurrentFile.Empty(); m_bClicked = false;
}

CPaneShortcut::~CPaneShortcut()
{
}

void CPaneShortcut::InvokeNewFolderDialog()
{
	CDlgNewFolder dlg;
	dlg.DoModal();
}

void CPaneShortcut::InvokeNewFileDialog()
{
	CDlgNewFile dlg;
	dlg.SetCurrentFolderName(m_strCurrentFolder);
	dlg.DoModal();
}

void CPaneShortcut::InvokeNewFormDialog()
{
	CDlgNewForm dlg;
	dlg.m_strCurrentFolder = m_strCurrentFolder;
	dlg.m_strCurrentFile = m_strCurrentFile;
	dlg.DoModal();
}

void CPaneShortcut::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHORTCUT, m_listShortcut);
}


void CPaneShortcut::DoDeleteFile()
{
	//AfxMessageBox(_T("delete file")); return;
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

#if 0
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();
	vector<vector<wchar_t*>>::iterator itFormByTables = pDoc->m_vvFormByTables.begin();

	while (itFormByTables != pDoc->m_vvFormByTables.end()) {
		vector<wchar_t*>::const_iterator itcFormByTables = itFormByTables->begin();

		itcFormByTables++; itcFormByTables++;
		while (itcFormByTables != itFormByTables->end()) {
			ss.str(""); ss.clear();
			ss << "delete from " << CW2A((wchar_t*)*itcFormByTables, CP_UTF8) << "where file_id=" << file_id << ";";
			help->execSQL(ss.str().c_str());

			itcFormByTables++;
		}

		itFormByTables++;
	}
	ss.str(""); ss.clear();
	ss << "delete from orgnization_file where file_id=" << file_id << "';";
	help->execSQL(ss.str().c_str());
#else
	ss.str(""); ss.clear();
	ss << "update orgnization_file set del_status=1 where file_id=" << file_id << "';";
	help->execSQL(ss.str().c_str());
#endif

	help->closeDB(); delete help;
	ss.str(""); ss.clear();

}

void CPaneShortcut::DoDeleteFolder()
{
	//AfxMessageBox(_T("delete folder."));  return;

	stringstream ss;
	ss << "select file_id from orgnization_file where folder_name='" <<	CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	
	if (row < 1) {
		ss.str(""); ss.clear();
		ss << "delete from orgnization_folder where folder_name='" << CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
		help->closeDB(); delete help;
		ss.str(""); ss.clear();
		return;
	}

#if 0
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();
	vector<vector<wchar_t*>>::iterator itFormByTables = pDoc->m_vvFormByTables.begin();

	while (itFormByTables != pDoc->m_vvFormByTables.end()) {
		vector<wchar_t*>::const_iterator itcFormByTables = itFormByTables->begin();

		itcFormByTables++; itcFormByTables++;
		while (itcFormByTables != itFormByTables->end()) {
			for (int r = 0; r < row; r++) {
				int file_id = atoi(re[(r + 1)*col + 0]);

				ss.str(""); ss.clear();
				ss << "delete from " << CW2A((wchar_t*)*itcFormByTables, CP_UTF8) << "where file_id=" << file_id << ";";
				help->execSQL(ss.str().c_str());
			}

			itcFormByTables++;
		}

		itFormByTables++;
	}

	ss.str(""); ss.clear();
	ss << "delete from orgnization_file where folder_name='" << CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	help->execSQL(ss.str().c_str());

	ss.str(""); ss.clear();
	ss << "delete from orgnization_folder where folder_name='" << CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	help->execSQL(ss.str().c_str());
#else
	ss.str(""); ss.clear();
	ss << "update orgnization_file set del_status=1 where folder_name='" << CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	help->execSQL(ss.str().c_str());

	ss.str(""); ss.clear();
	ss << "update orgnization_folder set del_status=1 where folder_name='" << CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	help->execSQL(ss.str().c_str());
#endif

	help->closeDB(); delete help;
	ss.str(""); ss.clear();
}

BEGIN_MESSAGE_MAP(CPaneShortcut, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHORTCUT, &CPaneShortcut::OnItemchangedListShortcut)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHORTCUT, &CPaneShortcut::OnClickListShortcut)
END_MESSAGE_MAP()


// CPaneShortcut 消息处理程序


BOOL CPaneShortcut::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//return true;
	// TODO:  在此添加额外的初始化
	m_listShortcut.SetImageList(&m_ilTreeIcons, LVSIL_SMALL);
	m_listShortcut.InsertColumn(0, _T("Column One"), LVCFMT_LEFT, 125);
	m_listShortcut.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);

	int iItem=0;
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 0;
		lvitem.pszText = _T("1、新增单位");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 1;
		lvitem.pszText = _T("2、新增人员");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 2;
		lvitem.pszText = _T("3、新建廉政档案");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 3;
		lvitem.pszText = _T("4、删除单位或人员");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	CFont font1; font1.CreateFontIndirect(&lf);
	m_listShortcut.SetFont(&font1); font1.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CPaneShortcut::OnItemchangedListShortcut(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	return;
	/*
	int row = m_listShortcut.GetNextItem(-1, LVIS_SELECTED);

	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(action), 0l);
	*/
}

void CPaneShortcut::OnClickListShortcut(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CRect rt;
	int nCount = m_listShortcut.GetItemCount();
	for (int i = 0; i < nCount; i++) {
		m_listShortcut.GetItemRect(i, &rt, LVIR_BOUNDS);
		if (rt.PtInRect(pNMItemActivate->ptAction)) {
			CString strText = m_listShortcut.GetItemText(i, -1);
			int action = _ttoi(strText.Left(1));

			switch (action) {
			case 1:
				InvokeNewFolderDialog();
				break;
			case 2:
				if (!m_strCurrentFolder.IsEmpty())
					InvokeNewFileDialog();
				else
					MessageBox(_T("请先选中单位，再新建人员"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
				break;
			case 3:
				if (!m_strCurrentFile.IsEmpty())
					InvokeNewFormDialog();
				else
					MessageBox(_T("请先选中人员，再新建档案"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
				break;
			case 4:
				if (!m_strCurrentFile.IsEmpty()) {
					int ok1 = MessageBox(_T("删除人员：") + m_strCurrentFile + _T(" 将同时删除其所有廉政档案！"), _T("《廉政档案管理系统》"), MB_ICONWARNING | IDOK);
					if (ok1 == IDOK) {
						DoDeleteFile();

						CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
						::PostMessage(pWnd->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
					}
				}
				else if (!m_strCurrentFolder.IsEmpty()){
					int ok1 = MessageBox(_T("删除部门：") + m_strCurrentFolder + _T(" 将同时删除该部门所有人员及其廉政档案！"), _T("《廉政档案管理系统》"), MB_ICONWARNING | IDOK );
					if (ok1 == IDOK) {
						DoDeleteFolder();

						CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
						::PostMessage(pWnd->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
					}
				}
				break;
			}

		}
	}
}
