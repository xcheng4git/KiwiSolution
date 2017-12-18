// PersonalForm28.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm28.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm28

IMPLEMENT_DYNCREATE(CPersonalForm28, CFormView)

CPersonalForm28::CPersonalForm28()
	: CFormView(CPersonalForm28::IDD)
{
	m_FormID = 28;
	int parameters1[1][25] = { { IDC_EDIT2, IDC_EDIT348, IDC_EDIT349, IDC_EDIT354, IDC_EDIT352, IDC_EDIT355, IDC_EDIT356, 
		IDC_DATETIMEPICKER2, IDC_EDIT358, IDC_EDIT359, IDC_EDIT360,
		IDC_DATETIMEPICKER46, IDC_EDIT361, IDC_EDIT369, IDC_EDIT363, IDC_EDIT362, 
		IDC_DATETIMEPICKER1, 
		IDC_DATETIMEPICKER45, IDC_EDIT364, IDC_COMBO4, 
		IDC_DATETIMEPICKER47, IDC_EDIT368, IDC_EDIT365, IDC_EDIT366, IDC_EDIT367 } };
	int structure1[27] = { 1, 25, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, 
		DATEPKR, EDITBX, EDITBX, EDITBX,
		DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX, 
		DATEPKR, 
		DATEPKR, EDITBX, EDITBX, 
		DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 25; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 27; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[26] = { _T("有无"), _T("姓名"), _T("性别"), _T("身份证号码"), _T("单位"), _T("职务"), 
		_T("问题摘要"), _T("问题线索来源"), _T("问题线索受理时间"), _T("问题线索来源单位"), _T("调查情况"),
		_T("承办单位"), _T("办结时间"), _T("属实程度"), _T("存在问题类型"),_T("处理机关"),
		_T("处理文号"), _T("处分起始时间"), _T("处分终止时间"), _T("处分情况"), _T("是否立案"),
		_T("立案时间"), _T("四种形态类型"), _T("通报曝光情况"), _T("通报曝光类型"), _T("通报曝光范围") };
	int structure10[26] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure11[3 + 1 + 25] = { -1, 1, 25, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 26; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);


	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm28::~CPersonalForm28()
{
}

void CPersonalForm28::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm28, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm28::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm28::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm28::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm28::OnBnClickedCmdUpdateForm)
	ON_CBN_SETFOCUS(IDC_COMBO3, &CPersonalForm28::OnSetfocusCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &CPersonalForm28::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm28::OnBnClickedCmdNextForm)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CPersonalForm28::OnCbnSelchangeCombo4)
END_MESSAGE_MAP()


// CPersonalForm28 诊断

#ifdef _DEBUG
void CPersonalForm28::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm28::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm28::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm28::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm28::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm28::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm28::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm28::hasData(int isub, int irow)
{
	CString strText;

	if ((isub == 1) || (isub == 2)){
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}

void CPersonalForm28::InitFourType()
{
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);

	pCombo1->SetWindowTextW(_T(""));
	while (pCombo1->GetCount()) pCombo1->DeleteString(0);
	pCombo2->SetWindowTextW(_T(""));
	while (pCombo2->GetCount()) pCombo2->DeleteString(0);

	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	ss << "select * from four_punish_category where first_category=-1";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

	int nIndx = pCombo1->AddString(_T("")); pCombo1->SetItemData(nIndx, (DWORD)-1);
	for (int r = 1; r <= row; r++) {
		nIndx = pCombo1->AddString(CA2W(re[r*col + 2], CP_UTF8));
		pCombo1->SetItemData(nIndx, (DWORD)atoi(re[r*col + 0]));
	}
}

// CPersonalForm28 消息处理程序


void CPersonalForm28::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO4);
	int nItem = pCombo->GetCurSel();
	if (nItem == 0) {
		GetDlgItem(IDC_EDIT368)->SetWindowTextW(_T("-1"));
	}
	else {
		CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);
		if (pCombo2->IsWindowVisible()) {
			int nIndx = pCombo2->GetCurSel();
			if (nIndx == -1) {
				MessageBox(_T("请确认四种形态是否选择正确！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
				return;
			}
			CString strText;
			strText.Format(_T("%d"), pCombo2->GetItemData(nIndx));
			GetDlgItem(IDC_EDIT368)->SetWindowTextW(strText);
		}
	}

	DoSaveForm();

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm28::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();

	help->closeDB(); delete help;


	ss.str(""); ss.clear();
	//ss << "select * from file_invertigated_form_13 where file_id=" << file_id << " limit 0,1;";
	ss << "select f.file_id,f.form_recid,f.file_name,f.file_gender,f.file_idcard,f.file_unit,f.file_position,";
	ss << " f.[acceptance_summary], f.acceptance_source, f.accepted_date, f.acceptance_source_file, f.[inverstigation_summary], ";
	ss << " f.inverstigation_unit, f.[inverstigated_date], f.inverstigation_fact, f.clearing_summary, f.clearing_unit, ";
	ss << " f.clearing_docno, f.clearing_punish_start_date, f.clearing_punish_end_date, f.clearing_memo, f.[clearing_isregister], f.[clearing_register_date], ";
	
	//ss << "  (select b.category_name from four_punish_category as a inner join four_punish_category as b ";
	//ss << " on a.[first_category] = b.punish_id and a.punish_id=p.punish_id) || '" << CW2A(_T("——"), CP_UTF8) << "' || p.category_name as punish_category_name, ";
	//ss << " f.clearing_public, f.[clearing_public_type], f.[clearing_public_degree] from file_invertigated_form_13 as f inner join four_punish_category as p ";
	//ss << " on f.clearing_four_xt = p.[punish_id] where f.file_id = " << file_id << " limit 0, 1; ";

	ss << " case f.clearing_four_xt when -1 then '" << CW2A(_T("否"), CP_UTF8) << "' else ";
	ss << " (select b.category_name || '" << CW2A(_T("——"), CP_UTF8) << "' || a.category_name from four_punish_category as a inner join four_punish_category as b";
	ss << " on a.[first_category] = b.punish_id and a.punish_id=f.clearing_four_xt) ";
	ss << " end as punish_category_name, ";
	ss << " f.clearing_public, f.[clearing_public_type], f.[clearing_public_degree] from file_invertigated_form_13 as f where f.file_id = " << file_id << " limit 0, 1; ";
	_vSubformQueryString.push_back(ss.str());

	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表13.dotx")));
}


void CPersonalForm28::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}

void CPersonalForm28::OnBnClickedCmdUpdateForm()
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO4);
	int nItem = pCombo->GetCurSel();
	if (nItem == 0) {
		GetDlgItem(IDC_EDIT368)->SetWindowTextW(_T("-1"));
	}
	else {
		CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);
		if (pCombo2->IsWindowVisible()) {
			int nIndx = pCombo2->GetCurSel();
			if (nIndx == -1) {
				MessageBox(_T("请确认四种形态是否选择正确！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
				return;
			}
			CString strText;
			strText.Format(_T("%d"), pCombo2->GetItemData(nIndx));
			GetDlgItem(IDC_EDIT368)->SetWindowTextW(strText);
		}
	}
	DoUpdateForm();
}


void CPersonalForm28::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	int i = 0;
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		while (itVVparameter != itVVVparameter->end()) {
			int j = 0;

			vector<int>::iterator itV = itVVparameter->begin();
			while (itV != itVVparameter->end()) {
				if ((_vvSubformStructure[i][2 + j] != RADIOBTN) && (_vvSubformStructure[i][2 + j] != ATTACHMENTBX)) {
					GetDlgItem(*itV)->SetFont(&m_fontEdit);
				}

				itV++; j++;
			}
			itVVparameter++;
		}
		itVVVparameter++; i++;
	}
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO4); pCombo->AddString(_T("是")); pCombo->AddString(_T("否"));
	
	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM3))->SetBitmap(m_bmpClose);
	DoShowForm();

	BOOL hasData = FALSE;
	vector<int>::iterator itHas = _vHaveDataSubform.begin();
	while (itHas != _vHaveDataSubform.end()) {
		if (*itHas != -1) {
			hasData = TRUE; break;
		}
		itHas++;
	}
	if (hasData) {
		CString strText;
		GetDlgItem(IDC_EDIT368)->GetWindowTextW(strText); strText.Trim();
		if (!strText.IsEmpty()) {
			stringstream ss;
			ss << "select b.[punish_id],a.[category_name] as first_category,b.[category_name] as second_category from four_punish_category as a left join four_punish_category as b on b.first_category=a.punish_id where b.first_category<>-1 and b.[punish_id]=";
			ss << CW2A(strText.GetBuffer(), CP_UTF8) << ";";
			TRACE(_T("\n%s"), CA2W(ss.str().c_str(), CP_UTF8));

			CSQLiteHelper *help = new CSQLiteHelper();
			help->openDB("kiwi.db3");
			int row, col;
			char *eee = "i"; char **result = &eee;
			char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
			if (row >= 1) {
				strText.ReleaseBuffer();
				strText.Format(_T("%s-%s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8),
					strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
				GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->SetWindowText(strText);
			}
		}
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}
	else {
		stringstream ss;
		ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
			CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		int row, col;
		char *eee = "i"; char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		int file_id = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select file_name, file_gender,file_IDCard,file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << file_id << ";";
		TRACE(CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			GetDlgItem(IDC_EDIT2)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
			GetDlgItem(IDC_EDIT348)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
			GetDlgItem(IDC_EDIT349)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
			GetDlgItem(IDC_EDIT354)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));
			GetDlgItem(IDC_EDIT352)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
		}
		help->closeDB(); delete help;

		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

		InitFourType();
	}
}


void CPersonalForm28::OnSetfocusCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);

	pCombo2->SetWindowTextW(_T(""));
	while (pCombo2->GetCount()) pCombo2->DeleteString(0);

	int nItem = pCombo1->GetCurSel();
	if (nItem != -1) {
		stringstream ss;
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");

		ss << "select * from four_punish_category where first_category=" << pCombo1->GetItemData(nItem) << ";";
		int row, col;
		char *eee = "i";
		char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

		for (int r = 1; r <= row; r++) {
			int nIndx = pCombo2->AddString(CA2W(re[r*col + 2], CP_UTF8));
			pCombo2->SetItemData(nIndx, (DWORD)atoi(re[r*col + 0]));
		}
	}
}


void CPersonalForm28::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

	InitFourType();
}


void CPersonalForm28::OnBnClickedCmdNextForm()
{
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(29), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}


void CPersonalForm28::OnCbnSelchangeCombo4()
{
	// TODO:  在此添加控件通知处理程序代码
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO4);
	int nItem = pCombo->GetCurSel();
	if (nItem == 0) {
		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_COMBO2)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_COMBO3)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(FALSE);
	}
	else {
		BOOL hasData = FALSE;
		vector<int>::iterator itHas = _vHaveDataSubform.begin();
		while (itHas != _vHaveDataSubform.end()) {
			if (*itHas != -1) {
				hasData = TRUE; break;
			}
			itHas++;
		}
		if (hasData) {
			CString strText;
			GetDlgItem(IDC_EDIT368)->GetWindowTextW(strText); strText.Trim();
			if (!strText.IsEmpty()) {
				stringstream ss;
				ss << "select b.[punish_id],a.[category_name] as first_category,b.[category_name] as second_category from four_punish_category as a left join four_punish_category as b on b.first_category=a.punish_id where b.first_category<>-1 and b.[punish_id]=";
				ss << CW2A(strText.GetBuffer(), CP_UTF8) << ";";
				TRACE(_T("\n%s"), CA2W(ss.str().c_str(), CP_UTF8));

				CSQLiteHelper *help = new CSQLiteHelper();
				help->openDB("kiwi.db3");
				int row, col;
				char *eee = "i"; char **result = &eee;
				char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
				if (row >= 1) {
					strText.ReleaseBuffer();
					strText.Format(_T("%s-%s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8),
						strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
					GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->SetWindowText(strText);
				}
			}
			GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
		}
		else {
			GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

			InitFourType();
		}
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO3)->EnableWindow(TRUE);
	}
}
