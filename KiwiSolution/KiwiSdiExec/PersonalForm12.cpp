// PersonalForm12.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm12.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm12

IMPLEMENT_DYNCREATE(CPersonalForm12, CFormView)

CPersonalForm12::CPersonalForm12()
: CFormView(CPersonalForm12::IDD)
, m_Radio12_2_0(0)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm12::~CPersonalForm12()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm12::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

void CPersonalForm12::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio12_2_0);
}

BEGIN_MESSAGE_MAP(CPersonalForm12, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm12::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm12::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm12::OnBnClickedButtonCloseForm3)
END_MESSAGE_MAP()


// CPersonalForm12 诊断

#ifdef _DEBUG
void CPersonalForm12::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm12::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm12 消息处理程序


void CPersonalForm12::OnBnClickedCmdSaveForm()
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
	int Parameters[14][4] = { { IDC_EDIT47, IDC_EDIT98, IDC_EDIT97, IDC_EDIT99 },
	{ IDC_EDIT48, IDC_EDIT102, IDC_EDIT133, IDC_EDIT110 },
	{ IDC_EDIT49, IDC_EDIT103, IDC_EDIT134, IDC_EDIT111 },
	{ IDC_EDIT50, IDC_EDIT118, IDC_EDIT135, IDC_EDIT150 },
	{ IDC_EDIT51, IDC_EDIT119, IDC_EDIT136, IDC_EDIT151 },
	{ IDC_EDIT52, IDC_EDIT120, IDC_EDIT137, IDC_EDIT152 },
	{ IDC_EDIT53, IDC_EDIT121, IDC_EDIT138, IDC_EDIT153 },
	{ IDC_EDIT54, IDC_EDIT122, IDC_EDIT139, IDC_EDIT154 },
	{ IDC_EDIT55, IDC_EDIT123, IDC_EDIT140, IDC_EDIT155 },
	{ IDC_EDIT91, IDC_EDIT124, IDC_EDIT141, IDC_EDIT156 },
	{ IDC_EDIT92, IDC_EDIT125, IDC_EDIT142, IDC_EDIT157 },
	{ IDC_EDIT93, IDC_EDIT126, IDC_EDIT143, IDC_EDIT158 },
	{ IDC_EDIT94, IDC_EDIT127, IDC_EDIT144, IDC_EDIT159 },
	{ IDC_EDIT95, IDC_EDIT128, IDC_EDIT145, IDC_EDIT160 }};

	double amount1, amount2=0;
	for (int i = 0; i < 14; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_18 values(" << file_id << ",";

		ss << "'" << strText << "',"; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][1])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		amount1 = wcstod(strText.GetBuffer(), NULL);
		ss << amount1 << ")"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

		amount2 += amount1;
	}


FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);

			 strText.Format(_T("%f"), amount2);
			 GetDlgItem(IDC_EDIT161)->SetWindowTextW(strText);
}


void CPersonalForm12::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm12::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}
