
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "PaneOrgnization.h"
#include "PaneShortcut.h"
#include "KiwiSdiExecDoc.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CXTPDockingPaneManager& GetDockingPaneManager() { return m_paneManager; }
	CMap<UINT, UINT, CWnd*, CWnd*> m_mapPanes;

// ����
public:
	CKiwiSdiExecDoc* GetDocument();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CXTPDockingPaneManager m_paneManager;

	CPaneOrgnization m_wndPaneOrgnization;
	CPaneShortcut m_wndPaneShortcut;

	bool m_bFullscreen;
	CRect m_rcMainFrame;

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	CView* CreatePersonalForm(CRuntimeClass* pNewViewClass, int nID);
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnCreatePersonalForm(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowPersonalSummary(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateOrgnization(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnToolFullscreen();
	afx_msg void OnUpdateToolFullscreen(CCmdUI *pCmdUI);
protected:
	afx_msg LRESULT OnShowDefaultSummary(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnQueryByFolder();
protected:
	afx_msg LRESULT OnModifyPersonalForm(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDatabaseInitial();
	afx_msg void OnDatabaseBackup();
	afx_msg void OnToolNewUser();
	afx_msg void OnQueryByPosition();
	afx_msg void OnQueryByParty();
	afx_msg void OnQueryByHandinForm();
	afx_msg void OnQueryByForm();
	afx_msg void OnQueryByPunish();
	afx_msg void OnQueryByDegree();
	afx_msg void OnQueryByAge();
};

