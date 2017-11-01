// PersonalForm09.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm09.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm09

IMPLEMENT_DYNCREATE(CPersonalForm09, CFormView)

CPersonalForm09::CPersonalForm09()
: CFormView(CPersonalForm09::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm09::~CPersonalForm09()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm09::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

void CPersonalForm09::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO78, m_Radio11_3_1);
	DDX_Radio(pDX, IDC_RADIO82, m_Radio11_3_2);
	DDX_Radio(pDX, IDC_RADIO132, m_Radio11_3_3);
	DDX_Radio(pDX, IDC_RADIO85, m_Radio11_4_1);
	DDX_Radio(pDX, IDC_RADIO89, m_Radio11_4_2);
	DDX_Radio(pDX, IDC_RADIO125, m_Radio11_4_3);
	DDX_Radio(pDX, IDC_RADIO92, m_Radio11_5_1);
	DDX_Radio(pDX, IDC_RADIO96, m_Radio11_5_2);
	DDX_Radio(pDX, IDC_RADIO118, m_Radio11_5_3);
	DDX_Radio(pDX, IDC_RADIO99, m_Radio11_6_1);
	DDX_Radio(pDX, IDC_RADIO103, m_Radio11_6_2);
	DDX_Radio(pDX, IDC_RADIO106, m_Radio11_6_3);
}

BEGIN_MESSAGE_MAP(CPersonalForm09, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm09::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm09::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm09::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm09::OnBnClickedCmdUpdateForm3)
END_MESSAGE_MAP()


// CPersonalForm09 诊断

#ifdef _DEBUG
void CPersonalForm09::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm09::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm09 消息处理程序


void CPersonalForm09::OnBnClickedCmdSaveForm()
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
	int Parameters[4][8] = { { IDC_EDIT52, m_Radio11_3_1, m_Radio11_3_2, IDC_EDIT54, IDC_EDIT55, m_Radio11_3_3, IDC_EDIT103, IDC_EDIT105 },
	{ IDC_EDIT53, m_Radio11_4_1, m_Radio11_4_2, IDC_EDIT63, IDC_EDIT64, m_Radio11_4_3, IDC_EDIT107, IDC_EDIT108 },
	{ IDC_EDIT96, m_Radio11_5_1, m_Radio11_5_2, IDC_EDIT68, IDC_EDIT110, m_Radio11_5_3, IDC_EDIT114, IDC_EDIT116 },
	{ IDC_EDIT109, m_Radio11_6_1, m_Radio11_6_2, IDC_EDIT66, IDC_EDIT111, m_Radio11_6_3, IDC_EDIT115, IDC_EDIT117 } };

	for (int i = 0; i < 4; i++) {
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


FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm09::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm09::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm09::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	

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
	ss << "select * from file_form_16 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row <= 2) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	int Parameters[4][8] = { { IDC_EDIT52, m_Radio11_3_1, m_Radio11_3_2, IDC_EDIT54, IDC_EDIT55, m_Radio11_3_3, IDC_EDIT103, IDC_EDIT105 },
	{ IDC_EDIT53, m_Radio11_4_1, m_Radio11_4_2, IDC_EDIT63, IDC_EDIT64, m_Radio11_4_3, IDC_EDIT107, IDC_EDIT108 },
	{ IDC_EDIT96, m_Radio11_5_1, m_Radio11_5_2, IDC_EDIT68, IDC_EDIT110, m_Radio11_5_3, IDC_EDIT114, IDC_EDIT116 },
	{ IDC_EDIT109, m_Radio11_6_1, m_Radio11_6_2, IDC_EDIT66, IDC_EDIT111, m_Radio11_6_3, IDC_EDIT115, IDC_EDIT117 } };
	// TODO:  在此添加专用代码和/或调用基类
	int a = row;
	if (row > 6) row = 6;
	for (int i = 3; i <= row-1; i++){
		GetDlgItem(Parameters[i - 3][0])->SetWindowTextW(CA2W(re[ i * col + 1], CP_UTF8));
		GetDlgItem(Parameters[i - 3][3])->SetWindowTextW(CA2W(re[i * col + 4], CP_UTF8));
		GetDlgItem(Parameters[i - 3][4])->SetWindowTextW(CA2W(re[i * col + 5], CP_UTF8));
		GetDlgItem(Parameters[i - 3][6])->SetWindowTextW(CA2W(re[i * col + 7], CP_UTF8));
		GetDlgItem(Parameters[i - 3][7])->SetWindowTextW(CA2W(re[i * col + 8], CP_UTF8));
	}
	if (row >= 3){
		m_Radio11_3_1 = atoi(re[3 * col + 2]);
		m_Radio11_3_2 = atoi(re[3 * col + 3]);
		m_Radio11_3_3 = atoi(re[3 * col + 6]);
	}
	if (row >= 4){
		m_Radio11_4_1 = atoi(re[4 * col + 2]);
		m_Radio11_4_2 = atoi(re[4 * col + 3]);
		m_Radio11_4_3 = atoi(re[4 * col + 6]);
	}
	if (row >= 5){
		m_Radio11_5_1 = atoi(re[5 * col + 2]);
		m_Radio11_5_2 = atoi(re[5 * col + 3]);
		m_Radio11_5_3 = atoi(re[5 * col + 6]);
	}
	/*
	if (row == 6){
		m_Radio11_6_1 = atoi(re[6 * col + 2]);
		m_Radio11_6_2 = atoi(re[6 * col + 3]);
		m_Radio11_6_3 = atoi(re[6 * col + 6]);
	}
	*/
	help->closeDB();
	delete help;
	UpdateData(FALSE);
}

void CPersonalForm09::OnBnClickedCmdUpdateForm3()
{
	// TODO:  在此添加控件通知处理程序代码
}