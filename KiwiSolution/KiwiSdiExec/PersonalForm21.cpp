// PersonalForm21.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm21.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"
#include "Utility.h"

// CPersonalForm21

IMPLEMENT_DYNCREATE(CPersonalForm21, CFormView)

CPersonalForm21::CPersonalForm21()
: CFormView(CPersonalForm21::IDD)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);

	//m_isCurrentModify = FALSE;
	m_FormID = 21;
	int parameters1[1][3] = { { IDC_EDIT237, IDC_EDIT58,0  } };
	int structure1[5] = { 1, 3, EDITBX, EDITBX, ATTACHMENTBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 3; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 5; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[3] = { _T("有无"), _T("年度"), _T("报告内容")};
	int structure10[3] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure11[4 + 2] = { -1, 1, 2, 2, 1, 1 };  //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....

	vector<CBookmarkEx> vBke;//循环次数改一下
	for (int i = 0; i < 3; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);

	
}

CPersonalForm21::~CPersonalForm21()
{
	//m_fontEdit.DeleteObject();

	//for (int i = 0; i < m_vFormRecid.size(); i++)
	//	CString(m_vFormRecid[i]).ReleaseBuffer();
}

//void CPersonalForm21::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


//void CPersonalForm21::SetModifyFlag(int flag)
//{
//	if (flag)
//		m_isCurrentModify = TRUE;
//}

void CPersonalForm21::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm21, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm21::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm21::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm21::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm21::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm21 诊断

#ifdef _DEBUG
void CPersonalForm21::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm21::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm21::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm21::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm21::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm21::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm21::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm21::hasData(int isub, int irow)
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
// CPersonalForm21 消息处理程序


void CPersonalForm21::OnBnClickedCmdSaveForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();

	CString strText;

	ss << "insert into file_form_27 values(" << file_id << ",";
	strText = CUtility::GetGuid();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT237)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << "21, " << "'" << CW2A(_T("表6"),CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoSaveForm();
	//保存盖章原件图片

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm21::OnBnClickedCmdPrintForm()
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

	help->closeDB(); delete help;

	ss.str("");  ss.clear();
	ss << "select * from file_form_27 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表6.dotx")));
}


void CPersonalForm21::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm21::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_EDIT237)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT58)->SetFont(&m_fontEdit);

#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;
	char *eee = "i"; char **result = &eee;
	char** re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from personal_form_info where file_id=" << file_id << " and ";
	ss << " form_serial='" << CW2A(_T("表6"), CP_UTF8) << "';";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	ss.str(""); ss.clear();
	ss << "select * from file_form_27 where file_id=" << file_id << " order by file_ReportYear desc limit 0,1;";

	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}
	CString str; str.Format(_T("%s"), CA2W(re[1 * col + 1], CP_UTF8));
	m_vFormRecid.push_back(str);

	GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT237)->SetWindowTextW( CA2W(re[1*col + 2], CP_UTF8) );
	GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));

	help->closeDB(); delete help;
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
		//显示图片

		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}
}


void CPersonalForm21::OnBnClickedCmdUpdateForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();


	CString strText;
	ss << "update file_form_27 set file_ReportYear=";
	GetDlgItem(IDC_EDIT237)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	ss << "\"file_Annual report form of social morality\"=";
	GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "'"; strText.ReleaseBuffer();

	ss << " where form_recid='" << CW2A(CString(m_vFormRecid[0]).GetBuffer(), CP_UTF8) << "';";

	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	ss.str("");  ss.clear();
	ss << "update personal_form_info set modify_date=";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' "; strText.ReleaseBuffer();
	ss << " where file_id=" << file_id << " and form_serial=";
	ss << "'" << CW2A(_T("表6"), CP_UTF8) << "';";

	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoUpdateForm();

	//更新图片地址
}
