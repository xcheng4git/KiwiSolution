// PersonalForm03.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm03.h"
#include <sstream>
#include <iomanip>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// PersonalForm03

IMPLEMENT_DYNCREATE(PersonalForm03, CFormView)

PersonalForm03::PersonalForm03()
: CFormView(PersonalForm03::IDD)
, m_Radio1_0(-1)
, m_Radio2_0(-1)
, m_Radio3_0(-1)
{
	m_FormID = 3;
	int parameters1[][5] = { { IDC_EDIT1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER3, IDC_EDIT4, IDC_EDIT5 },
	{ IDC_EDIT6, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER4, IDC_EDIT9, IDC_EDIT10 } };
	int structure1[7] = { 2, 5, EDITBX, DATEPKR, DATEPKR, EDITBX, EDITBX };

	int parameters2[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };
	int structure2[8] = { 3, 6, DATEPKR, DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX };

	int parameters3[][6] = { { IDC_EDIT33, IDC_EDIT35, IDC_DATETIMEPICKER11, IDC_DATETIMEPICKER12, IDC_EDIT37, IDC_EDIT38 },
	{ IDC_EDIT34, IDC_EDIT39, IDC_DATETIMEPICKER13, IDC_DATETIMEPICKER14, IDC_EDIT41, IDC_EDIT42 },
	{ IDC_EDIT36, IDC_EDIT40, IDC_DATETIMEPICKER15, IDC_DATETIMEPICKER16, IDC_EDIT43, IDC_EDIT44 } };
	int structure3[8] = { 3, 6, EDITBX, EDITBX, DATEPKR, DATEPKR, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 2; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure3[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[6] = { _T("有无"), _T("护照号"), _T("签发日期"), _T("有效期至"), _T("保管机构"), _T("备注") };
	int structure10[6] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure11[4+6] = { 1,2,5,2, 2,1, 1, 1, 1, 1 };

	const wchar_t *pBookmarks2[7] = { _T("有无"), _T("起止时间起"), _T("起止时间止"), _T("所到国家"), _T("事由"), _T("审批机构"), _T("所用护照号") };
	int structure20[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure21[4+7] = { 0,3,6,2, 2,1,1, 1, 1, 1, 1 };

	const wchar_t *pBookmarks3[7] = { _T("有无"), _T("证件名称"), _T("证件号码"), _T("起止时间起"), _T("起止时间止"), _T("保管机构"), _T("备注") };
	int structure30[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[4+7] = { 1,3,6,2, 2, 1,1, 1, 1, 1, 1 };

	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 6; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure30[i], pBookmarks3[i], structure31[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure21[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure31[i]);
	_vvSubformFlags.push_back(vStr);
}

PersonalForm03::~PersonalForm03()
{
	//m_fontEdit.DeleteObject();
	//m_bmpClose.DeleteObject();
}
//void PersonalForm03::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//
//	m_isModify = FALSE; for (int i = 0; i < 3; i++) m_modifiedSubform[i] = -1;
//}
void PersonalForm03::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio1_0);
	DDX_Radio(pDX, IDC_RADIO12, m_Radio2_0);
	DDX_Radio(pDX, IDC_RADIO13, m_Radio3_0);
}
#if 0

void PersonalForm03::QueryAndFillFileForm()
{
	int parameters1[][5] = { { IDC_EDIT1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER3, IDC_EDIT4, IDC_EDIT5 },
	{ IDC_EDIT6, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER4, IDC_EDIT9, IDC_EDIT10 } };

	int parameters2[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };

	int parameters3[][6] = { { IDC_EDIT33, IDC_EDIT35, IDC_DATETIMEPICKER11, IDC_DATETIMEPICKER12, IDC_EDIT37, IDC_EDIT38 },
	{ IDC_EDIT34, IDC_EDIT39, IDC_DATETIMEPICKER13, IDC_DATETIMEPICKER14, IDC_EDIT41, IDC_EDIT42 },
	{ IDC_EDIT36, IDC_EDIT40, IDC_DATETIMEPICKER15, IDC_DATETIMEPICKER16, IDC_EDIT43, IDC_EDIT44 } };

	BOOL haveRecords[3] = { TRUE, TRUE, TRUE };
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	std::vector<CString> vSubformRecid;

	ss.str(""); ss.clear();
	ss << "select * from file_form_04 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		GetDlgItem(parameters1[0][0])->SetWindowTextW(_T("无"));
		ss.str(""); ss.clear();
		goto ShowForm2_2;
	}

	for (int r = 0; r < (row>2 ? 2 : row); r++) {
		CString str; str.Format(_T("%s"), CA2W(re[(r+1) * col + 1], CP_UTF8));
		vSubformRecid.push_back(str);

		GetDlgItem(parameters1[r][0])->SetWindowTextW(CA2W(re[(r+1) * col + 2], CP_UTF8));
		COleDateTime t; t.ParseDateTime(CA2W(re[1 * col + 3], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters1[r][1]))->SetTime(t);
		t.ParseDateTime(CA2W(re[1 * col + 4], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters1[r][2]))->SetTime(t);
		GetDlgItem(parameters1[r][3])->SetWindowTextW(CA2W(re[(r + 1) * col + 5], CP_UTF8));
		GetDlgItem(parameters1[r][4])->SetWindowTextW(CA2W(re[(r + 1) * col + 6], CP_UTF8));
	}
	m_vvFormRecid.push_back(vSubformRecid); vSubformRecid.clear(); m_modifiedSubform[0] = 4;
	m_isModify = TRUE;


ShowForm2_2:

	ss.str(""); ss.clear();
	ss << "select * from file_form_05 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		haveRecords[1] = FALSE;
		ss.str(""); ss.clear();
		goto ShowForm3_1;
	}

	for (int r = 0; r < (row>3 ? 3 : row); r++) {
		CString str; str.Format(_T("%s"), CA2W(re[(r + 1) * col + 1], CP_UTF8));
		vSubformRecid.push_back(str);

		COleDateTime t; t.ParseDateTime(CA2W(re[(r + 1) * col + 2], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters2[r][0]))->SetTime(t);
		t.ParseDateTime(CA2W(re[(r + 1) * col + 3], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters2[r][1]))->SetTime(t);
		for (int j = 2; j < 6;j++)
			GetDlgItem(parameters2[r][j])->SetWindowTextW(CA2W(re[(r + 1) * col + j+2], CP_UTF8));
	}
	m_vvFormRecid.push_back(vSubformRecid); vSubformRecid.clear();  m_modifiedSubform[1] = 5;
	m_isModify = TRUE;

ShowForm3_1:
	ss.str(""); ss.clear();
	ss << "select * from file_form_06 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		GetDlgItem(parameters3[0][0])->SetWindowTextW(_T("无"));
		goto ShowEnd;
	}
	for (int r = 0; r < (row>3 ? 3 : row); r++) {
		CString str; str.Format(_T("%s"), CA2W(re[(r + 1) * col + 1], CP_UTF8));
		vSubformRecid.push_back(str);

		GetDlgItem(parameters3[r][0])->SetWindowTextW(CA2W(re[(r + 1) * col + 2], CP_UTF8));
		GetDlgItem(parameters3[r][1])->SetWindowTextW(CA2W(re[(r + 1) * col + 3], CP_UTF8));
		COleDateTime t; t.ParseDateTime(CA2W(re[(r + 1) * col + 4], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters3[r][2]))->SetTime(t);
		t.ParseDateTime(CA2W(re[(r + 1) * col + 5], CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(parameters1[r][3]))->SetTime(t);
		GetDlgItem(parameters3[r][4])->SetWindowTextW(CA2W(re[(r + 1) * col + 6], CP_UTF8));
		GetDlgItem(parameters3[r][5])->SetWindowTextW(CA2W(re[(r + 1) * col + 7], CP_UTF8));
	}
	m_vvFormRecid.push_back(vSubformRecid); vSubformRecid.clear();  m_modifiedSubform[2] = 6;
	m_isModify = TRUE;

ShowEnd:

	if ( m_isModify)
		if (!haveRecords[1]) ((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
		else ((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(TRUE);

	help->closeDB(); delete help;
	ss.str(""); ss.clear();
}
#endif

BEGIN_MESSAGE_MAP(PersonalForm03, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &PersonalForm03::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &PersonalForm03::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &PersonalForm03::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &PersonalForm03::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// PersonalForm03 诊断

#ifdef _DEBUG
void PersonalForm03::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void PersonalForm03::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void PersonalForm03::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void PersonalForm03::ShowRadiobtn(int nWhich, char *data)
{

}

void PersonalForm03::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void PersonalForm03::GetNumber(int nWhich, int &num)
{

}

void PersonalForm03::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL PersonalForm03::hasData(int isub, int irow)
{
	CString strText;
	if ((isub == 1) || (isub == 3)) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}
	else if (isub == 2) {
		if (m_Radio2_0 == -1 || m_Radio2_0 == 1)
			return FALSE;
	}

	return TRUE;
}

// PersonalForm03 消息处理程序


void PersonalForm03::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
#if 0
	int parameters1[][5] = { { IDC_EDIT1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER3, IDC_EDIT4, IDC_EDIT5 },
	{ IDC_EDIT6, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER4, IDC_EDIT9, IDC_EDIT10 } };

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 5; j++)
			GetDlgItem(parameters1[i][j])->SetFont(&m_fontEdit);

	int parameters2[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6; j++)
			GetDlgItem(parameters2[i][j])->SetFont(&m_fontEdit);

	int parameters3[][6] = { { IDC_EDIT33, IDC_EDIT35, IDC_DATETIMEPICKER11, IDC_DATETIMEPICKER12, IDC_EDIT37, IDC_EDIT38 },
	{ IDC_EDIT34, IDC_EDIT39, IDC_DATETIMEPICKER13, IDC_DATETIMEPICKER14, IDC_EDIT41, IDC_EDIT42 },
	{ IDC_EDIT36, IDC_EDIT40, IDC_DATETIMEPICKER15, IDC_DATETIMEPICKER16, IDC_EDIT43, IDC_EDIT44 } };

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 6; j++)
			GetDlgItem(parameters3[i][j])->SetFont(&m_fontEdit);

	QueryAndFillFileForm();

	if (m_isModify) {
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM3))->SetBitmap(m_bmpClose);
#endif
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
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}

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
	ss << "select file_5IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio2_0 = -1;
	}
	else
		m_Radio2_0 = 1 - atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);

}

void PersonalForm03::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码

	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void PersonalForm03::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
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
	ss.str(""); ss.clear();
	
	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	//int parameters1[][5] = { { IDC_EDIT1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER3, IDC_EDIT4, IDC_EDIT5 },
	//{ IDC_EDIT6, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER4, IDC_EDIT9, IDC_EDIT10 } };

	//int parameters2[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	//{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	//{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };

	//int parameters3[][6] = { { IDC_EDIT33, IDC_EDIT35, IDC_DATETIMEPICKER11, IDC_DATETIMEPICKER12, IDC_EDIT37, IDC_EDIT38 },
	//{ IDC_EDIT34, IDC_EDIT39, IDC_DATETIMEPICKER13, IDC_DATETIMEPICKER14, IDC_EDIT41, IDC_EDIT42 },
	//{ IDC_EDIT36, IDC_EDIT40, IDC_DATETIMEPICKER15, IDC_DATETIMEPICKER16, IDC_EDIT43, IDC_EDIT44 } };

	CString strText;
	/////////////////////////////////////////////////////////////////////////////
	//表2-1
#pragma region FillForm2_1
	
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_4IfHaveThisSituation=0 where file_id=" << file_id; 
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm2_2;
	}

	{
		ss << "update file_form_flags set file_4IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	
	{
		if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_4IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str()); 
			ss.str(""); ss.clear();
			goto FillForm2_2;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_4IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
#if 0
	{
		for (int i = 0; i < 2; i++) {
			GetDlgItem(parameters1[i][0])->GetWindowTextW(strText);
			strText.Trim();
			if (!strText.IsEmpty()) {
				strText.ReleaseBuffer();

				ss.str(""); ss.clear();
				ss << "insert into file_form_04 values(" << file_id << ",";
				strText = CUtility::GetGuid();
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				for (int j = 0; j < 4; j++) {
					GetDlgItem(parameters1[i][j])->GetWindowTextW(strText);
					ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				}
				GetDlgItem(parameters1[i][4])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

				//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
				help->execSQL(ss.str().c_str());
				ss.str(""); ss.clear();
			}
			else break;
		}
	}
#endif
#pragma endregion

	/////////////////////////////////////////////////////////////////////////////
	//表2-2
#pragma region FillForm2_2
FillForm2_2:
	{
		if (((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_5IfHaveThisSituation=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm2_3;
		}

		ss << "update file_form_flags set file_5IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

#if 0
	{
		for (int i = 0; i < 3; i++) {
			GetDlgItem(parameters2[i][0])->GetWindowTextW(strText);
			strText.Trim();
			if (!strText.IsEmpty()) {
				strText.ReleaseBuffer();

				ss.str(""); ss.clear();
				ss << "insert into file_form_05 values(" << file_id << ",";
				strText = CUtility::GetGuid();
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				for (int j = 0; j < 5; j++) {
					GetDlgItem(parameters2[i][j])->GetWindowTextW(strText);
					ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				}
				GetDlgItem(parameters2[i][5])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

				//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
				help->execSQL(ss.str().c_str());
				ss.str(""); ss.clear();
			}
			else break;
		}
	}
#endif

#pragma endregion

	/////////////////////////////////////////////////////////////////////////////
	//表3-1
#pragma region FillForm2_3
FillForm2_3 :
	GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_6IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_6IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_6IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO13))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_6IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

#if 0
	{
		for (int i = 0; i < 3; i++) {
			GetDlgItem(parameters3[i][0])->GetWindowTextW(strText);
			strText.Trim();
			if (!strText.IsEmpty()) {
				strText.ReleaseBuffer();

				ss.str(""); ss.clear();
				ss << "insert into file_form_06 values(" << file_id << ",";
				strText = CUtility::GetGuid();
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				for (int j = 0; j < 5; j++) {
					GetDlgItem(parameters3[i][j])->GetWindowTextW(strText);
					ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
				}
				GetDlgItem(parameters3[i][5])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

				//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
				help->execSQL(ss.str().c_str());
				ss.str(""); ss.clear();
			}
			else break;
		}
	}
#endif
	
#pragma endregion

FillComplete:
#if 0
	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << "3, " << "'" << CW2A(_T("表2-2"), CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	DoSaveForm();

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}

void PersonalForm03::OnBnClickedCmdPrintForm()
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

	ss.str("");  ss.clear();
	ss << "select * from file_form_04 where file_id=" << file_id << " limit 0,2;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_05 where file_id=" << file_id << " limit 0,3;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_06 where file_id=" << file_id << " limit 0,3;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-2.dotx")));
}


void PersonalForm03::OnBnClickedCmdUpdateForm()
{
#if 0
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
	ss.str(""); ss.clear();

	//int parameters1[][5] = { { IDC_EDIT1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER3, IDC_EDIT4, IDC_EDIT5 },
	//{ IDC_EDIT6, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER4, IDC_EDIT9, IDC_EDIT10 } };
	//
	//int parameters2[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	//{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	//{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };
	//
	//int parameters3[][6] = { { IDC_EDIT33, IDC_EDIT35, IDC_DATETIMEPICKER11, IDC_DATETIMEPICKER12, IDC_EDIT37, IDC_EDIT38 },
	//{ IDC_EDIT34, IDC_EDIT39, IDC_DATETIMEPICKER13, IDC_DATETIMEPICKER14, IDC_EDIT41, IDC_EDIT42 },
	//{ IDC_EDIT36, IDC_EDIT40, IDC_DATETIMEPICKER15, IDC_DATETIMEPICKER16, IDC_EDIT43, IDC_EDIT44 } };

	std::vector<std::vector<std::vector<int>>>::iterator itVVV = _vvvParameters.begin();
	
	int subformFields[] = { 5, 6, 6 };
	CString strText;
	std::vector<std::vector<CString>>::iterator itSubformRecids = m_vvFormRecid.begin();
	for (int i = 0; i < 3; i++) {
		if (m_modifiedSubform[i] == -1) {
			itVVV++;
			continue;
		}
		std::vector<CString>::const_iterator itcRecid = itSubformRecids->begin();
		std::vector<std::vector<int>>::iterator itVV = itVVV->begin();

		ss.str(""); ss.clear();
		ss << "select * from file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " where file_id=" << file_id << " limit 0,1;";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);

		while (itcRecid != itSubformRecids->end()) {
			std::vector<int>::iterator itV = itVV->begin();
			ss.str(""); ss.clear();
			ss << "update file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " set  ";
			for (int k = 0; k < subformFields[i] - 1; k++) {
				GetDlgItem(itV[k])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + k] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
			}
			GetDlgItem(itV[subformFields[i] - 1])->GetWindowTextW(strText); strText.Trim();
			ss << re[2 + subformFields[i] - 1] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "'  ";
			ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());

			itcRecid++;  itVV++;
		}

		itVVV++ ;
		/*
		if (m_modifiedSubform[i] == 4) {
			ss.str(""); ss.clear();
			ss << "select * from file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " where file_id=" << file_id << " limit 0,1;";
			re = help->rawQuery(ss.str().c_str(), &row, &col, result);

			int j = 0;
			while (itcRecid != itSubformRecids->end()) {
				ss.str(""); ss.clear();
				ss << "update file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " set  ";
				for (int k = 0; k < subformFields[i] - 2; k++) {
					GetDlgItem(parameters1[j][k])->GetWindowTextW(strText); strText.Trim();
					ss << re[2 + k] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
				}
				GetDlgItem(parameters1[j][subformFields[i] - 1])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + subformFields[i] - 1] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "'  ";
				ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

				TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
				help->execSQL(ss.str().c_str());

				itcRecid++;  j++;
			}
		}

		if (m_modifiedSubform[i] == 5) {
			ss.str(""); ss.clear();
			ss << "select * from file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " where file_id=" << file_id << " limit 0,1;";
			re = help->rawQuery(ss.str().c_str(), &row, &col, result);

			int j = 0;
			while (itcRecid != itSubformRecids->end()) {
				ss.str(""); ss.clear();
				ss << "update file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " set  ";
				for (int k = 0; k < subformFields[i] - 2; k++) {
					GetDlgItem(parameters2[j][k])->GetWindowTextW(strText); strText.Trim();
					ss << re[2 + k] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
				}
				GetDlgItem(parameters2[j][subformFields[i] - 1])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + subformFields[i] - 1] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "'  ";
				ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

				TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
				help->execSQL(ss.str().c_str());

				itcRecid++;  j++;
			}
		}

		if (m_modifiedSubform[i] == 6) {
			ss.str(""); ss.clear();
			ss << "select * from file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " where file_id=" << file_id << " limit 0,1;";
			re = help->rawQuery(ss.str().c_str(), &row, &col, result);

			int j = 0;
			while (itcRecid != itSubformRecids->end()) {
				ss.str(""); ss.clear();
				ss << "update file_form_" << setfill('0') << setw(2) << m_modifiedSubform[i] << " set  ";
				for (int k = 0; k < subformFields[i] - 2; k++) {
					GetDlgItem(parameters3[j][k])->GetWindowTextW(strText); strText.Trim();
					ss << re[2 + k] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
				}
				GetDlgItem(parameters3[j][subformFields[i] - 1])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + subformFields[i] - 1] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "'  ";
				ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

				TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
				help->execSQL(ss.str().c_str());

				itcRecid++;  j++;
			}
		}
		*/
		itSubformRecids++;
	}

	ss.str("");  ss.clear();
	ss << "update personal_form_info set modify_date=";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << " where file_id=" << file_id << " and form_serial=";
	ss << "'" << CW2A(_T("表2-2"), CP_UTF8) << "';";
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB();
	delete help;
	ss.str("");  ss.clear();
#endif
	UpdateData();

	DoUpdateForm();
}
