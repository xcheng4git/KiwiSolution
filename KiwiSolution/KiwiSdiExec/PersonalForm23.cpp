// PersonalForm23.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm23.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm23

IMPLEMENT_DYNCREATE(CPersonalForm23, CFormView)

CPersonalForm23::CPersonalForm23()
: CFormView(CPersonalForm23::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm23::~CPersonalForm23()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm23::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}


void CPersonalForm23::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm23, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm23::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm23::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm23::OnBnClickedButtonCloseForm3)
END_MESSAGE_MAP()


// CPersonalForm23 诊断

#ifdef _DEBUG
void CPersonalForm23::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm23::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm23 消息处理程序


void CPersonalForm23::OnBnClickedCmdSaveForm()
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

	CString strText;
	GetDlgItem(IDC_EDIT302)->GetWindowTextW(strText); strText.Trim();
	if (strText.IsEmpty()) {
		strText.ReleaseBuffer();
		goto FillComplete;
	}

	int parameters[8] = { IDC_EDIT302, IDC_DATETIMEPICKER28, IDC_EDIT237, IDC_EDIT238, IDC_EDIT239, IDC_EDIT240, IDC_EDIT241, IDC_EDIT242 };

	ss << "insert into file_form_29 values(" << file_id << ",";
	for (int i = 0; i < 4; i++){
		GetDlgItem(parameters[i])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}
	GetDlgItem(parameters[4])->GetWindowTextW(strText); strText.Trim();
	ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
	GetDlgItem(parameters[5])->GetWindowTextW(strText); strText.Trim();
	ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

	GetDlgItem(parameters[6])->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(parameters[7])->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm23::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm23::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void CPersonalForm23::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	GetDlgItem(IDC_EDIT302)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_DATETIMEPICKER28)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT237)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT238)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT239)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT240)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT241)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT242)->SetFont(&m_fontEdit);



	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	//根据界面中文本内容得到对应的特定ID
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;

	char *eee = "i"; char **result = &eee;//未使用
	//sql条件限制所以取到一条记录
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);//取结果集中file_id字段 

	//GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8)) ;

	ss.str("");

	ss << "select * from file_form_29 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	GetDlgItem(IDC_EDIT302)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));//从数据取到数据根据对应ID填入界面
	GetDlgItem(IDC_DATETIMEPICKER28)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	GetDlgItem(IDC_EDIT237)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));
	GetDlgItem(IDC_EDIT238)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
	GetDlgItem(IDC_EDIT239)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
	GetDlgItem(IDC_EDIT240)->SetWindowTextW(CA2W(re[1 * col + 6], CP_UTF8));
	GetDlgItem(IDC_EDIT241)->SetWindowTextW(CA2W(re[1 * col + 7], CP_UTF8));
	GetDlgItem(IDC_EDIT242)->SetWindowTextW(CA2W(re[1 * col + 8], CP_UTF8));


	help->closeDB();
	delete help;//+++++++

}
