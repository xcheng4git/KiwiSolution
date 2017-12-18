#pragma once


#include "PersonalFormInterface.h"
// CPersonalForm18 窗体视图

class CPersonalForm18 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm18)

protected:
	CPersonalForm18();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm18();

public:
	enum { IDD = IDD_PERSONAL_FORM18 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	//CString m_strCurrentFile;
	//CString m_strCurrentFolder;
	//void SetCurrentFile(CString filePath);
	//CFont m_fontEdit;
	virtual void ShowEditbox(int nID, char *data);
	virtual void ShowRadiobtn(int nWhich, char *data);
	virtual void ShowDatapicker(int nID, char *data);

	virtual void GetNumber(int nWhich, int &num);
	virtual void GetString(int nID, CString &str);

	virtual int hasData(int isub, int irow);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();

	afx_msg void OnBnClickedCmdUpdateForm();

	virtual void OnInitialUpdate();

	afx_msg void OnBnClickedCmdNextForm();
};


