// PersonalForm24.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm24.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm24

IMPLEMENT_DYNCREATE(CPersonalForm24, CFormView)

CPersonalForm24::CPersonalForm24()
: CFormView(CPersonalForm24::IDD)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 24;
	int parameters1[1][2] = { { IDC_EDIT342, IDC_EDIT343 } };
	int structure1[4] = { 1, 2, EDITBX, EDITBX};
	int parameters2[6][3] = { { IDC_EDIT325, IDC_EDIT330, IDC_EDIT341 },
	{ IDC_EDIT302, IDC_EDIT331, IDC_EDIT340 },
	{ IDC_EDIT326, IDC_EDIT332, IDC_EDIT339 },
	{ IDC_EDIT327, IDC_EDIT333, IDC_EDIT338 },
	{ IDC_EDIT328, IDC_EDIT334, IDC_EDIT337 },
	{ IDC_EDIT329, IDC_EDIT335, IDC_EDIT336 } };
	int structure2[5] = { 6, 3, EDITBX, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 2; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 6; i++) {
		vector<int> vPara;
		for (int j = 0; j < 3; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 4; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 5; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
}

CPersonalForm24::~CPersonalForm24()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm24::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


void CPersonalForm24::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm24, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm24::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm24::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm24::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm24::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm24 诊断

#ifdef _DEBUG
void CPersonalForm24::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm24::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm24::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm24::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm24::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm24::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm24::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm24::hasData(int isub, int irow)
{
	CString strText;

	if ((isub == 1) || (isub == 2)){
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}
// CPersonalForm24 消息处理程序


void CPersonalForm24::OnBnClickedCmdSaveForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
#if 0
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

	ss << "insert into file_form_30_0 values(" << file_id << ",";
	GetDlgItem(IDC_EDIT342)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT343)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

	GetDlgItem(IDC_EDIT325)->GetWindowTextW(strText); strText.Trim();
	if (strText.IsEmpty()) {
		strText.ReleaseBuffer();
		goto FillComplete;
	}

	int parameters[6][3] = { { IDC_EDIT325, IDC_EDIT330, IDC_EDIT341 },
	{ IDC_EDIT302, IDC_EDIT331, IDC_EDIT340 }, 
	{ IDC_EDIT326, IDC_EDIT332, IDC_EDIT339 }, 
	{ IDC_EDIT327, IDC_EDIT333, IDC_EDIT338 }, 
	{ IDC_EDIT328, IDC_EDIT334, IDC_EDIT337 }, 
	{ IDC_EDIT329, IDC_EDIT335, IDC_EDIT336 }};

	for (int i = 0; i < 6; i++) {
		ss << "insert into file_form_30 values(" << file_id << ",";
		for (int j = 0; j < 2; j++) {
			GetDlgItem(parameters[i][j])->GetWindowTextW(strText); strText.Trim();
			if (strText.IsEmpty()) {
				strText.ReleaseBuffer();
				goto FillComplete;
			}
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		}
		GetDlgItem(parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoSaveForm();

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm24::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm24::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm24::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_EDIT342)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT343)->SetFont(&m_fontEdit);
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
	ss << "select * from file_form_30_0 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	GetDlgItem(IDC_EDIT342)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
	GetDlgItem(IDC_EDIT343)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));

	ss.str(""); ss.clear();
	ss << "select * from file_form_30 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int parameters[6][3] = { { IDC_EDIT325, IDC_EDIT330, IDC_EDIT341 },
	{ IDC_EDIT302, IDC_EDIT331, IDC_EDIT340 },
	{ IDC_EDIT326, IDC_EDIT332, IDC_EDIT339 },
	{ IDC_EDIT327, IDC_EDIT333, IDC_EDIT338 },
	{ IDC_EDIT328, IDC_EDIT334, IDC_EDIT337 },
	{ IDC_EDIT329, IDC_EDIT335, IDC_EDIT336 } };

	COleDateTime t;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 3; j++){
			GetDlgItem(parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
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
}


void CPersonalForm24::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	DoUpdateForm();
}
