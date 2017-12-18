#pragma once
#include "afxwin.h"


// CDlgRestoreDatabase 对话框

class CDlgRestoreDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRestoreDatabase)

public:
	CDlgRestoreDatabase(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRestoreDatabase();

// 对话框数据
	enum { IDD = IDD_DIALOG_DATABASE_RESTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPBrowseEdit m_editPath;
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
