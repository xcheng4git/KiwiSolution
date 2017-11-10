// PersonalForm08.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm08.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm08

IMPLEMENT_DYNCREATE(CPersonalForm08, CFormView)

CPersonalForm08::CPersonalForm08()
: CFormView(CPersonalForm08::IDD)
, m_Radio10_0(-1)
, m_Radio11_0(-1)
, m_Radio11_1_1(-1)
, m_Radio11_1_2(-1)
, m_Radio11_1_3(-1)
, m_Radio11_2_1(-1)
, m_Radio11_2_2(-1)
, m_Radio11_2_3(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 8;
	int parameters1[][4] = { { IDC_EDIT47, IDC_EDIT97, IDC_EDIT98, IDC_EDIT99 } };
	int structure1[6] = { 1, 4, EDITBX, EDITBX, EDITBX, EDITBX };
	int parameters2[][7] = { { IDC_EDIT48, IDC_EDIT49, IDC_EDIT50, IDC_EDIT51, IDC_EDIT101, IDC_EDIT100, IDC_EDIT102 } };
	int structure2[9] = { 1, 7, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX };
	int parameters3[2][8] = { { IDC_EDIT52, 3 * 256 + 1, 3 * 256 + 2, IDC_EDIT54, IDC_EDIT55, 3 * 256 + 3, IDC_EDIT103, IDC_EDIT105 },
	{ IDC_EDIT53, 3 * 256 + 4, 3 * 256 + 5, IDC_EDIT63, IDC_EDIT64, 3 * 256 + 6, IDC_EDIT107, IDC_EDIT108 } };
	int structure3[10] = { 2, 8, EDITBX, RADIOBTN, RADIOBTN, EDITBX, EDITBX, RADIOBTN, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 4; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 7; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 2; i++) {
		vector<int> vPara;
		for (int j = 0; j < 8; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 6; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 9; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 10; i++) {
		vStr.push_back(structure3[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[5] = { _T("有无"), _T("工资"), _T("奖金"), _T("其他"), _T("合计") };
	int structure10[5] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure11[3 + 1 + 5] = { -1, 1, 4, 2, 2, 1, 1, 1, 1};
	//
	const wchar_t *pBookmarks2[8] = { _T("有无"), _T("讲学"), _T("写作"), _T("咨询"), _T("审稿"), _T("书画"), _T("其他"), _T("合计") };
	int structure20[8] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure21[3 + 1 + 8] = { 0, 1, 7, 2, 2, 1, 1, 1, 1, 1,1,1 };
	//
	const wchar_t *pBookmarks3[9] = { _T("有无"), _T("姓名"), _T("来源"), _T("去向"), _T("具体地址"), _T("面积"), _T("房产性质"), _T("交易时间"), _T("交易价格") };
	int structure30[9] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[3 + 1 + 9] = { 1, 2, 8, 2, 2, 1, 4,3,1, 1, 7, 1,1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....

	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 5; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 8; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 9; i++) {
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

CPersonalForm08::~CPersonalForm08()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm08::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm08::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio10_0);
	DDX_Radio(pDX, IDC_RADIO16, m_Radio11_0);
	DDX_Radio(pDX, IDC_RADIO78, m_Radio11_1_1);
	DDX_Radio(pDX, IDC_RADIO82, m_Radio11_1_2);
	DDX_Radio(pDX, IDC_RADIO106, m_Radio11_1_3);
	DDX_Radio(pDX, IDC_RADIO85, m_Radio11_2_1);
	DDX_Radio(pDX, IDC_RADIO89, m_Radio11_2_2);
	DDX_Radio(pDX, IDC_RADIO109, m_Radio11_2_3);
}

BEGIN_MESSAGE_MAP(CPersonalForm08, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm08::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm08::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm08::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm08::OnBnClickedCmdUpdateForm3)
END_MESSAGE_MAP()


// CPersonalForm08 诊断

#ifdef _DEBUG
void CPersonalForm08::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm08::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm08::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm08::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

	if (nSub == 3) {
		switch (nSWhich) {
		case 1:
			m_Radio11_1_1 = atoi(data);
			break;
		case 2:
			m_Radio11_1_2 = atoi(data);
			break;
		case 3:
			m_Radio11_1_3 = atoi(data);
			break;
		case 4:
			m_Radio11_2_1 = atoi(data);
			break;
		case 5:
			m_Radio11_2_2 = atoi(data);
			break;
		case 6:
			m_Radio11_2_3 = atoi(data);
			break;
		}
	}

}

void CPersonalForm08::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm08::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

	if (nSub == 3) {
		switch (nSWhich) {
		case 1:
			num = m_Radio11_1_1;
			break;
		case 2:
			num = m_Radio11_1_2;
			break;
		case 3:
			num = m_Radio11_1_3;
			break;
		case 4:
			num = m_Radio11_2_1;
			break;
		case 5:
			num = m_Radio11_2_2;
			break;
		case 6:
			num = m_Radio11_2_3;
			break;
		}
	}
}

void CPersonalForm08::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm08::hasData(int isub, int irow)
{
	CString strText;
	if (isub == 2) {
		if (m_Radio10_0 == 1)
			return FALSE;
	}
	else if (isub == 3) {
		switch (irow) {
		case 1:
		case 2:
			GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
			//if (strText == _T("无"))
			if (!strText.IsEmpty())
				return FALSE;
			break;
		//case 2:
		//	GetDlgItem(IDC_EDIT53)->GetWindowTextW(strText);
		//	strText.Trim();
		//	if (!strText.IsEmpty())
		//		return FALSE;
		//	break;
		}
	}

	return TRUE;
}
// CPersonalForm08 消息处理程序


void CPersonalForm08::OnBnClickedCmdSaveForm()
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
#pragma region FillForm9
FillForm9:
	/*
	{
		ss << "insert into file_form_14 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT97)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT98)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT99)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ")"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}
	*/
#pragma endregion

#pragma region FillForm10
FillForm10:
	if (m_Radio10_0 == -1) {
		MessageBox(_T("请选择是否存在 10 本人从事各种劳务所得 ！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
		help->closeDB(); delete help;
		ss.str("");  ss.clear();
		return;
	}
	else {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_15IfHaveThisSituation=";
		ss << m_Radio10_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}

#if 0
	if (m_Radio10_0 == 1) {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_15IfHaveThisSituation=0 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
	} else {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_15IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
	}
#endif
	/*
	{
		ss << "insert into file_form_15 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT49)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT50)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT51)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT101)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT100)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT102)->GetWindowTextW(strText);
		ss << wcstod(strText.GetBuffer(), NULL) << ")"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE(_T("\n"));
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}
	*/
#pragma endregion

#pragma region FillForm11
FillForm11 :
	GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_16IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
	} else {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_16IfHaveThisSituation=0 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
	}

	if (m_Radio11_0 != -1) {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_16IfChange=";
		ss << m_Radio11_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}

#if 0
	if (m_Radio11_0 == 1){
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_16IfChange=0 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
	} else if (m_Radio11_0 == 0)
		{
			ss.str(""); ss.clear();
			ss << "update file_form_flags set file_16IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
		}
#endif
	/*
	int Parameters[2][8] = { { IDC_EDIT52, m_Radio11_1_1, m_Radio11_1_2, IDC_EDIT54, IDC_EDIT55, m_Radio11_1_3, IDC_EDIT103, IDC_EDIT105 },
	{ IDC_EDIT53, m_Radio11_2_1, m_Radio11_2_2, IDC_EDIT63, IDC_EDIT64, m_Radio11_2_3, IDC_EDIT107, IDC_EDIT108 } };

	for (int i = 0; i < 2; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_16 values(" << file_id << ",";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << Parameters[i][1] << ", ";
		ss << Parameters[i][2] << ", ";

		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

		ss << Parameters[i][5] << ", ";
		GetDlgItem(Parameters[i][6])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][7])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ")"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	*/

#pragma endregion


FillComplete:

	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	DoSaveForm();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm08::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_14 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_15 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_16 where file_id=" << file_id << " limit 0,2;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-7.dotx")));
}


void CPersonalForm08::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm08::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

#if 0
FillForm14 :
	//第一张表********************************************
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
	ss << "select * from file_form_14 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		goto FillForm15;
	}

	GetDlgItem(IDC_EDIT47)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
	GetDlgItem(IDC_EDIT97)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	GetDlgItem(IDC_EDIT98)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));
	GetDlgItem(IDC_EDIT99)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
FillForm15 :
	//第二张表********************************************
	ss.str(""); ss.clear();
	ss << "select file_15IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		goto FillForm16;
	}
	m_Radio10_0 = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from file_form_15 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		goto FillForm16;
	}
	GetDlgItem(IDC_EDIT48)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
	GetDlgItem(IDC_EDIT49)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	GetDlgItem(IDC_EDIT50)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));
	GetDlgItem(IDC_EDIT51)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
	GetDlgItem(IDC_EDIT101)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
	GetDlgItem(IDC_EDIT100)->SetWindowTextW(CA2W(re[1 * col + 6], CP_UTF8));
	GetDlgItem(IDC_EDIT102)->SetWindowTextW(CA2W(re[1 * col + 7], CP_UTF8));

	
FillForm16 :
	//第三张表********************************************
	ss.str(""); ss.clear();
	ss << "select file_16IfHaveThisSituation, file_16IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}
	m_Radio11_0 = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();
	ss << "select * from file_form_16 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		GetDlgItem(IDC_EDIT52)->SetWindowTextW(_T("无"));
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	int Parameters[2][8] = { { IDC_EDIT52, m_Radio11_1_1, m_Radio11_1_2, IDC_EDIT54, IDC_EDIT55, m_Radio11_1_3, IDC_EDIT103, IDC_EDIT105 },
	{ IDC_EDIT53, m_Radio11_2_1, m_Radio11_2_2, IDC_EDIT63, IDC_EDIT64, m_Radio11_2_3, IDC_EDIT107, IDC_EDIT108 } };
	if (row > 2) row = 2;
	for (int i = 0; i < row; i++){
		GetDlgItem(Parameters[i][0])->SetWindowTextW(CA2W(re[(i + 1) * col + 1], CP_UTF8));
		GetDlgItem(Parameters[i][3])->SetWindowTextW(CA2W(re[(i + 1) * col + 4], CP_UTF8));
		GetDlgItem(Parameters[i][4])->SetWindowTextW(CA2W(re[(i + 1) * col + 5], CP_UTF8));
		GetDlgItem(Parameters[i][6])->SetWindowTextW(CA2W(re[(i + 1) * col + 7], CP_UTF8));
		GetDlgItem(Parameters[i][7])->SetWindowTextW(CA2W(re[(i + 1) * col + 8], CP_UTF8));
	}
	m_Radio11_1_1 = atoi(re[1 * col + 2]);
	m_Radio11_1_2 = atoi(re[1 * col + 3]);
	m_Radio11_1_3 = atoi(re[1 * col + 6]);
	m_Radio11_2_1 = atoi(re[2 * col + 2]);
	m_Radio11_2_2 = atoi(re[2 * col + 3]);
	m_Radio11_2_3 = atoi(re[2 * col + 6]);

	help->closeDB();
	delete help;
	UpdateData(FALSE);
#endif
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
	ss << "select file_15IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio10_0 = -1;
	} else 
		m_Radio10_0 = atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);
}

void CPersonalForm08::OnBnClickedCmdUpdateForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
}
