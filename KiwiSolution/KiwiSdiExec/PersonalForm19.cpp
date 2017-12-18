// PersonalForm19.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm19.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm19

IMPLEMENT_DYNCREATE(CPersonalForm19, CFormView)

CPersonalForm19::CPersonalForm19()
: CFormView(CPersonalForm19::IDD)
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

	m_FormID = 19;
	int parameters1[1][3] = { { IDC_EDIT237,IDC_EDIT58,0 } };
	int structure1[5] = { 1, 3, EDITBX, EDITBX, ATTACHMENTBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 3; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 5; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[4] = { _T("有无"), _T("年度"), _T("报告内容"), _T("附件") };
	int structure10[4] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::ATTBOX };
	int structure11[4 + 3] = { -1, 1, 3, 2, 1, 1, 1 };  //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....

	vector<CBookmarkEx> vBke;//循环次数改一下
	for (int i = 0; i < 4; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);


	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm19::~CPersonalForm19()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm19::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


void CPersonalForm19::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editAttachPath);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT, m_listAttachments);
}

BEGIN_MESSAGE_MAP(CPersonalForm19, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm19::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm19::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm19::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm19::OnBnClickedCmdUpdateForm)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IMAGE, &CPersonalForm19::OnBnClickedButtonAddImage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ATTACHMENT, &CPersonalForm19::OnNMDblclkListAttachment)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm19::OnBnClickedCmdNextForm)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ATTACHMENT, &CPersonalForm19::OnBnClickedButtonDelAttachment)
END_MESSAGE_MAP()


// CPersonalForm19 诊断

#ifdef _DEBUG
void CPersonalForm19::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm19::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm19::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm19::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm19::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm19::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm19::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm19::hasData(int isub, int irow)
{
	CString strText;

	if (isub == 1) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}

void CPersonalForm19::InsertListItem(CListCtrl &list, CString& ext, int cntAttach, int data)
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

void CPersonalForm19::ShowAttachment()
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

void CPersonalForm19::SaveAttachment(CString form_recid)
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

void CPersonalForm19::UpdateAttachment()
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
			ss << m_FormID << ",";
			ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "'" << ",";
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

// CPersonalForm19 消息处理程序


void CPersonalForm19::OnBnClickedCmdSaveForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
#if 0
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

	CString strText;

	ss << "insert into file_form_25 values(" << file_id << ",";
	
	GetDlgItem(IDC_EDIT237)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	CString form_recid = DoSaveForm();

	SaveAttachment(form_recid);

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm19::OnBnClickedCmdPrintForm()
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

	ss.str("");  ss.clear();
	ss << "select * from file_form_25 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表4.dotx")));
}


void CPersonalForm19::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm19::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	m_editAttachPath.Initialize(this, BES_XTP_CHOOSEFILE);
	m_listAttachments.SetImageList(&m_ilIcons, LVSIL_NORMAL);

	GetDlgItem(IDC_EDIT237)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT58)->SetFont(&m_fontEdit);

#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;

	char *eee = "i"; char **result = &eee;//未使用

	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	//GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8)) ;

	ss.str("");

	ss << "select * from file_form_25 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	GetDlgItem(IDC_EDIT237)->SetWindowTextW(CA2W(re[1*col+1],CP_UTF8));
	GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));

	help->closeDB();
	delete help;//+++++++
#endif
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
		ShowAttachment();

		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}
}


void CPersonalForm19::OnBnClickedCmdUpdateForm()
{
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][2] = m_nAttachCount; break;

		itVVVparameter++;
	}
	
	DoUpdateForm();

	UpdateAttachment();
}


void CPersonalForm19::OnBnClickedButtonAddImage()
{
	CString strPath;
	m_editAttachPath.GetWindowTextW(strPath);
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


void CPersonalForm19::OnNMDblclkListAttachment(NMHDR *pNMHDR, LRESULT *pResult)
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
	CString str; str.Format(_T("%d:表16"), file_id);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_FORM_ATTACHMENT, WPARAM(new CString(str)), LPARAM(&(m_vAttachment[pNMItemActivate->iItem].path)));


	*pResult = 0;

}


void CPersonalForm19::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(20), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}


void CPersonalForm19::OnBnClickedButtonDelAttachment()
{
	// TODO:  在此添加控件通知处理程序代码
	int nItem = m_listAttachments.GetNextItem(-1, LVIS_SELECTED);
	if (nItem == -1) {
		MessageBox(_T("请先选择要删除的附件！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
	}
	else {
		m_listAttachments.DeleteItem(nItem);
		m_vAttachment.at(nItem).status = -1; m_nAttachCount--;
	}
}
