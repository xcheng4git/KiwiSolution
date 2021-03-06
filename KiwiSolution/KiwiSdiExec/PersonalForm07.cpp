// PersonalForm07.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm07.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm07

IMPLEMENT_DYNCREATE(CPersonalForm07, CFormView)

CPersonalForm07::CPersonalForm07()
	: CFormView(CPersonalForm07::IDD)
	, m_Radio7_c2_0(-1)
	, m_Radio7_c2_1(-1)
	, m_Radio7_c2_2(-1)
	, m_Radio7_c2_3(-1)
	, m_Radio7_c2_4(-1)
	, m_Radio7_c2_5(-1)
	, m_Radio7_c2_6(-1)
	, m_Radio7_c2_7(-1)
	, m_Radio8_0(-1)
	, m_Radio8_1(-1)
	, m_Radio8_2(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);

	m_FormID = 7;
	int parameters1[][11] = { { 1 * 256 + 1, IDC_EDIT86, 1 * 256 + 2, IDC_EDIT87, IDC_EDIT90, 1 * 256 + 3, 1 * 256 + 4, 1 * 256 + 5, 1 * 256 + 6, IDC_EDIT88, IDC_EDIT89 } };
	int structure1[13] = { 1, 11, RADIOBTN, EDITBX, RADIOBTN, EDITBX, EDITBX, RADIOBTN, RADIOBTN, RADIOBTN, RADIOBTN, EDITBX, EDITBX };
	int parameters2[][11] = { { 2 * 256 + 1, IDC_EDIT86, IDC_EDIT91, IDC_EDIT92, IDC_EDIT95, 2 * 256 + 2, 2 * 256 + 3, 2 * 256 + 4, 2 * 256 + 5, IDC_EDIT93, IDC_EDIT94 } };
	int structure2[13] = { 1, 11, RADIOBTN, EDITBX, EDITBX, EDITBX, EDITBX, RADIOBTN, RADIOBTN, RADIOBTN, RADIOBTN, EDITBX, EDITBX };
	int parameters3[][5] = { { IDC_EDIT47, IDC_DATETIMEPICKER25, IDC_EDIT97, 3 * 256 + 1, IDC_EDIT100 },
	{ IDC_EDIT48, IDC_DATETIMEPICKER26, IDC_EDIT98, 3 * 256 + 2, IDC_EDIT102 } };
	int structure3[7] = { 2, 5, EDITBX, DATEPKR, EDITBX, RADIOBTN, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 11; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 11; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 2; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 13; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 13; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure3[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(1); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(1); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks2[12] = { _T("有无"), _T("子女"), _T("姓名"), _T("共同生活子女"), _T("单位"), _T("现任职务"), _T("单位性质1"), _T("单位性质2"), _T("单位性质3"), _T("单位性质4"), _T("证件名称"), _T("证件号码") };
	int structure20[12] = { CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX,
		CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure21[3 + 1 + 12] = { -1, 1, 11, 2, 2, 2, 1, 2, 1, 1, 6, 4, 2, 1, 1, 1 };
	//
	const wchar_t *pBookmarks3[10] = { _T("有无"), _T("姓名"), _T("单位"), _T("现任职务"), _T("单位性质1"), _T("单位性质2"), _T("单位性质3"), _T("单位性质4"), _T("证件名称"), _T("证件号码") };
	int structure30[10] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX,
		CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[3 + 1 + 10] = { -1, 1, 9, 4, 2, 1, 1, 1, 6, 4, 2, 1, 1, 1 };
	//
	const wchar_t *pBookmarks4[6] = { _T("有无"), _T("问题姓名"), _T("问题时间"), _T("问题原因"), _T("问题阶段"), _T("问题处理") };
	int structure40[6] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX,	CBookmarkEx::CHKBOX,CBookmarkEx::TXTBOX };
	int structure41[3 + 1 + 6] = { 1, 2, 5, 2, 2, 1, 1, 1, 6, 1 };


	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 12; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 10; i++) {
		CBookmarkEx bookmark(structure30[i], pBookmarks3[i], structure31[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 6; i++) {
		CBookmarkEx bookmark(structure40[i], pBookmarks4[i], structure41[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure21[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure31[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure41[i]);
	_vvSubformFlags.push_back(vStr);

}

CPersonalForm07::~CPersonalForm07()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm07::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm07::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO45, m_Radio7_c2_0);
	DDX_Radio(pDX, IDC_RADIO59, m_Radio7_c2_1);
	DDX_Radio(pDX, IDC_RADIO44, m_Radio7_c2_2);
	DDX_Radio(pDX, IDC_RADIO54, m_Radio7_c2_3);
	DDX_Radio(pDX, IDC_RADIO52, m_Radio7_c2_4);
	DDX_Radio(pDX, IDC_RADIO61, m_Radio7_c2_5);
	DDX_Radio(pDX, IDC_RADIO69, m_Radio7_c2_6);
	DDX_Radio(pDX, IDC_RADIO67, m_Radio7_c2_7);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio8_0);
	DDX_Radio(pDX, IDC_RADIO29, m_Radio8_1);
	DDX_Radio(pDX, IDC_RADIO41, m_Radio8_2);
}

BEGIN_MESSAGE_MAP(CPersonalForm07, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm07::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm07::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm07::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm07::OnBnClickedCmdUpdateForm3)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm07::OnBnClickedCmdNextForm)
END_MESSAGE_MAP()


// CPersonalForm07 诊断

#ifdef _DEBUG
void CPersonalForm07::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm07::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm07::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm07::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;
	if (nSub == 1) {
		switch (nSWhich) {
		case 1:
			m_Radio7_c2_0 = atoi(data);
			break;
		case 2:
			m_Radio7_c2_1 = atoi(data);
			break;
		case 3:
			m_Radio7_c2_2 = atoi(data);
			break;
		case 4:
			m_Radio7_c2_3 = atoi(data);
			break;
		case 5:
			m_Radio7_c2_4 = atoi(data);
			break;
		case 6:
		{
			int c = atoi(data);
			if (c == 1)
				((CButton *)GetDlgItem(IDC_RADIO58))->SetCheck(TRUE);
		}
			break;
		}
	}
	else if (nSub == 2) {
		switch (nSWhich) {
		case 2:
			m_Radio7_c2_5 = atoi(data);
			break;
		case 3:
			m_Radio7_c2_6 = atoi(data);
			break;
		case 4:
			m_Radio7_c2_7 = atoi(data);
			break;
		case 5:
		{
			int c = atoi(data);
			if (c == 1)
				((CButton *)GetDlgItem(IDC_RADIO73))->SetCheck(TRUE);
		}
			break;
		}
	}
	else if (nSub == 3) {
		switch (nSWhich) {
		case 1:
			m_Radio8_1 = atoi(data);
			break;
		case 2:
			m_Radio8_2 = atoi(data);
			break;
		}
	}
}

void CPersonalForm07::ShowDatapicker(int nID, char *data)
{
	if (strlen(data) < 8)
		return;
	else {
		COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
	}
}

void CPersonalForm07::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;
	if (nSub == 1) {
		switch (nSWhich) {
		case 1:
			num = m_Radio7_c2_0;
			break;
		case 2:
			num = m_Radio7_c2_1;
			break;
		case 3:
			num = m_Radio7_c2_2;
			break;
		case 4:
			num = m_Radio7_c2_3;
			break;
		case 5:
			num = m_Radio7_c2_4;
			break;
		case 6:
			((CButton *)GetDlgItem(IDC_RADIO58))->GetCheck();
			break;
		}
	}
	else if (nSub == 2) {
		switch (nSWhich) {
		case 2:
			num = m_Radio7_c2_5;
			break;
		case 3:
			num = m_Radio7_c2_6;
			break;
		case 4:
			num = m_Radio7_c2_7;
			break;
		case 5:
			((CButton *)GetDlgItem(IDC_RADIO73))->GetCheck();
			break;
		}
	} else if (nSub == 3) {
		switch (nSWhich) {
		case 1:
			num = m_Radio8_1;
			break;
		case 2:
			num = m_Radio8_2;
			break;
		}
	}
}

void CPersonalForm07::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm07::hasData(int isub, int irow)
{
	CString strText;
	if (isub == 1) {
		if (m_Radio7_c2_0 == -1)
			return FALSE;
	}
	else if (isub == 2) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][1])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}
	else if (isub == 3) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
		else if (_T("无") == strText)
			return 2;
	}

	return TRUE;
}
// CPersonalForm07 消息处理程序


void CPersonalForm07::OnBnClickedCmdSaveForm()
{
	UpdateData();
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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	CString strText;
	/*
#pragma region FillForm7_c2_1
FillForm7_c2_1 :
	if (m_Radio7_c2_0 == -1)
		goto FillComplete;
	{
		ss << "insert into file_form_12_c values(" << file_id << ",";

		ss << m_Radio7_c2_0 << ",";

		GetDlgItem(IDC_EDIT86)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << m_Radio7_c2_1 << ",";

		GetDlgItem(IDC_EDIT87)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT90)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		ss << m_Radio7_c2_2 << ",";
		ss << m_Radio7_c2_3 << ",";
		ss << m_Radio7_c2_4 << ",";
		ss << ((CButton *)GetDlgItem(IDC_RADIO58))->GetCheck() << ",";
		GetDlgItem(IDC_EDIT88)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT89)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}

#pragma endregion

	//////////////////////////////////////////////////////////////////////////
	// 子女配偶
#pragma region FillForm7_c2_2
FillForm7_c2_2 :
	GetDlgItem(IDC_EDIT91)->GetWindowTextW(strText);
	if (strText == _T("无"))
		goto FillComplete;

	{
		ss << "insert into file_form_12_cl values(" << file_id << ",";

		ss << m_Radio7_c2_0 << ",";

		GetDlgItem(IDC_EDIT86)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(IDC_EDIT91)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT92)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT95)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		ss << m_Radio7_c2_5 << ",";
		ss << m_Radio7_c2_6 << ",";
		ss << m_Radio7_c2_7 << ",";
		ss << ((CButton *)GetDlgItem(IDC_RADIO73))->GetCheck() << ",";
		GetDlgItem(IDC_EDIT93)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT94)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}

#pragma endregion
	*/
#pragma region FillForm8
FillForm8 :
	GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
	if (strText == _T("无"))
		ss << "update file_form_flags set file_13IfHaveThisSituation=1 where file_id=" << file_id;
	else
		ss << "update file_form_flags set file_13IfHaveThisSituation=0 where file_id=" << file_id;
	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

	{
		if (m_Radio8_0 != -1) {
			ss.str(""); ss.clear();
			ss << "update file_form_flags set file_13IfChange=";
			ss << m_Radio8_0 << " where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
		}

#if 0
		if (m_Radio8_0 == 1)
		{
			ss << "update file_form_flags set file_13IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio8_0 == 0)
		{
			ss << "update file_form_flags set file_13IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
#endif
	}
	/*
	{
		ss << "insert into file_form_13 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER25)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT97)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << m_Radio8_1 << ",";

		GetDlgItem(IDC_EDIT100)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}

	GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
	strText.Trim();
	if (!strText.IsEmpty()) {
		ss << "insert into file_form_13 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER26)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT98)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << m_Radio8_2 << ",";

		GetDlgItem(IDC_EDIT102)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}
	*/
#pragma endregion



FillComplete :
	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	DoSaveForm();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm07::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_12_c where file_id=" << file_id << " limit 1,2;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select cl.* from file_form_12_c as c left outer join file_form_12_cl as cl on c.file_ChildrenName=cl.file_ChildrenName  where c.file_id=" << file_id << " limit 1,2;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_13 where file_id=" << file_id << " limit 0,2;";
	_vSubformQueryString.push_back(ss.str());
	ss.str("");  ss.clear();

	DoPrintForm(CString(_T("表2-6.dotx")));
}


void CPersonalForm07::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm07::OnBnClickedCmdUpdateForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
	
	DoUpdateFlag(3, 1, m_Radio8_0);
}


void CPersonalForm07::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
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
		GetDlgItem(IDC_CMD_UPDATE_FORM3)->ShowWindow(SW_SHOW);
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
	ss << "select file_13IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio8_0 = -1;
	}
	else {
		m_Radio8_0 = atoi(re[1 * col + 0]);  //分组的原因, m_Radio8_0=0表示有此类情况，即第一个单选按钮
	}
	help->closeDB(); delete help;

	UpdateData(FALSE);
}


void CPersonalForm07::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(8), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}
