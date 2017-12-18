#pragma once


#include "PersonalFormInterface.h"
#include "afxwin.h"
#include "afxcmn.h"
// CPersonalForm19 窗体视图

class CPersonalForm19 : public CFormView, public CPersonalFormInterface
{
	DECLARE_DYNCREATE(CPersonalForm19)

protected:
	CPersonalForm19();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm19();

public:
	enum { IDD = IDD_PERSONAL_FORM19 };
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

	virtual int hasData(int isub, int irow);

private:
	CImageList m_ilIcons;
	int m_nAttachCount;
	vector<Attachment> m_vAttachment;
	void InsertListItem(CListCtrl &list, CString& ext, int cntAttach, int data);
	void ShowAttachment();
	void SaveAttachment(CString form_recid);
	void UpdateAttachment();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCmdUpdateForm();
	CXTPBrowseEdit m_editAttachPath;
	CListCtrl m_listAttachments;
	afx_msg void OnBnClickedButtonAddImage();
	afx_msg void OnNMDblclkListAttachment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCmdNextForm();
	afx_msg void OnBnClickedButtonDelAttachment();
};


