// PersonalForm14.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm14.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm14

IMPLEMENT_DYNCREATE(CPersonalForm14, CFormView)

CPersonalForm14::CPersonalForm14()
: CFormView(CPersonalForm14::IDD)
, m_Radio13_0(-1)
, m_Radio13_1(-1)
, m_Radio13_2(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 14;
	int parameters1[2][12] = { { IDC_EDIT47, IDC_EDIT48, IDC_EDIT79, IDC_DATETIMEPICKER3, IDC_EDIT166, IDC_EDIT167, IDC_EDIT168, 1 * 256 + 1, IDC_EDIT169, IDC_EDIT170, IDC_EDIT172, IDC_EDIT171 },
	{ IDC_EDIT50, IDC_EDIT174, IDC_EDIT87, IDC_DATETIMEPICKER48, IDC_EDIT173, IDC_EDIT176, IDC_EDIT177, 1 * 256 + 2, IDC_EDIT178, IDC_EDIT179, IDC_EDIT181, IDC_EDIT180 } };
	int structure1[14] = { 2, 12, EDITBX, EDITBX, EDITBX, DATEPKR, EDITBX, EDITBX, EDITBX, RADIOBTN, EDITNUM, EDITNUM, EDITNUM, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 2; i++) {
		vector<int> vPara;
		for (int j = 0; j < 12; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 14; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(2); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[13] = { _T("有无"), _T("姓名"), _T("代码或注册号"), _T("主体名称"), _T("成立日期"), _T("经营范围"), _T("注册地"), _T("经营地"), _T("主题类型"), _T("注册出资额"), _T("个人出资额"), _T("个人出资比例"), _T("备注") };
	int structure10[13] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, };
	int structure11[3 + 1 + 13] = { 1, 2, 12, 2, 2, 1, 1, 1, 1, 1, 1, 1,  7, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	//
	//const wchar_t *pBookmarks2[13] = { _T("有无"), _T("姓名"), _T("统一社会信用"), _T("企业或其他"), _T("成立日期"), _T("经营范围"), _T("注册地"), _T("经营地"), _T("企业或其他市场类型主体"), _T("注册资本"), _T("个人认缴出资额"), _T("个人认缴出资比例或个人出资比例"), _T("备注") };
	//int structure20[13] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, };
	//int structure21[3 + 1 + 12] = { -1, 1, 10, 2,  1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1 };
	////
	


	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 13; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	//vBke.clear();
	//for (int i = 0; i < 12; i++) {
	//	CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
	//	vBke.push_back(bookmark);
	//}
	//_vvBookmarks.push_back(vBke);
	

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	//for (int i = 0; i < 4; i++)
	//	vStr.push_back(structure21[i]);
	//_vvSubformFlags.push_back(vStr);
	
}

CPersonalForm14::~CPersonalForm14()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm14::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm14::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio13_0);
	DDX_Radio(pDX, IDC_RADIO139, m_Radio13_1);
	DDX_Radio(pDX, IDC_RADIO146, m_Radio13_2);
}

BEGIN_MESSAGE_MAP(CPersonalForm14, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM2, &CPersonalForm14::OnBnClickedCmdSaveForm2)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM2, &CPersonalForm14::OnBnClickedCmdPrintForm2)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM4, &CPersonalForm14::OnBnClickedButtonCloseForm4)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM2, &CPersonalForm14::OnBnClickedCmdUpdateForm2)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm14::OnBnClickedCmdNextForm)
END_MESSAGE_MAP()


// CPersonalForm14 诊断

#ifdef _DEBUG
void CPersonalForm14::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm14::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPersonalForm14::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm14::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

	if (nSub == 1){
		switch (nSWhich)
		{
		case 1:
			m_Radio13_1 = atoi(data);
			break;
		case 2:
			m_Radio13_2 = atoi(data);
			break;
		default:
			break;
		}
	}
}

void CPersonalForm14::ShowDatapicker(int nID, char *data)
{
	if (strlen(data) < 8)
		return;
	else {
		COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
	}
}

void CPersonalForm14::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;
	
	if (nSub == 1) {
		switch (nSWhich)
		{
		case 1:
			num = m_Radio13_1;
			break;
		case 2:
			num = m_Radio13_2;
			break;
		}
	}
}

void CPersonalForm14::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

int CPersonalForm14::hasData(int isub, int irow)
{
	CString strText;

	if (isub == 1) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		switch (irow)
		{
		case 0:
			GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
			if (strText.IsEmpty())
				return FALSE;
			else if (_T("无") == strText)
				return 2;
			break;
		case 1:
			GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
			if (strText.IsEmpty())
				return FALSE;
			else if (_T("无") == strText)
				return 2;
			break;
		default:
			break;
		}
	}

	return TRUE;
}
// CPersonalForm14 消息处理程序


void CPersonalForm14::OnBnClickedCmdSaveForm2()
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

	int Parameters[2][12] = { { IDC_EDIT47, IDC_EDIT48, IDC_EDIT79, IDC_EDIT83, IDC_EDIT166, IDC_EDIT167, IDC_EDIT168, m_Radio13_1, IDC_EDIT169, IDC_EDIT170, IDC_EDIT172, IDC_EDIT171}, 
	{ IDC_EDIT50, IDC_EDIT174, IDC_EDIT87, IDC_EDIT175, IDC_EDIT173, IDC_EDIT176, IDC_EDIT177, m_Radio13_2, IDC_EDIT178, IDC_EDIT179, IDC_EDIT181, IDC_EDIT180 } };

	CString strText;
#pragma region FillForm13_1
FillForm13_1 :
	GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
	if (strText == _T("无"))
		ss << "update file_form_flags set file_20IfHaveThisSituation=1 where file_id=" << file_id;
	else
		ss << "update file_form_flags set file_20IfHaveThisSituation=0 where file_id=" << file_id;
	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

	{
		if (m_Radio13_0 != -1) {
			ss.str(""); ss.clear();
			ss << "update file_form_flags set file_13IfChange=";
			ss << m_Radio13_0 << " where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
		}
	}

#if 0
	for (int i = 0; i < 2; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_20 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		for (int j = 0; j < 7; j++) {
			GetDlgItem(Parameters[i][j])->GetWindowTextW(strText); strText.Trim();
			ss << "'" << strText << "',"; strText.ReleaseBuffer();
		}

		ss << Parameters[i][7] << ",";

		for (int j = 8; j < 11; j++) {
			GetDlgItem(Parameters[i][j])->GetWindowTextW(strText); strText.Trim();
			ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		}

		GetDlgItem(Parameters[i][11])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
#pragma endregion
#endif
FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();

			 DoSaveForm();

			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm14::OnBnClickedCmdPrintForm2()
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
	ss << "select * from file_form_20 where file_id=" << file_id << " limit 0,2;";
	_vSubformQueryString.push_back(ss.str());
	
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-13.dotx")));
}


void CPersonalForm14::OnBnClickedButtonCloseForm4()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm14::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
#if 0
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
	ss << "select file_20IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	m_Radio13_0 = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from file_form_20 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int Parameters[2][12] = { { IDC_EDIT47, IDC_EDIT48, IDC_EDIT79, IDC_EDIT83, IDC_EDIT166, IDC_EDIT167, IDC_EDIT168, m_Radio13_1, IDC_EDIT169, IDC_EDIT170, IDC_EDIT172, IDC_EDIT171 },
	{ IDC_EDIT50, IDC_EDIT174, IDC_EDIT87, IDC_EDIT175, IDC_EDIT173, IDC_EDIT176, IDC_EDIT177, m_Radio13_2, IDC_EDIT178, IDC_EDIT179, IDC_EDIT181, IDC_EDIT180 } };
	m_Radio13_1 = atoi(re[1 * col + 8]);
	m_Radio13_2 = atoi(re[2 * col + 8]);
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 12; j++){
			if (j == 7) continue;
			GetDlgItem(Parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
		}
		if (i + 1 >= row) break;
	}	
	help->closeDB();
	delete help;
	UpdateData(FALSE);
#endif

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM4))->SetBitmap(m_bmpClose);
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
		GetDlgItem(IDC_CMD_SAVE_FORM2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM2)->ShowWindow(SW_SHOW);
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
	ss << "select file_20IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio13_0 = -1;
	}
	else
		m_Radio13_0 = atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);
}

void CPersonalForm14::OnBnClickedCmdUpdateForm2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
	DoUpdateFlag(1, 1, m_Radio13_0);
	
}


void CPersonalForm14::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(15), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}
