// PersonalForm13.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm13.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm13

IMPLEMENT_DYNCREATE(CPersonalForm13, CFormView)

CPersonalForm13::CPersonalForm13()
: CFormView(CPersonalForm13::IDD)
, m_Radio12_3_0(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 13;
	int parameters1[10][5] = { { IDC_EDIT47, IDC_EDIT98, IDC_EDIT97, IDC_EDIT99, IDC_EDIT100 },
	{ IDC_EDIT48, IDC_EDIT102, IDC_EDIT133, IDC_EDIT110, IDC_EDIT101 },
	{ IDC_EDIT49, IDC_EDIT103, IDC_EDIT134, IDC_EDIT111, IDC_EDIT129 },
	{ IDC_EDIT50, IDC_EDIT118, IDC_EDIT135, IDC_EDIT150, IDC_EDIT130 },
	{ IDC_EDIT51, IDC_EDIT119, IDC_EDIT136, IDC_EDIT151, IDC_EDIT131 },
	{ IDC_EDIT52, IDC_EDIT120, IDC_EDIT137, IDC_EDIT152, IDC_EDIT132 },
	{ IDC_EDIT53, IDC_EDIT121, IDC_EDIT138, IDC_EDIT153, IDC_EDIT146 },
	{ IDC_EDIT54, IDC_EDIT122, IDC_EDIT139, IDC_EDIT154, IDC_EDIT147 },
	{ IDC_EDIT55, IDC_EDIT123, IDC_EDIT140, IDC_EDIT155, IDC_EDIT148 },
	{ IDC_EDIT91, IDC_EDIT124, IDC_EDIT141, IDC_EDIT156, IDC_EDIT149 } };
	int structure1[7] = { 10, 5, EDITBX, EDITBX, EDITBX, EDITBX, EDITNUM };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 10; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(10); _vvSubformRecordRange.push_back(vStr);

}

CPersonalForm13::~CPersonalForm13()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm13::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm13::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio12_3_0);
}

BEGIN_MESSAGE_MAP(CPersonalForm13, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm13::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm13::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm13::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm13::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm13 诊断

#ifdef _DEBUG
void CPersonalForm13::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm13::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPersonalForm13::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm13::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm13::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm13::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm13::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm13::hasData(int isub, int irow)
{
	CString strText;

	if (isub == 1) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}

// CPersonalForm13 消息处理程序


void CPersonalForm13::OnBnClickedCmdSaveForm()
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

	if (m_Radio12_3_0 == 1)
	{
		ss << "update file_form_flags set file_19IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_19IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

#if 0
	int Parameters[10][5] = { { IDC_EDIT47, IDC_EDIT98, IDC_EDIT97, IDC_EDIT99, IDC_EDIT100 },
	{ IDC_EDIT48, IDC_EDIT102, IDC_EDIT133, IDC_EDIT110, IDC_EDIT101 },
	{ IDC_EDIT49, IDC_EDIT103, IDC_EDIT134, IDC_EDIT111, IDC_EDIT129 },
	{ IDC_EDIT50, IDC_EDIT118, IDC_EDIT135, IDC_EDIT150, IDC_EDIT130 },
	{ IDC_EDIT51, IDC_EDIT119, IDC_EDIT136, IDC_EDIT151, IDC_EDIT131 },
	{ IDC_EDIT52, IDC_EDIT120, IDC_EDIT137, IDC_EDIT152, IDC_EDIT132 },
	{ IDC_EDIT53, IDC_EDIT121, IDC_EDIT138, IDC_EDIT153, IDC_EDIT146 },
	{ IDC_EDIT54, IDC_EDIT122, IDC_EDIT139, IDC_EDIT154, IDC_EDIT147 },
	{ IDC_EDIT55, IDC_EDIT123, IDC_EDIT140, IDC_EDIT155, IDC_EDIT148 },
	{ IDC_EDIT91, IDC_EDIT124, IDC_EDIT141, IDC_EDIT156, IDC_EDIT149 }};

	double amount1, amount2 = 0;
	for (int i = 0; i < 10; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillAmount;

		ss << "insert into file_form_19 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "',"; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][1])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][4])->GetWindowTextW(strText); strText.Trim();
		amount1 = wcstod(strText.GetBuffer(), NULL);
		ss << amount1 << ")"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

		amount2 += amount1;
	}

FillAmount:
	strText.Format(_T("%f"), amount2);
	GetDlgItem(IDC_EDIT161)->SetWindowTextW(strText);
#endif

FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();

			 DoSaveForm();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm13::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm13::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm13::OnInitialUpdate()
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
	ss << "select file_19IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}
	m_Radio12_3_0 = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from file_form_19 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int Parameters[10][5] = { { IDC_EDIT47, IDC_EDIT98, IDC_EDIT97, IDC_EDIT99, IDC_EDIT100 },
	{ IDC_EDIT48, IDC_EDIT102, IDC_EDIT133, IDC_EDIT110, IDC_EDIT101 },
	{ IDC_EDIT49, IDC_EDIT103, IDC_EDIT134, IDC_EDIT111, IDC_EDIT129 },
	{ IDC_EDIT50, IDC_EDIT118, IDC_EDIT135, IDC_EDIT150, IDC_EDIT130 },
	{ IDC_EDIT51, IDC_EDIT119, IDC_EDIT136, IDC_EDIT151, IDC_EDIT131 },
	{ IDC_EDIT52, IDC_EDIT120, IDC_EDIT137, IDC_EDIT152, IDC_EDIT132 },
	{ IDC_EDIT53, IDC_EDIT121, IDC_EDIT138, IDC_EDIT153, IDC_EDIT146 },
	{ IDC_EDIT54, IDC_EDIT122, IDC_EDIT139, IDC_EDIT154, IDC_EDIT147 },
	{ IDC_EDIT55, IDC_EDIT123, IDC_EDIT140, IDC_EDIT155, IDC_EDIT148 },
	{ IDC_EDIT91, IDC_EDIT124, IDC_EDIT141, IDC_EDIT156, IDC_EDIT149 } };
	double sum = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 5; j++){
			GetDlgItem(Parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
			if (j == 4){
				sum += wcstod(CA2W(re[(i + 1) * col + j + 1]), NULL);
			}
		}
		if (i + 1 >= row) break;
	}

	CString str;
	str.Format(_T("%f"), sum);
	GetDlgItem(IDC_EDIT161)->SetWindowTextW(str);
	help->closeDB();
	delete help;
#endif

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
	ss << "select file_17IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio12_3_0 = -1;
	}
	else
		m_Radio12_3_0 = 1 - atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);
}

void CPersonalForm13::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	DoUpdateForm();
}
