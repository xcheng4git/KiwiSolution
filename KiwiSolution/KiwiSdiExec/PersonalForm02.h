#pragma once



// CPersonalForm02 窗体视图

class CPersonalForm02 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm02)

protected:
	CPersonalForm02();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm02();

public:
	enum { IDD = IDD_PERSONAL_FORM02 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void QueryAndFillFileForm();

public:
	   CFont m_fontEdit;
	   CString m_strCurrentFile;
	   CString m_strCurrentFolder;
	   CString m_strPicPathname;
	   void SetCurrentFile(CString filePath);
	   virtual void OnInitialUpdate();
	   CBitmap m_bmpClose;
	   afx_msg void OnClickedButtonCloseForm02();
	   afx_msg void OnClickedFilePicture();

private:
	BOOL m_bMarriChanged;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL m_isModify;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticbox1();
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm01();
	afx_msg void OnBnClickedButtonCloseForm02();
	// 初始化函数
//	BOOL m_radiobtngroup1;
	int m_Radio2_1;
	int m_Radio2_2;
	int m_Radio2_3;
	afx_msg void OnBnClickedCmdUpdateForm();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedCmdNextForm();
};


