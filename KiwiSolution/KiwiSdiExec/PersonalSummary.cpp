
// PersonalSummary.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalSummary.h"
#include "SQLiteHelper.h"
#include <sstream>
using namespace std;
#include "MainFrm.h"
// CPersonalSummary

IMPLEMENT_DYNCREATE(CPersonalSummary, CFormView)

CPersonalSummary::CPersonalSummary()
	: CFormView(CPersonalSummary::IDD)
	, m_strHeader(_T(""))
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 15;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 400;
	m_fontText.CreateFontIndirect(&lf);

	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);
}

CPersonalSummary::~CPersonalSummary()
{
	m_fontText.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalSummary::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_HEADER, m_strHeader);
	DDX_Text(pDX, IDC_STATICBOX1, m_strBox1);
	DDX_Control(pDX, IDC_LIST_SUMMARY_1, m_listSummary1);
	DDX_Text(pDX, IDC_STATICBOX2, m_strBox2);
	DDX_Control(pDX, IDC_LIST_SUMMARY_2, m_listSummary2);
}

BEGIN_MESSAGE_MAP(CPersonalSummary, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPersonalSummary::OnClickedButtonClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPersonalSummary ���

#ifdef _DEBUG
void CPersonalSummary::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalSummary::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalSummary ��Ϣ�������




void CPersonalSummary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//���ݲ�����������ȥ���ݿ�ȡ������Ϣ������ʾ
	m_strHeader.Format(_T("%s %s ����������"), m_strCurrentFolder, m_strCurrentFile);
	m_strBox1.Format(_T("1.�������"));
	m_strBox2.Format(_T("2.�������ӵ���"));
	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE))->SetBitmap(m_bmpClose);
	UpdateData(FALSE);

	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 700;
	CFont font1; font1.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_HEADER)->SetFont(&font1); font1.DeleteObject();

	GetDlgItem(IDC_STATICBOX1)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATICBOX2)->SetFont(&m_fontText);
	GetDlgItem(IDC_STATIC_ERROR_MSG)->SetFont(&m_fontText);

	// TODO:  �ڴ����ר�ô����/����û���
	m_listSummary1.DeleteAllItems();

	m_listSummary1.InsertColumn(0, _T("�Ա�"), LVCFMT_CENTER, 40);
	m_listSummary1.InsertColumn(1, _T("����״̬"), LVCFMT_CENTER, 60);
	m_listSummary1.InsertColumn(2, _T("����"), LVCFMT_CENTER, 40);
	m_listSummary1.InsertColumn(3, _T("����"), LVCFMT_CENTER, 100);
	m_listSummary1.InsertColumn(4, _T("ѧ��"), LVCFMT_CENTER, 100);
	m_listSummary1.InsertColumn(5, _T("������ò"), LVCFMT_CENTER, 100);
	m_listSummary1.InsertColumn(6, _T("��λ"), LVCFMT_CENTER, 200);
	m_listSummary1.InsertColumn(7, _T("ְ������ְʱ��"), LVCFMT_CENTER, 200);
	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));
	
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row �ǲ�������м�¼,col��ÿ����¼���ٸ��ֶ�
	int file_id = atoi(re[1 * col + 0]);
	ss.str("");
	
	ss << "select file_gender,file_birth_date,file_birth_place," << 
		"file_full_educate_degree,file_part_educate_degree," << 
		"file_party, file_work_unit, file_current_position from file_form_01 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);

	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		GetDlgItem(IDC_STATIC_ERROR_MSG)->ShowWindow(SW_SHOW);
		return;
	}

	int iItem = 0;
	char *file_state, *file_IDCard, *file_birthday, *file_age, *file_NativePlace, *file_EducationBackground, *file_PoliticalStatus, *file_rank, *file_UnitsAndDuties;

	file_state = re[col + 1]; file_IDCard = re[col + 2]; file_birthday = re[col + 3]; file_age = re[col + 4]; file_NativePlace = re[col + 5]; file_EducationBackground = re[col + 6]; file_PoliticalStatus = re[col + 7]; file_rank = re[col + 8]; file_UnitsAndDuties = re[col + 9];
	m_listSummary1.InsertItem(iItem, CA2W(re[1*col+0], CP_UTF8));

	//m_listSummary1.SetItem(iItem, 1, LVIF_TEXT, CA2W(file_IDCard, CP_UTF8), 0, NULL, NULL, NULL);
	//m_listSummary1.SetItem(iItem, 2, LVIF_TEXT, CA2W(file_birthday, CP_UTF8), 0, NULL, NULL, NULL);

	m_listSummary1.SetItem(iItem, 3, LVIF_TEXT, CA2W(re[1 * col + 2], CP_UTF8), 0, NULL, NULL, NULL);

	//m_listSummary1.SetItem(iItem, 4, LVIF_TEXT, CA2W(re[1 * col + 4], CP_UTF8), 0, NULL, NULL, NULL);

	m_listSummary1.SetItem(iItem, 5, LVIF_TEXT, CA2W(re[1 * col + 5], CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 6, LVIF_TEXT, CA2W(re[1 * col + 6], CP_UTF8), 0, NULL, NULL, NULL);
	m_listSummary1.SetItem(iItem, 7, LVIF_TEXT, CA2W(re[1 * col + 7], CP_UTF8), 0, NULL, NULL, NULL);



	help->closeDB();
	delete help;

	m_listSummary1.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT | LVS_EX_FULLROWSELECT);
	m_listSummary1.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

	//	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE


	//��2
	m_listSummary2.InsertColumn(0, _T("����"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(1, _T("��������"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(2, _T("��ע"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(3, _T("��������"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(4, _T("����޸�����"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(5, _T("�ϱ�����"), LVCFMT_LEFT, 100);
	m_listSummary2.InsertColumn(6, _T("����"), LVCFMT_LEFT, 100);

	//m_listCtrl01.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	/*	m_listSummary2.InsertItem(0, _T("��ְ"));
	m_listSummary2.SetItemText(0, 1, _T("123456789012345678"));
	m_listSummary2.SetItemText(0, 2, _T("7980.12"));
	m_listSummary2.SetItemText(0, 3, _T("-5877"));
	m_listSummary2.SetItemText(0, 4, _T(" "));
	m_listSummary2.SetItemText(0, 5, _T("˶ʿ�о���"));
	m_listSummary2.SetItemText(0, 6, _T("�й���Ա"));
	m_listSummary2.SetItemText(0, 7, _T("��Ƽ���ְ"));
	m_listSummary2.SetItemText(0, 8, _T(" "));
	*/
	//	m_listSummary1.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	m_listSummary2.ModifyExtendedStyle(LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

}



void CPersonalSummary::OnClickedButtonClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
}


HBRUSH CPersonalSummary::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ERROR_MSG)
		pDC->SetTextColor(RGB(255, 0, 0));//�޸��������ɫ

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
