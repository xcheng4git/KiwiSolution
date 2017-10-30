// QueryByFolder.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "QueryByFolder.h"


// CQueryByFolder

IMPLEMENT_DYNCREATE(CQueryByFolder, CFormView)

CQueryByFolder::CQueryByFolder()
	: CFormView(CQueryByFolder::IDD)
{

}

CQueryByFolder::~CQueryByFolder()
{
}

void CQueryByFolder::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUERY_BYFOLDER, m_listQuery);
	DDX_Control(pDX, IDC_COMBO_FOLDERS, m_comboFolders);
}

BEGIN_MESSAGE_MAP(CQueryByFolder, CFormView)
END_MESSAGE_MAP()


// CQueryByFolder 诊断

#ifdef _DEBUG
void CQueryByFolder::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CQueryByFolder::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQueryByFolder 消息处理程序
