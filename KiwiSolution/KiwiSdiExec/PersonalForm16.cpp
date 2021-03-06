// PersonalForm16.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm16.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm16

IMPLEMENT_DYNCREATE(CPersonalForm16, CFormView)

CPersonalForm16::CPersonalForm16()
	: CFormView(CPersonalForm16::IDD)
	, m_Radio14_2_0(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 16;
	int parameters1[9][6] = { { IDC_EDIT55, IDC_EDIT56, IDC_EDIT58, IDC_EDIT203, IDC_EDIT212, IDC_EDIT221 },
	{ IDC_EDIT90, IDC_EDIT92, IDC_EDIT94, IDC_EDIT204, IDC_EDIT213, IDC_EDIT222 },
	{ IDC_EDIT182, IDC_EDIT189, IDC_EDIT196, IDC_EDIT205, IDC_EDIT214, IDC_EDIT223 },
	{ IDC_EDIT183, IDC_EDIT190, IDC_EDIT197, IDC_EDIT206, IDC_EDIT215, IDC_EDIT224 },
	{ IDC_EDIT184, IDC_EDIT191, IDC_EDIT198, IDC_EDIT207, IDC_EDIT216, IDC_EDIT225 },
	{ IDC_EDIT185, IDC_EDIT192, IDC_EDIT199, IDC_EDIT208, IDC_EDIT217, IDC_EDIT226 },
	{ IDC_EDIT186, IDC_EDIT193, IDC_EDIT200, IDC_EDIT209, IDC_EDIT218, IDC_EDIT227 },
	{ IDC_EDIT187, IDC_EDIT194, IDC_EDIT201, IDC_EDIT210, IDC_EDIT219, IDC_EDIT228 },
	{ IDC_EDIT188, IDC_EDIT195, IDC_EDIT202, IDC_EDIT211, IDC_EDIT220, IDC_EDIT229 } };
	int structure1[8] = { 9, 6, EDITBX, EDITBX, EDITBX, EDITBX, EDITNUM, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 9; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(9); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[7] = { _T("有无"), _T("投资人姓名"), _T("投资的国家"), _T("投资情况"), _T("币种"), _T("投资金额"), _T("备注") };
	int structure10[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX
		};
	int structure11[3 + 1 + 7] = { 0, 9, 6, 2,     2,   1, 1, 1, 1, 1, 1, }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	//



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
	
}

CPersonalForm16::~CPersonalForm16()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm16::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm16::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio14_2_0);
}

BEGIN_MESSAGE_MAP(CPersonalForm16, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm16::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm16::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm16::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm16::OnBnClickedCmdUpdateForm)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm16::OnBnClickedCmdNextForm)
END_MESSAGE_MAP()


// CPersonalForm16 诊断

#ifdef _DEBUG
void CPersonalForm16::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm16::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm16::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm16::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm16::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm16::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm16::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm16::hasData(int isub, int irow)
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
// CPersonalForm16 消息处理程序


void CPersonalForm16::OnBnClickedCmdSaveForm()
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
#pragma region FillForm16
FillForm16 :
	ss << "update file_form_flags set file_22IfHaveThisSituation=" << m_Radio14_2_0 << " where file_id=" << file_id;
	TRACE(_T("\r\n%s"), CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

#if 0
	int Parameters[9][6] = { { IDC_EDIT55, IDC_EDIT56, IDC_EDIT58, IDC_EDIT203, IDC_EDIT212, IDC_EDIT221 },
	{ IDC_EDIT90, IDC_EDIT92, IDC_EDIT94, IDC_EDIT204, IDC_EDIT213, IDC_EDIT222 },
	{ IDC_EDIT182, IDC_EDIT189, IDC_EDIT196, IDC_EDIT205, IDC_EDIT214, IDC_EDIT223 },
	{ IDC_EDIT183, IDC_EDIT190, IDC_EDIT197, IDC_EDIT206, IDC_EDIT215, IDC_EDIT224 },
	{ IDC_EDIT184, IDC_EDIT191, IDC_EDIT198, IDC_EDIT207, IDC_EDIT216, IDC_EDIT225 },
	{ IDC_EDIT185, IDC_EDIT192, IDC_EDIT199, IDC_EDIT208, IDC_EDIT217, IDC_EDIT226 },
	{ IDC_EDIT186, IDC_EDIT193, IDC_EDIT200, IDC_EDIT209, IDC_EDIT218, IDC_EDIT227 },
	{ IDC_EDIT187, IDC_EDIT194, IDC_EDIT201, IDC_EDIT210, IDC_EDIT219, IDC_EDIT228 },
	{ IDC_EDIT188, IDC_EDIT195, IDC_EDIT202, IDC_EDIT211, IDC_EDIT220, IDC_EDIT229 } };

	for (int i = 0; i < 9; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_22 values(" << file_id << ",";

		ss << "'" << strText << "',"; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][1])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][5])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

	}
#endif
#pragma endregion


FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();

			 DoSaveForm();

			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm16::OnBnClickedCmdPrintForm()
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

	
	ss.str(""); ss.clear();
	ss << "select * from file_form_22 where file_id=" << file_id << " limit 0,9;";
	_vSubformQueryString.push_back(ss.str());
	
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-15.dotx")));

}


void CPersonalForm16::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm16::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

#if 0
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
	ss << "select file_22IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}
	m_Radio14_2_0 = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from file_form_22 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int Parameters[9][6] = { { IDC_EDIT55, IDC_EDIT56, IDC_EDIT58, IDC_EDIT203, IDC_EDIT212, IDC_EDIT221 },
	{ IDC_EDIT90, IDC_EDIT92, IDC_EDIT94, IDC_EDIT204, IDC_EDIT213, IDC_EDIT222 },
	{ IDC_EDIT182, IDC_EDIT189, IDC_EDIT196, IDC_EDIT205, IDC_EDIT214, IDC_EDIT223 },
	{ IDC_EDIT183, IDC_EDIT190, IDC_EDIT197, IDC_EDIT206, IDC_EDIT215, IDC_EDIT224 },
	{ IDC_EDIT184, IDC_EDIT191, IDC_EDIT198, IDC_EDIT207, IDC_EDIT216, IDC_EDIT225 },
	{ IDC_EDIT185, IDC_EDIT192, IDC_EDIT199, IDC_EDIT208, IDC_EDIT217, IDC_EDIT226 },
	{ IDC_EDIT186, IDC_EDIT193, IDC_EDIT200, IDC_EDIT209, IDC_EDIT218, IDC_EDIT227 },
	{ IDC_EDIT187, IDC_EDIT194, IDC_EDIT201, IDC_EDIT210, IDC_EDIT219, IDC_EDIT228 },
	{ IDC_EDIT188, IDC_EDIT195, IDC_EDIT202, IDC_EDIT211, IDC_EDIT220, IDC_EDIT229 } };
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 6; j++){
			GetDlgItem(Parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
		}
		if (i + 1 >= row) break;
	}
	help->closeDB();
	delete help;
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
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}

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
	ss << "select file_22IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio14_2_0 = -1;
	}
	else
		m_Radio14_2_0 = atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);
}


void CPersonalForm16::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();

	DoUpdateFlag(1, 0, m_Radio14_2_0);
}


void CPersonalForm16::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(17), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}
