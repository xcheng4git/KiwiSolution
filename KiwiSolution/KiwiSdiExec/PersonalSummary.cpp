
// PersonalSummary.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalSummary.h"
#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"
// CPersonalSummary

IMPLEMENT_DYNCREATE(CPersonalSummary, CFormView)

CPersonalSummary::CPersonalSummary()
	: CFormView(CPersonalSummary::IDD)
	, m_strHeader(_T(""))
{
	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);
}

CPersonalSummary::~CPersonalSummary()
{
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

	//根据部门名和人名去数据库取个人信息，并显示
	m_strHeader.Format(_T("%s %s 的廉政档案"), m_strCurrentFolder, m_strCurrentFile);
	m_strBox1.Format(_T("1.基本情况"));
	m_strBox2.Format(_T("2.廉政电子档案"));

	//表1
	// TODO:  在此添加专用代码和/或调用基类
	m_listSummary1.DeleteAllItems();

	m_listSummary1.InsertColumn(0, _T("状态"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(1, _T("身份证"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(2, _T("出身日期"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(3, _T("年龄"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(4, _T("籍贯"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(5, _T("学历"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(6, _T("政治面貌"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(7, _T("职级"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(8, _T("单位及职务"), LVCFMT_LEFT, 100);
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
	ss.str("");
	
	ss << "select * from list_summary_1 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);

	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	int iItem = 0;
	char *file_state, *file_IDCard, *file_birthday, *file_age, *file_NativePlace, *file_EducationBackground, *file_PoliticalStatus, *file_rank, *file_UnitsAndDuties;

	file_state = re[col + 1]; file_IDCard = re[col + 2]; file_birthday = re[col + 3]; file_age = re[col + 4]; file_NativePlace = re[col + 5]; file_EducationBackground = re[col + 6]; file_PoliticalStatus = re[col + 7]; file_rank = re[col + 8]; file_UnitsAndDuties = re[col + 9];
	m_listSummary1.InsertItem(iItem, CA2W(file_state, CP_UTF8));
	m_listSummary1.SetItem(iItem, 1, LVIF_TEXT, CA2W(file_IDCard, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 2, LVIF_TEXT, CA2W(file_birthday, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 3, LVIF_TEXT, CA2W(file_age, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 4, LVIF_TEXT, CA2W(file_NativePlace, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 5, LVIF_TEXT, CA2W(file_EducationBackground, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 6, LVIF_TEXT, CA2W(file_PoliticalStatus, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 7, LVIF_TEXT, CA2W(file_rank, CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 8, LVIF_TEXT, CA2W(file_UnitsAndDuties, CP_UTF8), 0, NULL, NULL, NULL);



	help->closeDB();
	delete help;

	m_listSummary1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT | LVS_EX_FULLROWSELECT);
	m_listSummary1.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	//	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE


	//表2
	m_listSummary2.InsertColumn(0, _T("类型"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(1, _T("档案名称"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(2, _T("备注"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(3, _T("建党日期"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(4, _T("最后修改日期"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(5, _T("上报日期"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(6, _T("操作"), LVCFMT_LEFT, 100);

	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	/*	m_listSummary2.InsertItem(0, _T("在职"));
	m_listSummary2.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary2.SetItemText(0, 2, _T("7980.12"));
	m_listSummary2.SetItemText(0, 3, _T("-5877"));
	m_listSummary2.SetItemText(0, 4, _T(" "));
	m_listSummary2.SetItemText(0, 5, _T("硕士研究生"));
	m_listSummary2.SetItemText(0, 6, _T("中共党员"));
	m_listSummary2.SetItemText(0, 7, _T("乡科级副职"));
	m_listSummary2.SetItemText(0, 8, _T(" "));
	*/
	//	m_listSummary1.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	m_listSummary2.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE))->SetBitmap(m_bmpClose);

	UpdateData(FALSE);
}



void CPersonalSummary::OnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}
