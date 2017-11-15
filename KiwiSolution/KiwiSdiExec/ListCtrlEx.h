#pragma once

#include "ButtonEx.h"
#include <map>
using namespace std;

typedef map<int, CButtonEx*> button_map;
// CListCtrlEx

//class CListCtrlEx : public CListCtrl
class CListCtrlEx : public CXTPListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()

public :
    //动态创建Button
    void createItemButton(int nItem, int nSubItem, HWND hMain, LPCTSTR lpszCaption, void * pData);
    //释放创建的Button
    void release();
    void deleteItemEx(int nItem);
	button_map m_mButton;

public:
    UINT m_uID;
    CFont font;    //按钮上面的字体
    void updateListCtrlButtonPos(); //更新按钮的位置
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


