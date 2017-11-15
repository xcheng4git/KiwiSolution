// DlgShowAttachment.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgShowAttachment.h"
#include "afxdialogex.h"

#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"


// CDlgShowAttachment �Ի���

IMPLEMENT_DYNAMIC(CDlgShowAttachment, CDialogEx)

CDlgShowAttachment::CDlgShowAttachment(CString& file_form, CString& attachmentPath, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowAttachment::IDD, pParent)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
	memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 30;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 700;
	m_fontHeader.CreateFontIndirect(&lf);

	CString fileId = file_form.Left(file_form.Find(_T(":"), 0));
	m_strFormName = file_form.Right(file_form.GetLength() - file_form.Find(_T(":"), 0) - 1);

	m_nFile_Id = atoi(CW2A(fileId.GetBuffer(), CP_UTF8));
	m_strAttachmentPath = attachmentPath;
	CImage  image;
	image.Load(m_strAttachmentPath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
	if (image.IsNull()) {
		m_strAttachmentPath = CUtility::GetModuleDirectory() + _T("\\attachment\\not_an_image.jpg");
	}
}

CDlgShowAttachment::~CDlgShowAttachment()
{
	m_fontEdit.DeleteObject();
	m_fontHeader.DeleteObject();
}

void CDlgShowAttachment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE_ATTACHMENT, m_imageAttachment);
}


BEGIN_MESSAGE_MAP(CDlgShowAttachment, CDialogEx)
	ON_WM_PAINT()
//	ON_WM_SIZE()
ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CDlgShowAttachment::OnBnClickedCmdPrintForm)
END_MESSAGE_MAP()


// CDlgShowAttachment ��Ϣ�������


BOOL CDlgShowAttachment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT12)->SetFont(&m_fontEdit);
	CString header; header.Format(_T("%s �ĸ���ͼƬ"), m_strFormName);
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetWindowTextW(header);

	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;

	ss.str(""); ss.clear();
	ss << "select file_name, file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << m_nFile_Id << ";";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	char **re = re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row >= 1) {
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
		CString strText; strText.Format(_T("%s %s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8), strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT12)->SetWindowTextW(strText.GetBuffer());
	}

	//ss.str(""); ss.clear();
	//ss << "select attachment_path from file_form_attachment where attachment_recid='" << CW2A(m_strAttachmentRecid.GetBuffer(), CP_UTF8) << "';";
	//re = re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	//if (row >= 1) {
	//	CString strText; strText.Format(_T("%s"), strlen(re[1 * col + 0]) < 1 ? _T("") : CA2W(re[1 * col + 0], CP_UTF8));
	//	if (PathFileExists(strText)) {
	//		CImage  image;
	//		image.Load(strText); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
	//		CRect   rect; m_imageAttachment.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
	//		CDC *pDc = m_imageAttachment.GetDC();//��ȡpicture��DC  
	//		image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
	//		ReleaseDC(pDc);
	//	}
	//}
	help->closeDB(); delete help;

	if (PathFileExists(m_strAttachmentPath)){
#if 0
		CBitmap mBitmap;
		CImage pic;
		pic.Load(m_strAttachmentPath);
		CDC *pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		mBitmap.CreateCompatibleBitmap(pDC, 100, 100);
		CBitmap *OldBitmap = memDC.SelectObject(&mBitmap);
		pic.Draw(memDC.m_hDC, 0, 0, 100, 100, 0, 0, 100, 100);

		memDC.SelectObject(OldBitmap);
		DeleteDC(memDC);
		OldBitmap = NULL;

		((CStatic *)GetDlgItem(IDC_STATIC_IMAGE_ATTACHMENT))->SetBitmap(mBitmap);
		Invalidate();
#endif
				//CImage  image;
				//image.Load(m__strAttachmentPath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
				//CRect   rect; m_imageAttachment.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
				//CDC *pDc = m_imageAttachment.GetDC();//��ȡpicture��DC  
				//image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
				//ReleaseDC(pDc);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgShowAttachment::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	if (PathFileExists(m_strAttachmentPath)){
		CImage  image;
		image.Load(m_strAttachmentPath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
		CRect   rect; //m_imageAttachment.GetWindowRect(&rect); //
		m_imageAttachment.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
		CDC *pDc = m_imageAttachment.GetDC();//��ȡpicture��DC  
		image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
		ReleaseDC(pDc);
	}
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


//void CDlgShowAttachment::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO:  �ڴ˴������Ϣ����������
//	CWnd *pWnd;
//	CRect rect; 
//	if (pWnd = GetDlgItem(IDC_STATIC_GROUP_BOUNDBOX)) {
//		pWnd->GetWindowRect(&rect);
//		if (pWnd = GetDlgItem(IDC_STATIC_IMAGE_ATTACHMENT)) {
//			pWnd->MoveWindow(&rect, FALSE);
//		}
//	}
//}


void CDlgShowAttachment::OnBnClickedCmdPrintForm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;

	ss.str(""); ss.clear();
	ss << "select file_name, file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << m_nFile_Id << ";";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	char **re = re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		AfxMessageBox(_T("û�д����ݿ����������"));
		return;
	}

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\����.dotx")); //dot(_T("template1.dot")); // 

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

	bookmark = bookmarks.Item(&_variant_t(_T("����")));
	range = bookmark.get_Range();
	range.put_Text(m_strFormName);


	bookmark = bookmarks.Item(&_variant_t(_T("����")));
	range = bookmark.get_Range();
	range.put_Text((CA2W(re[1 * col + 0], CP_UTF8)));

	CString strText; strText.Format(_T("%s %s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8), strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
	bookmark = bookmarks.Item(&_variant_t(_T("������λ��ְ��")));
	range = bookmark.get_Range();
	range.put_Text(strText);

	//����ͼƬ
	if (PathFileExists(m_strAttachmentPath)) {
		bookmark = bookmarks.Item(&_variant_t(_T("ͼƬ")));
		range = bookmark.get_Range();
		CnlineShapes shape = docx.get_InlineShapes();
		//shape.AddPicture(_T("C:\\Projects\\Kiwi.Git\\KiwiSolution\\KiwiSdiExec\\a.jpg"), covFalse, covTrue, &_variant_t(range));
		shape.AddPicture(m_strAttachmentPath.GetBuffer(), covFalse, covTrue, &_variant_t(range));
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

	help->closeDB(); delete help;
}
