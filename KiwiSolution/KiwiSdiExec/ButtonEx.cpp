// ButtonEx.cpp : ʵ���ļ�
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



// CButtonEx ��Ϣ�������




void CButtonEx::OnBnClicked()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	int flag = 1 << 16;
	::PostMessage(pWnd->m_hWnd, WM_MODIFY_PERSONAL_FORM, WPARAM(flag+m_inItem+1), LPARAM(m_file_id));

}
