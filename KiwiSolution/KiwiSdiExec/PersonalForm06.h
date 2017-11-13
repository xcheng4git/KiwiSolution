#pragma once


#include "PersonalFormInterface.h"
// CPersonalForm06 窗体视图

class CPersonalForm06 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm06)

protected:
	CPersonalForm06();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm06();

public:
	enum { IDD = IDD_PERSONAL_FORM06 };
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

private:
	BOOL m_bOuterS1, m_bOuterS2, m_bOuterS3;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	int m_Radio7;
	int m_Radio7_1;
	int m_Radio7_2;
	int m_Radio7_3;
	int m_Radio7_4;
	int m_Radio7_5;
	int m_Radio7_6;
	int m_Radio7_7;
	int m_Radio7_8;
	int m_Radio7_9;
	int m_Radio7_4_0;
	int m_Radio7_0;
	int m_Radio7_4_1;
	afx_msg void OnBnClickedCmdUpdateForm3();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRadio43();
	afx_msg void OnBnClickedRadio58();
	afx_msg void OnBnClickedRadio73();
};


