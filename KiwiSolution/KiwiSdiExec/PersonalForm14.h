#pragma once



// CPersonalForm14 ������ͼ

class CPersonalForm14 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm14)

protected:
	CPersonalForm14();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPersonalForm14();

public:
	enum { IDD = IDD_PERSONAL_FORM14 };
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
	afx_msg void OnBnClickedCmdSaveForm2();
	afx_msg void OnBnClickedCmdPrintForm2();
	afx_msg void OnBnClickedButtonCloseForm4();
	int m_Radio13_0;
	int m_Radio13_1;
	int m_Radio13_2;

	afx_msg void OnBnClickedCmdUpdateForm2();

	virtual void OnInitialUpdate();

};


