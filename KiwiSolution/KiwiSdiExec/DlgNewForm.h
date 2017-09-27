#pragma once

#include "Resource.h"
#include "afxcmn.h"

// CDlgNewForm �Ի���

class CDlgNewForm : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewForm)

public:
	CDlgNewForm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewForm();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_FORM };
	CString m_strCurrentFile;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl m_listFormType;
	CXTPHeaderCtrl   m_header;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
