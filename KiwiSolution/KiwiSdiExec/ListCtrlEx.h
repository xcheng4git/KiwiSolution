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
    //��̬����Button
    void createItemButton(int nItem, int nSubItem, HWND hMain, LPCTSTR lpszCaption, void * pData);
    //�ͷŴ�����Button
    void release();
    void deleteItemEx(int nItem);
	button_map m_mButton;

public:
    UINT m_uID;
    CFont font;    //��ť���������
    void updateListCtrlButtonPos(); //���°�ť��λ��
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


