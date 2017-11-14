#pragma once


// CDlgNewUser 对话框

class CDlgNewUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewUser)

public:
	CDlgNewUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewUser();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_strUserName;
	CString m_strUserPwd;
	CString m_strUserPwd2;
	afx_msg void OnSetfocusEditNewUserPwd();
	afx_msg void OnSetfocusEditNewUserPwd2();
	afx_msg void OnBnClickedButtonModifyPwd();
};
