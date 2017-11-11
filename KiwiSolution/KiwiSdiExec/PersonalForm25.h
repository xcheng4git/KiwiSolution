#pragma once



#include "PersonalFormInterface.h"
#include "afxwin.h"
// CPersonalForm25 窗体视图

class CPersonalForm25 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm25)

protected:
	CPersonalForm25();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm25();

public:
	enum { IDD = IDD_PERSONAL_FORM25 };
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

private:
	CString m_strCheckImage;
	CString m_strRegisterImage;
	CImageList m_ilIcons;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnDraw(CDC* /*pDC*/);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	afx_msg void OnBnClickedCmdUpdateForm();
	virtual void OnInitialUpdate();
	CXTPBrowseEdit m_editCheckImage;
	CXTPBrowseEdit m_editRegisterImage;
	CStatic m_checkImage;
	CStatic m_registerImage;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit348();
//	afx_msg void OnPaint();
};


