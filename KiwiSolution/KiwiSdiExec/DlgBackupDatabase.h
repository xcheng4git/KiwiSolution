#pragma once
#include "afxwin.h"


// CDlgBackupDatabase �Ի���

class CDlgBackupDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBackupDatabase)

public:
	CDlgBackupDatabase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBackupDatabase();

// �Ի�������
	enum { IDD = IDD_DIALOG_DATABASE_BACKUP };

private:
	bool hasEncodedName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CXTPBrowseEdit m_editPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusEditNameBackup();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
