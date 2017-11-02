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
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm14::~CPersonalForm14()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm14::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

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
	{
		ss << "update file_form_flags set file_20IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_20IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (m_Radio13_0 == 1)
		{
			ss << "update file_form_flags set file_20IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio13_0 == 0)
		{
			ss << "update file_form_flags set file_20IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	for (int i = 0; i < 2; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_20 values(" << file_id << ",";

		ss << "'" << strText << "',"; strText.ReleaseBuffer();

		for (int j = 1; j < 7; j++) {
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

FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm14::OnBnClickedCmdPrintForm2()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm14::OnBnClickedButtonCloseForm4()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void CPersonalForm14::OnBnClickedCmdUpdateForm2()
{
	// TODO:  在此添加控件通知处理程序代码
}
