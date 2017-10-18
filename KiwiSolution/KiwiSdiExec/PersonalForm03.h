#pragma once



// PersonalForm03 窗体视图

class PersonalForm03 : public CFormView
{
	DECLARE_DYNCREATE(PersonalForm03)

protected:
	PersonalForm03();           // 动态创建所使用的受保护的构造函数
	virtual ~PersonalForm03();

public:
	enum { IDD = IDD_PERSONAL_FORM03 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CString m_strCurrentFile;
	CString m_strCurrentFolder;
	void SetCurrentFile(CString filePath);
	CFont m_fontEdit;
	CString m_strPicPathname;
	CStatic m_picFile;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInitialUpdate();
//	afx_msg void OnBnClickedCmdSaveForm();
//	afx_msg void OnBnClickedCmdPrintForm();
//	afx_msg void OnBnClickedButtonCloseForm03();
	afx_msg void OnStnClickedFilePicture();
	afx_msg void OnBnClickedButtonCloseForm3();
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
};


