// ButtonEx.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "ButtonEx.h"
#include "MainFrm.h"

// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
{

}
CButtonEx::CButtonEx(int nItem, int nSubItem, CRect rect, HWND hParent, void * pData)
{
   m_inItem = nItem;
   m_inSubItem = nSubItem;
   m_rect = rect;
    m_hParent = hParent;
    bEnable = TRUE;
    m_pData = pData;

	m_file_id = *(int*)pData;
}

CButtonEx::~CButtonEx()
{

}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonEx::OnBnClicked)
END_MESSAGE_MAP()



// CButtonEx 消息处理程序




void CButtonEx::OnBnClicked()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	int flag = 1 << 16;
	::PostMessage(pWnd->m_hWnd, WM_MODIFY_PERSONAL_FORM, WPARAM(flag+m_inItem+1), LPARAM(m_file_id));

}
