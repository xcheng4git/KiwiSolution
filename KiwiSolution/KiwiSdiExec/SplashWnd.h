#pragma once


// CSplashWnd

class CSplashWnd : public CWnd
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd();
	virtual ~CSplashWnd();

protected:

	CBitmap m_bitmap;                                              //����SplashScreenͼƬ��

	static CSplashWnd* c_pSplashWnd;        //CSplashWnd��ľ�������������ж�CSplashWnd�Ƿ��Ѿ�����������

	static BOOL c_bShowSplashWnd;             //��ʶ�Ƿ���ʾ��ʾ��������̬��Ա��Ҫ��������г�ʼ��

public:

	static void EnableSplashScreen(BOOL bEnable = TRUE);        //�����趨c_bShowSplashWnd

	static void ShowSplashScreen(CWnd* pParentWnd = NULL); //������ʾSplashScreen����

	static BOOL PreTranslateAppMessage(MSG* pMsg);                         //��������һЩ��Ϣ  ע�����ﲻ�Ǽ̳���CWnd���PreTranslateMessage����

protected:

	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnPaint();

	BOOL Create(CWnd* pParentWnd = NULL);           //��������

	void HideSplashScreen(void);                              //���ش���

	DECLARE_MESSAGE_MAP()
};


