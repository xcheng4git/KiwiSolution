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
, m_Radio12_2_0(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 12;
	int parameters1[14][4] = { { IDC_EDIT47, IDC_EDIT98, IDC_EDIT97, IDC_EDIT99 },
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
	{ IDC_EDIT95, IDC_EDIT128, IDC_EDIT145, IDC_EDIT160 } };
	int structure1[6] = { 14, 4, EDITBX, EDITBX, EDITNUM, EDITNUM };
	int parameters2[1][1] = { { IDC_EDIT161 } };
	int structure2[3] = { 1, 1, EDITNUM };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 14; i++) {
		vector<int> vPara;
		for (int j = 0; j < 4; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 1; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 6; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 3; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(14); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[5] = { _T("有无"), _T("持有人姓名"), _T("名称或代码"), _T("基金份额"), _T("前一日净值") };
	int structure10[5] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX};
	int structure11[3 + 1 + 5] = { 0, 14, 4, 2,  2, 1,1,1,1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....
	const wchar_t *pBookmarks2[2] = { _T("有无"), _T("前一日总净值") };
	int structure20[2] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX};
	int structure21[3 + 1 + 2] = { -1, 1, 1, 2, 2, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 5; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 2; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
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

}

CPersonalForm12::~CPersonalForm12()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm12::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm12::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio12_2_0);
}

BEGIN_MESSAGE_MAP(CPersonalForm12, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm12::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm12::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm12::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm12::OnBnClickedCmdUpdateForm)
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


void CPersonalForm12::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm12::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm12::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm12::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm12::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm12::hasData(int isub, int irow)
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

	if (m_Radio12_2_0 == -1) {
		MessageBox(_T("请选择是否存在 12-2 本人等投资基金的情况 ！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
		help->closeDB(); delete help;
		ss.str("");  ss.clear();
		return;
	}
	else {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_18IfHaveThisSituation=";
		ss << m_Radio12_2_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}

#if 0
	if (m_Radio12_2_0 == 1)
	{
		ss << "update file_form_flags set file_18IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_18IfHaveThisSituation=1 where file_id=" << file_id;
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
	{ IDC_EDIT95, IDC_EDIT128, IDC_EDIT145, IDC_EDIT160 } };

	double amount1, amount2 = 0;
	for (int i = 0; i < 14; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_18 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
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
	strText.Format(_T("%f"), amount2);
	GetDlgItem(IDC_EDIT161)->SetWindowTextW(strText);
#endif

FillComplete :
	//ss.str("");  ss.clear();
	//ss << "insert into personal_form_info values (" << file_id << ",";
	//ss << "12, " << "'" << CW2A(_T("表2-11"), CP_UTF8) << "',";
	//CTime today = CTime::GetCurrentTime();
	//strText = today.Format("%Y-%m-%d");
	//ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	//ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	////TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	//help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
			 ss.str("");  ss.clear();

			 DoSaveForm();

			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);


}


void CPersonalForm12::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_18 where file_id=" << file_id << " limit 0,14;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_18_1 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());

	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-11.dotx")));
}


void CPersonalForm12::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm12::OnInitialUpdate()
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
	ss << "select file_18IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}
	m_Radio12_2_0 = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from file_form_18 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

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
	{ IDC_EDIT95, IDC_EDIT128, IDC_EDIT145, IDC_EDIT160 } };
	double sum = 0;
	for (int i = 0; i < 14; i++){
		for (int j = 0; j < 4; j++){
			GetDlgItem(Parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
			if (j == 3){
				sum += wcstod(CA2W(re[(i + 1) * col + j + 1]), NULL);
			}
		}
		if (i + 1 >= row) break;
	}
	
	CString str;
	str.Format(_T("%f"), sum);
	GetDlgItem(IDC_EDIT161)->SetWindowTextW(str);
	help->closeDB();
	delete help;
#endif
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
	ss << "select file_17IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio12_2_0 = -1;
	}
	else
		m_Radio12_2_0 = 1 - atoi(re[1 * col + 0]);  //分组的原因，使得要用1-
	help->closeDB(); delete help;

	UpdateData(FALSE);
}

void CPersonalForm12::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	DoUpdateForm();
}
