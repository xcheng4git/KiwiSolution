// PersonalForm26.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm26.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

#include "dlgshowattachment.h"

// CPersonalForm26

IMPLEMENT_DYNCREATE(CPersonalForm26, CFormView)

CPersonalForm26::CPersonalForm26()
	: CFormView(CPersonalForm26::IDD)
{
	UINT attachmentIcons[] =
	{
		IDI_ICON_EXT_JPEG,
		IDI_ICON_EXT_BMP,
		IDI_ICON_EXT_PDF,
		IDI_ICON_EXT_DOC,
		IDI_ICON_EXT_ZIP,
		IDI_ICON_EXT_XLS,
		IDI_ICON_EXT_NO
	};
	m_ilIcons.Create(48, 48, ILC_MASK | ILC_COLOR32, 1, 1);
	for (int i = 0; i < _countof(attachmentIcons); i++) {
		HICON hIcon = AfxGetApp()->LoadIcon(attachmentIcons[i]);
		ASSERT(hIcon);
		m_ilIcons.Add(hIcon);
	}
	m_nAttachCount = 0;

	m_FormID = 26;
	int parameters1[1][8] = { { IDC_EDIT1, IDC_EDIT12, IDC_DATETIMEPICKER1, IDC_EDIT344, IDC_EDIT13, IDC_EDIT368, IDC_EDIT345, 0 } };
	int structure1[10] = { 1, 8, EDITBX, EDITBX, DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX, ATTACHMENTBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 8; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 10; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[9] = { _T("有无"), _T("姓名"), _T("工作单位及职务"), _T("通报曝光时间"), _T("通报曝光载体"), _T("主要问题典型"), _T("四种形态"), _T("通报曝光典型"), _T("附件") };
	int structure10[9] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::ATTBOX };
	int structure11[3 + 1 + 9] = { -1, 1, 7, 2,   2, 1, 1, 1, 1, 1, 1,1,1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 9; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);


	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm26::~CPersonalForm26()
{
}

void CPersonalForm26::InsertListItem(CListCtrl &list, CString& ext, int cntAttach, int data)
{
	int nItem;
	if (ext == _T("jpeg") || ext == _T("jpg"))
		nItem = list.InsertItem(cntAttach, _T(""), 0);
	else if (ext == _T("bmp"))
		nItem = list.InsertItem(cntAttach, _T(""), 1);
	else if (ext == _T("pdf"))
		nItem = list.InsertItem(cntAttach, _T(""), 2);
	else if (ext == _T("doc") || ext == _T("docx"))
		nItem = list.InsertItem(cntAttach, _T(""), 3);
	else if (ext == _T("zip"))
		nItem = list.InsertItem(cntAttach, _T(""), 4);
	else
		nItem = list.InsertItem(cntAttach, _T(""), 6);

	list.SetItemData(nItem, (DWORD)data);
}

void CPersonalForm26::ShowAttachment()
{
	stringstream ss;
	ss << "select attachment_recid, attachment_path from file_form_attachment where form_recid=";
	ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row >= 1) {
		m_nAttachCount = 0;
		for (int r = 0; r < row; r++) {
			CString strPath; strPath.Format(_T("%s"), CA2W(re[(r + 1) * col + 1]));

			int Which = strPath.ReverseFind('.');
			CString ext = strPath.Right(strPath.GetLength() - Which - 1); ext.MakeLower();
			InsertListItem(m_listAttachments, ext, m_nAttachCount, m_nAttachCount);

			m_vAttachment.push_back(Attachment(CString(CA2W(re[(r + 1) * col + 0])), strPath, 1));
			m_nAttachCount++;
		}
	}
	help->closeDB(); delete help;
}

void CPersonalForm26::SaveAttachment(CString form_recid)
{
	if (m_vAttachment.size() < 1)
		return;
	
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);


	vector<Attachment>::iterator itAttachment = m_vAttachment.begin();
	while (itAttachment != m_vAttachment.end()) {
		if (itAttachment->status == 0) {
			ss.str(""); ss.clear();
			ss << "insert into file_form_attachment values (" << file_id << ",";
			ss << m_FormID << ",";
			ss << "'" << CW2A(form_recid.GetBuffer(), CP_UTF8) << "'" << ",";
			CString attachId = CUtility::GetGuid();
			ss << "'" << CW2A(attachId.GetBuffer(), CP_UTF8) << "',";
			ss << 1 << ",";
			ss << "'" << CW2A(itAttachment->path.GetBuffer(), CP_UTF8) << "',";
			ss << "date(), date());";
		}
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
		itAttachment->status = 1;

		itAttachment++;
	}

	help->closeDB(); delete help;
}

void CPersonalForm26::UpdateAttachment()
{
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);


	vector<Attachment>::iterator itAttachment = m_vAttachment.begin();
	while (itAttachment != m_vAttachment.end()) {
		if (itAttachment->status == 0) {

			ss.str(""); ss.clear();
			ss << "insert into file_form_attachment values (" << file_id << ",";
			ss  << m_FormID << ",";
			ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "'" << "," ;
			CString attachId = CUtility::GetGuid();
			ss << "'" << CW2A(attachId.GetBuffer(), CP_UTF8) << "',";
			ss << 1 << ",";
			ss << "'" << CW2A(itAttachment->path.GetBuffer(), CP_UTF8) << "',";
			ss << "date(), date());";
			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());
			itAttachment->status = 1;

			itAttachment++;  continue;
		}
		else if (itAttachment->status == -1) {
			ss.str(""); ss.clear();
			ss << "delete from file_form_attachment where attachment_recid=";
			ss << "'" << CW2A(itAttachment->recid.GetBuffer(), CP_UTF8) << "';";
			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());

			itAttachment = m_vAttachment.erase(itAttachment); continue;
		}

		itAttachment++;
		
	}

	help->closeDB(); delete help;
}

void CPersonalForm26::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editImagePath);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT, m_listAttachments);
}

BEGIN_MESSAGE_MAP(CPersonalForm26, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm26::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm26::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm26::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm26::OnBnClickedCmdUpdateForm)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IMAGE, &CPersonalForm26::OnBnClickedButtonAddImage)
//	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CPersonalForm26::OnHdnItemdblclickListAttachment)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ATTACHMENT, &CPersonalForm26::OnNMDblclkListAttachment)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm26::OnBnClickedCmdNextForm)
	ON_BN_CLICKED(IDC_CHK_BEING_FOUR_TYPE, &CPersonalForm26::OnBnClickedChkBeingFourType)
	ON_CBN_SETFOCUS(IDC_COMBO3, &CPersonalForm26::OnCbnSetfocusCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &CPersonalForm26::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPersonalForm26 诊断

#ifdef _DEBUG
void CPersonalForm26::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm26::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm26::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm26::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm26::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm26::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm26::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm26::hasData(int isub, int irow)
{
	CString strText;

	if ((isub == 1) || (isub == 2)){
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}


void CPersonalForm26::InitFourType()
{
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);

	pCombo1->SetWindowTextW(_T(""));
	while (pCombo1->GetCount()) pCombo1->DeleteString(0);
	pCombo2->SetWindowTextW(_T(""));
	while (pCombo2->GetCount()) pCombo2->DeleteString(0);

	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	ss << "select * from four_punish_category where first_category=-1";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
	//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

	int nIndx = pCombo1->AddString(_T("")); pCombo1->SetItemData(nIndx, (DWORD)-1);
	for (int r = 1; r <= row; r++) {
		nIndx = pCombo1->AddString(CA2W(re[r*col + 2], CP_UTF8));
		pCombo1->SetItemData(nIndx, (DWORD)atoi(re[r*col + 0]));
	}
}

// CPersonalForm26 消息处理程序


void CPersonalForm26::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][7] = m_nAttachCount; break;

		itVVVparameter++;
	}

	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);
	if (pCombo2->IsWindowVisible()) {
		int nIndx = pCombo2->GetCurSel();
		if (nIndx == -1) {
			MessageBox(_T("请确认四种形态是否选择正确！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
			return;
		}
		CString strText;
		strText.Format(_T("%d"), pCombo2->GetItemData(nIndx));
		GetDlgItem(IDC_EDIT368)->SetWindowTextW(strText);
	}

	CString form_recid = DoSaveForm();

	SaveAttachment(form_recid);

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm26::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();

	help->closeDB(); delete help;


	ss.str(""); ss.clear();
	//ss << "select * from file_invertigated_form_11 where file_id=" << file_id << " limit 0,1;";
	ss << "select file_id,form_recid,file_name,file_unit_position,being_public_date,public_media,main_problem_indeed,";
	ss << " case problem_four_xt when -1 then '"<<CW2A(_T("否"), CP_UTF8) << "' else ";
	ss << " (select b.category_name || '" << CW2A(_T("——"), CP_UTF8) << "' || a.category_name from four_punish_category as a inner join four_punish_category as b";
	ss << " on a.[first_category] = b.punish_id and a.punish_id=problem_four_xt) ";
	ss << " end as punish_category_name, public_problem_content,public_attachment ";
	ss << " from file_invertigated_form_11 where file_id = " << file_id << " limit 0, 1; ";
	_vSubformQueryString.push_back(ss.str());

	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表11.dotx")));
}


void CPersonalForm26::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}

void CPersonalForm26::OnBnClickedCmdUpdateForm()
{
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][7] = m_nAttachCount; break;

		itVVVparameter++;
	}

	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);
	if (pCombo2->IsWindowVisible()) {
		int nIndx = pCombo2->GetCurSel();
		if (nIndx == -1) {
			MessageBox(_T("请确认四种形态是否选择正确！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
			return;
		}
		CString strText;
		strText.Format(_T("%d"), pCombo2->GetItemData(nIndx));
		GetDlgItem(IDC_EDIT368)->SetWindowTextW(strText);
	}

	DoUpdateForm();

	UpdateAttachment();
}


void CPersonalForm26::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);
	//////////////////////////////////////////////////////////////////////////
	m_editImagePath.Initialize(this, BES_XTP_CHOOSEFILE);
	m_listAttachments.SetImageList(&m_ilIcons, LVSIL_NORMAL);


	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	int i = 0;
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		while (itVVparameter != itVVVparameter->end()) {
			int j = 0;

			vector<int>::iterator itV = itVVparameter->begin();
			while (itV != itVVparameter->end()) {
				if ((_vvSubformStructure[i][2 + j] != RADIOBTN) && (_vvSubformStructure[i][2 + j] != ATTACHMENTBX)) {
					GetDlgItem(*itV)->SetFont(&m_fontEdit);
				}

				itV++; j++;
			}
			itVVparameter++;
		}
		itVVVparameter++; i++;
	}

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM3))->SetBitmap(m_bmpClose);
	DoShowForm();

	BOOL hasData = FALSE;
	vector<int>::iterator itHas = _vHaveDataSubform.begin();
	while (itHas != _vHaveDataSubform.end()) {
		if (*itHas != -1) {
			hasData = TRUE; break;
		}
		itHas++;
	}
	if (hasData) {
		//显示附件
		ShowAttachment();

		CString strText;
		GetDlgItem(IDC_EDIT368)->GetWindowTextW(strText); strText.Trim();
		if (!strText.IsEmpty()) {
			if (strText == _T("-1")) {
				((CButton*)GetDlgItem(IDC_CHK_BEING_FOUR_TYPE))->SetCheck(TRUE);
				OnBnClickedChkBeingFourType();
			}
			else {
				stringstream ss;
				ss << "select b.[punish_id],a.[category_name] as first_category,b.[category_name] as second_category from four_punish_category as a left join four_punish_category as b on b.first_category=a.punish_id where b.first_category<>-1 and b.[punish_id]=";
				ss << CW2A(strText.GetBuffer(), CP_UTF8) << ";";
				TRACE(_T("\n%s"), CA2W(ss.str().c_str(), CP_UTF8));

				CSQLiteHelper *help = new CSQLiteHelper();
				help->openDB("kiwi.db3");
				int row, col;
				char *eee = "i"; char **result = &eee;
				char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
				if (row >= 1) {
					strText.ReleaseBuffer();
					strText.Format(_T("%s-%s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8),
						strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
					GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->SetWindowText(strText);
				}
			}
		}

		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}
	else {
		stringstream ss;
		ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
			CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		int row, col;
		char *eee = "i"; char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		int file_id = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select file_name, file_WorkUnit, file_CurrentPosition from file_form_02 where file_id=" << file_id << ";";
		TRACE(CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			GetDlgItem(IDC_EDIT1)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
			CString strText; strText.Format(_T("%s %s"), strlen(re[1 * col + 1]) < 1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8), strlen(re[1 * col + 2]) < 1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
			GetDlgItem(IDC_EDIT12)->SetWindowTextW(strText.GetBuffer());
		}
		help->closeDB(); delete help;

		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

		InitFourType();
	}


}


void CPersonalForm26::OnBnClickedButtonAddImage()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPath;
	m_editImagePath.GetWindowTextW(strPath);
	strPath.Trim();
	if (!strPath.IsEmpty()) {
		if (PathFileExists(strPath)) {
			int Which = strPath.ReverseFind('.');
			CString ext = strPath.Right(strPath.GetLength() - Which - 1); ext.MakeLower();
			CString strKiwiPath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".") + ext;

			if (CopyFile(strPath, strKiwiPath, FALSE)) {
				InsertListItem(m_listAttachments, ext, m_nAttachCount, -1);
				m_vAttachment.push_back(Attachment(_T(""), strKiwiPath)); m_nAttachCount++;
			}
		}
	}

}


//void CPersonalForm26::OnHdnItemdblclickListAttachment(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO:  在此添加控件通知处理程序代码
//
//	*pResult = 0;
//}


void CPersonalForm26::OnNMDblclkListAttachment(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (-1 == pNMItemActivate->iItem)
		return;

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	help->closeDB(); delete help;
	
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();
	CString str; str.Format(_T("%d:表11"), file_id);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_FORM_ATTACHMENT, WPARAM(new CString(str)),LPARAM(&(m_vAttachment[pNMItemActivate->iItem].path)));


	*pResult = 0;
}


void CPersonalForm26::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(27), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}


void CPersonalForm26::OnBnClickedChkBeingFourType()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHK_BEING_FOUR_TYPE))->GetCheck()){
		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT368)->SetWindowTextW(_T("-1"));
	}
	else {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}


void CPersonalForm26::OnCbnSetfocusCombo3()
{
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox* pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO3);

	pCombo2->SetWindowTextW(_T(""));
	while (pCombo2->GetCount()) pCombo2->DeleteString(0);

	int nItem = pCombo1->GetCurSel();
	if (nItem != -1) {
		stringstream ss;
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");

		ss << "select * from four_punish_category where first_category=" << pCombo1->GetItemData(nItem) << ";";
		int row, col;
		char *eee = "i";
		char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段
		//char *lr = re[(1)*col + 1]; //re[(1)*col+1] --> re是指向数组的指针。(1)为第1行，1表示第1列,从0计数,第0行是字段名。*/

		for (int r = 1; r <= row; r++) {
			int nIndx = pCombo2->AddString(CA2W(re[r*col + 2], CP_UTF8));
			pCombo2->SetItemData(nIndx, (DWORD)atoi(re[r*col + 0]));
		}
	}

}


void CPersonalForm26::OnBnClickedButton1()
{
	GetDlgItem(IDC_EDIT_FOUR_XT_SHOW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

	InitFourType();
}
