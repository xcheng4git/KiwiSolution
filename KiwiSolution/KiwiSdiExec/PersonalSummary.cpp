
// PersonalSummary.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalSummary.h"
#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"
#include "Utility.h"

// CPersonalSummary

IMPLEMENT_DYNCREATE(CPersonalSummary, CFormView)

CPersonalSummary::CPersonalSummary()
	: CFormView(CPersonalSummary::IDD)
	, m_strHeader(_T(""))
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontText.CreateFontIndirect(&lf);
	lf.lfHeight = 30;
	m_fontTitle.CreateFontIndirect(&lf);

	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);
}

CPersonalSummary::~CPersonalSummary()
{
	m_fontText.DeleteObject(); m_fontTitle.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalSummary::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_HEADER, m_strHeader);
	DDX_Text(pDX, IDC_STATICBOX1, m_strBox1);
	DDX_Control(pDX, IDC_LIST_SUMMARY_1, m_listSummary1);
	DDX_Text(pDX, IDC_STATICBOX2, m_strBox2);
	DDX_Control(pDX, IDC_LIST_SUMMARY_2, m_listSummary2);
}

BEGIN_MESSAGE_MAP(CPersonalSummary, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPersonalSummary::OnClickedButtonClose)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPersonalSummary 诊断

#ifdef _DEBUG
void CPersonalSummary::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalSummary::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalSummary 消息处理程序




void CPersonalSummary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	GetDlgItem(IDC_STATIC_DEFULAT_TITLE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetFont(&m_fontText);
	CTime today = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("现在是：%4d年%02d月%02d日 %02d时%02d分%02d秒"), today.GetYear(), today.GetMonth(), today.GetDay(),
		today.GetHour(), today.GetMinute(), today.GetSecond());
	GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetWindowTextW(str);

	SetTimer(DateTimeTimer, 1000, NULL);


	//根据部门名和人名去数据库取个人信息，并显示
	m_strHeader.Format(_T("%s %s 的廉政档案"), m_strCurrentFolder, m_strCurrentFile);
	m_strBox1.Format(_T("1.基本情况"));
	m_strBox2.Format(_T("2.廉政电子档案"));
	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE))->SetBitmap(m_bmpClose);
	UpdateData(FALSE);

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 700;
	CFont font1; font1.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_HEADER)->SetFont(&font1); font1.DeleteObject();

	GetDlgItem(IDC_STATICBOX1)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATICBOX2)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_ERROR_MSG)->SetFont(&m_fontText);

	// TODO:  在此添加专用代码和/或调用基类
	CImageList   m_l;
	m_l.Create(1, 30, TRUE | ILC_COLOR32, 1, 0);
#pragma region ListSummary1
	m_listSummary1.SetImageList(&m_l, LVSIL_SMALL);
	m_listSummary1.SetFont(&m_fontText);

	m_listSummary1.DeleteAllItems();
	m_listSummary1.InsertColumn(0, _T("状态"), LVCFMT_CENTER, 40);
	m_listSummary1.InsertColumn(1, _T("性别"), LVCFMT_CENTER, 40);
	m_listSummary1.InsertColumn(2, _T("身份证"), LVCFMT_CENTER, 160);
	m_listSummary1.InsertColumn(3, _T("年龄"), LVCFMT_CENTER, 40);
	m_listSummary1.InsertColumn(4, _T("籍贯"), LVCFMT_CENTER, 100);
	m_listSummary1.InsertColumn(5, _T("学历"), LVCFMT_CENTER, 60);
	m_listSummary1.InsertColumn(6, _T("政治面貌"), LVCFMT_CENTER, 80);
	m_listSummary1.InsertColumn(7, _T("职级"), LVCFMT_CENTER, 60);
	m_listSummary1.InsertColumn(8, _T("单位及职务"), LVCFMT_CENTER, 200);
	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	int file_id = atoi(re[1 * col + 0]);

#pragma region 查询file_form_02

	ss.str("");
	ss << "select file_WorkingState, file_IDCard,file_PoliticalStatus,file_rank,file_WorkUnit,file_CurrentPosition from file_form_02 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_SHOW);
		return;
	}

	int iItem = 0;
	m_listSummary1.InsertItem(iItem, CUtility::WorkingStatus2String(atoi(re[1 * col + 0])));
	//1
	m_listSummary1.SetItem(iItem, 2, LVIF_TEXT, CA2W(re[1 * col + 1], CP_UTF8), 0, NULL, NULL, NULL);
	//3
	//4
	//5
	m_listSummary1.SetItem(iItem, 6, LVIF_TEXT, CA2W(re[1 * col + 2], CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 7, LVIF_TEXT, CA2W(re[1 * col + 3], CP_UTF8), 0, NULL, NULL, NULL);
	CString strText;
	strText.Format(_T("%s　%s"), strlen(re[1 * col + 4])<1 ? _T("") : CA2W(re[1 * col + 4], CP_UTF8), strlen(re[1 * col + 5])<1 ? _T("") : CA2W(re[1 * col + 5], CP_UTF8));

	m_listSummary1.SetItem(iItem, 8, LVIF_TEXT, strText, 0, NULL, NULL, NULL);
#pragma endregion

#pragma region 查询file_form_01
	strText.ReleaseBuffer();

	ss.str(""); ss.clear();
	ss << "select file_gender,file_birth_date,file_birth_place," << 
		"file_full_educate_degree,file_part_educate_degree from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);

	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_SHOW);
		return;
	}

	//0
	m_listSummary1.SetItem(iItem, 1, LVIF_TEXT, CA2W(re[1*col+0], CP_UTF8), 0, NULL, NULL, NULL);
	//2
	COleDateTime birthDate; birthDate.ParseDateTime(CA2W(re[1 * col + 1], CP_UTF8));
	COleDateTime curDate; curDate = COleDateTime::GetCurrentTime();
	int age = curDate.GetYear() - birthDate.GetYear();
	COleDateTime tt(curDate.GetYear(), birthDate.GetMonth(), birthDate.GetDay(),0,0,0);
	if ( curDate <= tt)
		strText.Format(_T("%d"), age);
	else
		strText.Format(_T("%d"), age+1);
	m_listSummary1.SetItem(iItem, 3, LVIF_TEXT, strText, 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 4, LVIF_TEXT, CA2W(re[1 * col + 2], CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 5, LVIF_TEXT, CA2W(re[1 * col + 3], CP_UTF8), 0, NULL, NULL, NULL);

#pragma endregion


	m_listSummary1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT | LVS_EX_FULLROWSELECT);
	m_listSummary1.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);


#pragma endregion

#pragma region ListSummary2
	m_listSummary2.SetImageList(&m_l, LVSIL_SMALL);
	m_listSummary2.SetFont(&m_fontText);
	//表2
	m_listSummary2.InsertColumn(0, _T("类型"), LVCFMT_CENTER, 50);
	m_listSummary2.InsertColumn(1, _T("档案名称"), LVCFMT_CENTER, 200);
	m_listSummary2.InsertColumn(2, _T("备注"), LVCFMT_CENTER, 100);
	m_listSummary2.InsertColumn(3, _T("建档日期"), LVCFMT_CENTER, 100);
	m_listSummary2.InsertColumn(4, _T("最后修改日期"), LVCFMT_CENTER, 100);
	//m_listSummary2.InsertColumn(5, _T("上报日期"), LVCFMT_CENTER, 100);
	m_listSummary2.InsertColumn(5, _T("操作"), LVCFMT_CENTER, 100);

	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();

	re = help->rawQuery("select type_serial, type_name from form_type;", &row, &col, result);

	int iRow = 0;
	std::vector<std::vector<wchar_t *>>::iterator itForm = pDoc->m_vvFormByTables.begin(); 
	while (itForm != pDoc->m_vvFormByTables.end()) {
		std::vector<wchar_t *>::const_iterator itcTables = itForm->begin();
		m_listSummary2.InsertItem(iRow, *itcTables);
		m_listSummary2.SetItem(iRow, 1, LVIF_TEXT, CA2W(re[(iRow+1) * col + 1], CP_UTF8), 0, NULL, NULL, NULL);

		itForm++; iRow++;
	}

	iRow = 0;
	itForm = pDoc->m_vvFormByTables.begin();
	while (itForm != pDoc->m_vvFormByTables.end()) {
		std::vector<wchar_t *>::const_iterator itcTables = itForm->begin();

		ss.str(""); ss.clear();
		ss << "select file_id, create_date, modify_date from personal_form_info where file_id=" << file_id << " and form_serial='";
		ss << CW2A(*itcTables, CP_UTF8) << "';";

		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row > 0) {
			m_listSummary2.SetItem(iRow, 3, LVIF_TEXT, CA2W(re[1 * col + 1], CP_UTF8), 0, NULL, NULL, NULL);
			m_listSummary2.SetItem(iRow, 4, LVIF_TEXT, CA2W(re[1 * col + 2], CP_UTF8), 0, NULL, NULL, NULL);
			m_listSummary2.createItemButton(iRow, 5, m_listSummary2, _T("修改"), &file_id);
		}
		else
			m_listSummary2.SetItem(iRow, 2, LVIF_TEXT, _T("未填报"), 0, NULL, NULL, NULL);

		itForm++; iRow++;
	}


	m_listSummary2.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	
#pragma endregion
	help->closeDB(); delete help;

}



void CPersonalSummary::OnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


HBRUSH CPersonalSummary::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ERROR_MSG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CPersonalSummary::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == DateTimeTimer) {
		KillTimer(DateTimeTimer);

		CTime today = CTime::GetCurrentTime();
		CString str;
		str.Format(_T("现在是：%4d年%02d月%02d日 %02d时%02d分%02d秒"),today.GetYear(),today.GetMonth(),today.GetDay(),
			today.GetHour(), today.GetMinute(), today.GetSecond()); 
		GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetWindowTextW(str);

		SetTimer(DateTimeTimer, 1000, NULL);
	}
	CFormView::OnTimer(nIDEvent);
}
