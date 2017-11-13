// PersonalForm01.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"

#include "PersonalForm01.h"

#include "MainFrm.h"

#include "Utility.h"
#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "msword/msword.h"

// CPersonalForm01

IMPLEMENT_DYNCREATE(CPersonalForm01, CFormView)

CPersonalForm01::CPersonalForm01()
//	: CAutoFocusWnd<CFormView>(CPersonalForm01::IDD)
	: CFormView(CPersonalForm01::IDD)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);

	m_strPicPathname = _T("");
	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);

	m_isModify = FALSE;
}

CPersonalForm01::~CPersonalForm01()
{
	m_fontEdit.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalForm01::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);

	m_isModify = FALSE;
}
#if 0

void CPersonalForm01::DrawFormHeader(CDC* pDC, CRect* pBox)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 40;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 700;
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	//CFont font; font.CreatePointFont(120, _T("仿宋体"));
	CFont* pOldFont = pDC->SelectObject(&font); pDC->SetBkMode(TRANSPARENT);

	int lenText = 11 * (lf.lfHeight*0.87);
	int len = pBox->right - pBox->left;
	pDC->TextOutW(pBox->left + len*0.5 - lenText *0.5, pBox->top, _T("科级干部基本情况登记表"));
	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	//pDC->MoveTo(pBox->left + len*0.5 - lenText *0.5, pBox->top + 13);
	//pDC->LineTo(pBox->left + len*0.5 - lenText *0.5 + 11 * (lf.lfHeight*0.895), pBox->top + 20);   //40*0.87, 30*0.895
	//pDC->MoveTo(pBox->left + len*0.25, pBox->top);
	//pDC->LineTo(pBox->left + len*0.25, pBox->top + lf.lfHeight);
}

void CPersonalForm01::DrawForm(CDC* pDC, CRect* pBox)
{
	pDC->Rectangle(pBox);
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 30;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); //lf.lfWeight = 700;
	//CFont font; VERIFY(font.CreateFontIndirect(&lf));
	CFont* pOldFont = pDC->SelectObject(&m_fontEdit); pDC->SetBkMode(TRANSPARENT);

	int len = pBox->right - pBox->left;
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("姓名")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("性别")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("民族")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("籍贯")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("出生年月")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("政治面貌")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("入党时间")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("工作时间")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("有何专长")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
		DrawTextCell(pDC, CRect(pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->right, pBox->top + 5 * CELL_HEIGHT), CString(_T("")), BorderLeft | BorderBottom);
	//
		DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("学历学位")), BorderRight | BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT), CString(_T("全日制教育")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 4 * CELL_HEIGHT), CString(_T("毕业院校及专业")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 3 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("在职教育")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 5 * CELL_HEIGHT), CString(_T("毕业院校及专业")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 4 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("是否党代表")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("是否人大代表")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("是否政协委员")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->right, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("工作单位")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("现任职务及任职时间")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->right, pBox->top + 7 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("家庭住址")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("联系电话")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->right, pBox->top + 8 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 9 * CELL_HEIGHT), CString(_T("起止时间及单位职务")), 0);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 12 * CELL_HEIGHT), CString(_T("")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 12 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 13 * CELL_HEIGHT), CString(_T("主要工")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 13 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 14 * CELL_HEIGHT), CString(_T("作经历")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 14 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->bottom), CString(_T("")), BorderRight);
	

	pDC->SelectObject(pOldFont);
	//font.DeleteObject();

	delete pBox;
}

void CPersonalForm01::DrawTextCell(CDC* pDC, CRect& box, CString& strText, int enumBorder)
{
	const int TextHeight = 30;
	if (!strText.IsEmpty()){
		int width = box.right - box.left;
		int height = box.bottom - box.top;
		int lenText = strText.GetLength() * TextHeight * 0.895;
		pDC->TextOutW(box.left + width*0.5 - lenText *0.5, box.top + height*0.5 - TextHeight * 0.5, strText);
	}
	if (enumBorder == 0)
		return;

	if (enumBorder & BorderLeft) {
		pDC->MoveTo(box.TopLeft()); pDC->LineTo(box.left, box.bottom);
	};
	if (enumBorder & BorderTop) {
		pDC->MoveTo(box.TopLeft()); pDC->LineTo(box.right, box.top);
	}
	if (enumBorder & BorderRight) {
		pDC->MoveTo(box.BottomRight()); pDC->LineTo(box.right, box.top);
	}
	if (enumBorder & BorderBottom) {
		pDC->MoveTo(box.BottomRight()); pDC->LineTo(box.left, box.bottom);
	}
}
#endif

void CPersonalForm01::QueryAndFillFileForm()
{
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
	ss.str("");

	ss << "select * from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_COMBO_GENDER)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));
	GetDlgItem(IDC_EDIT_NATION)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));

	GetDlgItem(IDC_EDIT_BIRTH_PLACE)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
	COleDateTime t; t.ParseDateTime(CA2W(re[1 * col + 6], CP_UTF8));
	m_ctrlBirthday.SetTime(t);
	//GetDlgItem(IDC_COMBO_BIRTHDAY)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
	GetDlgItem(IDC_COMBO_PARTY)->SetWindowTextW(CA2W(re[1 * col + 7], CP_UTF8));

	t.ParseDateTime(CA2W(re[1 * col + 8], CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(IDC_PICKER_INPARTY_DATE))->SetTime(t);
	t.ParseDateTime(CA2W(re[1 * col + 9], CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(IDC_PICKER_INWORK_DATE))->SetTime(t);
	GetDlgItem(IDC_EDIT_PROFESSION)->SetWindowTextW(CA2W(re[1 * col + 10], CP_UTF8));

	GetDlgItem(IDC_EDIT_FULL_EDUCATE_DEGREE)->SetWindowTextW(CA2W(re[1 * col + 11], CP_UTF8));
	GetDlgItem(IDC_EDIT_FULL_EDUCATE_PLACE)->SetWindowTextW(CA2W(re[1 * col + 12], CP_UTF8));

	GetDlgItem(IDC_EDIT_PART_EDUCATE_DEGREE)->SetWindowTextW(CA2W(re[1 * col + 13], CP_UTF8));
	GetDlgItem(IDC_EDIT_PART_EDUCATE_PLACE)->SetWindowTextW(CA2W(re[1 * col + 14], CP_UTF8));

	GetDlgItem(IDC_EDIT_PARTY_REP)->SetWindowTextW(CA2W(re[1 * col + 15], CP_UTF8));
	GetDlgItem(IDC_EDIT_NPC_MEMBER)->SetWindowTextW(CA2W(re[1 * col + 16], CP_UTF8));
	GetDlgItem(IDC_EDIT_CPPCC_MEMBER)->SetWindowTextW(CA2W(re[1 * col + 17], CP_UTF8));

	GetDlgItem(IDC_EDIT_WORKING_UNIT)->SetWindowTextW(CA2W(re[1 * col + 18], CP_UTF8));
	GetDlgItem(IDC_EDIT_CURRENT_POSITION)->SetWindowTextW(CA2W(re[1 * col + 19], CP_UTF8));

	t.ParseDateTime(CA2W(re[1 * col + 20], CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(IDC_DATE_4_CURPOSITION))->SetTime(t);

	GetDlgItem(IDC_EDIT_HOME_ADDRESS)->SetWindowTextW(CA2W(re[1 * col + 21], CP_UTF8));
	GetDlgItem(IDC_EDIT_PHONE)->SetWindowTextW(CA2W(re[1 * col + 22], CP_UTF8));

	GetDlgItem(IDC_EDIT_RESUME)->SetWindowTextW(CA2W(re[1 * col + 23], CP_UTF8));

	m_strPicPathname.Format(_T("%s"), CA2W(re[1 * col + 24], CP_UTF8));
	if (!m_strPicPathname.IsEmpty() && m_strPicPathname != _T("(null)") ) {
		if (true == (bool)PathFileExists(m_strPicPathname.GetBuffer())) {
			CImage  image;
			image.Load(m_strPicPathname);
			CRect   rect; m_picFile.GetClientRect(&rect);//获取句柄指向控件区域的大小  
			CDC *pDc = m_picFile.GetDC();//获取picture的DC  
			image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
			ReleaseDC(pDc);
		} else
			m_strPicPathname.Empty();
	}
	else
		m_strPicPathname.Empty();

	ss.str(""); ss.clear();
	help->closeDB();
	delete help;

}

void CPersonalForm01::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BIRTHDAY, m_ctrlBirthday);
	//  DDX_Control(pDX, IDC_FILE_PICTURE, m_picFile);
	DDX_Control(pDX, IDC_FILE_PICTURE, m_picFile);
	DDX_Control(pDX, IDC_COMBO_GENDER, m_comboGender);
}

BEGIN_MESSAGE_MAP(CPersonalForm01, CFormView)
//	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm01::OnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm01::OnClickedCmdPrintForm)
	ON_STN_CLICKED(IDC_FILE_PICTURE, &CPersonalForm01::OnClickedFilePicture)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM01, &CPersonalForm01::OnClickedButtonCloseForm01)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm01::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm01 诊断

#ifdef _DEBUG
void CPersonalForm01::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm01::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm01 消息处理程序


void CPersonalForm01::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	//SetScaleToFitSize(CSize(1, 1));
	//ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM01))->SetBitmap(m_bmpClose);

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 30;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 700;
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	GetDlgItem(IDC_STATIC_FORM01_HEADER)->SetFont(&font);
	font.DeleteObject();

	GetDlgItem(IDC_CMD_SAVE_FORM)->SetFont(&m_fontEdit); 


	GetDlgItem(IDC_EDIT_NAME)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(m_strCurrentFile);

	GetDlgItem(IDC_COMBO_GENDER)->SetFont(&m_fontEdit);
	CComboBox *pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO_GENDER);
	pCombo1->AddString(_T("男")); pCombo1->AddString(_T("女"));

	GetDlgItem(IDC_EDIT_NATION)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_BIRTH_PLACE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_COMBO_BIRTHDAY)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_COMBO_PARTY)->SetFont(&m_fontEdit);
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_PARTY);
	pCombo->AddString(_T("中国共产党")); pCombo->AddString(_T("民主党派")); pCombo->AddString(_T("无党派")); pCombo->SetCurSel(2);

	GetDlgItem(IDC_PICKER_INPARTY_DATE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_PICKER_INWORK_DATE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_PROFESSION)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_FULL_EDUCATE_DEGREE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_FULL_EDUCATE_PLACE)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_PART_EDUCATE_DEGREE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_PART_EDUCATE_PLACE)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_PARTY_REP)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_NPC_MEMBER)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_CPPCC_MEMBER)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_WORKING_UNIT)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_CURRENT_POSITION)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_DATE_4_CURPOSITION)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_HOME_ADDRESS)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT_PHONE)->SetFont(&m_fontEdit);

	GetDlgItem(IDC_EDIT_RESUME)->SetFont(&m_fontEdit);

	QueryAndFillFileForm();
}


void CPersonalForm01::OnDraw(CDC* /*pDC*/)
{
	// TODO:  在此添加专用代码和/或调用基类
	//CClientDC dc(this);

	//CRect rt; GetClientRect(&rt);
	////dc.Rectangle(new CRect(rt.left + MARGIN_X, rt.top + MARGIN_Y, rt.right - MARGIN_X, rt.bottom - MARGIN_Y));
	//DrawFormHeader(&dc, new CRect(rt.left + MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X,
	//	rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y,
	//	rt.right - MARGIN_X - PAGE_START_OFFSET_X - HEADER_START_OFFSET_X,
	//	rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT));
	//dc.DeleteDC();

	/*
	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC(NULL);
	CRect rt; GetClientRect(&rt);
	memBitmap.CreateCompatibleBitmap(&dc, rt.Width(), rt.Height());
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);

	//CPen dotPen; dotPen.CreatePen(PS_DOT, 1, RGB(0x33, 0x66, 0x99));
	//CGdiObject* pOldPen = memDC.SelectObject(&dotPen);
	memDC.Rectangle(new CRect(rt.left + MARGIN_X, rt.top + MARGIN_Y, rt.right - MARGIN_X, rt.bottom - MARGIN_Y));
	//memDC.SelectObject(pOldPen); dotPen.DeleteObject();

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	CFont font; 
	
	VERIFY(font.CreateFontIndirect(&lf)); CFont* pOldFont = memDC.SelectObject(&font); memDC.SetBkMode(TRANSPARENT);
	memDC.TextOutW(rt.right - 200, rt.top + MARGIN_Y + 10, _T("表1"));
	memDC.SelectObject(pOldFont); font.DeleteObject();

	////lf.lfHeight = 30; VERIFY(font.CreateFontIndirect(&lf)); pOldFont = memDC.SelectObject(&font);
	//pOldFont = memDC.SelectObject(&m_fontEdit); COLORREF oldColor = memDC.SetTextColor(RGB(255, 0, 0));
	//memDC.TextOutW(rt.left+ 100, rt.top + MARGIN_Y + 10, _T("填完表后，请点击工具栏按钮保存！"));
	//memDC.SelectObject(pOldFont); memDC.SetTextColor(oldColor); //font.DeleteObject();

	DrawFormHeader(&memDC, new CRect(rt.left + MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X,
								  rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y, 
								  rt.right - MARGIN_X - PAGE_START_OFFSET_X - HEADER_START_OFFSET_X, 
								  rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT));
	DrawForm(&memDC, new CRect(rt.left + MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X,
		rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT + 1, 
		rt.right - MARGIN_X - PAGE_START_OFFSET_X, rt.bottom - MARGIN_Y - PAGE_START_OFFSET_Y));

	dc.BitBlt(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, &memDC, 0, 0, SRCCOPY);
	memBitmap.DeleteObject(); memDC.DeleteDC();
	*/
	if (!m_strPicPathname.IsEmpty()) {
		CImage  image;
		image.Load(m_strPicPathname);
		CRect   rect; m_picFile.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_picFile.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
	}

	//dc.DeleteDC();
}


//void CPersonalForm01::OnSize(UINT nType, int cx, int cy)
//{
//	CFormView::OnSize(nType, cx, cy);
//
//	// TODO:  在此处添加消息处理程序代码
//	CRect rt; GetClientRect(&rt);
//	CWnd *pWnd; CRect *pRt;
//	//////////////////////////////////////////////////////
//	//if (pWnd = GetDlgItem(IDC_FILE_PICTURE)) {
//	//	pRt = new CRect(rt.left + 630, rt.top + 120, rt.left + 750, rt.top + 280);
//	//	pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	//}
//	if (pWnd = GetDlgItem(IDC_BUTTON_CLOSE_FORM01)) {
//		((CButton*)pWnd)->SetBitmap(m_bmpClose);
//	}
//	return;
//
//#if 0
//	if (pWnd = GetDlgItem(IDC_BUTTON_CLOSE_FORM01)) {
//		pRt = new CRect(rt.right - MARGIN_X - 17, rt.top + MARGIN_Y, rt.right - MARGIN_X, rt.top + MARGIN_Y + 17);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//		((CButton*)pWnd)->SetBitmap(m_bmpClose);
//	}
//
//	rt.left += (MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X);
//	rt.top += (MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT + 1);
//	rt.right -= (MARGIN_X + PAGE_START_OFFSET_X);
//	rt.bottom -= (MARGIN_Y + PAGE_START_OFFSET_Y);
//
//	int len = rt.right - rt.left;
//
//	 
//	if (pWnd = GetDlgItem(IDC_EDIT_NAME)) {
//		pRt = new CRect(rt.left + int(1 * len*CELL_WIDTH_RATIO + 5), rt.top + 0 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//		if (pWnd = GetDlgItem(IDC_EDIT_GENDER)) {
//			pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
//			pWnd->MoveWindow(pRt, FALSE); delete pRt;
//		}
//			if (pWnd = GetDlgItem(IDC_EDIT_NATION)) {
//				pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
//				pWnd->MoveWindow(pRt, FALSE); delete pRt;
//			}
//	///////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_BIRTH_PLACE)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_COMBO_BIRTHDAY)) {
//		pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_COMBO_PARTY)) {
//		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_PICKER_INPARTY_DATE)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 2 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 3 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_PICKER_INWORK_DATE)) {
//		pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 2 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 3 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_PROFESSION)) {
//		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 2 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 3 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_FILE_PICTURE)) {
//		pRt = new CRect(rt.left + 6 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.right - 5, rt.top + 5 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_FULL_EDUCATE_DEGREE)) {
//		pRt = new CRect(rt.left + 2 * len*CELL_WIDTH_RATIO + 5, rt.top + 3 * CELL_HEIGHT + 5, rt.left + 3 * len*CELL_WIDTH_RATIO - 5, rt.top + 4 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_FULL_EDUCATE_PLACE)) {
//		pRt = new CRect(rt.left + 4 * len*CELL_WIDTH_RATIO*1.1 + 5, rt.top + 3 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 4 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_PART_EDUCATE_DEGREE)) {
//		pRt = new CRect(rt.left + 2 * len*CELL_WIDTH_RATIO + 5, rt.top + 4 * CELL_HEIGHT + 5, rt.left + 3 * len*CELL_WIDTH_RATIO - 5, rt.top + 5 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_PART_EDUCATE_PLACE)) {
//		pRt = new CRect(rt.left + 4 * len*CELL_WIDTH_RATIO*1.1 + 5, rt.top + 4 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 5 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_PARTY_REP)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 5 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 6 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_NPC_MEMBER)) {
//		pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 5 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 6 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_CPPCC_MEMBER)) {
//		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 5 * CELL_HEIGHT + 5, rt.right - 5, rt.top + 6 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_WORKING_UNIT)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 6 * CELL_HEIGHT + 5, rt.left + 3 * len*CELL_WIDTH_RATIO - 5, rt.top + 7 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_CURRENT_POSITION)) {
//		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 6 * CELL_HEIGHT + 5, rt.right - 5, rt.top + 7 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_HOME_ADDRESS)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 7 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 8 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	if (pWnd = GetDlgItem(IDC_EDIT_PHONE)) {
//		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 7 * CELL_HEIGHT + 5, rt.right - 5, rt.top + 8 * CELL_HEIGHT - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//	//////////////////////////////////////////////////////
//	if (pWnd = GetDlgItem(IDC_EDIT_RESUME)) {
//		pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 9 * CELL_HEIGHT + 5, rt.right - 5, rt.bottom - 5);
//		pWnd->MoveWindow(pRt, FALSE); delete pRt;
//	}
//#endif
//
//
//	//InvalidateRect(NULL);
//}


void CPersonalForm01::OnClickedCmdSaveForm()
{
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

	ss << "select count(*) from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	
	if (hasRecord) {
		ss << "delete from file_form_01 where file_id=" << file_id << ";";
		help->execSQL(ss.str().c_str());

		//应该把原来的照片文件删除
	}

	CString strText;
	ss << "insert into file_form_01 values(" << file_id << ",";
	strText = CUtility::GetGuid();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_COMBO_GENDER)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_NATION)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_BIRTH_PLACE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_COMBO_BIRTHDAY)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_COMBO_PARTY)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_PICKER_INPARTY_DATE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_PICKER_INWORK_DATE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_PROFESSION)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_FULL_EDUCATE_DEGREE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_FULL_EDUCATE_PLACE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_PART_EDUCATE_DEGREE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_PART_EDUCATE_PLACE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_PARTY_REP)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_NPC_MEMBER)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_CPPCC_MEMBER)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_WORKING_UNIT)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_CURRENT_POSITION)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_DATE_4_CURPOSITION)->GetWindowTextW(strText);
	strText.Replace(_T("/"), _T("-"));
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_HOME_ADDRESS)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT_PHONE)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_RESUME)->GetWindowTextW(strText);
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', "; strText.ReleaseBuffer();

	if (!m_strPicPathname.IsEmpty()){
		CImage  image;
		image.Load(m_strPicPathname); //把图像保存到特定目录,然后将路径存数据库
		m_strPicPathname = CUtility::GetModuleDirectory() + _T("\\photo\\") + CUtility::GetGuid() + _T(".jpg");
		image.Save(m_strPicPathname.GetBuffer());
		ss << "'" << CW2A(m_strPicPathname.GetBuffer(), CP_UTF8) << "', ";
	}
	else {
		ss << "'', ";
	}
	ss << "date(), date());";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());

	if (!m_isModify) {
		ss.str("");  ss.clear();
		ss << "insert into personal_form_info values (" << file_id << ",";
		ss << "1, " << "'" << CW2A(_T("表1"), CP_UTF8) << "',";
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
		ss << "'" << CW2A(_T("表1"), CP_UTF8) << "';";
		//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());

	}

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}

const wchar_t *pBookmarks[] = { _T("姓名"), _T("性别"), _T("民族"), _T("籍贯"), _T("出生年月"), _T("政治面貌"), _T("入党时间"), _T("参加工作时间"), 
								_T("有何专长"), _T("全日制学位"), _T("全日制学校"), _T("在职学位"), _T("在职学校"), _T("党代表"), _T("人大代表"), 
								_T("政协委员"), _T("工作单位"), _T("现任职务"), _T("家庭住址"), _T("联系电话"), _T("工作简历") };
void CPersonalForm01::OnClickedCmdPrintForm()
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
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory()+_T("\\template\\表1.dotx")); //dot(_T("template1.dot")); // 

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

	for (int i = 0; i < 17; i++) {
		bookmark = bookmarks.Item(&_variant_t(pBookmarks[i]));
		range = bookmark.get_Range();
		range.put_Text((CA2W(re[1 * col + i+2], CP_UTF8)));
	}
	{
		int i = 17;
		bookmark = bookmarks.Item(&_variant_t(pBookmarks[i]));
		range = bookmark.get_Range();
		CString strText; strText.Format(_T("%s %s"), strlen(re[1 * col + i+2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8),
			strlen(re[1 * col + i + 3]) < 1 ? _T("") : CA2W(re[1 * col + i + 3], CP_UTF8));
		range.put_Text(strText);
	}
	for (int i = 18; i < 21; i++) {
		bookmark = bookmarks.Item(&_variant_t(pBookmarks[i]));
		range = bookmark.get_Range();
		range.put_Text((CA2W(re[1 * col + i + 3], CP_UTF8)));
	}

	//插入图片
	bookmark = bookmarks.Item(&_variant_t(_T("照片")));
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

	help->closeDB(); delete help;
}


void CPersonalForm01::OnClickedFilePicture()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strFileName;
	CFileDialog dlg(TRUE, _T("*.jpg"), strFileName, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, _T("图像文件(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), this);

	if (dlg.DoModal() == IDOK)
	{
		m_strPicPathname = dlg.GetPathName();

		//string filename = CW2A(m_strPicPathname.GetBuffer(), CP_UTF8);
		//cv::Mat img = cv::imread(filename);
		//CRect   rect; m_picFile.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		//cv::Mat matPixel; cv::resize(img, matPixel, cv::Size(rect.Width(), rect.Height())); img.release();
		//int nChannels = (matPixel.type() >> 3) - CV_8U + 1;
		//int iSize = matPixel.cols*matPixel.rows*nChannels;
		//HBITMAP hBmp = CreateBitmap(matPixel.cols, matPixel.rows, 1, nChannels * 8, matPixel.data);
		//HBITMAP hOldBmp = m_picFile.SetBitmap(hBmp);
		//DeleteObject(hOldBmp);

		//////CDC *pDc = m_picFile.GetDC();
		////CClientDC dc(this);
		////CDC dcCompatible;
		////dcCompatible.CreateCompatibleDC(&dc);
		////dcCompatible.SelectObject(hBmp);
		////dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, SRCCOPY);
		//////ReleaseDC(pDc);
		//InvalidateRect(NULL);

		CImage  image;
		image.Load(m_strPicPathname); //把图像保存到特定目录,然后将路径存数据库
		CRect   rect; m_picFile.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_picFile.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
		
	}

}


void CPersonalForm01::OnClickedButtonCloseForm01()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);

	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm01::OnBnClickedCmdUpdateForm()
{
	//因为数据表中只有一个记录，所以更新可以采用删除原来的，再插入新的
	m_isModify = TRUE;
	OnClickedCmdSaveForm();
}