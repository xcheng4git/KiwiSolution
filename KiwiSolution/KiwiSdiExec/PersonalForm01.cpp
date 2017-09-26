// PersonalForm01.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm01.h"


// CPersonalForm01

IMPLEMENT_DYNCREATE(CPersonalForm01, CFormView)

CPersonalForm01::CPersonalForm01()
	: CAutoFocusWnd<CFormView>(CPersonalForm01::IDD)
//	: CFormView(CPersonalForm01::IDD)
{

}

CPersonalForm01::~CPersonalForm01()
{
}

void CPersonalForm01::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm01, CFormView)
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
	SetScaleToFitSize(CSize(1, 1));
	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
}
