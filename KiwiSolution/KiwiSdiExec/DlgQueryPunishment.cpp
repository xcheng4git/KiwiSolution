// DlgQueryPunishment.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgQueryPunishment.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"
#include "Utility.h"

// CDlgQueryPunishment 对话框

IMPLEMENT_DYNAMIC(CDlgQueryPunishment, CDialogEx)

CDlgQueryPunishment::CDlgQueryPunishment(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgQueryPunishment::IDD, pParent)
{
	CBitmap bitmap;
	//VERIFY(bitmap.LoadBitmap(IDB_BITMAP_REPORT));
	// create the image list used by the report control.
	//if (m_ilIcons.Create(16, 15, ILC_COLOR24 | ILC_MASK, 0, 1))
	//	m_ilIcons.Add(&bitmap, RGB(255, 0, 255));

	VERIFY(bitmap.LoadBitmap(IDB_BITMAP_FOUR_XT));
	if (m_ilIcons.Create(16, 15, ILC_COLOR24 | ILC_MASK, 0, 1))
		m_ilIcons.Add(&bitmap, RGB(0, 255, 0));
}

CDlgQueryPunishment::~CDlgQueryPunishment()
{
}

void CDlgQueryPunishment::InitFourType()
{
	m_treeFourType.SetImageList(&m_ilIcons, TVSIL_NORMAL);

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select * from four_punish_category where first_category=-1";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

	for (int r = 1; r <= row; r++) {
		HTREEITEM hItem = m_treeFourType.InsertItem(CA2W(re[r*col + 2], CP_UTF8), 0, 0);
		m_treeFourType.SetItemData(hItem, (DWORD)atoi(re[r*col + 0]));
	}

	char sql2[500];
	HTREEITEM hItemParent = m_treeFourType.GetFirstVisibleItem();
	while (hItemParent != NULL) {
		sprintf_s(sql2, 500, "select * from four_punish_category where first_category=%d", m_treeFourType.GetItemData(hItemParent));
		re = help->rawQuery(sql2, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		for (int r = 1; r <= row; r++) {
			HTREEITEM hItem = m_treeFourType.InsertItem(CA2W(re[r*col + 2], CP_UTF8), atoi(re[r*col + 3]), atoi(re[r*col + 3]), hItemParent);
			m_treeFourType.SetItemData(hItem, (DWORD)atoi(re[r*col + 0]));
		}
		m_treeFourType.Expand(hItemParent, TVE_EXPAND);

		hItemParent = m_treeFourType.GetNextVisibleItem(hItemParent);
	}

	help->closeDB();
	delete help;

	

}

void CDlgQueryPunishment::ConsistentChildCheck(HTREEITEM hItem)
{
	BOOL bCheck = m_treeFourType.GetCheck(hItem);

	if (m_treeFourType.ItemHasChildren(hItem)) {
		HTREEITEM hChildItem = m_treeFourType.GetChildItem(hItem);
		while (hChildItem != NULL) {
			m_treeFourType.SetCheck(hChildItem, bCheck);

			hChildItem = m_treeFourType.GetNextItem(hChildItem, TVGN_NEXT);
		}

	}
}

void CDlgQueryPunishment::ConsistentParentCheck(HTREEITEM hItem)
{
	HTREEITEM hParentItem = m_treeFourType.GetParentItem(hItem);
	if (hParentItem != NULL) {
		m_treeFourType.SetCheck(hParentItem, TRUE);
		HTREEITEM hChildItem = m_treeFourType.GetChildItem(hParentItem);
		while (hChildItem != NULL) {
			if (m_treeFourType.GetCheck(hChildItem) == FALSE) {
				m_treeFourType.SetCheck(hParentItem, FALSE);
				break;
			}

			hChildItem = m_treeFourType.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}

string CDlgQueryPunishment::GenerateXingTaiWhere()
{
	stringstream ss;
	BOOL bChecked = FALSE;

	ss << " and file_id in (select file_id from file_invertigated_form_13 where clearing_four_xt in ( -1";

	HTREEITEM hParentItem = m_treeFourType.GetRootItem();
	//HTREEITEM hParentItem = m_treeFourType.GetFirstVisibleItem();
	while (hParentItem != NULL) {
		if (m_treeFourType.ItemHasChildren(hParentItem)) {
			HTREEITEM hChildItem = m_treeFourType.GetChildItem(hParentItem);
			while (hChildItem != NULL) {
				if (m_treeFourType.GetCheck(hChildItem) == TRUE) {
					bChecked = TRUE;
					ss << "," << m_treeFourType.GetItemData(hChildItem);
				}

				hChildItem = m_treeFourType.GetNextItem(hChildItem, TVGN_NEXT);
			}
		}

		//hParentItem = m_treeFourType.GetNextVisibleItem(hParentItem);
		hParentItem = m_treeFourType.GetNextSiblingItem(hParentItem);
	}

	if (bChecked)
		ss << ")) ";
	else
		ss.str("");

	return ss.str();
}

void CDlgQueryPunishment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeFourType);
	DDX_Control(pDX, IDC_LIST1, m_listFiles);
	DDX_Control(pDX, IDC_COMBO_FILE, m_comboFiles);
	DDX_Control(pDX, IDC_COMBO_FOLDER, m_combo_Folders);
}


BEGIN_MESSAGE_MAP(CDlgQueryPunishment, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgQueryPunishment::OnClickedButtonSearch)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDlgQueryPunishment::OnSelchangedTree1)
	ON_CBN_SETFOCUS(IDC_COMBO_FILE, &CDlgQueryPunishment::OnSetfocusComboFile)
	ON_CBN_DROPDOWN(IDC_COMBO_FOLDER, &CDlgQueryPunishment::OnDropdownComboFolder)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDlgQueryPunishment::OnClickTree1)
END_MESSAGE_MAP()


// CDlgQueryPunishment 消息处理程序


void CDlgQueryPunishment::OnClickedButtonSearch()
{
	m_listFiles.DeleteAllItems();


	stringstream ss;

	ss << "select file_id,file_name, file_work_unit, file_current_position,file_birth_date,file_date_4_position from file_form_01 where 1=1 ";
	CString strText;
	int nItem = m_comboFiles.GetCurSel();
	if (nItem != -1)
		ss << " and file_id=" << m_comboFiles.GetItemData(nItem);
	else {
		m_combo_Folders.GetWindowTextW(strText); strText.Trim();
		if (!strText.IsEmpty()) {
			ss << " and file_id in (select file_id from orgnization_file where folder_name=";
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')";
		}
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_START))->GetCheck()) {
		GetDlgItem(IDC_DATETIMEPICKER_START)->GetWindowTextW(strText);
		COleDateTime t; t.ParseDateTime(strText);
		ss << " and file_id in (select file_id from file_invertigated_form_13 where clearing_punish_start_date<=";
		ss << "'" << t.GetYear() << "-" << t.GetMonth() << "-" << t.GetDay() << "'";
		ss << ") ";
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_END))->GetCheck() || ((CButton*)GetDlgItem(IDC_CHECK_NOTFULL))->GetCheck()) {
		GetDlgItem(IDC_DATETIMEPICKER_END)->GetWindowTextW(strText);
		COleDateTime t; t.ParseDateTime(strText);
		ss << " and file_id in (select file_id from file_invertigated_form_13 where clearing_punish_end_date>=";
		ss << "'" << t.GetYear() << "-" << t.GetMonth() << "-" << t.GetDay() << "'";
		ss << ") ";
	}

	//////////////////////////////////////////////
	//加入四种形态条件
	ss << GenerateXingTaiWhere();

	ss << ";";
	TRACE(_T("\n%s"), CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");


	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

	if (row < 1) {
		help->closeDB(); delete help;
		return;
	}

	vector<int> file_ids;
	for (int r = 0; r < row; r++) {
		file_ids.push_back(atoi(re[(r + 1)*col + 0]));

		CString str;
		str.Format(_T("%d"), r + 1);
		m_listFiles.InsertItem(r, str);
		
		m_listFiles.SetItem(r, 2, LVIF_TEXT, CA2W(re[(r + 1) * col + 1], CP_UTF8), 0, NULL, NULL, NULL);

		str.ReleaseBuffer(); str.Format(_T("%s %s"), strlen(re[(r + 1) * col + 2]) < 1 ? _T("") : CA2W(re[(r + 1) * col + 2], CP_UTF8), 
			strlen(re[(r + 1) * col + 3]) < 1 ? _T("") : CA2W(re[(r + 1) * col + 3], CP_UTF8));
		m_listFiles.SetItem(r, 3, LVIF_TEXT, str, 0, NULL, NULL, NULL);

		str.ReleaseBuffer();
		COleDateTime birthDate; birthDate.ParseDateTime(CA2W(re[(r + 1) * col + 4], CP_UTF8));
		COleDateTime curDate; curDate = COleDateTime::GetCurrentTime();
		int age = curDate.GetYear() - birthDate.GetYear();
		COleDateTime tt(curDate.GetYear(), birthDate.GetMonth(), birthDate.GetDay(), 0, 0, 0);
		if (curDate <= tt)
			str.Format(_T("%d"), age);
		else
			str.Format(_T("%d"), age + 1);
		m_listFiles.SetItem(r, 4, LVIF_TEXT, str, 0, NULL, NULL, NULL);

		m_listFiles.SetItem(r, 5, LVIF_TEXT, CA2W(re[(r + 1) * col + 5], CP_UTF8), 0, NULL, NULL, NULL);

	}
	for (int r = 0; r < file_ids.size(); r++) {
		ss.str(""); ss.clear();
		ss << "select file_WorkingState from file_form_02 where file_id=" << file_ids[r] << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if ( row >= 1)
			m_listFiles.SetItem(r, 1, LVIF_TEXT, CUtility::WorkingStatus2String(atoi(re[1 * col + 0])), 0, NULL, NULL, NULL);
		//else
		//	m_listFiles.SetItem(r, 1, LVIF_TEXT, _T("未填报"), 0, NULL, NULL, NULL);
	}

	help->closeDB(); delete help;
}


void CDlgQueryPunishment::OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CDlgQueryPunishment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
#pragma region Init_ComboFolder

	m_combo_Folders.AddString(_T(""));

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

		m_combo_Folders.AddString(CA2W(folder_name, CP_UTF8));
	}

	help->closeDB(); delete help;
#pragma endregion

	InitFourType();

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	CFont font1; font1.CreateFontIndirect(&lf);
	m_listFiles.SetFont(&font1); font1.DeleteObject();

	CImageList   m_l;
	m_l.Create(1, 20, TRUE | ILC_COLOR32, 1, 0);
	m_listFiles.SetImageList(&m_l, LVSIL_SMALL);

	m_listFiles.InsertColumn(0, _T(" "), LVCFMT_CENTER, 30);
	m_listFiles.InsertColumn(1, _T("状态"), LVCFMT_CENTER, 50);
	m_listFiles.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 80);
	m_listFiles.InsertColumn(3, _T("单位及职务"), LVCFMT_CENTER, 300);
	m_listFiles.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, 50);
	m_listFiles.InsertColumn(5, _T("任现职时间"), LVCFMT_CENTER, 150);
	m_listFiles.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgQueryPunishment::OnSetfocusComboFile()
{
	//m_comboFiles.SetWindowTextW(_T(""));
	//while (m_comboFiles.GetCount()) m_comboFiles.DeleteString(0);

	// TODO:  在此添加控件通知处理程序代码
	CString strText;
	m_combo_Folders.GetWindowTextW(strText); strText.Trim();
	if (!strText.IsEmpty()) {
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");

		stringstream ss;
		ss << "select * from orgnization_file where folder_name = ";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' and  del_status = 0;";
		int row, col;
		char *eee = "i";
		char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

		char *folder_id, *folder_name;
		for (int r = 1; r <= row; r++) {
			int nItem = m_comboFiles.AddString(CA2W(re[r*col + 1], CP_UTF8));
			m_comboFiles.SetItemData(nItem, atoi(re[r*col + 0]));
		}

		help->closeDB(); delete help;
	}
}

void CDlgQueryPunishment::OnDropdownComboFolder()
{
	// TODO:  在此添加控件通知处理程序代码
	m_comboFiles.SetWindowTextW(_T(""));
	while (m_comboFiles.GetCount()) m_comboFiles.DeleteString(0);
}


void CDlgQueryPunishment::OnClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	CPoint oPoint;
	UINT nFlag;
	GetCursorPos(&oPoint);
	m_treeFourType.ScreenToClient(&oPoint);
	HTREEITEM oSelectItem = m_treeFourType.HitTest(oPoint, &nFlag);
	if (oSelectItem == NULL)
		return;

	m_treeFourType.SelectItem(oSelectItem);

	if (nFlag& TVHT_ONITEMSTATEICON) {
		BOOL bCheck = !m_treeFourType.GetCheck(oSelectItem);
		m_treeFourType.SetCheck(oSelectItem, bCheck);

		ConsistentChildCheck(oSelectItem);
		ConsistentParentCheck(oSelectItem);

		m_treeFourType.SetCheck(oSelectItem, !bCheck);
	}

	*pResult = 0;
}
