// PersonalForm03.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm03.h"


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
	
}
