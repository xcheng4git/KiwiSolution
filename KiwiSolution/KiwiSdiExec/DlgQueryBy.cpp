// DlgQueryBy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgQueryBy.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"

// CDlgQueryBy �Ի���

IMPLEMENT_DYNAMIC(CDlgQueryBy, CDialogEx)

CDlgQueryBy::CDlgQueryBy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgQueryBy::IDD, pParent)
{
	m_queryType = -1;
}

CDlgQueryBy::~CDlgQueryBy()
{
}

void CDlgQueryBy::InitQueryByList()
{
	CImageList   m_l;
	m_l.Create(1, 30, TRUE | ILC_COLOR32, 1, 0);
	m_listQueryBy.SetImageList(&m_l, LVSIL_SMALL);
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 400;
	CFont font1; font1.CreateFontIndirect(&lf);
	m_listQueryBy.SetFont(&font1); font1.DeleteObject();
	lf.lfHeight = 15;
	font1.CreateFontIndirect(&lf);
	m_listQuerySummary.SetFont(&font1); 
	m_listQuerySummary.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listQuerySummary.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listQueryBy.InsertColumn(0, _T("Column One"), LVCFMT_LEFT, 50);
	m_listQueryBy.InsertColumn(1, _T("Column two"), LVCFMT_LEFT, 100);
	m_listQueryBy.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//int iItem;
	//iItem = 0;  m_listQueryBy.InsertItem(iItem, _T("1"));
	//m_listQueryBy.SetItem(iItem, 1, LVIF_TEXT, _T("��������λ              "), 0, NULL, NULL, NULL);
	//iItem = 1;  m_listQueryBy.InsertItem(iItem, _T("2"));
	//m_listQueryBy.SetItem(iItem, 1, LVIF_TEXT, _T("��������λ              "), 0, NULL, NULL, NULL);

	m_listQueryBy.InsertItem(0, _T("1����ְ��ͳ�ơ�����������������"));
	m_listQueryBy.InsertItem(1, _T("2��������ͳ�ơ�����������������"));
	m_listQueryBy.InsertItem(2, _T("3����ѧ��ͳ�ơ�����������������"));
	m_listQueryBy.InsertItem(3, _T("4����������òͳ�ơ�������������"));
	m_listQueryBy.InsertItem(4, _T("5���������Ͻ����ͳ�ơ���������"));
	m_listQueryBy.InsertItem(5, _T("6������������ͳ�ơ�������������"));

	//int iItem = 0;
	//{
	//	LV_ITEM lvitem;
	//	memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
	//	lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	//	lvitem.iItem = iItem;
	//	lvitem.iSubItem = 0;
	//	lvitem.stateMask = 0;
	//	lvitem.pszText = _T("1��������λ");
	//	m_listQueryBy.InsertItem(&lvitem);
	//	iItem++;
	//}
	//{
	//	LV_ITEM lvitem;
	//	memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
	//	lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	//	lvitem.iItem = iItem;
	//	lvitem.iSubItem = 0;
	//	lvitem.stateMask = 0;
	//	lvitem.pszText = _T("2��������Ա");
	//	m_listQueryBy.InsertItem(&lvitem);
	//	iItem++;
	//}
	//{
	//	LV_ITEM lvitem;
	//	memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
	//	lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	//	lvitem.iItem = iItem;
	//	lvitem.iSubItem = 0;
	//	lvitem.stateMask = 0;
	//	lvitem.pszText = _T("3���½���������");
	//	m_listQueryBy.InsertItem(&lvitem);
	//	iItem++;
	//}
	//{
	//	LV_ITEM lvitem;
	//	memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
	//	lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	//	lvitem.iItem = iItem;
	//	lvitem.iSubItem = 0;
	//	lvitem.stateMask = 0;
	//	lvitem.pszText = _T("4��ɾ����λ����Ա");
	//	m_listQueryBy.InsertItem(&lvitem);
	//	iItem++;
	//}
	
	m_listQueryDetail.InsertColumn(0, _T(" "), LVCFMT_CENTER, 30);
	m_listQueryDetail.InsertColumn(1, _T("����"), LVCFMT_CENTER, 80);
	m_listQueryDetail.InsertColumn(2, _T("�Ա�"), LVCFMT_CENTER, 50);
	m_listQueryDetail.InsertColumn(3, _T("����"), LVCFMT_CENTER, 100);
	m_listQueryDetail.InsertColumn(4, _T("����ְ��"), LVCFMT_CENTER, 220);
	m_listQueryDetail.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listQueryDetail.SetFont(&font1); font1.DeleteObject();

}

void CDlgQueryBy::DoQueryBy()
{
	switch (m_queryType) {
	case QUERY_BY_RANK:
		DoQueryByRank();
		break;
	case QUERY_BY_AGE:
		DoQueryByAge();
		break;
	case QUERY_BY_DEGREE:
		DoQueryByDegree();
		break;
	case QUERY_BY_PARTY:
		DoQueryByParty();
		break;
	case QUERY_BY_HANDIN_FORM:
		DoQueryByHandinForm();
		break;
	case QUERY_BY_FORM:
		DoQueryByForm();
		break;
	}
}

void CDlgQueryBy::DoQueryByRank()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

	m_listQuerySummary.InsertColumn(0, _T(""), LVCFMT_CENTER, 25);
	m_listQuerySummary.InsertColumn(1, _T("ְ��"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("����"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("����"), LVCFMT_CENTER, 60);

	stringstream ss;

	ss << "select file_Rank, count(*) from file_form_02 where file_id in(select file_id from orgnization_file where del_status = 0 ";
	CString strText;
	m_comboFolder.GetWindowTextW(strText); strText.Trim();
	if (!strText.IsEmpty()) {
		ss << " and folder_name=";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
	}
	ss << ") group by file_rank; ";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");


	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�

	if (row < 1) {
		help->closeDB(); delete help;
		return;
	}

	float sum = 0.0;
	for (int r = 0; r < row; r++) {
		CString str;
		str.Format(_T("%d"), r+1);
		m_listQuerySummary.InsertItem(r, str);

		m_listQuerySummary.SetItem(r, 1, LVIF_TEXT, CA2W(re[(r+1) * col + 0], CP_UTF8), 0, NULL, NULL, NULL);

		int t = atoi(re[(r + 1) * col + 1]); sum += (float)t;
		str.ReleaseBuffer(); str.Format(_T("%d"), t);
		m_listQuerySummary.SetItem(r, 2, LVIF_TEXT, str, 0, NULL, NULL, NULL);
	}
	for (int r = 0; r < row; r++) {
		CString str;
		int t = atoi(re[(r + 1) * col + 1]);
		str.ReleaseBuffer(); str.Format(_T("%2.1f%%"), (t / sum) * 100 );
		m_listQuerySummary.SetItem(r, 3, LVIF_TEXT, str, 0, NULL, NULL, NULL);
	}

	help->closeDB(); delete help;
}

void CDlgQueryBy::DoQueryByRankDetail()
{
	m_listQueryDetail.DeleteAllItems();
	stringstream ss;

	ss << "select file_name, file_gender, file_nation, file_CurrentPosition from file_form_02 where file_rank=";
	ss << "'" << CW2A(m_vParam4Detail[1].GetBuffer(), CP_UTF8) << "' and ";
	ss << " file_id in(select file_id from orgnization_file where del_status = 0 ";
	CString strText;
	m_comboFolder.GetWindowTextW(strText); strText.Trim();
	if (!strText.IsEmpty()) {
		ss << " and folder_name=";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
	}
	ss << "); ";
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");


	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�

	if (row < 1) {
		help->closeDB(); delete help;
		return;
	}

	for (int r = 0; r < row; r++) {
		CString str;
		str.Format(_T("%d"), r + 1);
		m_listQueryDetail.InsertItem(r, str);

		for (int i = 0; i < 4; i++)
			m_listQueryDetail.SetItem(r, i+1, LVIF_TEXT, CA2W(re[(r + 1) * col + i], CP_UTF8), 0, NULL, NULL, NULL);
	}

	help->closeDB(); delete help;
}

void CDlgQueryBy::DoQueryByAge()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

	m_listQuerySummary.InsertColumn(0, _T(""), LVCFMT_CENTER, 25);
	m_listQuerySummary.InsertColumn(1, _T("�����"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("����"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("����"), LVCFMT_CENTER, 60);
}

void CDlgQueryBy::DoQueryByAgeDetail()
{

}

void CDlgQueryBy::DoQueryByDegree()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

	m_listQuerySummary.InsertColumn(0, _T(""), LVCFMT_CENTER, 25);
	m_listQuerySummary.InsertColumn(1, _T("ѧλ"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("����"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("����"), LVCFMT_CENTER, 60);
}

void CDlgQueryBy::DoQueryByDegreeDetail()
{

}

void CDlgQueryBy::DoQueryByParty()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

	m_listQuerySummary.InsertColumn(0, _T(""), LVCFMT_CENTER, 25);
	m_listQuerySummary.InsertColumn(1, _T("������ò"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("����"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("����"), LVCFMT_CENTER, 60);

	stringstream ss;

	ss << "select file_PoliticalStatus, count(*) from file_form_02 where file_id in(select file_id from orgnization_file where del_status = 0 ";
	CString strText;
	m_comboFolder.GetWindowTextW(strText); strText.Trim();
	if (!strText.IsEmpty()) {
		ss << " and folder_name=";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
	}
	ss << ") group by file_PoliticalStatus; ";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");


	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�

	if (row < 1) {
		help->closeDB(); delete help;
		return;
	}

	float sum = 0.0;
	for (int r = 0; r < row; r++) {
		CString str;
		str.Format(_T("%d"), r + 1);
		m_listQuerySummary.InsertItem(r, str);

		m_listQuerySummary.SetItem(r, 1, LVIF_TEXT, CA2W(re[(r + 1) * col + 0], CP_UTF8), 0, NULL, NULL, NULL);

		int t = atoi(re[(r + 1) * col + 1]); sum += (float)t;
		str.ReleaseBuffer(); str.Format(_T("%d"), t);
		m_listQuerySummary.SetItem(r, 2, LVIF_TEXT, str, 0, NULL, NULL, NULL);
	}
	for (int r = 0; r < row; r++) {
		CString str;
		int t = atoi(re[(r + 1) * col + 1]);
		str.ReleaseBuffer(); str.Format(_T("%2.1f%%"), (t / sum) * 100);
		m_listQuerySummary.SetItem(r, 3, LVIF_TEXT, str, 0, NULL, NULL, NULL);
	}

	help->closeDB(); delete help;

}

void CDlgQueryBy::DoQueryByPartyDetail()
{
	m_listQueryDetail.DeleteAllItems();
	stringstream ss;

	ss << "select file_name, file_gender, file_nation, file_CurrentPosition from file_form_02 where file_PoliticalStatus=";
	ss << "'" << CW2A(m_vParam4Detail[1].GetBuffer(), CP_UTF8) << "' and ";
	ss << " file_id in(select file_id from orgnization_file where del_status = 0 ";
	CString strText;
	m_comboFolder.GetWindowTextW(strText); strText.Trim();
	if (!strText.IsEmpty()) {
		ss << " and folder_name=";
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
	}
	ss << "); ";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");


	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�

	if (row < 1) {
		help->closeDB(); delete help;
		return;
	}

	for (int r = 0; r < row; r++) {
		CString str;
		str.Format(_T("%d"), r + 1);
		m_listQueryDetail.InsertItem(r, str);

		for (int i = 0; i < 4; i++)
			m_listQueryDetail.SetItem(r, i + 1, LVIF_TEXT, CA2W(re[(r + 1) * col + i], CP_UTF8), 0, NULL, NULL, NULL);
	}

	help->closeDB(); delete help;
}

void CDlgQueryBy::DoQueryByForm()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

	m_listQuerySummary.InsertColumn(0, _T(""), LVCFMT_CENTER, 25);
	m_listQuerySummary.InsertColumn(1, _T("�������"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("����"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("����"), LVCFMT_CENTER, 60);

}

void CDlgQueryBy::DoQueryByFormDetail()
{

}

void CDlgQueryBy::DoQueryByHandinForm()
{
	m_listQueryDetail.DeleteAllItems();
	m_listQuerySummary.DeleteAllItems();
	int nColumnCount = m_listQuerySummary.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++) m_listQuerySummary.DeleteColumn(0);

}

void CDlgQueryBy::DoQueryByHandinFormDetail()
{

}

void CDlgQueryBy::DoQueryByDetail()
{
	switch (m_queryType) {
	case QUERY_BY_RANK:
		DoQueryByRankDetail();
		break;
	case QUERY_BY_AGE:
		DoQueryByAgeDetail();
		break;
	case QUERY_BY_DEGREE:
		DoQueryByDegreeDetail();
		break;
	case QUERY_BY_PARTY:
		DoQueryByPartyDetail();
		break;
	case QUERY_BY_HANDIN_FORM:
		DoQueryByHandinFormDetail();
		break;
	case QUERY_BY_FORM:
		DoQueryByFormDetail();
		break;
	}
}

void CDlgQueryBy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUERY_TYPE, m_listQueryBy);
	DDX_Control(pDX, IDC_LIST_QUERY_SUMMARY, m_listQuerySummary);
	DDX_Control(pDX, IDC_LIST_QUERY_DETAIL, m_listQueryDetail);
	DDX_Control(pDX, IDC_COMBO_FOLDER, m_comboFolder);
}


BEGIN_MESSAGE_MAP(CDlgQueryBy, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_QUERY_TYPE, &CDlgQueryBy::OnItemchangedListQueryType)
	ON_NOTIFY(NM_CLICK, IDC_LIST_QUERY_TYPE, &CDlgQueryBy::OnClickListQueryType)
	ON_NOTIFY(NM_CLICK, IDC_LIST_QUERY_SUMMARY, &CDlgQueryBy::OnClickListQuerySummary)
END_MESSAGE_MAP()


// CDlgQueryBy ��Ϣ�������


BOOL CDlgQueryBy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_comboFolder.AddString(_T(""));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select * from orgnization_folder where del_status=0";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re��ָ�������ָ�롣(1)Ϊ��1�У�1��ʾ��1��,��0����,��0�����ֶ�����*/

	char *folder_id, *folder_name;
	for (int r = 1; r <= row; r++) {
		folder_id = re[r*col + 0]; folder_name = re[r*col + 1];

		m_comboFolder.AddString(CA2W(folder_name, CP_UTF8));
	}

	help->closeDB(); delete help;

	InitQueryByList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgQueryBy::OnItemchangedListQueryType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CDlgQueryBy::OnClickListQueryType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//if (pNMItemActivate->uChanged == LVIF_STATE)
	{
		//if (pNMItemActivate->uNewState & LVIS_SELECTED)
		{
			//��������
			m_queryType = pNMItemActivate->iItem;
			DoQueryBy();
		}
	}

	*pResult = 0;
}


void CDlgQueryBy::OnClickListQuerySummary(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int nItem = pNMItemActivate->iItem;
	if (nItem != -1) {
		m_vParam4Detail.clear();
		m_vParam4Detail.push_back(m_listQuerySummary.GetItemText(nItem, 0));
		m_vParam4Detail.push_back(m_listQuerySummary.GetItemText(nItem, 1));
		DoQueryByDetail();
	}
	*pResult = 0;
}
