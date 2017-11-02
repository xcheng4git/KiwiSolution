#pragma once



#include "PersonalFormInterface.h"
// CPersonalForm07 窗体视图

class CPersonalForm07 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm07)

protected:
	CPersonalForm07();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm07();

public:
	enum { IDD = IDD_PERSONAL_FORM07 };
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

	virtual BOOL hasData(int isub, int irow);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	int m_Radio7_c2_0;
	int m_Radio7_c2_1;
	int m_Radio7_c2_2;
	int m_Radio7_c2_3;
	int m_Radio7_c2_4;
	int m_Radio7_c2_5;
	int m_Radio7_c2_6;
	int m_Radio7_c2_7;
	int m_Radio8_0;
	int m_Radio8_1;
	int m_Radio8_2;
	afx_msg void OnBnClickedCmdUpdateForm3();
	virtual void OnInitialUpdate();
};


