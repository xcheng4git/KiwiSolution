#pragma once



#include "PersonalFormInterface.h"
#include "afxwin.h"
#include "afxcmn.h"
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

	virtual int hasData(int isub, int irow);

private:
	CImageList m_ilIcons;
	int m_nCheckAttachCount, m_nRegisterAttachCount;
	vector<Attachment> m_vCheckAttachment;
	vector<Attachment> m_vRegisterAttachment;
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
	afx_msg void OnBnClickedCmdUpdateForm();
	virtual void OnInitialUpdate();
	CXTPBrowseEdit m_editCheckPath;
	CXTPBrowseEdit m_editRegisterPath;
	CListCtrl m_listCheckImages;
	CListCtrl m_listRegisterImages;
	afx_msg void OnBnClickedButtonAddCheckImage();
	afx_msg void OnBnClickedButtonAddRegisterImage();
	afx_msg void OnNMDblclkListAttachment2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListAttachment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCmdNextForm();
};


