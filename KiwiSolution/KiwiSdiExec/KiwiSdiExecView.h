
// KiwiSdiExecView.h : CKiwiSdiExecView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"


class CKiwiSdiExecView : public CFormView
{
protected: // �������л�����
	CKiwiSdiExecView();
	DECLARE_DYNCREATE(CKiwiSdiExecView)

public:
	enum{ IDD = IDD_KIWISDIEXEC_FORM };

// ����
public:
	CKiwiSdiExecDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
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
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picGroup1_2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // KiwiSdiExecView.cpp �еĵ��԰汾
inline CKiwiSdiExecDoc* CKiwiSdiExecView::GetDocument() const
   { return reinterpret_cast<CKiwiSdiExecDoc*>(m_pDocument); }
#endif

