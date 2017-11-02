#pragma once



// CPersonalForm15 ������ͼ

class CPersonalForm15 : public CFormView
{
	DECLARE_DYNCREATE(CPersonalForm15)

protected:
	CPersonalForm15();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPersonalForm15();

public:
	enum { IDD = IDD_PERSONAL_FORM15 };
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
	int m_Radio14_1_0;
	afx_msg void OnBnClickedCmdUpdateForm();
};


