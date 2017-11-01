#pragma once



// CPersonalForm09 窗体视图

class CPersonalForm09 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm09)

protected:
	CPersonalForm09();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm09();

public:
	enum { IDD = IDD_PERSONAL_FORM09 };
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


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();

	int m_Radio11_3_1;
	int m_Radio11_3_2;
	int m_Radio11_3_3;
	int m_Radio11_4_1;
	int m_Radio11_4_2;
	int m_Radio11_4_3;
	int m_Radio11_5_1;
	int m_Radio11_5_2;
	int m_Radio11_5_3;
	int m_Radio11_6_1;
	int m_Radio11_6_2;
	int m_Radio11_6_3;
	virtual void OnInitialUpdate();
};


