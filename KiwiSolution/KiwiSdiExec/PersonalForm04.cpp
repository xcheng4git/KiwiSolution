// PersonalForm04.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm04.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm04

IMPLEMENT_DYNCREATE(CPersonalForm04, CFormView)

CPersonalForm04::CPersonalForm04()
	: CFormView(CPersonalForm04::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm04::~CPersonalForm04()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm04::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

void CPersonalForm04::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm04, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm04::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm04::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm04::OnBnClickedButtonCloseForm3)
END_MESSAGE_MAP()


// CPersonalForm04 诊断

#ifdef _DEBUG
void CPersonalForm04::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm04::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm04 消息处理程序


void CPersonalForm04::OnBnClickedCmdSaveForm()
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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	CString strText;
#pragma region FillForm3_2
	{
		if (((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_7IfHaveThisSituation=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm4;
		}

		ss << "update file_form_flags set file_7IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		ss << "insert into file_form_7 values(" << file_id << ",";

		GetDlgItem(IDC_DATETIMEPICKER5)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER6)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT11)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT24)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT27)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT30)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	{
		GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";

			strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER7)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER8)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT25)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT28)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT31)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm4;

		GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";

			strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER9)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER10)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT26)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT29)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT32)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
#pragma endregion

#pragma region FillForm4
FillForm4:
	GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_8IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm5;
	}

	{
		ss << "update file_form_flags set file_8IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO16))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_8IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm5;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO15))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_8IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	{
		ss << "insert into file_form_8 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT50)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT53)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT56)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER3)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_8 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT51)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT54)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT57)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER17)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm5;

		GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_8 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT49)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT55)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER18)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm5;
	}
#pragma endregion

#pragma region FillForm5
FillForm5:
	GetDlgItem(IDC_EDIT60)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_9IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_9IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO16))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_9IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO15))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_9IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	{
		ss << "insert into file_form_9 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT60)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT62)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT65)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT68)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT71)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER19)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT59)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_9 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT59)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT63)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT66)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT69)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT72)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER20)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;

		GetDlgItem(IDC_EDIT61)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_9 values(" << file_id << ",";

			GetDlgItem(IDC_EDIT61)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT64)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT67)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT70)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT73)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER21)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;
	}
#pragma endregion


FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm04::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm04::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void CPersonalForm04::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	#pragma region FillForm3_2
	{
		
	}
	#pragma endregion

	#pragma region FillForm4
	FillForm4 :
	{
		

		ss.str(""); ss.clear();
		ss << "select file_8IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}
		//m_Radio14_1_0 = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select * from file_form_08 where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			goto FillForm5;
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}

		COleDateTime t;

		GetDlgItem(IDC_EDIT45)->SetWindowTextW(CA2W(re[ 1 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT47)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT50)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT53)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT56)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[1 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3)->SetTime(t);

		GetDlgItem(IDC_EDIT33)->SetWindowTextW(CA2W(re[2 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT48)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT51)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT54)->SetWindowTextW(CA2W(re[2 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT57)->SetWindowTextW(CA2W(re[2 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[2 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER17)->SetTime(t);

		GetDlgItem(IDC_EDIT46)->SetWindowTextW(CA2W(re[3 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT49)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT52)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT55)->SetWindowTextW(CA2W(re[3 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[3 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[3 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER18)->SetTime(t);
	}
	#pragma endregion

	#pragma region FillForm5
	FillForm5 :
	{
		ss.str(""); ss.clear();
		ss << "select file_9IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}
		//m_Radio14_1_0 = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select * from file_form_09 where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			goto FillComplete;
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}

		COleDateTime t;

		GetDlgItem(IDC_EDIT60)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT62)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT65)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT68)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT71)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[1 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER19)->SetTime(t);

		GetDlgItem(IDC_EDIT59)->SetWindowTextW(CA2W(re[2 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT63)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT66)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT69)->SetWindowTextW(CA2W(re[2 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT72)->SetWindowTextW(CA2W(re[2 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[2 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER20)->SetTime(t);
			
		GetDlgItem(IDC_EDIT61)->SetWindowTextW(CA2W(re[3 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT64)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT67)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT70)->SetWindowTextW(CA2W(re[3 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT73)->SetWindowTextW(CA2W(re[3 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[3 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER21)->SetTime(t);
	}
	#pragma endregion


	FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();


}
