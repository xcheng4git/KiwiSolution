#pragma once


#include "PersonalFormInterface.h"
// CPersonalForm14 窗体视图

class CPersonalForm14 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm14)

protected:
	CPersonalForm14();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm14();

public:
	enum { IDD = IDD_PERSONAL_FORM14 };
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
	afx_msg void OnBnClickedCmdSaveForm2();
	afx_msg void OnBnClickedCmdPrintForm2();
	afx_msg void OnBnClickedButtonCloseForm4();
	int m_Radio13_0;
	int m_Radio13_1;
	int m_Radio13_2;

	afx_msg void OnBnClickedCmdUpdateForm2();

	virtual void OnInitialUpdate();

};


