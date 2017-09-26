
// KiwiSdiExecView.cpp : CKiwiSdiExecView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KiwiSdiExec.h"
#endif

#include "KiwiSdiExecDoc.h"
#include "KiwiSdiExecView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKiwiSdiExecView

IMPLEMENT_DYNCREATE(CKiwiSdiExecView, CFormView)

BEGIN_MESSAGE_MAP(CKiwiSdiExecView, CFormView)
END_MESSAGE_MAP()

// CKiwiSdiExecView 构造/析构

CKiwiSdiExecView::CKiwiSdiExecView()
	: CFormView(CKiwiSdiExecView::IDD)
{
	// TODO:  在此处添加构造代码

}

CKiwiSdiExecView::~CKiwiSdiExecView()
{
}

void CKiwiSdiExecView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CKiwiSdiExecView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CKiwiSdiExecView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CKiwiSdiExecView 诊断

#ifdef _DEBUG
void CKiwiSdiExecView::AssertValid() const
{
	CFormView::AssertValid();
}

void CKiwiSdiExecView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CKiwiSdiExecDoc* CKiwiSdiExecView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKiwiSdiExecDoc)));
	return (CKiwiSdiExecDoc*)m_pDocument;
}
#endif //_DEBUG


// CKiwiSdiExecView 消息处理程序
