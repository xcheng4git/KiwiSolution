#pragma once



// PersonalForm03 ������ͼ

class PersonalForm03 : public CFormView
{
	DECLARE_DYNCREATE(PersonalForm03)

protected:
	PersonalForm03();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~PersonalForm03();

public:
	enum { IDD = IDD_PERSONAL_FORM03 };
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void OnInitialUpdate();
};


