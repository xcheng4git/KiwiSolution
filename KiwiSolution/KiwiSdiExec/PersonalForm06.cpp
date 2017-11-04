// PersonalForm06.cpp : 实现文件
//
#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm06.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm06

IMPLEMENT_DYNCREATE(CPersonalForm06, CFormView)

CPersonalForm06::CPersonalForm06()
: CFormView(CPersonalForm06::IDD)
, m_Radio7(-1)
, m_Radio7_1(-1)
, m_Radio7_2(-1)
, m_Radio7_3(-1)
, m_Radio7_4(-1)
, m_Radio7_5(-1)
, m_Radio7_6(-1)
, m_Radio7_7(-1)
, m_Radio7_8(-1)
, m_Radio7_9(-1)
, m_Radio7_4_0(-1)
, m_Radio7_0(-1)
, m_Radio7_4_1(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);

	m_FormID = 6;
	int parameters1[][10] = { { 1 * 256 + 1, IDC_EDIT78, IDC_EDIT79, IDC_EDIT85, 1 * 256 + 2, 1 * 256 + 3, 1 * 256 + 4, 1 * 256 + 5, IDC_EDIT83, IDC_EDIT84 } };
	int structure1[12] = { 1, 10, RADIOBTN, EDITBX, EDITBX, EDITBX, RADIOBTN, RADIOBTN, RADIOBTN, RADIOBTN, EDITBX, EDITBX };
	int parameters2[][11] = { { 2 * 256 + 1, IDC_EDIT86, 2 * 256 + 2, IDC_EDIT87, IDC_EDIT90, 2 * 256 + 3, 2 * 256 + 4, 2 * 256 + 5, 2 * 256 + 6, IDC_EDIT88, IDC_EDIT89 } };
	int structure2[13] = { 1, 11, RADIOBTN, EDITBX, RADIOBTN, EDITBX, EDITBX, RADIOBTN, RADIOBTN, RADIOBTN, RADIOBTN, EDITBX, EDITBX };
	int parameters3[][11] = { { 3 * 256 + 1, IDC_EDIT86, IDC_EDIT91, IDC_EDIT92, IDC_EDIT95, 3 * 256 + 2, 3 * 256 + 3, 3 * 256 + 4, 3 * 256 + 5, IDC_EDIT93, IDC_EDIT94 } };
	int structure3[13] = { 1, 11, RADIOBTN, EDITBX, EDITBX, EDITBX, EDITBX, RADIOBTN, RADIOBTN, RADIOBTN, RADIOBTN, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 10; j++)
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
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 11; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 12; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 13; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 13; i++) {
		vStr.push_back(structure3[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);
	
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[11] = { _T("有无"), _T("配偶"), _T("姓名"), _T("单位"), _T("现任职务"), _T("单位性质1"), _T("单位性质2"), _T("单位性质3"), _T("单位性质4"), _T("证件名称"), _T("证件号码") };
	int structure10[11] = { CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, 
		CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure11[3+1 + 11] = { 1, 1, 10, 2, 2, 2, 1, 1, 1, 6, 4, 2,1,1,1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	//
	const wchar_t *pBookmarks2[12] = { _T("有无"), _T("子女"), _T("姓名"), _T("共同生活子女"), _T("单位"), _T("现任职务"), _T("单位性质1"), _T("单位性质2"), _T("单位性质3"), _T("单位性质4"), _T("证件名称"), _T("证件号码") };
	int structure20[12] = { CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX,
		CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure21[3+1 + 12] = { -1, 1, 11, 2,2, 2, 1, 2, 1, 1, 6, 4, 2, 1, 1, 1 };
	//
	const wchar_t *pBookmarks3[10] = { _T("有无"), _T("姓名"), _T("单位"), _T("现任职务"), _T("单位性质1"), _T("单位性质2"), _T("单位性质3"), _T("单位性质4"), _T("证件名称"), _T("证件号码") };
	int structure30[10] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX,
		CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[3+1 + 10] = { -1, 1, 9, 4, 2, 1, 1, 1, 6, 4, 2, 1, 1, 1 };


	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 11; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
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

CPersonalForm06::~CPersonalForm06()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm06::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm06::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio7);
	DDX_Radio(pDX, IDC_RADIO28, m_Radio7_1);
	DDX_Radio(pDX, IDC_RADIO37, m_Radio7_3);
	DDX_Radio(pDX, IDC_RADIO39, m_Radio7_2);
	DDX_Radio(pDX, IDC_RADIO44, m_Radio7_4);
	DDX_Radio(pDX, IDC_RADIO54, m_Radio7_5);
	DDX_Radio(pDX, IDC_RADIO52, m_Radio7_6);
	DDX_Radio(pDX, IDC_RADIO61, m_Radio7_7);
	DDX_Radio(pDX, IDC_RADIO69, m_Radio7_8);
	DDX_Radio(pDX, IDC_RADIO67, m_Radio7_9);
	DDX_Radio(pDX, IDC_RADIO59, m_Radio7_4_1);
	DDX_Radio(pDX, IDC_RADIO30, m_Radio7_0);
	DDX_Radio(pDX, IDC_RADIO45, m_Radio7_4_0);
}

BEGIN_MESSAGE_MAP(CPersonalForm06, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm06::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm06::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm06::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm06::OnBnClickedCmdUpdateForm3)
	ON_BN_CLICKED(IDC_RADIO43, &CPersonalForm06::OnBnClickedRadio43)
END_MESSAGE_MAP()


// CPersonalForm06 诊断

#ifdef _DEBUG
void CPersonalForm06::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm06::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm06::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm06::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;
	if (nSub == 1) {
		switch (nSWhich) {
		case 1:
			m_Radio7_0 = atoi(data);
			break;
		case 2:
			m_Radio7_1 = atoi(data);
			break;
		case 3:
			m_Radio7_2 = atoi(data);
			break;
		case 4:
			m_Radio7_3 = atoi(data);
			break;
		case 5:
		{
			int c = atoi(data);
			if (c == 1)
				((CButton *)GetDlgItem(IDC_RADIO43))->SetCheck(TRUE);
		}
			break;
		}
	}
	else if (nSub == 2) {
		switch (nSWhich) {
		case 1:
			m_Radio7_4_0 = atoi(data);
			break;
		case 2:
			m_Radio7_4_1 = atoi(data);
			break;
		case 3:
			m_Radio7_4 = atoi(data);
			break;
		case 4:
			m_Radio7_5 = atoi(data);
			break;
		case 5:
			m_Radio7_6 = atoi(data);
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
	else if (nSub == 3) {
		switch (nSWhich) {
		case 2:
			m_Radio7_7 = atoi(data);
			break;
		case 3:
			m_Radio7_8 = atoi(data);
			break;
		case 4:
			m_Radio7_9 = atoi(data);
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
}

void CPersonalForm06::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm06::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;
	if (nSub == 1) {
		switch (nSWhich) {
		case 1:
			num = m_Radio7_0;
			break;
		case 2:
			num = m_Radio7_1;
			break;
		case 3:
			num = m_Radio7_2;
			break;
		case 4:
			num = m_Radio7_3;
			break;
		case 5:
			num = ((CButton *)GetDlgItem(IDC_RADIO43))->GetCheck();
			break;
		}
	}
	else if (nSub == 2) {
		switch (nSWhich) {
		case 1:
			num = m_Radio7_4_0;
			break;
		case 2:
			num = m_Radio7_4_1;
			break;
		case 3:
			num = m_Radio7_4;
			break;
		case 4:
			num = m_Radio7_5;
			break;
		case 5:
			num = m_Radio7_6;
			break;
		case 6:
			((CButton *)GetDlgItem(IDC_RADIO58))->GetCheck();
			break;
		}
	}
	else if (nSub == 3) {
		switch (nSWhich) {
		case 2:
			num = m_Radio7_7;
			break;
		case 3:
			num = m_Radio7_8;
			break;
		case 4:
			num = m_Radio7_9;
			break;
		case 5:
			((CButton *)GetDlgItem(IDC_RADIO73))->GetCheck();
			break;
		}
	}
}

void CPersonalForm06::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm06::hasData(int isub, int irow)
{
	CString strText;
	if (isub == 1) {
		GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
		if (m_Radio7_0 == -1 || strText == _T("无"))
			return FALSE;
	}
	else if (isub == 2) {
		if (m_Radio7_4_0 == -1)
			return FALSE;
	}
	else if (isub == 3) {
		GetDlgItem(IDC_EDIT91)->GetWindowTextW(strText);
		if (strText == _T("无"))
			return FALSE;
	}

	return TRUE;
}

// CPersonalForm06 消息处理程序


void CPersonalForm06::OnBnClickedCmdSaveForm()
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
#pragma region FillForm7_1
	GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
	if (m_Radio7_0==-1 || strText == _T("无"))
	{
		ss << "update file_form_flags set file_12IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_12IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (m_Radio7 == 1)
		{
			ss << "update file_form_flags set file_12IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio7 == 0)
		{
			ss << "update file_form_flags set file_12IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	/*
	{
		ss << "insert into file_form_12 values(" << file_id << ",";

		ss << m_Radio7_0 << ",";

		GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT79)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT85)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		ss << m_Radio7_1 << ",";
		ss << m_Radio7_2 << ",";
		ss << m_Radio7_3 << ",";
		ss << ((CButton *)GetDlgItem(IDC_RADIO43))->GetCheck() << ",";
		GetDlgItem(IDC_EDIT83)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT84)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}
	*/
#pragma endregion
	/*
#pragma region FillForm7_2_1
FillForm7_2_1 :
	if (m_Radio7_4_0 == -1)
		goto FillComplete;
	{
		ss << "insert into file_form_12_c values(" << file_id << ",";

		ss << m_Radio7_4_0 << ",";

		GetDlgItem(IDC_EDIT86)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << m_Radio7_4_1 << ",";

		GetDlgItem(IDC_EDIT87)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT90)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		ss << m_Radio7_4 << ",";
		ss << m_Radio7_5 << ",";
		ss << m_Radio7_6 << ",";
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
#pragma region FillForm7_2_2
FillForm7_2_2 :
	GetDlgItem(IDC_EDIT91)->GetWindowTextW(strText);
	if (strText == _T("无"))
		goto FillComplete;

	{
		ss << "insert into file_form_12_cl values(" << file_id << ",";

		ss << m_Radio7_4_0 << ",";

		GetDlgItem(IDC_EDIT86)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(IDC_EDIT91)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT92)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT95)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		ss << m_Radio7_7 << ",";
		ss << m_Radio7_8 << ",";
		ss << m_Radio7_9 << ",";
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

FillComplete :
	help->closeDB(); delete help;
    ss.str("");  ss.clear();

	DoSaveForm();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}

void CPersonalForm06::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_12 where file_id=" << file_id << ";";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_12_c where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select cl.* from file_form_12_c as c left outer join file_form_12_cl as cl on c.file_ChildrenName=cl.file_ChildrenName  where c.file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-5.dotx")));
}

void CPersonalForm06::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm06::OnBnClickedCmdUpdateForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
}


void CPersonalForm06::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
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
	if (_vHaveDataSubform[2] == -1)
		GetDlgItem(IDC_EDIT91)->SetWindowTextW(_T("无"));

	UpdateData(FALSE);
}


void CPersonalForm06::OnBnClickedRadio43()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_RADIO43))->GetCheck())
		((CButton *)GetDlgItem(IDC_RADIO43))->SetCheck(FALSE);
}
