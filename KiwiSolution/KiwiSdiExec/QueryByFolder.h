#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CQueryByFolder ������ͼ

class CQueryByFolder : public CFormView
{
	DECLARE_DYNCREATE(CQueryByFolder)

protected:
	CQueryByFolder();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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


