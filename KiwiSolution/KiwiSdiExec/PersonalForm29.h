#pragma once



#include "PersonalFormInterface.h"
// CPersonalForm29 窗体视图

class CPersonalForm29 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm29)

protected:
	CPersonalForm29();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm29();

public:
	enum { IDD = IDD_PERSONAL_FORM29 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void ShowEditbox(int nID, char *data);
	virtual void ShowRadiobtn(int nWhich, char *data);
	virtual void ShowDatapicker(int nID, char *data);

	virtual void GetNumber(int nWhich, int &num);
	virtual void GetString(int nID, CString &str);

	virtual BOOL hasData(int isub, int irow);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	afx_msg void OnBnClickedCmdUpdateForm();
};


