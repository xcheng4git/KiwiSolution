
// KiwiSdiExecView.h : CKiwiSdiExecView 类的接口
//

#pragma once

#include "resource.h"
#include "afxwin.h"


class CKiwiSdiExecView : public CFormView
{
protected: // 仅从序列化创建
	CKiwiSdiExecView();
	DECLARE_DYNCREATE(CKiwiSdiExecView)

public:
	enum{ IDD = IDD_KIWISDIEXEC_FORM };

// 特性
public:
	CKiwiSdiExecDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CKiwiSdiExecView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CFont m_fontGroup, m_fontTip, m_fontTitle;
	CBitmap m_bmpXingt1, m_bmpXingt2, m_bmpXingt3, m_bmpXingt4;
	CBitmap m_bmpTip;

protected:
	enum {DateTimeTimer=1};
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picGroup1_2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // KiwiSdiExecView.cpp 中的调试版本
inline CKiwiSdiExecDoc* CKiwiSdiExecView::GetDocument() const
   { return reinterpret_cast<CKiwiSdiExecDoc*>(m_pDocument); }
#endif

