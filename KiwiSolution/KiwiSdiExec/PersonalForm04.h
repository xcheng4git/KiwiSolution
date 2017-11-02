#pragma once

#include <vector>

// CPersonalForm04 窗体视图

class CPersonalForm04 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm04)

protected:
	CPersonalForm04();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm04();

public:
	enum { IDD = IDD_PERSONAL_FORM04 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	std::vector<std::vector<std::vector<int>>> _vvvParameters;
	int m_modifiedSubform[3];
	std::vector<std::vector<CString>> m_vvFormRecid;
	BOOL m_isModify;

public:
	CString m_strCurrentFile;
	CString m_strCurrentFolder;
	void SetCurrentFile(CString filePath);
	CFont m_fontEdit;
	CBitmap m_bmpClose;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void QueryAndFillFileForm();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	afx_msg void OnBnClickedCmdUpdateForm3();
	virtual void OnInitialUpdate();
	int m_Radio7_0;
	int m_Radio8_0;
	int m_Radio9_0;

};


