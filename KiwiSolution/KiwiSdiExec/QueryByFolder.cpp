// QueryByFolder.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "QueryByFolder.h"
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

#include "Utility.h"

// CQueryByFolder

IMPLEMENT_DYNCREATE(CQueryByFolder, CFormView)

CQueryByFolder::CQueryByFolder()
	: CFormView(CQueryByFolder::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontText.CreateFontIndirect(&lf);

	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);
}

CQueryByFolder::~CQueryByFolder()
{
	m_fontText.DeleteObject();
	m_bmpClose.DeleteObject();
}

int CQueryByFolder::GetFilledFormNumber(int file_id)
{
	stringstream ss;

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;
	char *eee = "i";
	char **result = &eee;

	int iNum = 0;

	int iFlag = 0;
	ss.str(""); ss.clear();
	ss << "select count(*) from file_form_01 where file_id=" << file_id << ";";
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	iFlag = atoi(re[1 * col + 0]);
	iNum += iFlag;

	for (int i = 2; i <= 3; i++) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_" << setw(2) << i << " where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
		if (iFlag > 0) break;
	}
	iNum += iFlag;

	for (int i = 4; i <= 6; i++) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_" << setw(2) << i << " where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
		if (iFlag > 0) break;
	}
	iNum += iFlag;

	for (int i = 7; i <= 9; i++) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_" << setw(2) << i << " where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
		if (iFlag > 0) break;
	}
	iNum += iFlag;

	for (int i = 10; i <= 11; i++) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_" << setw(2) << i << " where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
		if (iFlag > 0) break;
	}
	iNum += iFlag;

	for (int i = 120; i <= 121; i++) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_" << setw(2) << i << " where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
		if (iFlag > 0) break;
	}
	iNum += iFlag;

	ss.str(""); ss.clear();
	ss << "select count(*) from file_form_121 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	iFlag = atoi(re[1 * col + 0]);
	if (iFlag <= 1) {
		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_13 where file_id=" << file_id << ";";
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		iFlag = atoi(re[1 * col + 0]);
	}
	iNum += iFlag;


	help->closeDB(); delete help;
	ss.str(""); ss.clear();

	return iNum;
}

void CQueryByFolder::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUERY_BYFOLDER, m_listQuery);
	DDX_Control(pDX, IDC_COMBO_FOLDERS, m_comboFolders);
}

BEGIN_MESSAGE_MAP(CQueryByFolder, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_BYFOLDER, &CQueryByFolder::OnBnClickedButtonQueryByfolder)
	ON_CBN_SELCHANGE(IDC_COMBO_FOLDERS, &CQueryByFolder::OnCbnSelchangeComboFolders)
	ON_WM_CTLCOLOR()
	ON_CBN_DROPDOWN(IDC_COMBO_FOLDERS, &CQueryByFolder::OnCbnDropdownComboFolders)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM, &CQueryByFolder::OnBnClickedButtonCloseForm)
END_MESSAGE_MAP()


// CQueryByFolder 诊断

#ifdef _DEBUG
void CQueryByFolder::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CQueryByFolder::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQueryByFolder 消息处理程序


void CQueryByFolder::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 700;
	CFont font1; font1 .CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_QUERY_HEADER)->SetFont(&font1); font1.DeleteObject();

	GetDlgItem(IDC_LIST_QUERY_BYFOLDER)->SetFont(&m_fontText);


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

		m_comboFolders.AddString(CA2W(folder_name, CP_UTF8));
	}

	help->closeDB(); delete help;

	m_listQuery.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, 100);
	m_listQuery.InsertColumn(1, _T("性别"), LVCFMT_LEFT, 50);
	m_listQuery.InsertColumn(2, _T("婚姻状态"), LVCFMT_LEFT, 100);
	m_listQuery.InsertColumn(3, _T("子女数"), LVCFMT_LEFT, 50);

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM))->SetBitmap(m_bmpClose);
}


void CQueryByFolder::OnBnClickedButtonQueryByfolder()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_comboFolders.GetCurSel() == -1) {
		GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_SHOW);
		return;
	}

	m_listQuery.DeleteAllItems();

	CString strText;
	m_comboFolders.GetLBText(m_comboFolders.GetCurSel(), strText);
	stringstream ss;
	ss << "select file_id, file_name from orgnization_file where folder_name='" << CW2A(strText.GetBuffer(), CP_UTF8) << "' and del_status=0;";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

	vector<int> file_ids; 
	for (int i = 0; i < row; i++) {
		file_ids.push_back(atoi(re[(i + 1) * col + 0]));
		m_listQuery.InsertItem(i, CA2W(re[(i + 1) * col + 1], CP_UTF8));
		
	}

	for (int i = 0; i < file_ids.size(); i++) {
		ss.str(""); ss.clear();
		ss << "select file_gender from file_form_01 where  file_id=" << file_ids[i] << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		if (row < 1) 
			m_listQuery.SetItem(i, 1, LVIF_TEXT, _T("未填报"), 0, NULL, NULL, NULL);
		else
			m_listQuery.SetItem(i, 1, LVIF_TEXT, CA2W(re[1 * col + 0], CP_UTF8), 0, NULL, NULL, NULL);

		ss.str(""); ss.clear();
		ss << "select file_MarriageStatus from file_form_03 where  file_id=" << file_ids[i] << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		if (row < 1) {
			m_listQuery.SetItem(i, 2, LVIF_TEXT, _T("未填报"), 0, NULL, NULL, NULL);
		}
		else {
			m_listQuery.SetItem(i, 2, LVIF_TEXT, CUtility::MarriageStatus2String(atoi(re[1 * col + 0])), 0, NULL, NULL, NULL);
		}

		ss.str(""); ss.clear();
		ss << "select count(*) from file_form_12_c where  file_id=" << file_ids[i] << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		m_listQuery.SetItem(i, 3, LVIF_TEXT, CA2W(re[1 * col + 0], CP_UTF8), 0, NULL, NULL, NULL);

	}
	file_ids.clear();
	help->closeDB(); delete help;
	ss.str(""); ss.clear();
}


void CQueryByFolder::OnCbnSelchangeComboFolders()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_HIDE);
}


HBRUSH CQueryByFolder::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ERROR_MSG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CQueryByFolder::OnCbnDropdownComboFolders()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_HIDE);
}


void CQueryByFolder::OnBnClickedButtonCloseForm()
{
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}
