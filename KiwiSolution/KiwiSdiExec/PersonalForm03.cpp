// PersonalForm03.cpp : ʵ���ļ�
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

}

PersonalForm03::~PersonalForm03()
{
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


// PersonalForm03 ���

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


// PersonalForm03 ��Ϣ�������


void PersonalForm03::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���

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




const wchar_t *pBookmarks2[] = { _T("���պ�"), _T("ǩ������"), _T("��Ч����"), _T("���ܻ���"), _T("��ע") };

void PersonalForm03::OnStnClickedFilePicture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strFileName;
	CFileDialog dlg(TRUE, _T("*.jpg"), strFileName, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, _T("ͼ���ļ�(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), this);

	if (dlg.DoModal() == IDOK)
	{
		m_strPicPathname = dlg.GetPathName();
		CImage  image;
		image.Load(m_strPicPathname); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
		CRect   rect; m_picFile.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
		CDC *pDc = m_picFile.GetDC();//��ȡpicture��DC  
		image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
		ReleaseDC(pDc);
	}
}


void PersonalForm03::OnBnClickedButtonCloseForm3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


void PersonalForm03::OnBnClickedCmdSaveForm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	//��һ�ű�
	ss << "select count(*) from file_form_4 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); ss.str(""); ss.clear();
	int hasRecord = atoi(re[1 * col + 0]);

	if (hasRecord) {
		ss << "delete from file_form_4 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str()); ss.str(""); ss.clear();

		//Ӧ�ð�ԭ������Ƭ�ļ�ɾ��
	}

	CString strText;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(strText);
	if (strText == _T("��"))
	{
		ss << "insert into test(file_id,file_4IfHaveThisSituation) values(" << file_id << ",";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();
	}
	else{
		ss << "insert into test(file_id,file_4IfHaveThisSituation) values(" << file_id << "," ;
		ss << "'" << _T("��") << "') ";
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

		if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)
		{
			ss << "insert into test(file_4IfChange) values(";
			GetDlgItem(IDC_RADIO2)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
		{
			ss << "insert into test(file_4IfChange) values(";
			GetDlgItem(IDC_RADIO1)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

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
		}
		
	}
	
	
	

	/*
	ss << "insert into file_form_4 values(" << file_id << ",";
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_DATETIMEPICKER2)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_DATETIMEPICKER4)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT9)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT10)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();
	*/
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());
	//�ڶ��ű�

	ss << "select count(*) from file_form_5 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); ss.str(""); ss.clear();


	if (hasRecord) {
		ss << "delete from file_form_5 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str()); ss.str(""); ss.clear();

		//Ӧ�ð�ԭ������Ƭ�ļ�ɾ��
	}


	ss << "insert into file_form_5 values(" << file_id << ",";

	if (((CButton *)GetDlgItem(IDC_RADIO12))->GetCheck() == 1)
	{
		GetDlgItem(IDC_RADIO12)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}
	else
	{
		GetDlgItem(IDC_RADIO3)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}

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

	//�����ű�

	ss << "select count(*) from file_form_6 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result); ss.str(""); ss.clear();


	if (hasRecord) {
		ss << "delete from file_form_6 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str()); ss.str(""); ss.clear();

		//Ӧ�ð�ԭ������Ƭ�ļ�ɾ��
	}


	ss << "insert into file_form_6 values(" << file_id << ",";

	if (((CButton *)GetDlgItem(IDC_RADIO13))->GetCheck() == 1)
	{
		GetDlgItem(IDC_RADIO13)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}
	else
	{
		GetDlgItem(IDC_RADIO5)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	}

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

	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());


	help->closeDB();
	delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void PersonalForm03::OnBnClickedCmdPrintForm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(_T("û�д����ݿ������ " + m_strCurrentFolder + m_strCurrentFile + " ������"));
		return;
	}

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\��1.dotx")); //dot(_T("template1.dot")); // 

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

	//����ͼƬ
	bookmark = bookmarks.Item(&_variant_t(_T("��Ƭ")));
	range = bookmark.get_Range();
	CnlineShapes shape = docx.get_InlineShapes();
	//shape.AddPicture(_T("C:\\Projects\\Kiwi.Git\\KiwiSolution\\KiwiSdiExec\\a.jpg"), covFalse, covTrue, &_variant_t(range));
	shape.AddPicture(m_strPicPathname.GetBuffer(), covFalse, covTrue, &_variant_t(range));

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
