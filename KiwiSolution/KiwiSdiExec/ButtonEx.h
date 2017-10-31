#pragma once


// CButtonEx

class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)

	public:
	    CButtonEx();
	    CButtonEx(int nItem, int nSubItem, CRect rect, HWND hParent, void * pData);
	    virtual ~CButtonEx();
	
	protected:
	    DECLARE_MESSAGE_MAP()
	public :
	    //afx_msg void OnBnClicked(); //点击响应函数
	    int m_inItem;           //所属listctrl的行
	    int m_inSubItem;        //所属listctrl的列
	    CRect m_rect;           //按钮所在的位置
	    HWND m_hParent;         //按钮的父窗口
	    BOOL bEnable;
	    void * m_pData;         //按钮带的用户自定义数据
		int m_file_id;

		afx_msg void OnBnClicked();
};


