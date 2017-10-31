
// KiwiSdiExec.h : KiwiSdiExec 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CKiwiSdiExecApp:
// 有关此类的实现，请参阅 KiwiSdiExec.cpp
//

class CKiwiSdiExecApp : public CWinApp
{
public:
	CKiwiSdiExecApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CKiwiSdiExecApp theApp;

#define WM_CREATE_PERSONAL_FORM WM_USER + 1
#define WM_SHOW_PERSONAL_SUMMARY WM_USER + 2
#define WM_SHOW_DEFAULT_SUMMARY WM_USER + 3
#define WM_UPDATE_ORGNIZATION WM_USER + 4
#define WM_SELECTED_FOLDER_CHANGED  WM_USER + 5

#define WM_MODIFY_PERSONAL_FORM  WM_USER + 6
