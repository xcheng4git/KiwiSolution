// ListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "ListCtrlEx.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
	m_uID = 0;
	font.CreatePointFont(100, _T("宋体"));
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

    m_mButton.insert( make_pair( nItem, pButton ) );    //纵向添加用
    //m_mButton.insert(make_pair(nSubItem, pButton)); //单行横向添加用

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



// CListCtrlEx 消息处理程序




void CListCtrlEx::updateListCtrlButtonPos()
{
   button_map::iterator iter = m_mButton.begin();
   button_map::iterator itrEnd = m_mButton.end();
   
   CRect rect;
   GetClientRect(rect);
   long height = rect.bottom;
   
   GetSubItemRect(0, 0, LVIR_BOUNDS, rect);
   long lineHeight = rect.bottom - rect.top;

   int posy = GetScrollPos(SB_VERT);//取得垂直滚动条的位置
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
               //其他的都超出了显示范围
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	updateListCtrlButtonPos();

	Invalidate();
}
