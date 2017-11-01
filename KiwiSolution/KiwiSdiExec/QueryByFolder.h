#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CQueryByFolder 窗体视图

class CQueryByFolder : public CFormView
{
	DECLARE_DYNCREATE(CQueryByFolder)

protected:
	CQueryByFolder();           // 动态创建所使用的受保护的构造函数
	virtual ~CQueryByFolder();

public:
	enum { IDD = IDD_DIALOG_QUERY_BYFOLDER };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	CFont m_fontText;
	CBitmap m_bmpClose;
protected:
	int GetFilledFormNumber(int file_id);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listQuery;
	CComboBox m_comboFolders;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonQueryByfolder();
	afx_msg void OnCbnSelchangeComboFolders();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnDropdownComboFolders();
	afx_msg void OnBnClickedButtonCloseForm();
};


