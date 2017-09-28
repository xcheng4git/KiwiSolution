#pragma once
#include "afxcmn.h"


// CPaneOrgnization �Ի���

class CPaneOrgnization : public CDialogEx
{
	DECLARE_DYNAMIC(CPaneOrgnization)

public:
	CPaneOrgnization(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPaneOrgnization();

// �Ի�������
	enum { IDD = IDD_PANE_ORGNIZATION };

protected:
	CString m_strCurrentFolder, m_strCurrentFile;
	bool m_bClicked;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
