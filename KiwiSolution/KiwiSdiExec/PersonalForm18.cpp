// PersonalForm18.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm18.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm18

IMPLEMENT_DYNCREATE(CPersonalForm18, CFormView)

CPersonalForm18::CPersonalForm18()
: CFormView(CPersonalForm18::IDD)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 18;
	int parameters1[10][6] = { {IDC_DATETIMEPICKER25, IDC_EDIT236, IDC_EDIT237, IDC_EDIT248, IDC_EDIT259 },
	{ IDC_DATETIMEPICKER27, IDC_EDIT260, IDC_EDIT226, IDC_EDIT238, IDC_EDIT249 },
	{ IDC_DATETIMEPICKER28, IDC_EDIT261, IDC_EDIT227, IDC_EDIT239, IDC_EDIT250 },
	{ IDC_DATETIMEPICKER29, IDC_EDIT262, IDC_EDIT228, IDC_EDIT240, IDC_EDIT251 },
	{ IDC_DATETIMEPICKER30, IDC_EDIT263, IDC_EDIT229, IDC_EDIT241, IDC_EDIT252 },
	{ IDC_DATETIMEPICKER31, IDC_EDIT264, IDC_EDIT230, IDC_EDIT242, IDC_EDIT253 },
	{ IDC_DATETIMEPICKER32, IDC_EDIT265, IDC_EDIT231, IDC_EDIT243, IDC_EDIT254 },
	{ IDC_DATETIMEPICKER33, IDC_EDIT266, IDC_EDIT232, IDC_EDIT244, IDC_EDIT255 },
	{ IDC_DATETIMEPICKER34, IDC_EDIT267, IDC_EDIT233, IDC_EDIT245, IDC_EDIT256 },
	{ IDC_DATETIMEPICKER35, IDC_EDIT268, IDC_EDIT234, IDC_EDIT246, IDC_EDIT257 } };
	int structure1[7] = { 10, 5, DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX };
	int parameters2[9][5] = { { IDC_DATETIMEPICKER36, IDC_EDIT269, IDC_EDIT235, IDC_EDIT247, IDC_EDIT258 },
	{ IDC_DATETIMEPICKER37, IDC_EDIT270, IDC_EDIT278, IDC_EDIT286, IDC_EDIT294 },
	{ IDC_DATETIMEPICKER38, IDC_EDIT271, IDC_EDIT279, IDC_EDIT287, IDC_EDIT295 },
	{ IDC_DATETIMEPICKER39, IDC_EDIT272, IDC_EDIT280, IDC_EDIT288, IDC_EDIT296 },
	{ IDC_DATETIMEPICKER40, IDC_EDIT273, IDC_EDIT281, IDC_EDIT289, IDC_EDIT297 },
	{ IDC_DATETIMEPICKER41, IDC_EDIT274, IDC_EDIT282, IDC_EDIT290, IDC_EDIT298 },
	{ IDC_DATETIMEPICKER42, IDC_EDIT275, IDC_EDIT283, IDC_EDIT291, IDC_EDIT299 },
	{ IDC_DATETIMEPICKER43, IDC_EDIT276, IDC_EDIT284, IDC_EDIT292, IDC_EDIT300 },
	{ IDC_DATETIMEPICKER44, IDC_EDIT277, IDC_EDIT285, IDC_EDIT293, IDC_EDIT301 } };
	int structure2[7] = { 9, 5, DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 10; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 9; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(10); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(9); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[6] = { _T("有无"), _T("时间"), _T("获奖单位"), _T("资历机关"), _T("文号"), _T("备注") };
	int structure10[6] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure11[3 + 1 + 6] = { -1, 9, 5, 2,  2, 1, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	//
	const wchar_t *pBookmarks2[6] = { _T("有无"), _T("时间"), _T("获奖单位"), _T("资历机关"), _T("文号"), _T("备注") };
	int structure20[6] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure21[3 + 1 + 6] = { -1, 9, 5, 2, 2, 1, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	//
	const wchar_t *pBookmarks3[4] = { _T("有无"), _T("姓名"), _T("单位"), _T("职务") };
	int structure30[4] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[3 + 1 + 4] = { -1, 1, 3, 0, 2, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 6; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 6; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 4; i++) {
		CBookmarkEx bookmark(structure30[i], pBookmarks3[i], structure31[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure21[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure31[i]);
	_vvSubformFlags.push_back(vStr);
	
}

CPersonalForm18::~CPersonalForm18()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm18::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm18::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm18, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm18::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm18::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm18::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm18::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm18 诊断

#ifdef _DEBUG
void CPersonalForm18::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm18::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPersonalForm18::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm18::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm18::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm18::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm18::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm18::hasData(int isub, int irow)
{
	CString strText;

	if ((isub == 1) || (isub == 2)) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][1])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}
// CPersonalForm18 消息处理程序


void CPersonalForm18::OnBnClickedCmdSaveForm()
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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	CString strText;
#pragma region FillForm18
FillForm18 :

	int Parameters1[10][5] = { { IDC_DATETIMEPICKER25, IDC_EDIT236, IDC_EDIT237, IDC_EDIT248, IDC_EDIT259 },
	{ IDC_DATETIMEPICKER27, IDC_EDIT260, IDC_EDIT226, IDC_EDIT238, IDC_EDIT249 },
	{ IDC_DATETIMEPICKER28, IDC_EDIT261, IDC_EDIT227, IDC_EDIT239, IDC_EDIT250 },
	{ IDC_DATETIMEPICKER29, IDC_EDIT262, IDC_EDIT228, IDC_EDIT240, IDC_EDIT251 },
	{ IDC_DATETIMEPICKER30, IDC_EDIT263, IDC_EDIT229, IDC_EDIT241, IDC_EDIT252 },
	{ IDC_DATETIMEPICKER31, IDC_EDIT264, IDC_EDIT230, IDC_EDIT242, IDC_EDIT253 },
	{ IDC_DATETIMEPICKER32, IDC_EDIT265, IDC_EDIT231, IDC_EDIT243, IDC_EDIT254 },
	{ IDC_DATETIMEPICKER33, IDC_EDIT266, IDC_EDIT232, IDC_EDIT244, IDC_EDIT255 },
	{ IDC_DATETIMEPICKER34, IDC_EDIT267, IDC_EDIT233, IDC_EDIT245, IDC_EDIT256 },
	{ IDC_DATETIMEPICKER35, IDC_EDIT268, IDC_EDIT234, IDC_EDIT246, IDC_EDIT257 } };
	for (int i = 0; i < 10; i++) {
		GetDlgItem(Parameters1[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty()) {
			strText.ReleaseBuffer();
			break;
		}

		ss << "insert into file_form_24 values(" << file_id << ",";
		ss << 1 << ",";
		for (int j = 0; j < 4; j++) {
			GetDlgItem(Parameters1[i][j])->GetWindowTextW(strText); strText.Trim();
			ss << "'" << strText << "',"; strText.ReleaseBuffer();
		}
		GetDlgItem(Parameters1[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	int Parameters2[9][5] = { { IDC_DATETIMEPICKER36, IDC_EDIT269, IDC_EDIT235, IDC_EDIT247, IDC_EDIT258 },
	{ IDC_DATETIMEPICKER37, IDC_EDIT270, IDC_EDIT278, IDC_EDIT286, IDC_EDIT294 },
	{ IDC_DATETIMEPICKER38, IDC_EDIT271, IDC_EDIT279, IDC_EDIT287, IDC_EDIT295 },
	{ IDC_DATETIMEPICKER39, IDC_EDIT272, IDC_EDIT280, IDC_EDIT288, IDC_EDIT296 },
	{ IDC_DATETIMEPICKER40, IDC_EDIT273, IDC_EDIT281, IDC_EDIT289, IDC_EDIT297 },
	{ IDC_DATETIMEPICKER41, IDC_EDIT274, IDC_EDIT282, IDC_EDIT290, IDC_EDIT298 },
	{ IDC_DATETIMEPICKER42, IDC_EDIT275, IDC_EDIT283, IDC_EDIT291, IDC_EDIT299 },
	{ IDC_DATETIMEPICKER43, IDC_EDIT276, IDC_EDIT284, IDC_EDIT292, IDC_EDIT300 },
	{ IDC_DATETIMEPICKER44, IDC_EDIT277, IDC_EDIT285, IDC_EDIT293, IDC_EDIT301 }};
	for (int i = 0; i < 9; i++) {
		GetDlgItem(Parameters2[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty()) {
			strText.ReleaseBuffer();
			break;
		}

		ss << "insert into file_form_24 values(" << file_id << ",";
		ss << 0 << ",";
		for (int j = 0; j < 4; j++) {
			GetDlgItem(Parameters2[i][j])->GetWindowTextW(strText); strText.Trim();
			ss << "'" << strText << "',"; strText.ReleaseBuffer();
		}
		GetDlgItem(Parameters2[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
#pragma endregion

FillComplete :
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoSaveForm();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm18::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_24_1 where file_id=" << file_id << " limit 0,9;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_24_2 where file_id=" << file_id << " limit 0,9;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select file_name, file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << file_id << ";";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表3.dotx")));
}


void CPersonalForm18::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm18::OnInitialUpdate()
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
	ss << "select * from file_form_24 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int Parameters1[10][5] = { { IDC_DATETIMEPICKER25, IDC_EDIT236, IDC_EDIT237, IDC_EDIT248, IDC_EDIT259 },
	{ IDC_DATETIMEPICKER27, IDC_EDIT260, IDC_EDIT226, IDC_EDIT238, IDC_EDIT249 },
	{ IDC_DATETIMEPICKER28, IDC_EDIT261, IDC_EDIT227, IDC_EDIT239, IDC_EDIT250 },
	{ IDC_DATETIMEPICKER29, IDC_EDIT262, IDC_EDIT228, IDC_EDIT240, IDC_EDIT251 },
	{ IDC_DATETIMEPICKER30, IDC_EDIT263, IDC_EDIT229, IDC_EDIT241, IDC_EDIT252 },
	{ IDC_DATETIMEPICKER31, IDC_EDIT264, IDC_EDIT230, IDC_EDIT242, IDC_EDIT253 },
	{ IDC_DATETIMEPICKER32, IDC_EDIT265, IDC_EDIT231, IDC_EDIT243, IDC_EDIT254 },
	{ IDC_DATETIMEPICKER33, IDC_EDIT266, IDC_EDIT232, IDC_EDIT244, IDC_EDIT255 },
	{ IDC_DATETIMEPICKER34, IDC_EDIT267, IDC_EDIT233, IDC_EDIT245, IDC_EDIT256 },
	{ IDC_DATETIMEPICKER35, IDC_EDIT268, IDC_EDIT234, IDC_EDIT246, IDC_EDIT257 } };
	COleDateTime t;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 5; j++){
			if (j == 0){
				t.ParseDateTime(CA2W(re[(i + 1) * col + j + 2], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(Parameters1[i][j]))->SetTime(t);
				continue;
			}
			GetDlgItem(Parameters1[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 2], CP_UTF8));
		}
		if (i + 1 >= row) break;
	}

	int Parameters2[9][5] = { { IDC_DATETIMEPICKER36, IDC_EDIT269, IDC_EDIT235, IDC_EDIT247, IDC_EDIT258 },
	{ IDC_DATETIMEPICKER37, IDC_EDIT270, IDC_EDIT278, IDC_EDIT286, IDC_EDIT294 },
	{ IDC_DATETIMEPICKER38, IDC_EDIT271, IDC_EDIT279, IDC_EDIT287, IDC_EDIT295 },
	{ IDC_DATETIMEPICKER39, IDC_EDIT272, IDC_EDIT280, IDC_EDIT288, IDC_EDIT296 },
	{ IDC_DATETIMEPICKER40, IDC_EDIT273, IDC_EDIT281, IDC_EDIT289, IDC_EDIT297 },
	{ IDC_DATETIMEPICKER41, IDC_EDIT274, IDC_EDIT282, IDC_EDIT290, IDC_EDIT298 },
	{ IDC_DATETIMEPICKER42, IDC_EDIT275, IDC_EDIT283, IDC_EDIT291, IDC_EDIT299 },
	{ IDC_DATETIMEPICKER43, IDC_EDIT276, IDC_EDIT284, IDC_EDIT292, IDC_EDIT300 },
	{ IDC_DATETIMEPICKER44, IDC_EDIT277, IDC_EDIT285, IDC_EDIT293, IDC_EDIT301 } };

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 5; j++){
			if (j == 0){
				t.ParseDateTime(CA2W(re[(i + 1) * col + j + 2], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(Parameters2[i][j]))->SetTime(t);
				continue;
			}
			GetDlgItem(Parameters2[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 2], CP_UTF8));
		}
		if (i + 1 >= row) break;
	}

	help->closeDB();
	delete help;
#endif
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	int i = 0;
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		while (itVVparameter != itVVVparameter->end()) {
			int j = 0;

			vector<int>::iterator itV = itVVparameter->begin();
			while (itV != itVVparameter->end()) {
				if ((_vvSubformStructure[i][2 + j] != RADIOBTN) && (_vvSubformStructure[i][2 + j] != ATTACHMENTBX)) {
					GetDlgItem(*itV)->SetFont(&m_fontEdit);
				}

				itV++; j++;
			}
			itVVparameter++;
		}
		itVVVparameter++; i++;
	}
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT12)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT13)->SetFont(&m_fontEdit);

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

#pragma region 填不可更改的姓名单位信息

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
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
		GetDlgItem(IDC_EDIT12)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT13)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	}
	help->closeDB(); delete help;
#pragma endregion
}

void CPersonalForm18::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
}
