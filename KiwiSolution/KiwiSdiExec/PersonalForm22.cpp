// PersonalForm22.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm22.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm22

IMPLEMENT_DYNCREATE(CPersonalForm22, CFormView)

CPersonalForm22::CPersonalForm22()
: CFormView(CPersonalForm22::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

CPersonalForm22::~CPersonalForm22()
{
	m_fontEdit.DeleteObject();
}

void CPersonalForm22::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}


void CPersonalForm22::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm22, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm22::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm22::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm22::OnBnClickedButtonCloseForm3)
END_MESSAGE_MAP()


// CPersonalForm22 诊断

#ifdef _DEBUG
void CPersonalForm22::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm22::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm22 消息处理程序


void CPersonalForm22::OnBnClickedCmdSaveForm()
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

	int Parameters[16][6] = { { IDC_EDIT264, IDC_EDIT248, IDC_EDIT236, IDC_EDIT237, IDC_DATETIMEPICKER25, IDC_EDIT259  },
	{ IDC_EDIT253, IDC_EDIT238, IDC_EDIT260, IDC_EDIT226, IDC_DATETIMEPICKER27, IDC_EDIT249 }, 
	{ IDC_EDIT254, IDC_EDIT239, IDC_EDIT261, IDC_EDIT227, IDC_DATETIMEPICKER28, IDC_EDIT250 },
	{ IDC_EDIT255, IDC_EDIT240, IDC_EDIT262, IDC_EDIT228, IDC_DATETIMEPICKER28, IDC_EDIT251 },
	{ IDC_EDIT256, IDC_EDIT241, IDC_EDIT263, IDC_EDIT229, IDC_DATETIMEPICKER30, IDC_EDIT252 },
	{ IDC_EDIT267, IDC_EDIT274, IDC_EDIT302, IDC_EDIT308, IDC_DATETIMEPICKER31, IDC_EDIT318 },
	{ IDC_EDIT257, IDC_EDIT242, IDC_EDIT279, IDC_EDIT230, IDC_DATETIMEPICKER32, IDC_EDIT314 },
	{ IDC_EDIT258, IDC_EDIT243, IDC_EDIT280, IDC_EDIT231, IDC_DATETIMEPICKER33, IDC_EDIT315 },
	{ IDC_EDIT265, IDC_EDIT244, IDC_EDIT281, IDC_EDIT232, IDC_DATETIMEPICKER34, IDC_EDIT316 },
	{ IDC_EDIT266, IDC_EDIT245, IDC_EDIT282, IDC_EDIT233, IDC_DATETIMEPICKER34, IDC_EDIT317 },
	{ IDC_EDIT272, IDC_EDIT277, IDC_EDIT303, IDC_EDIT334, IDC_DATETIMEPICKER36, IDC_EDIT323 },
	{ IDC_EDIT268, IDC_EDIT246, IDC_EDIT284, IDC_EDIT313, IDC_DATETIMEPICKER37, IDC_EDIT319 },
	{ IDC_EDIT269, IDC_EDIT247, IDC_EDIT304, IDC_EDIT309, IDC_DATETIMEPICKER37, IDC_EDIT320 },
	{ IDC_EDIT270, IDC_EDIT275, IDC_EDIT305, IDC_EDIT310, IDC_DATETIMEPICKER39, IDC_EDIT321 },
	{ IDC_EDIT271, IDC_EDIT276, IDC_EDIT306, IDC_EDIT311, IDC_DATETIMEPICKER40, IDC_EDIT322 },
	{ IDC_EDIT273, IDC_EDIT278, IDC_EDIT307, IDC_EDIT312, IDC_DATETIMEPICKER41, IDC_EDIT324 }};

	for (int i = 0; i < 16; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty()) {
			strText.ReleaseBuffer();
			break;
		}

		ss << "insert into file_form_28 values(" << file_id << ",";
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][1])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][5])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm22::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm22::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void CPersonalForm22::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_EDIT237)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT58)->SetFont(&m_fontEdit);
}
