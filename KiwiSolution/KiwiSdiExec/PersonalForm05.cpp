// PersonalForm05.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm05.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm05

IMPLEMENT_DYNCREATE(CPersonalForm05, CFormView)

CPersonalForm05::CPersonalForm05()
	: CFormView(CPersonalForm05::IDD)
	, m_Radio6_1(-1)
	, m_Radio6_1_1(-1)
	, m_Radio6_1_2(-1)
	, m_Radio6_1_3(-1)
	, m_Radio6_2(-1)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm05::~CPersonalForm05()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm05::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

void CPersonalForm05::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio6_1);
	DDX_Radio(pDX, IDC_RADIO19, m_Radio6_1_1);
	DDX_Radio(pDX, IDC_RADIO22, m_Radio6_1_2);
	DDX_Radio(pDX, IDC_RADIO25, m_Radio6_1_3);
	DDX_Radio(pDX, IDC_RADIO28, m_Radio6_2);
}

BEGIN_MESSAGE_MAP(CPersonalForm05, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm05::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm05::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm05::OnBnClickedButtonCloseForm3)
END_MESSAGE_MAP()


// CPersonalForm05 诊断

#ifdef _DEBUG
void CPersonalForm05::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm05::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm05 消息处理程序


void CPersonalForm05::OnBnClickedCmdSaveForm()
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
#pragma region FillForm6_1
FillForm6_1:
	GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_10IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm6_2;
	}

	{
		ss << "update file_form_flags set file_10IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if  (m_Radio6_1 == 1)
		{
			ss << "update file_form_flags set file_10IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm6_2;
		}
		else if (m_Radio6_1 == 0)
		{
			ss << "update file_form_flags set file_10IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	
	{
		ss << "insert into file_form_10 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT50)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT53)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		ss << m_Radio6_1_1 << ", ";
		//switch (m_Radio6_1_1) {
		//case 0: strText = _T("外国国籍"); break;
		//case 1: strText = _T("永久居留资格"); break;
		//case 2: strText = _T("长期居留许可"); break;
		//}
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT74)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_10 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT51)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT54)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			ss << m_Radio6_1_2 << ", ";
			//switch (m_Radio6_1_2) {
			//case 0: strText = _T("外国国籍"); break;
			//case 1: strText = _T("永久居留资格"); break;
			//case 2: strText = _T("长期居留许可"); break;
			//}
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER45)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT75)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm6_2;

		GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_10 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT49)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT55)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			ss << m_Radio6_1_3 << ", ";
			//switch (m_Radio6_1_2) {
			//case 0: strText = _T("外国国籍"); break;
			//case 1: strText = _T("永久居留资格"); break;
			//case 2: strText = _T("长期居留许可"); break;
			//}
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER46)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT76)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm6_2;
	}
	
#pragma endregion

#pragma region FillForm6_2
FillForm6_2:
	GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_11IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_11IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (m_Radio6_2 == 1)
		{
			ss << "update file_form_flags set file_11IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio6_2 == 0)
		{
			ss << "update file_form_flags set file_11IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	{
		ss << "insert into file_form_11 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT63)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT66)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER22)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT80)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT77)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_11 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT77)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT64)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT67)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER23)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT81)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;

		GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_11 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT62)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT65)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT68)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER24)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT82)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;
	}
#pragma endregion

FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm05::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm05::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}
