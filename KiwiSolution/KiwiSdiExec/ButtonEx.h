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
	    //afx_msg void OnBnClicked(); //�����Ӧ����
	    int m_inItem;           //����listctrl����
	    int m_inSubItem;        //����listctrl����
	    CRect m_rect;           //��ť���ڵ�λ��
	    HWND m_hParent;         //��ť�ĸ�����
	    BOOL bEnable;
	    void * m_pData;         //��ť�����û��Զ�������
		int m_file_id;

		afx_msg void OnBnClicked();
};


