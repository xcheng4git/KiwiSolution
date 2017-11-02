#pragma once
#include "afxcmn.h"

#include "resource.h"

// CPaneShortcut 对话框

class CPaneShortcut : public CDialogEx
{
	DECLARE_DYNAMIC(CPaneShortcut)

public:
	CPaneShortcut(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPaneShortcut();

// 对话框数据
	enum { IDD = IDD_PANE_SHORTCUT };

public:
	void InvokeNewFolderDialog();
	void InvokeNewFileDialog();
	void InvokeNewFormDialog();

public:
	CString m_strCurrentFolder, m_strCurrentFile;
	bool m_bClicked;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl m_listShortcut;
	CImageList m_ilTreeIcons;
	afx_msg void OnItemchangedListShortcut(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnClickListShortcut(NMHDR *pNMHDR, LRESULT *pResult);
};
