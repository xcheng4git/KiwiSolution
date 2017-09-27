// PersonalSummary.cpp : ʵ���ļ�
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


// CPersonalSummary ���

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


// CPersonalSummary ��Ϣ�������


afx_msg LRESULT CPersonalSummary::OnShowPersonalSummary(WPARAM wParam, LPARAM lParam)
{
	CString *folder = (CString *)wParam, *file = (CString *)lParam;

	//���ݲ�����������ȥ���ݿ�ȡ������Ϣ������ʾ
	m_strHeader.Format(_T("%s %s ����������"), *folder, *file);
	m_strBox1.Format(_T("1.�������"));
	m_strBox2.Format(_T("2.�������ӵ���"));


	//���
	UpdateData(false);

	return 0;
}


void CPersonalSummary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//��1
	// TODO:  �ڴ����ר�ô����/����û���
	//m_listCtrl01.SetImageList(&m_ilTreeIcons, LVSIL_SMALL);
	m_listSummary1.InsertColumn(0, _T("״̬"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(1, _T("���֤"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(2, _T("��������"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(3, _T("����"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(4, _T("����"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(5, _T("ѧ��"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(6, _T("������ò"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(7, _T("ְ��"), LVCFMT_LEFT, 100);
	m_listSummary1.InsertColumn(8, _T("��λ��ְ��"), LVCFMT_LEFT, 100);
	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	m_listSummary1.InsertItem(0, _T("��ְ"));
	m_listSummary1.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary1.SetItemText(0, 2, _T("7980.12"));
	m_listSummary1.SetItemText(0, 3, _T("-5877"));
	m_listSummary1.SetItemText(0, 4, _T(" "));
	m_listSummary1.SetItemText(0, 5, _T("˶ʿ�о���"));
	m_listSummary1.SetItemText(0, 6, _T("�й���Ա"));
	m_listSummary1.SetItemText(0, 7, _T("��Ƽ���ְ"));
	m_listSummary1.SetItemText(0, 8, _T(" "));


	//��2
	m_listSummary2.InsertColumn(0, _T("״̬"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(1, _T("���֤"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(2, _T("��������"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(3, _T("����"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(4, _T("����"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(5, _T("ѧ��"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(6, _T("������ò"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(7, _T("ְ��"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(8, _T("��λ��ְ��"), LVCFMT_LEFT, 100);
	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	m_listSummary2.InsertItem(0, _T("��ְ"));
	m_listSummary2.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary2.SetItemText(0, 2, _T("7980.12"));
	m_listSummary2.SetItemText(0, 3, _T("-5877"));
	m_listSummary2.SetItemText(0, 4, _T(" "));
	m_listSummary2.SetItemText(0, 5, _T("˶ʿ�о���"));
	m_listSummary2.SetItemText(0, 6, _T("�й���Ա"));
	m_listSummary2.SetItemText(0, 7, _T("��Ƽ���ְ"));
	m_listSummary2.SetItemText(0, 8, _T(" "));

	m_listSummary2.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
}

