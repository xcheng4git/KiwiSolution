// DlgQueryBy.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgQueryBy.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"

// CDlgQueryBy 对话框

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
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
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
	//m_listQueryBy.SetItem(iItem, 1, LVIF_TEXT, _T("、新增单位              "), 0, NULL, NULL, NULL);
	//iItem = 1;  m_listQueryBy.InsertItem(iItem, _T("2"));
	//m_listQueryBy.SetItem(iItem, 1, LVIF_TEXT, _T("、新增单位              "), 0, NULL, NULL, NULL);

	m_listQueryBy.InsertItem(0, _T("1、按职级统计　　　　　　　　　"));
	m_listQueryBy.InsertItem(1, _T("2、按年龄统计　　　　　　　　　"));
	m_listQueryBy.InsertItem(2, _T("3、按学历统计　　　　　　　　　"));
	m_listQueryBy.InsertItem(3, _T("4、按政治面貌统计　　　　　　　"));
	m_listQueryBy.InsertItem(4, _T("5、按档案上交情况统计　　　　　"));
	m_listQueryBy.InsertItem(5, _T("6、按档案分类统计　　　　　　　"));

	//int iItem = 0;
	//{
	//	LV_ITEM lvitem;
	//	memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
	//	lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	//	lvitem.iItem = iItem;
	//	lvitem.iSubItem = 0;
	//	lvitem.stateMask = 0;
	//	lvitem.pszText = _T("1、新增单位");
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
	//	lvitem.pszText = _T("2、新增人员");
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
	//	lvitem.pszText = _T("3、新建廉政档案");
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
	//	lvitem.pszText = _T("4、删除单位或人员");
	//	m_listQueryBy.InsertItem(&lvitem);
	//	iItem++;
	//}
	
	m_listQueryDetail.InsertColumn(0, _T(" "), LVCFMT_CENTER, 30);
	m_listQueryDetail.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 80);
	m_listQueryDetail.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 50);
	m_listQueryDetail.InsertColumn(3, _T("民族"), LVCFMT_CENTER, 100);
	m_listQueryDetail.InsertColumn(4, _T("现任职务"), LVCFMT_CENTER, 220);
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
	m_listQuerySummary.InsertColumn(1, _T("职级"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("人数"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("比例"), LVCFMT_CENTER, 60);

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
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

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
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

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
	m_listQuerySummary.InsertColumn(1, _T("年龄段"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("人数"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("比例"), LVCFMT_CENTER, 60);
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
	m_listQuerySummary.InsertColumn(1, _T("学位"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("人数"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("比例"), LVCFMT_CENTER, 60);
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
	m_listQuerySummary.InsertColumn(1, _T("政治面貌"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("人数"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("比例"), LVCFMT_CENTER, 60);

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
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

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
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段

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
	m_listQuerySummary.InsertColumn(1, _T("档案类别"), LVCFMT_CENTER, 120);
	m_listQuerySummary.InsertColumn(2, _T("人数"), LVCFMT_CENTER, 50);
	m_listQuerySummary.InsertColumn(3, _T("比例"), LVCFMT_CENTER, 60);

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


// CDlgQueryBy 消息处理程序


BOOL CDlgQueryBy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboFolder.AddString(_T(""));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select * from orgnization_folder where del_status=0";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

	char *folder_id, *folder_name;
	for (int r = 1; r <= row; r++) {
		folder_id = re[r*col + 0]; folder_name = re[r*col + 1];

		m_comboFolder.AddString(CA2W(folder_name, CP_UTF8));
	}

	help->closeDB(); delete help;

	InitQueryByList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgQueryBy::OnItemchangedListQueryType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlgQueryBy::OnClickListQueryType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//if (pNMItemActivate->uChanged == LVIF_STATE)
	{
		//if (pNMItemActivate->uNewState & LVIS_SELECTED)
		{
			//处理内容
			m_queryType = pNMItemActivate->iItem;
			DoQueryBy();
		}
	}

	*pResult = 0;
}


void CDlgQueryBy::OnClickListQuerySummary(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	int nItem = pNMItemActivate->iItem;
	if (nItem != -1) {
		m_vParam4Detail.clear();
		m_vParam4Detail.push_back(m_listQuerySummary.GetItemText(nItem, 0));
		m_vParam4Detail.push_back(m_listQuerySummary.GetItemText(nItem, 1));
		DoQueryByDetail();
	}
	*pResult = 0;
}
