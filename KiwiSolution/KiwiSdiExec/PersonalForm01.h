#pragma once



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

class CPersonalForm01 : public CAutoFocusWnd<CFormView>
//class CPersonalForm01 : public CFormView
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


