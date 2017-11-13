#pragma once
#include "afxwin.h"


// CDlgShowAttachment �Ի���

class CDlgShowAttachment : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowAttachment)

public:
	CDlgShowAttachment(CString& file_form, CString& attachmentPath, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowAttachment();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_ATTACHMENT };

public:
	int m_nFile_Id;
	CString m_strFormName;
	CString m_strAttachmentPath;
private:
	CFont m_fontEdit;
	CFont m_fontHeader;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_imageAttachment;
	afx_msg void OnPaint();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCmdPrintForm();
};
