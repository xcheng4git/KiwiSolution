// PersonalSummary.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalSummary.h"


// CPersonalSummary

IMPLEMENT_DYNCREATE(CPersonalSummary, CFormView)

CPersonalSummary::CPersonalSummary()
	: CFormView(CPersonalSummary::IDD)
	, m_strHeader(_T(""))
{

}

CPersonalSummary::~CPersonalSummary()
{
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
	ON_MESSAGE(WM_SHOW_PERSONAL_SUMMARY, &CPersonalSummary::OnShowPersonalSummary)
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


afx_msg LRESULT CPersonalSummary::OnShowPersonalSummary(WPARAM wParam, LPARAM lParam)
{
	CString *folder = (CString *)wParam, *file = (CString *)lParam;

	//根据部门名和人名去数据库取个人信息，并显示
	m_strHeader.Format(_T("%s %s 的廉政档案"), *folder, *file);
	m_strBox1.Format(_T("1.基本情况"));
	m_strBox2.Format(_T("2.廉政电子档案"));


	//最后
	UpdateData(false);

	return 0;
}


void CPersonalSummary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//表1
	// TODO:  在此添加专用代码和/或调用基类
	//m_listCtrl01.SetImageList(&m_ilTreeIcons, LVSIL_SMALL);
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
	m_listSummary1.InsertItem(0, _T("在职"));
	m_listSummary1.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary1.SetItemText(0, 2, _T("7980.12"));
	m_listSummary1.SetItemText(0, 3, _T("-5877"));
	m_listSummary1.SetItemText(0, 4, _T(" "));
	m_listSummary1.SetItemText(0, 5, _T("硕士研究生"));
	m_listSummary1.SetItemText(0, 6, _T("中共党员"));
	m_listSummary1.SetItemText(0, 7, _T("乡科级副职"));
	m_listSummary1.SetItemText(0, 8, _T(" "));


	//表2
	m_listSummary2.InsertColumn(0, _T("状态"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(1, _T("身份证"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(2, _T("出身日期"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(3, _T("年龄"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(4, _T("籍贯"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(5, _T("学历"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(6, _T("政治面貌"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(7, _T("职级"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(8, _T("单位及职务"), LVCFMT_LEFT, 100);
	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	m_listSummary2.InsertItem(0, _T("在职"));
	m_listSummary2.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary2.SetItemText(0, 2, _T("7980.12"));
	m_listSummary2.SetItemText(0, 3, _T("-5877"));
	m_listSummary2.SetItemText(0, 4, _T(" "));
	m_listSummary2.SetItemText(0, 5, _T("硕士研究生"));
	m_listSummary2.SetItemText(0, 6, _T("中共党员"));
	m_listSummary2.SetItemText(0, 7, _T("乡科级副职"));
	m_listSummary2.SetItemText(0, 8, _T(" "));

	m_listSummary2.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
}

