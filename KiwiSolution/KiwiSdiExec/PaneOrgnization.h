#pragma once
#include "afxcmn.h"


// CPaneOrgnization 对话框

class CPaneOrgnization : public CDialogEx
{
	DECLARE_DYNAMIC(CPaneOrgnization)

public:
	CPaneOrgnization(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPaneOrgnization();

// 对话框数据
	enum { IDD = IDD_PANE_ORGNIZATION };

protected:
	CString m_strCurrentFolder, m_strCurrentFile;
	bool m_bClicked;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPTreeCtrl m_treeOrignization;
	CImageList m_ilTreeIcons;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeOrgnization(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnUpdateOrgnization(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickTreeOrgnization(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonTestForm();
};
