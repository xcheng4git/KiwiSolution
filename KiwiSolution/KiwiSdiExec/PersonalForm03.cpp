// PersonalForm03.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm03.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// PersonalForm03

IMPLEMENT_DYNCREATE(PersonalForm03, CFormView)

PersonalForm03::PersonalForm03()
	: CFormView(PersonalForm03::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
}

PersonalForm03::~PersonalForm03()
{
	m_fontEdit.DeleteObject();
}
void PersonalForm03::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}
void PersonalForm03::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(PersonalForm03, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &PersonalForm03::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &PersonalForm03::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &PersonalForm03::OnBnClickedCmdPrintForm)
END_MESSAGE_MAP()


// PersonalForm03 诊断

#ifdef _DEBUG
void PersonalForm03::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void PersonalForm03::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// PersonalForm03 消息处理程序


void PersonalForm03::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_DATETIMEPICKER1)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_DATETIMEPICKER3)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT4)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT5)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT6)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_DATETIMEPICKER2)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_DATETIMEPICKER4)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT9)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT10)->SetFont(&m_fontEdit);
	
	
}




void PersonalForm03::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码

	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void PersonalForm03::OnBnClickedCmdSaveForm()
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
	
	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	CString strText;
	/////////////////////////////////////////////////////////////////////////////
	//表2-1
#pragma region FillForm2_1
	
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_4IfHaveThisSituation=0 where file_id=" << file_id; 
		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm2_2;
	}

	{
		ss << "update file_form_flags set file_4IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	
	{
		if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_4IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str()); 
			ss.str(""); ss.clear();
			goto FillForm2_2;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_4IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	{
		ss << "insert into file_form_4 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT1)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER1)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER3)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT4)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT5)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT6)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_4 values(" << file_id << ",";

			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER4)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT9)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT10)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
#pragma endregion

	/////////////////////////////////////////////////////////////////////////////
	//表2-2
#pragma region FillForm2_2
FillForm2_2:
	{
		if (((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_5IfHaveThisSituation=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm2_3;
		}

		ss << "update file_form_flags set file_5IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		ss << "insert into file_form_5 values(" << file_id << ",";
		
		GetDlgItem(IDC_DATETIMEPICKER5)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER6)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT11)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT24)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT27)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT30)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}
	{
		GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";

			strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER7)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER8)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT25)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT28)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT31)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm2_3;

		GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";

			strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER9)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER10)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT26)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT29)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT32)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
#pragma endregion

	/////////////////////////////////////////////////////////////////////////////
	//表2-3
#pragma region FillForm2_3
FillForm2_3 :
	GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_6IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_6IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_6IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO13))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_6IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	{
		ss << "insert into file_form_6 values(" << file_id << ",";

		GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT35)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER11)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER12)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT37)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT38)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT34)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_6 values(" << file_id << ",";

			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT39)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER13)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER14)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT41)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT42)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		} else
			goto FillComplete;

		GetDlgItem(IDC_EDIT36)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_6 values(" << file_id << ",";

			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT40)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER15)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER14)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT43)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT44)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;
	}


#pragma endregion

FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}

const wchar_t *pBookmarks2[] = { _T("护照号"), _T("签发日期"), _T("有效期至"), _T("保管机构"), _T("备注") };
void PersonalForm03::OnBnClickedCmdPrintForm()
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

	ss << "select * from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		AfxMessageBox(_T("没有从数据库检索到 " + m_strCurrentFolder + m_strCurrentFile + " 的数据"));
		return;
	}

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\表1.dotx")); //dot(_T("template1.dot")); // 

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

	for (int i = 0; i < 21; i++) {
		bookmark = bookmarks.Item(&_variant_t(pBookmarks2[i]));
		range = bookmark.get_Range();
		range.put_Text((CA2W(re[1 * col + i + 1], CP_UTF8)));
	}

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

	docx.Close(covFalse, covOptional, covOptional);
	wordApp.Quit(covOptional, covOptional, covOptional);
	range.ReleaseDispatch(); bookmarks.ReleaseDispatch(); wordApp.ReleaseDispatch();
}
