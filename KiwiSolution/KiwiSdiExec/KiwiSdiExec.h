
// KiwiSdiExec.h : KiwiSdiExec Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKiwiSdiExecApp:
// �йش����ʵ�֣������ KiwiSdiExec.cpp
//

class CKiwiSdiExecApp : public CWinApp
{
public:
	CKiwiSdiExecApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
