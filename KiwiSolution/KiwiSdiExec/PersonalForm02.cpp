// PersonalForm02.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm02.h"


// CPersonalForm02

IMPLEMENT_DYNCREATE(CPersonalForm02, CFormView)

CPersonalForm02::CPersonalForm02()
	: CFormView(CPersonalForm02::IDD)
{

}

CPersonalForm02::~CPersonalForm02()
{
}

void CPersonalForm02::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm02, CFormView)
END_MESSAGE_MAP()


// CPersonalForm02 诊断

#ifdef _DEBUG
void CPersonalForm02::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm02::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm02 消息处理程序
