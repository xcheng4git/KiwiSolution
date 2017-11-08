// PersonalForm27.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm27.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm27

IMPLEMENT_DYNCREATE(CPersonalForm27, CFormView)

CPersonalForm27::CPersonalForm27()
	: CFormView(CPersonalForm27::IDD)
{
	m_FormID = 27;
	int parameters1[1][14] = { { IDC_EDIT1, IDC_EDIT12, IDC_EDIT13, IDC_EDIT345, IDC_EDIT344, IDC_EDIT346, IDC_EDIT347, 
		IDC_EDIT370, IDC_EDIT371, IDC_EDIT350, IDC_EDIT351, IDC_EDIT372, IDC_EDIT373, IDC_EDIT374 } };
	int structure1[16] = { 1, 6, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 14; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 16; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);
}

CPersonalForm27::~CPersonalForm27()
{
}

void CPersonalForm27::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm27, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm27::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm27::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm27::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm27::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm27 诊断

#ifdef _DEBUG
void CPersonalForm27::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm27::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm27::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm27::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm27::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm27::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm27::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm27::hasData(int isub, int irow)
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
// CPersonalForm27 消息处理程序


void CPersonalForm27::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
	DoSaveForm();

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm27::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm27::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}

void CPersonalForm27::OnBnClickedCmdUpdateForm()
{
	DoUpdateForm();
}


void CPersonalForm27::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	int i = 0;
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		while (itVVparameter != itVVVparameter->end()) {
			int j = 0;

			vector<int>::iterator itV = itVVparameter->begin();
			while (itV != itVVparameter->end()) {
				if (_vvSubformStructure[i][2 + j] != ATTACHMENTBX) {
					GetDlgItem(*itV)->SetFont(&m_fontEdit);
				}

				itV++; j++;
			}
			itVVparameter++;
		}
		itVVVparameter++; i++;
	}

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
	else {
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
		ss << "select file_name, file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << file_id << ";";
		TRACE(CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			GetDlgItem(IDC_EDIT345)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
			GetDlgItem(IDC_EDIT346)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
			GetDlgItem(IDC_EDIT344)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		}

		help->closeDB(); delete help;
	}
}
