#pragma once


// CDlgNewFolder 对话框

class CDlgNewFolder : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewFolder)

public:
	CDlgNewFolder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewFolder();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_FOLDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFolderName;
	virtual void OnOK();
	CString m_strContactTel;
	CString m_strContactPhone;
	CString m_strContactName;
};
