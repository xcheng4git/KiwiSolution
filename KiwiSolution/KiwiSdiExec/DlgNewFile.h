#pragma once
#include "afxwin.h"


// CDlgNewFile 对话框

class CDlgNewFile : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewFile)

public:
	CDlgNewFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_FILE };

public:
	void SetCurrentFolderName(CString& folderName);
	CString m_strCurrentFolder;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFileName;
	CComboBox m_comboFolderName;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
