
// KiwiSdiExecView.cpp : CKiwiSdiExecView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KiwiSdiExec.h"
#endif
#include "resource.h"
#include "KiwiSdiExecDoc.h"
#include "KiwiSdiExecView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKiwiSdiExecView

IMPLEMENT_DYNCREATE(CKiwiSdiExecView, CFormView)

BEGIN_MESSAGE_MAP(CKiwiSdiExecView, CFormView)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CKiwiSdiExecView 构造/析构

CKiwiSdiExecView::CKiwiSdiExecView()
	: CFormView(CKiwiSdiExecView::IDD)
{
	// TODO:  在此处添加构造代码
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("黑体"), 2); lf.lfWeight = 400;
	m_fontGroup.CreateFontIndirect(&lf);
	lf.lfHeight = 15;
	m_fontTip.CreateFontIndirect(&lf);
	lf.lfHeight = 30;
	m_fontTitle.CreateFontIndirect(&lf);

	m_bmpTip.LoadBitmap(IDB_BITMAP_TIP);
	m_bmpXingt1.LoadBitmap(IDB_BITMAP_XINGTAI1); m_bmpXingt2.LoadBitmap(IDB_BITMAP_XINGTAI2); 
	m_bmpXingt3.LoadBitmap(IDB_BITMAP_XINGTAI3); m_bmpXingt4.LoadBitmap(IDB_BITMAP_XINGTAI4);

}

CKiwiSdiExecView::~CKiwiSdiExecView()
{
	m_fontGroup.DeleteObject(); m_fontTip.DeleteObject(); m_fontTitle.DeleteObject();

	m_bmpTip.DeleteObject();
	m_bmpXingt1.DeleteObject(); m_bmpXingt2.DeleteObject();
	m_bmpXingt4.DeleteObject(); m_bmpXingt3.DeleteObject();
}

void CKiwiSdiExecView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_GROUP1_2, m_picGroup1_2);
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
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	GetDlgItem(IDC_STATIC_GROUP1)->SetFont(&m_fontGroup);
	GetDlgItem(IDC_STATIC_GROUP2)->SetFont(&m_fontGroup);
	GetDlgItem(IDC_STATIC_GROUP3)->SetFont(&m_fontGroup);

	CStatic* pPic;
	GetDlgItem(IDC_STATIC_GROUP1_1_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP1_1); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpTip);
	GetDlgItem(IDC_STATIC_GROUP1_1_DATA)->SetFont(&m_fontTip);
	GetDlgItem(IDC_STATIC_GROUP1_2_TIP)->SetFont(&m_fontTip);
	m_picGroup1_2.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); m_picGroup1_2.SetBitmap(m_bmpTip);

	GetDlgItem(IDC_STATIC_GROUP1_2_DATA)->SetFont(&m_fontTip);

	GetDlgItem(IDC_STATIC_GROUP2_1_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP2_1); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpXingt1);
	GetDlgItem(IDC_STATIC_GROUP2_1_DATA)->SetFont(&m_fontTip);
	GetDlgItem(IDC_STATIC_GROUP2_2_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP2_2); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpXingt2);
	GetDlgItem(IDC_STATIC_GROUP2_2_DATA)->SetFont(&m_fontTip);
	GetDlgItem(IDC_STATIC_GROUP2_3_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP2_3); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpXingt3);
	GetDlgItem(IDC_STATIC_GROUP2_3_DATA)->SetFont(&m_fontTip);
	GetDlgItem(IDC_STATIC_GROUP2_4_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP2_4); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpXingt4);
	GetDlgItem(IDC_STATIC_GROUP2_4_DATA)->SetFont(&m_fontTip);

	GetDlgItem(IDC_STATIC_GROUP3_1_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP3_1); pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpTip);
	GetDlgItem(IDC_STATIC_GROUP3_1_DATA)->SetFont(&m_fontTip);
	GetDlgItem(IDC_STATIC_GROUP3_2_TIP)->SetFont(&m_fontTip);
	pPic = (CStatic *)GetDlgItem(IDC_PIC_GROUP3_2); 
	pPic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); pPic->SetBitmap(m_bmpTip); 
	GetDlgItem(IDC_STATIC_GROUP3_2_DATA)->SetFont(&m_fontTip);


	GetDlgItem(IDC_STATIC_DEFULAT_TITLE)->SetFont(&m_fontTitle);
	GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetFont(&m_fontTip);
	CTime today = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("现在是：%4d年%02d月%02d日 %02d时%02d分%02d秒"), today.GetYear(), today.GetMonth(), today.GetDay(),
		today.GetHour(), today.GetMinute(), today.GetSecond());
	GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetWindowTextW(str);

	SetTimer(DateTimeTimer, 1000, NULL);

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


void CKiwiSdiExecView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == DateTimeTimer) {
		KillTimer(DateTimeTimer);

		CTime today = CTime::GetCurrentTime();
		CString str;
		str.Format(_T("现在是：%4d年%02d月%02d日 %02d时%02d分%02d秒"), today.GetYear(), today.GetMonth(), today.GetDay(),
			today.GetHour(), today.GetMinute(), today.GetSecond());
		GetDlgItem(IDC_STATIC_CURRENT_DATETIME)->SetWindowTextW(str);

		SetTimer(DateTimeTimer, 1000, NULL);
	}

	CFormView::OnTimer(nIDEvent);
}
