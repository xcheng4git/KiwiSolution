#pragma once
#include "afxcmn.h"

#include "resource.h"

// CPaneShortcut �Ի���

class CPaneShortcut : public CDialogEx
{
	DECLARE_DYNAMIC(CPaneShortcut)

public:
	CPaneShortcut(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPaneShortcut();

// �Ի�������
	enum { IDD = IDD_PANE_SHORTCUT };

public:
	void InvokeNewFolderDialog();
	void InvokeNewFileDialog();
	void InvokeNewFormDialog();

public:
	CString m_strCurrentFolder, m_strCurrentFile;
	bool m_bClicked;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl m_listShortcut;
	CImageList m_ilTreeIcons;
	afx_msg void OnItemchangedListShortcut(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnClickListShortcut(NMHDR *pNMHDR, LRESULT *pResult);
};
