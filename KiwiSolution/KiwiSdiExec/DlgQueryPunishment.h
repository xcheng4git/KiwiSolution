#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgQueryPunishment �Ի���

class CDlgQueryPunishment : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQueryPunishment)

public:
	CDlgQueryPunishment(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgQueryPunishment();

// �Ի�������
	enum { IDD = IDD_DIALOG_QUERY_PUNISHMENT };
private:
	void InitFourType();

protected:
	CImageList m_ilIcons;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeFourType;
	CListCtrl m_listFiles;
	CComboBox m_comboFiles;
	CComboBox m_combo_Folders;
	afx_msg void OnClickedButtonSearch();
	afx_msg void OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusComboFile();
	afx_msg void OnDropdownComboFolder();
};
