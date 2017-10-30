#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CQueryByFolder 窗体视图

class CQueryByFolder : public CFormView
{
	DECLARE_DYNCREATE(CQueryByFolder)

protected:
	CQueryByFolder();           // 动态创建所使用的受保护的构造函数
	virtual ~CQueryByFolder();

public:
	enum { IDD = IDD_DIALOG_QUERY_BYFOLDER };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listQuery;
	CComboBox m_comboFolders;
};


