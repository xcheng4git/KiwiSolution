#pragma once



// CPersonalForm10 ������ͼ

class CPersonalForm10 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm10)

protected:
	CPersonalForm10();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPersonalForm10();

public:
	enum { IDD = IDD_PERSONAL_FORM10 };
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
	CFont m_fontEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCmdSaveForm();
	afx_msg void OnBnClickedCmdPrintForm();
	afx_msg void OnBnClickedButtonCloseForm3();
	int m_Radio12_1_0;
	afx_msg void OnBnClickedCmdUpdateForm();
	virtual void OnInitialUpdate();
};


