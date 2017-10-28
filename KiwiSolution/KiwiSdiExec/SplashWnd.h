#pragma once


// CSplashWnd

class CSplashWnd : public CWnd
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd();
	virtual ~CSplashWnd();

protected:

	CBitmap m_bitmap;                                              //加载SplashScreen图片用

	static CSplashWnd* c_pSplashWnd;        //CSplashWnd类的句柄，可以用来判定CSplashWnd是否已经创建或消毁

	static BOOL c_bShowSplashWnd;             //标识是否显示显示用来，静态成员需要在类外进行初始化

public:

	static void EnableSplashScreen(BOOL bEnable = TRUE);        //用来设定c_bShowSplashWnd

	static void ShowSplashScreen(CWnd* pParentWnd = NULL); //用来显示SplashScreen窗口

	static BOOL PreTranslateAppMessage(MSG* pMsg);                         //用来处理一些消息  注意这里不是继承于CWnd类的PreTranslateMessage方法

protected:

	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnPaint();

	BOOL Create(CWnd* pParentWnd = NULL);           //创建窗口

	void HideSplashScreen(void);                              //隐藏窗口

	DECLARE_MESSAGE_MAP()
};


