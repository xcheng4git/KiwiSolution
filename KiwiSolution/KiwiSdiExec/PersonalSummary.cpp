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
	DDX_Control(pDX, IDC_LIST_SUMMARY_1, m_listSummary1);
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



	//最后
	UpdateData(false);

	return 0;
}


void CPersonalSummary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	m_listSummary1.DeleteAllItems();

	m_listSummary1.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);
	m_listSummary1.InsertColumn(1, _T("廉政档案名称"), LVCFMT_LEFT, 250);
	m_listSummary1.InsertColumn(2, _T("说明"), LVCFMT_LEFT, 100);

	m_listSummary1.InsertItem(0, _T("说明"));
	m_listSummary1.SetItem(0, 1, LVIF_TEXT, _T("说明"), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(0, 2, LVIF_TEXT, _T("说明"), 0, NULL, NULL, NULL);

}
