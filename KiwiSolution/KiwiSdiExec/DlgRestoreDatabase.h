#pragma once
#include "afxwin.h"


// CDlgRestoreDatabase �Ի���

class CDlgRestoreDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRestoreDatabase)

public:
	CDlgRestoreDatabase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRestoreDatabase();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_RESTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CXTPBrowseEdit m_editPath;
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
