// PersonalForm25.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm25.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"


// CPersonalForm25

IMPLEMENT_DYNCREATE(CPersonalForm25, CFormView)

CPersonalForm25::CPersonalForm25()
	: CFormView(CPersonalForm25::IDD)
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
	m_nCheckAttachCount = 0;
	m_nRegisterAttachCount = 0;

	m_FormID = 25;
	int parameters1[1][10] = { { IDC_EDIT1, IDC_EDIT12, IDC_DATETIMEPICKER1, IDC_EDIT13, IDC_EDIT370, IDC_DATETIMEPICKER45, IDC_EDIT347, IDC_EDIT344, 0, 0 } };
	int structure1[12] = { 1, 10, EDITBX, EDITBX, DATEPKR, EDITBX, EDITBX, DATEPKR, EDITBX, EDITBX, ATTACHMENTBX, ATTACHMENTBX };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 1; i++) {
		vector<int> vPara;
		for (int j = 0; j < 10; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 12; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); 

	vStr.clear(); vStr.push_back(0); vStr.push_back(1); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[11] = { _T("有无"), _T("姓名"), _T("工作单位及职务"), _T("初核时间"), _T("初核结论"), _T("适当处理"), _T("立案时间"), _T("立案结论"), _T("适当处理"), _T("初核附件"), _T("立案附件") };
	int structure10[11] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::ATTBOX, CBookmarkEx::ATTBOX };
	int structure11[3 + 1 + 10] = { -1, 1, 10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 11; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);


	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm25::~CPersonalForm25()
{
}

void CPersonalForm25::InsertListItem(CListCtrl &list, CString& ext, int cntAttach, int data)
{
	int nItem;
	if (ext == _T("jpeg") || ext == _T("jpg"))
		nItem = list.InsertItem(cntAttach, _T(""), 0);
	else if (ext == _T("bmp"))
		nItem = list.InsertItem(cntAttach, _T(""), 1);
	else if (ext == _T("pdf"))
		nItem = list.InsertItem(cntAttach, _T(""), 2);
	else if (ext == _T("doc"))
		nItem = list.InsertItem(cntAttach, _T(""), 3);
	else if (ext == _T("zip"))
		nItem = list.InsertItem(cntAttach, _T(""), 4);
	else
		nItem = list.InsertItem(cntAttach, _T(""), 6);

	list.SetItemData(nItem, (DWORD)data);
}

void CPersonalForm25::ShowAttachment()
{
	stringstream ss;
	ss << "select attachment_recid, which_attachment, attachment_path from file_form_attachment where form_recid=";
	ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row >= 1) {
		m_nCheckAttachCount = 0;
		m_nRegisterAttachCount = 0;
		for (int r = 0; r < row; r++) {
			CString strPath; strPath.Format(_T("%s"), CA2W(re[(r + 1) * col + 2]));
			CString ext = strPath.Right(strPath.GetLength() - strPath.ReverseFind('.') - 1); ext.MakeLower();

			int nWhich = atoi(re[(r + 1)*col + 1]);
			if (nWhich == 1) {
				InsertListItem(m_listCheckImages, ext, m_nCheckAttachCount, m_nCheckAttachCount);
				m_vCheckAttachment.push_back(Attachment(CString(CA2W(re[(r + 1) * col + 0])), strPath, 1));
				m_nCheckAttachCount++;
			} 
			else {
				InsertListItem(m_listRegisterImages, ext, m_nRegisterAttachCount, m_nRegisterAttachCount);
				m_vRegisterAttachment.push_back(Attachment(CString(CA2W(re[(r + 1) * col + 0])), strPath, 1));
				m_nRegisterAttachCount++;
			}
		}
	}
	help->closeDB(); delete help;
}

void CPersonalForm25::SaveAttachment(CString form_recid)
{
	if (m_vCheckAttachment.size() < 1 && m_vRegisterAttachment.size() < 1)
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


	vector<Attachment>::iterator itAttachment = m_vCheckAttachment.begin();
	while (itAttachment != m_vCheckAttachment.end()) {
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
	////
	itAttachment = m_vRegisterAttachment.begin();
	while (itAttachment != m_vRegisterAttachment.end()) {
		if (itAttachment->status == 0) {
			ss.str(""); ss.clear();
			ss << "insert into file_form_attachment values (" << file_id << ",";
			ss << m_FormID << ",";
			ss << "'" << CW2A(form_recid.GetBuffer(), CP_UTF8) << "'" << ",";
			CString attachId = CUtility::GetGuid();
			ss << "'" << CW2A(attachId.GetBuffer(), CP_UTF8) << "',";
			ss << 2 << ",";
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

void CPersonalForm25::UpdateAttachment()
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


	vector<Attachment>::iterator itAttachment = m_vCheckAttachment.begin();
	while (itAttachment != m_vCheckAttachment.end()) {
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

			itAttachment = m_vCheckAttachment.erase(itAttachment); continue;
		}
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
		itAttachment->status = 1;

		itAttachment++;
	}
	////
	itAttachment = m_vRegisterAttachment.begin();
	while (itAttachment != m_vRegisterAttachment.end()) {
		if (itAttachment->status == 0) {
			ss.str(""); ss.clear();
			ss << "insert into file_form_attachment values (" << file_id << ",";
			ss << m_FormID << ",";
			ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "'" << ",";
			CString attachId = CUtility::GetGuid();
			ss << "'" << CW2A(attachId.GetBuffer(), CP_UTF8) << "',";
			ss << 2 << ",";
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

			itAttachment = m_vRegisterAttachment.erase(itAttachment); continue;
		}
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
		itAttachment->status = 1;

		itAttachment++;
	}

	help->closeDB(); delete help;
}

void CPersonalForm25::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT348, m_editCheckPath);
	DDX_Control(pDX, IDC_EDIT2, m_editRegisterPath);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT2, m_listCheckImages);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT, m_listRegisterImages);
}

BEGIN_MESSAGE_MAP(CPersonalForm25, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm25::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm25::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm25::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm25::OnBnClickedCmdUpdateForm)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IMAGE2, &CPersonalForm25::OnBnClickedButtonAddCheckImage)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IMAGE, &CPersonalForm25::OnBnClickedButtonAddRegisterImage)
END_MESSAGE_MAP()


// CPersonalForm25 诊断

#ifdef _DEBUG
void CPersonalForm25::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm25::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm25::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm25::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm25::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm25::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm25::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm25::hasData(int isub, int irow)
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
// CPersonalForm25 消息处理程序


void CPersonalForm25::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][8] = m_nCheckAttachCount; 
		itVVparameter[0][9] = m_nRegisterAttachCount;
		break;

		itVVVparameter++;
	}

	CString form_recid = DoSaveForm();

	SaveAttachment(form_recid);

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm25::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_invertigated_form_10 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());

	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表10.dotx")));
}


void CPersonalForm25::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}

void CPersonalForm25::OnBnClickedCmdUpdateForm()
{
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][8] = m_nCheckAttachCount;
		itVVparameter[0][9] = m_nRegisterAttachCount;
		break;

		itVVVparameter++;
	}

	DoUpdateForm();

	UpdateAttachment();
}


void CPersonalForm25::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);
	m_editCheckPath.Initialize(this, BES_XTP_CHOOSEFILE);
	m_listCheckImages.SetImageList(&m_ilIcons, LVSIL_NORMAL);
	m_editRegisterPath.Initialize(this, BES_XTP_CHOOSEFILE);
	m_listRegisterImages.SetImageList(&m_ilIcons, LVSIL_NORMAL);

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	int i = 0;
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		while (itVVparameter != itVVVparameter->end()) {
			int j = 0;

			vector<int>::iterator itV = itVVparameter->begin();
			while (itV != itVVparameter->end()) {
				if (_vvSubformStructure[i][2 + j] != ATTACHMENTBX) {
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
		ShowAttachment();

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
			CString strText; strText.Format(_T("%s %s"), strlen(re[1 * col + 1])<1 ? _T("") : CA2W(re[1 * col + 1], CP_UTF8), strlen(re[1 * col + 2])<1 ? _T("") : CA2W(re[1 * col + 2], CP_UTF8));
			GetDlgItem(IDC_EDIT12)->SetWindowTextW(strText.GetBuffer());
		}

		help->closeDB(); delete help;
	}

}


void CPersonalForm25::OnBnClickedButtonAddCheckImage()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPath;
	m_editCheckPath.GetWindowTextW(strPath);
	strPath.Trim();
	if (!strPath.IsEmpty()) {
		int Which = strPath.ReverseFind('.');
		CString ext = strPath.Right(strPath.GetLength() - Which - 1); ext.MakeLower();
		CString strKiwiPath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".") + ext;

		if (CopyFile(strPath, strKiwiPath, FALSE)) {

			InsertListItem(m_listCheckImages, ext, m_nCheckAttachCount,-1);

			m_vCheckAttachment.push_back(Attachment(_T(""), strKiwiPath)); m_nCheckAttachCount++;
		}
	}
}


void CPersonalForm25::OnBnClickedButtonAddRegisterImage()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPath;
	m_editRegisterPath.GetWindowTextW(strPath);
	strPath.Trim();
	if (!strPath.IsEmpty()) {
		int Which = strPath.ReverseFind('.');
		CString ext = strPath.Right(strPath.GetLength() - Which - 1); ext.MakeLower();
		CString strKiwiPath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".") + ext;

		if (CopyFile(strPath, strKiwiPath, FALSE)) {

			InsertListItem(m_listRegisterImages, ext, m_nRegisterAttachCount,-1);

			m_vRegisterAttachment.push_back(Attachment(_T(""), strKiwiPath)); m_nRegisterAttachCount++;
		}
	}
}
