#pragma once
#include "afxwin.h"

#include "DatePickerCombo.h"
#include "afxdtctl.h"

template <class BASE_CLASS>
class CAutoFocusWnd : public BASE_CLASS
{
public:
	CAutoFocusWnd(UINT nIDTemplate) : BASE_CLASS(nIDTemplate)
	{
		m_hwndLastFocus = 0;
	}

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SETFOCUS:
			if (m_hwndLastFocus)
			{
				::SetFocus(m_hwndLastFocus);
				return TRUE;
			}
			break;

		case WM_IDLEUPDATECMDUI:

			HWND hwndFocus = ::GetFocus();

			if (m_hwndLastFocus != hwndFocus && ::IsChild(m_hWnd, hwndFocus))
			{
				m_hwndLastFocus = hwndFocus;
			}
			break;

		}

		return BASE_CLASS::WindowProc(message, wParam, lParam);
	}

protected:
	HWND m_hwndLastFocus;
};
// CPersonalForm01 窗体视图

//class CPersonalForm01 : public CAutoFocusWnd<CFormView>
class CPersonalForm01 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm01)

protected:
	CPersonalForm01();           // 动态创建所使用的受保护的构造函数
	virtual ~CPersonalForm01();

public:
	enum { IDD = IDD_PERSONAL_FORM01 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CString m_strCurrentFile;
	CString m_strCurrentFolder;
	void SetCurrentFile(CString filePath);

protected:
	enum { BorderLeft = 1, BorderTop = 2, BorderRight = 4, BorderBottom = 8 };
	void DrawFormHeader(CDC* pDC, CRect* pBox);
	void DrawForm(CDC* pDC, CRect* pBox);
	inline void DrawTextCell(CDC* pDC, CRect& box, CString& strText, int enumBorder);

	void QueryAndFillFileForm();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate(); 
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CFont m_fontEdit;
	afx_msg void OnClickedCmdSaveForm();
	CDateTimeCtrl m_ctrlBirthday;
	afx_msg void OnClickedCmdPrintForm();
	afx_msg void OnClickedFilePicture();
	CStatic m_picFile;
	CString m_strPicPathname;
};

#define MARGIN_X 20
#define MARGIN_Y 10
#define PAGE_START_OFFSET_X 20
#define PAGE_START_OFFSET_Y 20
#define HEADER_START_OFFSET_X 10
#define HEADER_START_OFFSET_Y 30
#define HEADER_HEIGHT 40
#define CELL_HEIGHT 40
#define CELL_WIDTH_RATIO 1.0/7.0