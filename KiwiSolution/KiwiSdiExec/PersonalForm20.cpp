// PersonalForm20.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm20.h"
#include "resource.h"

#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm20

IMPLEMENT_DYNCREATE(CPersonalForm20, CFormView)

CPersonalForm20::CPersonalForm20()
: CFormView(CPersonalForm20::IDD)
{
	_strReportImagePath = _T("");

	m_FormID = 20;
	int parameters1[1][3] = { { IDC_EDIT237, IDC_EDIT58,0 } };
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

	//������Ϊ�˴�ӡ��Ԥ��
	const wchar_t *pBookmarks1[4] = { _T("����"), _T("���"), _T("��������"), _T("�������챨��") };
	int structure10[4] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::PICBOX };
	int structure11[4 + 3] = { -1, 1, 3, 2,   1, 1, 1};  //���ޣ��У��У�������ѯ����ֶ�����ÿ����Ԫ���ڵı�ǩ��Ŀ....

	vector<CBookmarkEx> vBke;//ѭ��������һ��
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

CPersonalForm20::~CPersonalForm20()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm20::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


void CPersonalForm20::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HEALTH_REPORT, m_reportImage);
	DDX_Control(pDX, IDC_EDIT1, m_editReportImage);
}

BEGIN_MESSAGE_MAP(CPersonalForm20, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm20::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm20::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm20::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm20::OnBnClickedCmdUpdateForm)
	ON_EN_CHANGE(IDC_EDIT1, &CPersonalForm20::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CPersonalForm20 ���

#ifdef _DEBUG
void CPersonalForm20::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm20::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm20::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm20::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm20::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm20::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm20::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm20::hasData(int isub, int irow)
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
// CPersonalForm20 ��Ϣ�������


void CPersonalForm20::OnBnClickedCmdSaveForm()
{
	UpdateData();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	ss << "insert into file_form_26 values(" << file_id << ",";

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

	//������챨�浥ͼƬ
	if (!_strReportImagePath.IsEmpty()){
		if (PathFileExists(_strReportImagePath)) {
			CImage  image;
			image.Load(_strReportImagePath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ� 
			_strReportImagePath.ReleaseBuffer();
			_strReportImagePath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".jpg");
			image.Save(_strReportImagePath.GetBuffer());

			stringstream ss;
			ss << "update file_form_26 set file_ReportPic= ";
			ss << "'" << CW2A(_strReportImagePath.GetBuffer(), CP_UTF8) << "' where form_recid= ";
			ss << "'" << CW2A(form_recid.GetBuffer(), CP_UTF8) << "';";
			CSQLiteHelper *help = new CSQLiteHelper();
			help->openDB("kiwi.db3");
			help->execSQL(ss.str().c_str());
			ss.str("");
			help->closeDB(); delete help;
		}
	}


	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm20::OnBnClickedCmdPrintForm()
{

	


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	ss << "select * from file_form_26 where file_id=" << file_id << " limit 0,1;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("��5.dotx")));

	
	/*
	ss << "select file_ReportPic from file_form_26 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		AfxMessageBox(_T("û�д����ݿ������ " + m_strCurrentFolder + m_strCurrentFile + " ������"));
		return;
	}
	_strReportImagePath = re[1 * col + 0];
	

	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\��5.dotx")); //dot(_T("template1.dot")); // 

	CApplication wordApp;
	CDocuments docs;
	CDocument0 docx;
	CBookmarks bookmarks;
	CBookmark0 bookmark;
	CRange range;
	CCell cell;

	if (!wordApp.CreateDispatch(_T("Word.Application"))) {
		AfxMessageBox(_T("no word product."));
		return;
	}	
	
	//����ͼƬ
	bookmark = bookmarks.Item(&_variant_t(_T("�������챨��")));
	range = bookmark.get_Range();
	CnlineShapes shape = docx.get_InlineShapes();
	//shape.AddPicture(_T("C:\\Projects\\Kiwi.Git\\KiwiSolution\\KiwiSdiExec\\a.jpg"), covFalse, covTrue, &_variant_t(range));
	shape.AddPicture(_strReportImagePath.GetBuffer(), covFalse, covTrue, &_variant_t(range));
	

	
	help->closeDB(); delete help;
	*/
}


void CPersonalForm20::OnBnClickedButtonCloseForm3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm20::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	GetDlgItem(IDC_EDIT237)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EDIT58)->SetFont(&m_fontEdit);
	m_editReportImage.Initialize(this, BES_XTP_CHOOSEFILE);

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
	ss.str("");

	GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 0], CP_UTF8));
	ss << "select * from file_form_26 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);

	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}


	//GetDlgItem(IDC_EDIT58)->SetWindowTextW(_T("hllo world"));
	GetDlgItem(IDC_EDIT237)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
	GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
	ss.str(""); ss.clear();
	help->closeDB();
	delete help;
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
		//��ʾͼƬ
		stringstream ss;
		ss << "select file_ReportPic from file_form_26 where form_recid=";
		ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		int row, col;
		char *eee = "i"; char **result = &eee;
		char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			_strReportImagePath.ReleaseBuffer();
			_strReportImagePath.Format(_T("%s"), strlen(re[1 * col + 0])>1 ? CA2W(re[1 * col + 0], CP_UTF8) : _T(""));

			if (!_strReportImagePath.IsEmpty() && _strReportImagePath != _T("(null)")) {
				if (false == (bool)PathFileExists(_strReportImagePath.GetBuffer())) 
					_strReportImagePath.Empty();
			}
			else
				_strReportImagePath.Empty();



			UpdateWindow();
		}
		help->closeDB(); delete help;
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
		
	}

#if 0
	//��ʾͼƬ
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
	ss.str("");

	ss << "select file_ReportPic from file_form_26 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);

	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB(); delete help;
		return;
	}
	_strReportImagePath.Format(_T("%s"), CA2W(re[1 * col + 0], CP_UTF8));
	if (!_strReportImagePath.IsEmpty() && _strReportImagePath != _T("(null)")) {
		if (true == (bool)PathFileExists(_strReportImagePath.GetBuffer())) {
			CImage  image;
			image.Load(_strReportImagePath);
			CRect   rect; m_reportImage.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
			CDC *pDc = m_reportImage.GetDC();//��ȡpicture��DC  
			image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
			ReleaseDC(pDc);
		}
		else
			_strReportImagePath.Empty();
	}
	else
		_strReportImagePath.Empty();

	help->closeDB(); delete help;
#endif

}


void CPersonalForm20::OnBnClickedCmdUpdateForm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoUpdateForm();

	//����ͼƬ��ַ
	if (!_strReportImagePath.IsEmpty()) {
		if (PathFileExists(_strReportImagePath)) {
			CImage  image;
			image.Load(_strReportImagePath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ� 
			_strReportImagePath.ReleaseBuffer();
			_strReportImagePath = CUtility::GetModuleDirectory() + _T("\\attachment\\") + CUtility::GetGuid() + _T(".jpg");
			image.Save(_strReportImagePath.GetBuffer());

			stringstream ss;
			ss << "update file_form_26 set file_ReportPic= ";
			ss << "'" << CW2A(_strReportImagePath.GetBuffer(), CP_UTF8) << "' where form_recid= ";
			ss << "'" << CW2A(_vvSubformRecid[0][0].GetBuffer(), CP_UTF8) << "';";
			CSQLiteHelper *help = new CSQLiteHelper();
			help->openDB("kiwi.db3");
			help->execSQL(ss.str().c_str());
			ss.str("");
			help->closeDB(); delete help;
		}
	}
}

void CPersonalForm20::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д __super::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	m_editReportImage.GetWindowTextW(_strReportImagePath);
	_strReportImagePath.Trim();
	if (!_strReportImagePath.IsEmpty()) {
		if (PathFileExists(_strReportImagePath)) {
			CImage  image;
			image.Load(_strReportImagePath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
			CRect   rect; m_reportImage.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
			CDC *pDc = m_reportImage.GetDC();//��ȡpicture��DC  
			image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
			ReleaseDC(pDc);
		}
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CPersonalForm20::OnDraw(CDC* /*pDC*/)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (!_strReportImagePath.IsEmpty()) {
		if (PathFileExists(_strReportImagePath)) {
			CImage  image;
			image.Load(_strReportImagePath); //��ͼ�񱣴浽�ض�Ŀ¼,Ȼ��·�������ݿ�
			CRect   rect; m_reportImage.GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
			CDC *pDc = m_reportImage.GetDC();//��ȡpicture��DC  
			image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
			ReleaseDC(pDc);
		}
	}
}


