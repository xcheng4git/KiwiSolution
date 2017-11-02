// PersonalForm05.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm05.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"
#include "Utility.h"
// CPersonalForm05

IMPLEMENT_DYNCREATE(CPersonalForm05, CFormView)

CPersonalForm05::CPersonalForm05()
	: CFormView(CPersonalForm05::IDD)
	, m_Radio6_1(-1)
	, m_Radio6_1_1(-1)
	, m_Radio6_1_2(-1)
	, m_Radio6_1_3(-1)
	, m_Radio6_2(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);

	m_FormID = 5;
	int parameters1[3][7] = { { IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, 1, IDC_DATETIMEPICKER1, IDC_EDIT74 },
	{ IDC_EDIT33, IDC_EDIT48, IDC_EDIT51, IDC_EDIT54, 2, IDC_DATETIMEPICKER45, IDC_EDIT75 },
	{ IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, 3, IDC_DATETIMEPICKER46, IDC_EDIT76 } };
	int structure1[9] = { 3, 7, EDITBX, EDITBX, EDITBX, EDITBX, RADIOBTN, DATEPKR, EDITBX };

	int parameters2[3][5] = { { IDC_EDIT78, IDC_EDIT63, IDC_EDIT66, IDC_DATETIMEPICKER22, IDC_EDIT80 },
	{ IDC_EDIT77, IDC_EDIT64, IDC_EDIT67, IDC_DATETIMEPICKER23, IDC_EDIT81 },
	{ IDC_EDIT62, IDC_EDIT65, IDC_EDIT68, IDC_DATETIMEPICKER24, IDC_EDIT82 } };
	int structure2[7] = { 3, 5, EDITBX, EDITBX, EDITBX, DATEPKR, EDITBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 7; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 5; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 9; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 7; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);
}

CPersonalForm05::~CPersonalForm05()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm05::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}

void CPersonalForm05::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio6_1);
	DDX_Radio(pDX, IDC_RADIO19, m_Radio6_1_1);
	DDX_Radio(pDX, IDC_RADIO22, m_Radio6_1_2);
	DDX_Radio(pDX, IDC_RADIO25, m_Radio6_1_3);
	DDX_Radio(pDX, IDC_RADIO28, m_Radio6_2);
}

BEGIN_MESSAGE_MAP(CPersonalForm05, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm05::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm05::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm05::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm05::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm05 诊断

#ifdef _DEBUG
void CPersonalForm05::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm05::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif
#endif //_DEBUG

void CPersonalForm05::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm05::ShowRadiobtn(int nWhich, char *data)
{
	switch (nWhich) {
	case 1:
		m_Radio6_1_1 = atoi(data);
		break;
	case 2:
		m_Radio6_1_2 = atoi(data);
		break;
	case 3:
		m_Radio6_1_3 = atoi(data);
		break;
	}
}

void CPersonalForm05::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm05::GetNumber(int nWhich, int &num)
{
	switch (nWhich) {
	case 1:
		num = m_Radio6_1_1;
		break;
	case 2:
		num = m_Radio6_1_2;
		break;
	case 3:
		num = m_Radio6_1_3;
		break;
	}
}

void CPersonalForm05::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm05::hasData(int isub, int irow)
{
	return TRUE;
}

// CPersonalForm05 消息处理程序


void CPersonalForm05::OnBnClickedCmdSaveForm()
{
	UpdateData();

	// TODO:  在此添加控件通知处理程序代码
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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	CString strText;
#pragma region FillForm6_1
FillForm6_1:
	GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_10IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm6_2;
	}

	{
		ss << "update file_form_flags set file_10IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if  (m_Radio6_1 == 1)
		{
			ss << "update file_form_flags set file_10IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm6_2;
		}
		else if (m_Radio6_1 == 0)
		{
			ss << "update file_form_flags set file_10IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	
	int Parameters1[3][7] = { { IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, m_Radio6_1_1, IDC_DATETIMEPICKER1, IDC_EDIT74},
	{ IDC_EDIT33, IDC_EDIT48, IDC_EDIT51, IDC_EDIT54, m_Radio6_1_2, IDC_DATETIMEPICKER45, IDC_EDIT75 }, 
	{ IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, m_Radio6_1_3, IDC_DATETIMEPICKER46, IDC_EDIT76 }};

	for (int i = 0; i < 3; i++)
	{
		GetDlgItem(Parameters1[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillForm6_2;

		ss << "insert into file_form_10 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		for (int j = 0; j < 4; j++) {
			GetDlgItem(Parameters1[i][j])->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		}

		ss << Parameters1[i][4] << ", ";

		GetDlgItem(Parameters1[i][5])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters1[i][6])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8));
		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	
#pragma endregion

#pragma region FillForm6_2
FillForm6_2:
	GetDlgItem(IDC_EDIT78)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_11IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_11IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (m_Radio6_2 == 1)
		{
			ss << "update file_form_flags set file_11IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (m_Radio6_2 == 0)
		{
			ss << "update file_form_flags set file_11IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	int Parameters2[3][5] = { { IDC_EDIT78, IDC_EDIT63, IDC_EDIT66, IDC_DATETIMEPICKER22, IDC_EDIT80 },
	{ IDC_EDIT77, IDC_EDIT64, IDC_EDIT67, IDC_DATETIMEPICKER23, IDC_EDIT81 },
	{ IDC_EDIT62, IDC_EDIT65, IDC_EDIT68, IDC_DATETIMEPICKER24, IDC_EDIT82 } };

	for (int i = 0; i < 3; i++)
	{
		GetDlgItem(Parameters1[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			goto FillComplete;

		ss << "insert into file_form_11 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		for (int j = 0; j < 4; j++) {
			GetDlgItem(Parameters1[i][j])->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		}
		GetDlgItem(Parameters1[i][4])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8));
		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
#pragma endregion

FillComplete :
	help->closeDB(); delete help;
			 ss.str("");  ss.clear();
			 GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}

void CPersonalForm05::OnBnClickedCmdPrintForm()
{
	const wchar_t *pBookmarks1[] = { _T("有无"), _T("姓名"), _T("移居国家"), _T("现居住城市"), _T("移居证件号码"), _T("移居类别"), _T("移居时间"), _T("备注") };
	const wchar_t *pBookmarks2[] = { _T("有无"), _T("姓名"), _T("移居国家"), _T("现居住城市"), _T("移居时间"), _T("备注") };

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
	ss.str("");

	int isEmpty = 0;

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\表2-4.dotx")); 

	CApplication wordApp;
	CDocuments docs;
	CDocument0 docx;
	CBookmarks bookmarks;
	CBookmark0 bookmark;
	CRange range;
	CCell cell;

	if (!wordApp.CreateDispatch(_T("Word.Application"))) {
		AfxMessageBox(_T("no word product."));
		return;
	}

	wordApp.put_Visible(FALSE);
	CString wordVersion = wordApp.get_Version();
	docs = wordApp.get_Documents();
	docx = docs.Add(dot, covOptional, covOptional, covOptional);
	bookmarks = docx.get_Bookmarks();

	wchar_t szBookmark[50];
#pragma region PrintForm6_1

	ss << "select file_10IfHaveThisSituation, file_10IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的表2-4的数据"));
		goto PrintForm6_2;
	}
	int hasSituation = atoi(re[1 * col + 0]), ifChange = atoi(re[1 * col + 1]);
	for (int i = 0; i < 2; i++) {
		swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks1[0], i + 1);
		bookmark = bookmarks.Item(&_variant_t(szBookmark));
		range = bookmark.get_Range();
		if (i == ifChange)
			range.put_Text(_T("R"));
		else
			range.put_Text(_T("\x00A3"));
	}
	if (hasSituation == 0 || hasSituation == -1) {
		swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks1[1], 1);
		bookmark = bookmarks.Item(&_variant_t(szBookmark));
		range = bookmark.get_Range();
		range.put_Text(_T("无"));
		goto PrintForm6_2;
	}


	ss.str(""); ss.clear();
	ss << "select * from file_form_10 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row >= 1) {
		for (int r = 1; r <= row; r++){
			for (int c = 1; c < 5; c++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks1[c], r);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c+1], CP_UTF8)));
			}
			int yijuleibie = atoi(re[r * col + 5+1]);
			for (int j = 0; j < 3; j++) {
				swprintf_s(szBookmark, 50, _T("%s%d%d"), pBookmarks1[5], r, j + 1);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				if (j == yijuleibie) 
					range.put_Text(_T("R"));
				else
					range.put_Text(_T("\x00A3"));
			}
			for (int c = 6; c <= 7; c++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks1[c], r);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c+1], CP_UTF8)));
			}
		}

	}
	else {
		isEmpty++;
	}
	for (int i = row + 1; i <= 3; i++) {
		for (int j = 0; j < 3; j++) {
			swprintf_s(szBookmark, 50, _T("%s%d%d"), pBookmarks1[5], i, j + 1);
			bookmark = bookmarks.Item(&_variant_t(szBookmark));
			range = bookmark.get_Range();
			range.put_Text(_T("\x00A3"));
		}
	}
#pragma endregion

#pragma region PrintForm6_2
PrintForm6_2:
	ss.str(""); ss.clear();
	ss << "select file_11IfHaveThisSituation, file_11IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的表2-4的数据"));
		goto PrintFinish;
	}

	hasSituation = atoi(re[1 * col + 0]); ifChange = atoi(re[1 * col + 1]);
	for (int i = 0; i < 2; i++) {
		swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks2[0], i + 1 + 2);
		bookmark = bookmarks.Item(&_variant_t(szBookmark));
		range = bookmark.get_Range();
		if (i == ifChange)
			range.put_Text(_T("R"));
		else
			range.put_Text(_T("\x00A3"));
	}
	if (hasSituation == 0 || hasSituation == -1) {
		swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks2[1], 1+3);
		bookmark = bookmarks.Item(&_variant_t(szBookmark));
		range = bookmark.get_Range();
		range.put_Text(_T("无"));
		goto PrintForm;
	}


	ss.str(""); ss.clear();
	ss << "select * from file_form_11 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row >= 1) {
		for (int r = 1; r <= row; r++){
			for (int c = 1; c <= 5; c++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks2[c], r+3);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c+1], CP_UTF8)));
			}
		}
	}
	else {
		isEmpty++;
	}
#pragma endregion

	if (isEmpty == 2) {
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的表2-4的数据"));
		goto PrintFinish;
	}
PrintForm:
	{
		CString strSavePath = CUtility::GetModuleDirectory() + _T("\\temp.docx");
		docx.SaveAs(COleVariant(strSavePath), covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);

		docx.PrintOut(covFalse,              // Background.
			covOptional,           // Append.
			covOptional,           // Range.
			covOptional,           // OutputFileName.
			covOptional,           // From.
			covOptional,           // To.
			covOptional,           // Item.
			COleVariant((long)1),  // Copies.
			covOptional,           // Pages.
			covOptional,           // PageType.
			covOptional,           // PrintToFile.
			covOptional,           // Collate.
			covOptional,           // ActivePrinterMacGX.
			covOptional,           // ManualDuplexPrint.
			covOptional,           // PrintZoomColumn  New with Word 2002
			covOptional,           // PrintZoomRow          ditto
			covOptional,           // PrintZoomPaperWidth   ditto
			covOptional);          // PrintZoomPaperHeight  ditto*/
	}
PrintFinish:
	help->closeDB(); delete help;

	docx.Close(covFalse, covOptional, covOptional);
	wordApp.Quit(covOptional, covOptional, covOptional);
	range.ReleaseDispatch(); bookmarks.ReleaseDispatch(); wordApp.ReleaseDispatch();
}


void CPersonalForm05::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm05::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	DoUpdateForm();
}


void CPersonalForm05::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
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

	UpdateData(FALSE);
}
