#pragma once
#include "afxwin.h"
#include "afxcmn.h"


#include <vector>
// CDlgQueryBy 对话框

class CDlgQueryBy : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQueryBy)

public:
	CDlgQueryBy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgQueryBy();

// 对话框数据
	enum { IDD = IDD_DIALOG_QUERY };

	enum { QUERY_BY_RANK,QUERY_BY_AGE,QUERY_BY_DEGREE,QUERY_BY_PARTY,QUERY_BY_HANDIN_FORM,QUERY_BY_FORM	};
public:
	int m_queryType;
	std::vector<CString> m_vParam4Detail;

private:
	void InitQueryByList();
	void DoQueryBy();

	void DoQueryByRank();
	void DoQueryByRankDetail();

	void DoQueryByAge();
	void DoQueryByAgeDetail();

	void DoQueryByDegree();
	void DoQueryByDegreeDetail();

	void DoQueryByParty();
	void DoQueryByPartyDetail();

	void DoQueryByForm();
	void DoQueryByFormDetail();

	void DoQueryByHandinForm();
	void DoQueryByHandinFormDetail();

	void DoQueryByDetail();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl m_listQueryBy;
	CXTPListCtrl m_listQuerySummary;
	CXTPListCtrl m_listQueryDetail;
	CComboBox m_comboFolder;
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListQueryType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListQueryType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListQuerySummary(NMHDR *pNMHDR, LRESULT *pResult);
};

