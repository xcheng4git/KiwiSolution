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
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm06::~CPersonalForm06()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm06::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

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
FillForm7_1 :
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

#pragma endregion

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

FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm06::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm06::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}
