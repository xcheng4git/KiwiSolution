#pragma once

#include "Resource.h"
#include "afxcmn.h"

// CDlgNewForm 对话框

class CDlgNewForm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewForm)

public:
	CDlgNewForm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewForm();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_FORM };
	CString m_strCurrentFile;
	CString m_strCurrentFolder;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl m_listFormType;
	CXTPHeaderCtrl   m_header;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
