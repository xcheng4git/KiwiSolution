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
, m_Radio11_1_1(0)
, m_Radio11_1_2(0)
, m_Radio11_1_3(0)
, m_Radio11_2_1(0)
, m_Radio11_2_2(0)
, m_Radio11_2_3(0)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm08::~CPersonalForm08()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm08::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

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
#pragma endregion

#pragma region FillForm10
FillForm10:
	if (m_Radio10_0 == 1)
	{
		ss << "update file_form_flags set file_15IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm11;
	}

	{
		ss << "update file_form_flags set file_15IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

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
#pragma endregion

#pragma region FillForm11
FillForm11 :
	GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_16IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_16IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (m_Radio11_0 == 1)
		{
			ss << "update file_form_flags set file_16IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio11_0 == 0)
		{
			ss << "update file_form_flags set file_16IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

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

#pragma endregion


FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm08::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm08::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void CPersonalForm08::OnBnClickedCmdUpdateForm3()
{
	// TODO:  在此添加控件通知处理程序代码
}
