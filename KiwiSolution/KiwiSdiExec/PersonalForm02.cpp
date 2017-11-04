// PersonalForm02.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm02.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"
#include "Utility.h"
// CPersonalForm02

IMPLEMENT_DYNCREATE(CPersonalForm02, CFormView)

CPersonalForm02::CPersonalForm02()
	: CFormView(CPersonalForm02::IDD)
	, m_Radio2_1(-1)
	, m_Radio2_2(-1)
	, m_Radio2_3(-1)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);

	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);

	m_isModify = FALSE;
}

CPersonalForm02::~CPersonalForm02()
{
	m_fontEdit.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalForm02::QueryAndFillFileForm()
{
	int parameters1[] = { IDC_EDIT3, IDC_EDIT5, IDC_EDIT7, IDC_EDIT8, m_Radio2_1, IDC_EDIT14, IDC_EDIT15, IDC_EDIT16, IDC_EDIT18, IDC_EDIT20};
	int parameters2[] = { m_Radio2_2, IDC_RADIO7, m_Radio2_3, IDC_DATETIMEPICKER1, IDC_EDIT21};
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
	ss << "select file_name, file_gender, file_nation, file_party from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	GetDlgItem(parameters1[0])->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
	GetDlgItem(parameters1[1])->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
	GetDlgItem(parameters1[2])->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	GetDlgItem(parameters1[3])->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));

	ss.str(""); ss.clear();
	ss << "select * from file_form_02 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);

	m_Radio2_1 = atoi(re[1 * col + 6]);
	for (int i = 5; i < 10; i++) {
		GetDlgItem(parameters1[i])->SetWindowTextW(CA2W(re[1 * col + i + 2], CP_UTF8));
	}

	ss.str(""); ss.clear();
	ss << "select * from file_form_03 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}
	m_Radio2_2 = atoi(re[1 * col + 2]);
	int ifChange = atoi(re[1 * col + 3]);
	if (ifChange != -1) {
		((CButton*)GetDlgItem(parameters2[1]))->SetCheck(1);

		m_Radio2_3 = atoi(re[1 * col + 4]);

		GetDlgItem(parameters2[3])->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
		GetDlgItem(parameters2[4])->SetWindowTextW(CA2W(re[1 * col + 6], CP_UTF8));
	}

	help->closeDB(); delete help;

	UpdateData(FALSE);
}

void CPersonalForm02::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);

	m_isModify = FALSE;
}
void CPersonalForm02::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);


	//  DDX_Radio(pDX, IDC_RADIO3, m_radiobtngroup1);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio2_1);
	DDX_Radio(pDX, IDC_RADIO3, m_Radio2_2);
	DDX_Radio(pDX, IDC_RADIO8, m_Radio2_3);
}

BEGIN_MESSAGE_MAP(CPersonalForm02, CFormView)

	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm02::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm02::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM02, &CPersonalForm02::OnBnClickedButtonCloseForm02)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm02::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm02 诊断


#ifdef _DEBUG
void CPersonalForm02::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm02::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm02 消息处理程序
void CPersonalForm02::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 30;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("黑体"), 2); lf.lfWeight = 700;
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	GetDlgItem(IDC_STATIC_FORM02_HEADER1)->SetFont(&font);
	GetDlgItem(IDC_STATIC_FORM02_HEADER2)->SetFont(&font);
	font.DeleteObject();

	CWnd *pWnd = GetDlgItem(IDC_BUTTON_CLOSE_FORM02);
	((CButton*)pWnd)->SetBitmap(m_bmpClose);

	GetDlgItem(IDC_EDIT3)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT5)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT7)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT8)->SetFont(&m_fontEdit);
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
	{
		GetDlgItem(IDC_RADIO1)->SetFont(&m_fontEdit);
	}
	else
	{
		GetDlgItem(IDC_RADIO2)->SetFont(&m_fontEdit);
	}
	GetDlgItem(IDC_EDIT14)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT15)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT16)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT18)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT20)->SetFont(&m_fontEdit);
	{
		GetDlgItem(IDC_RADIO3)->SetFont(&m_fontEdit);
	}
		{
			GetDlgItem(IDC_RADIO4)->SetFont(&m_fontEdit);
		}
	{
		GetDlgItem(IDC_RADIO5)->SetFont(&m_fontEdit);
	}
	{
		GetDlgItem(IDC_RADIO6)->SetFont(&m_fontEdit);
	}
	{
		GetDlgItem(IDC_RADIO7)->SetFont(&m_fontEdit);
	}
	{
		GetDlgItem(IDC_RADIO8)->SetFont(&m_fontEdit);
	}
	{
		GetDlgItem(IDC_RADIO9)->SetFont(&m_fontEdit);
	}
	{
		GetDlgItem(IDC_RADIO10)->SetFont(&m_fontEdit);
	}
		GetDlgItem(IDC_RADIO11)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT21)->SetFont(&m_fontEdit);

	QueryAndFillFileForm();
}



void CPersonalForm02::OnBnClickedCmdSaveForm()
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
	
	//第一张表
	ss.str(""); ss.clear();
	ss << "select count(*) from file_form_02 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); ss.str(""); ss.clear();
	int hasRecord = atoi(re[1 * col + 0]);
	if (hasRecord) {
		ss << "delete from file_form_02 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str()); ss.str(""); ss.clear();

	}

	int parameters1[] = { IDC_EDIT3, IDC_EDIT5, IDC_EDIT7, IDC_EDIT8, m_Radio2_1, IDC_EDIT14, IDC_EDIT15, IDC_EDIT16, IDC_EDIT18, IDC_EDIT20 };
	CString strText;
	ss.str(""); ss.clear();
	ss << "insert into file_form_02 values(" << file_id << ",";
	strText = CUtility::GetGuid();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	for (int i = 0; i < 4; i++) {
		GetDlgItem(parameters1[i])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}
	
	ss << parameters1[4] << ",";
	
	for (int i = 5; i < 9; i++) {
		GetDlgItem(parameters1[i])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}
	GetDlgItem(parameters1[9])->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) <<  "') "; strText.ReleaseBuffer();

	OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8)); 
	help->execSQL(ss.str().c_str());
	
	//第二张表
	ss.str(""); ss.clear();
	ss << "select count(*) from file_form_03 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); ss.str(""); ss.clear();
	if (hasRecord) {
		ss << "delete from file_form_03 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str()); 

	}

	int parameters2[] = { m_Radio2_2, IDC_RADIO7, m_Radio2_3, IDC_DATETIMEPICKER1, IDC_EDIT21 };
	ss.str(""); ss.clear();
	ss << "insert into file_form_03 values(" << file_id << ",";
	strText = CUtility::GetGuid();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	ss << parameters2[0] << ", ";
	if (((CButton *)GetDlgItem(parameters2[1]))->GetCheck() == 1) {
		ss << "1, ";
		ss << parameters2[2] << ", ";
		GetDlgItem(parameters2[3])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', "; strText.ReleaseBuffer();
		GetDlgItem(parameters2[4])->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();
	} 
	else {
		ss << "-1, -1, '',''); ";
	}

	OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());

	if (!m_isModify) {
		ss.str("");  ss.clear();
		ss << "insert into personal_form_info values (" << file_id << ",";
		ss << "2, " << "'" << CW2A(_T("表2-1"), CP_UTF8) << "',";
		CTime today = CTime::GetCurrentTime();
		strText = today.Format("%Y-%m-%d");
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
		//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
	}
	else
	{
		ss.str("");  ss.clear();
		ss << "update personal_form_info set modify_date=";
		CTime today = CTime::GetCurrentTime();
		strText = today.Format("%Y-%m-%d");
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
		ss << " where file_id=" << file_id << " and form_serial=";
		ss << "'" << CW2A(_T("表2-1"), CP_UTF8) << "';";
		//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());

	}

	help->closeDB();
	delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm02::OnBnClickedCmdPrintForm()
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
	ss.str("");

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\表2-1.dotx")); //dot(_T("template1.dot")); // 

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

#pragma region 基本情况表
	wchar_t *pBookmarks1[] = { _T("姓名"), _T("性别"), _T("民族"), _T("政治面貌"), _T("在职状态"), _T("工作单位"),
		_T("现任职务"), _T("职级"), _T("身份证号码"), _T("户籍地址") };

	ss << "select * from file_form_02 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的基本情况表数据"));
		goto PrintMarige;
	}
	else {
		for (int r = 1; r <= 1; r++){
			for (int c = 0; c < 4; c++) {
				bookmark = bookmarks.Item(&_variant_t(pBookmarks1[c]));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c + 2], CP_UTF8)));
			}
			int zaizhizhuangtai = atoi(re[r * col + 6]);
			for (int j = 0; j < 2; j++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks1[4], j + 1);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				if (j == zaizhizhuangtai)
					range.put_Text(_T("R"));
				else
					range.put_Text(_T("\x00A3"));
			}
			for (int c = 5; c <10; c++) {
				bookmark = bookmarks.Item(&_variant_t(pBookmarks1[c]));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c +2], CP_UTF8)));
			}
		}
	}

#pragma endregion

	wchar_t *pBookmarks2[] = { _T("婚姻现状"), _T("无变化"), _T("有变化"), _T("变化时间"), _T("变化原因") };
#pragma region 婚姻情况表
PrintMarige:
	ss.str(""); ss.clear();
	ss << "select * from file_form_03 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的婚姻情况数据"));
		goto PrintForm;
	}
	else {
		for (int r = 1; r <= 1; r++){
			int hyxz = atoi(re[r * col + 2]);
			for (int j = 0; j < 4; j++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks2[0], j + 1);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				if (j == hyxz)
					range.put_Text(_T("R"));
				else
					range.put_Text(_T("\x00A3"));
			}

			int wbh = atoi(re[r * col + 3]);
			bookmark = bookmarks.Item(&_variant_t(pBookmarks2[1]));
			range = bookmark.get_Range();
			if (wbh == -1)
				range.put_Text(_T("\x00A3"));
			else
				range.put_Text(_T("R"));

			int ybh = atoi(re[r * col + 4]);
			for (int j = 0; j < 4; j++) {
				swprintf_s(szBookmark, 50, _T("%s%d"), pBookmarks2[2], j + 1);
				bookmark = bookmarks.Item(&_variant_t(szBookmark));
				range = bookmark.get_Range();
				if (j == ybh)
					range.put_Text(_T("R"));
				else
					range.put_Text(_T("\x00A3"));
			}

			for (int c = 3; c < 5; c++) {
				bookmark = bookmarks.Item(&_variant_t(pBookmarks2[c]));
				range = bookmark.get_Range();
				range.put_Text((CA2W(re[r * col + c + 2], CP_UTF8)));

			}
		}
	}
#pragma endregion

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

void CPersonalForm02::OnBnClickedButtonCloseForm02()
{// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm02::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	m_isModify = TRUE;
	OnBnClickedCmdSaveForm();
}
