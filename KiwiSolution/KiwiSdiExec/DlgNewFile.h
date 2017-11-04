#pragma once
#include "afxwin.h"


// CDlgNewFile �Ի���

class CDlgNewFile : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewFile)

public:
	CDlgNewFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_FILE };

public:
	void SetCurrentFolderName(CString& folderName);
	CString m_strCurrentFolder;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFileName;
	CComboBox m_comboFolderName;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CString m_strFilePhone;
};
