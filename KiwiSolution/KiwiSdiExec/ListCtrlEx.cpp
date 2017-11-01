// ListCtrlEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "ListCtrlEx.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
	m_uID = 0;
	font.CreatePointFont(100, _T("����"));
}

CListCtrlEx::~CListCtrlEx()
{
	release();
}


void CListCtrlEx::createItemButton(int nItem, int nSubItem, HWND hMain, LPCTSTR lpszCaption, void * pData)
{
   CRect rect;
   /*if( !EnsureVisible(nItem, TRUE))
        return ;*/

    GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
   //rect.bottom = rect.top + 30;
	rect.left += 20;  rect.right = rect.left + 60;

   DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_MULTILINE;
    CButtonEx *pButton = new CButtonEx(nItem, nSubItem, rect, hMain, pData);
    m_uID++;

    pButton->Create(lpszCaption, dwStyle, rect, this, m_uID);
    //CDC* pDC = pButton->GetDC();
    //pDC->SetTextColor(RGB(255,0,0));
    pButton->SetFont(&font);

    m_mButton.insert( make_pair( nItem, pButton ) );    //���������
    //m_mButton.insert(make_pair(nSubItem, pButton)); //���к��������

    return;
}

void CListCtrlEx::release()
{
    button_map::iterator iter = m_mButton.begin();
    while (iter != m_mButton.end())
    {
        delete iter->second;
        iter->second = NULL;
        iter++;
    }
    m_mButton.clear();
}

void CListCtrlEx::deleteItemEx(int nItem)
{

}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// CListCtrlEx ��Ϣ�������




void CListCtrlEx::updateListCtrlButtonPos()
{
   button_map::iterator iter = m_mButton.begin();
   button_map::iterator itrEnd = m_mButton.end();
   
   CRect rect;
   GetClientRect(rect);
   long height = rect.bottom;
   
   GetSubItemRect(0, 0, LVIR_BOUNDS, rect);
   long lineHeight = rect.bottom - rect.top;

   int posy = GetScrollPos(SB_VERT);//ȡ�ô�ֱ��������λ��
   for (; iter != itrEnd; ++iter)
    {
        iter->second->ShowWindow(SW_HIDE);

       rect = iter->second->m_rect;
	   rect.top -= posy*lineHeight;
	   rect.bottom -= posy*lineHeight;
        if (rect.top > 15)
        {
            if (rect.bottom > height)
            {
               //�����Ķ���������ʾ��Χ
                break;
            }
            iter->second->MoveWindow(&rect);
            iter->second->ShowWindow(SW_SHOW);
       }

        //CRect rect;
        //rect = iter->second->m_rect;
        //rect.top -= posy;
        //rect.bottom -= posy;
        //iter->second->ShowWindow(SW_HIDE);

        //iter->second->MoveWindow(&rect);
        //iter->second->ShowWindow(SW_SHOW);
        ///*if( iLine < iTopIndex )
        //{
        //    iterUp->second->ShowWindow( SW_HIDE );
        //}*/
    }
    return;
}

void CListCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	updateListCtrlButtonPos();

	Invalidate();
}
