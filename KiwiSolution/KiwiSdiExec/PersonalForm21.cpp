// PersonalForm21.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm21.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"
#include "Utility.h"

// CPersonalForm21

IMPLEMENT_DYNCREATE(CPersonalForm21, CFormView)

CPersonalForm21::CPersonalForm21()
: CFormView(CPersonalForm21::IDD)
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

	m_FormID = 21;
	int parameters1[1][3] = { { IDC_EDIT237, IDC_EDIT58,0  } };
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

CPersonalForm21::~CPersonalForm21()
{
	//m_fontEdit.DeleteObject();

	//for (int i = 0; i < m_vFormRecid.size(); i++)
	//	CString(m_vFormRecid[i]).ReleaseBuffer();
}

//void CPersonalForm21::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


//void CPersonalForm21::SetModifyFlag(int flag)
//{
//	if (flag)
//		m_isCurrentModify = TRUE;
//}

void CPersonalForm21::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, m_editImagePath);
	//DDX_Control(pDX, IDC_STATIC_HEALTH_REPORT, m_reportImage);
	DDX_Control(pDX, IDC_EDIT2, m_editAttachPath);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT, m_listAttachments);
}

BEGIN_MESSAGE_MAP(CPersonalForm21, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm21::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm21::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm21::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm21::OnBnClickedCmdUpdateForm)
	//ON_EN_CHANGE(IDC_EDIT1, &CPersonalForm21::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IMAGE, &CPersonalForm21::OnBnClickedButtonAddImage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ATTACHMENT, &CPersonalForm21::OnNMDblclkListAttachment)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm21::OnBnClickedCmdNextForm)
END_MESSAGE_MAP()


// CPersonalForm21 诊断

#ifdef _DEBUG
void CPersonalForm21::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm21::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm21::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm21::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm21::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm21::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm21::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm21::hasData(int isub, int irow)
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

void CPersonalForm21::InsertListItem(CListCtrl &list, CString& ext, int cntAttach, int data)
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

void CPersonalForm21::ShowAttachment()
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

void CPersonalForm21::SaveAttachment(CString form_recid)
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

void CPersonalForm21::UpdateAttachment()
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

// CPersonalForm21 消息处理程序


void CPersonalForm21::OnBnClickedCmdSaveForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();

	CString strText;

	ss << "insert into file_form_27 values(" << file_id << ",";
	strText = CUtility::GetGuid();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT237)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << "21, " << "'" << CW2A(_T("表6"),CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	CString form_recid = DoSaveForm();

#if 0
	//保存盖章图片
	if (!_strReportImagePath.IsEmpty()){
		if (PathFileExists(_strReportImagePath)) {
			int Which = _strReportImagePath.ReverseFind('.');
			CString ext = _strReportImagePath.Right(_strReportImagePath.GetLength() - Which - 1); ext.MakeLower();
			CString strKiwiPath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".") + ext;

			if (CopyFile(_strReportImagePath, strKiwiPath, FALSE)) {
				stringstream ss;
				ss << "update file_form_27 set file_ReportPic= ";
				ss << "'" << CW2A(strKiwiPath.GetBuffer(), CP_UTF8) << "' where form_recid= ";
				ss << "'" << CW2A(form_recid.GetBuffer(), CP_UTF8) << "';";
				CSQLiteHelper *help = new CSQLiteHelper();
				help->openDB("kiwi.db3");
				help->execSQL(ss.str().c_str());
				ss.str("");
				help->closeDB(); delete help;
			}
		}
	}
#endif

	SaveAttachment(form_recid);

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm21::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_27 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表6.dotx")));
}


void CPersonalForm21::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm21::OnInitialUpdate()
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
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	int row, col;
	char *eee = "i"; char **result = &eee;
	char** re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	ss.str(""); ss.clear();
	ss << "select * from personal_form_info where file_id=" << file_id << " and ";
	ss << " form_serial='" << CW2A(_T("表6"), CP_UTF8) << "';";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}

	ss.str(""); ss.clear();
	ss << "select * from file_form_27 where file_id=" << file_id << " order by file_ReportYear desc limit 0,1;";

	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}
	CString str; str.Format(_T("%s"), CA2W(re[1 * col + 1], CP_UTF8));
	m_vFormRecid.push_back(str);

	GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT237)->SetWindowTextW( CA2W(re[1*col + 2], CP_UTF8) );
	GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 3], CP_UTF8));

	help->closeDB(); delete help;
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
#if 0
		//显示图片
		stringstream ss;
		ss << "select file_ReportPic from file_form_27 where form_recid=";
		ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		int row, col;
		char *eee = "i"; char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			if (NULL != re[1 * col + 0]) {
				_strReportImagePath.ReleaseBuffer();
				_strReportImagePath.Format(_T("%s"), strlen(re[1 * col + 0]) > 1 ? CA2W(re[1 * col + 0], CP_UTF8) : _T(""));

				if (!_strReportImagePath.IsEmpty() && _strReportImagePath != _T("(null)")) {
					if (!PathFileExists(_strReportImagePath))
						_strReportImagePath.Empty();
					else {
						CImage  image;
						image.Load(_strReportImagePath); //把图像保存到特定目录,然后将路径存数据库
						if (!image.IsNull()) {
							_bIsImage = TRUE;
						}
						image.Destroy();
					}

				}
				else
					_strReportImagePath.Empty();
			}
			else
				_strReportImagePath.Empty();


			UpdateWindow();
		}
		help->closeDB(); delete help;
#endif
		ShowAttachment();

		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}
}


void CPersonalForm21::OnBnClickedCmdUpdateForm()
{
	UpdateData();
	// TODO:  在此添加控件通知处理程序代码
	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();
	while (itVVVparameter != _vvvParameters.end()) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		itVVparameter[0][2] = m_nAttachCount; break;

		itVVVparameter++;
	}

#if 0
	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";
	//TRACE(CA2W(ss.str().c_str(), CP_UTF8));

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);
	ss.str(""); ss.clear();


	CString strText;
	ss << "update file_form_27 set file_ReportYear=";
	GetDlgItem(IDC_EDIT237)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
	ss << "\"file_Annual report form of social morality\"=";
	GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText); strText.Trim();
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "'"; strText.ReleaseBuffer();

	ss << " where form_recid='" << CW2A(CString(m_vFormRecid[0]).GetBuffer(), CP_UTF8) << "';";

	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

FillComplete:
	ss.str("");  ss.clear();
	ss << "update personal_form_info set modify_date=";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' "; strText.ReleaseBuffer();
	ss << " where file_id=" << file_id << " and form_serial=";
	ss << "'" << CW2A(_T("表6"), CP_UTF8) << "';";

	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoUpdateForm();

#if 0
	//更新图片地址
	if (!_strReportImagePath.IsEmpty()) {
		if (PathFileExists(_strReportImagePath)) {
			int Which = _strReportImagePath.ReverseFind('.');
			CString ext = _strReportImagePath.Right(_strReportImagePath.GetLength() - Which - 1); ext.MakeLower();
			CString strKiwiPath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".") + ext;

			if (CopyFile(_strReportImagePath, strKiwiPath, FALSE)) {
				stringstream ss;
				ss << "update file_form_27 set file_ReportPic= ";
				ss << "'" << CW2A(strKiwiPath.GetBuffer(), CP_UTF8) << "' where form_recid= ";
				ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
				CSQLiteHelper *help = new CSQLiteHelper();
				help->openDB("kiwi.db3");
				help->execSQL(ss.str().c_str());
				ss.str("");
				help->closeDB(); delete help;
			}
		}
	}
#endif

	UpdateAttachment();

}

//void CPersonalForm21::OnDraw(CDC* /*pDC*/)
//{
//	// TODO:  在此添加专用代码和/或调用基类
//	if (!_strReportImagePath.IsEmpty()) {
//		if (PathFileExists(_strReportImagePath)) {
//			if (_bIsImage) {
//				CImage  image;
//				image.Load(_strReportImagePath); //把图像保存到特定目录,然后将路径存数据库
//				CRect   rect; m_reportImage.GetClientRect(&rect);//获取句柄指向控件区域的大小  
//				CDC *pDc = m_reportImage.GetDC();//获取picture的DC  
//				image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
//				ReleaseDC(pDc);
//			}
//		}
//	}
//}

void CPersonalForm21::OnBnClickedButtonAddImage()
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


void CPersonalForm21::OnNMDblclkListAttachment(NMHDR *pNMHDR, LRESULT *pResult)
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


void CPersonalForm21::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(22), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));

}
