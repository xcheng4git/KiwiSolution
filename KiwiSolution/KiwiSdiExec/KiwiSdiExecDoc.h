
// KiwiSdiExecDoc.h : CKiwiSdiExecDoc ��Ľӿ�
//


#pragma once
#include <vector>

class CKiwiSdiExecDoc : public CDocument
{
protected: // �������л�����
	CKiwiSdiExecDoc();
	DECLARE_DYNCREATE(CKiwiSdiExecDoc)

// ����
public:
	std::vector<std::vector<wchar_t *>> m_vvFormByTables;
	std::vector<std::vector<int>> m_vvFormBySubform;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CKiwiSdiExecDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
