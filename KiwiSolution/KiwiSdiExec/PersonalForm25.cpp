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
	int structure10[11] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
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

void CPersonalForm25::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editCheckImage);
	DDX_Control(pDX, IDC_EDIT348, m_editRegisterImage);
	DDX_Control(pDX, IDC_STATIC_CHECK_ATTACHMENT, m_checkImage);
	DDX_Control(pDX, IDC_STATIC_REGISTER_ATTACHMENT, m_registerImage);
}

BEGIN_MESSAGE_MAP(CPersonalForm25, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm25::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm25::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm25::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm25::OnBnClickedCmdUpdateForm)
	ON_EN_CHANGE(IDC_EDIT2, &CPersonalForm25::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT348, &CPersonalForm25::OnEnChangeEdit348)
	ON_WM_PAINT()
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
	DoSaveForm();

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
	DoUpdateForm();
}


void CPersonalForm25::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	GetDlgItem(IDC_STATIC_FORM_HEADER)->SetFont(&m_fontHeader);
	m_editCheckImage.Initialize(this, BES_XTP_CHOOSEFILE);
	m_editRegisterImage.Initialize(this, BES_XTP_CHOOSEFILE);

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


void CPersonalForm25::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	m_editCheckImage.GetWindowTextW(m_strCheckImage);
	m_strCheckImage.Trim();
	if (!m_strCheckImage.IsEmpty()) {
		CImage  image;
		image.Load(m_strCheckImage); //把图像保存到特定目录,然后将路径存数据库
		CRect   rect; m_checkImage.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_checkImage.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
	}
}


void CPersonalForm25::OnEnChangeEdit348()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	m_editRegisterImage.GetWindowTextW(m_strRegisterImage);
	m_strRegisterImage.Trim();
	if (!m_strRegisterImage.IsEmpty()) {
		CImage  image;
		image.Load(m_strRegisterImage); //把图像保存到特定目录,然后将路径存数据库
		CRect   rect; m_registerImage.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_registerImage.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
	}
}


void CPersonalForm25::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if (!m_strCheckImage.IsEmpty()) {
		CImage  image;
		image.Load(m_strCheckImage); //把图像保存到特定目录,然后将路径存数据库
		CRect   rect; m_checkImage.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_checkImage.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
	}

	if (!m_strRegisterImage.IsEmpty()) {
		CImage  image;
		image.Load(m_strRegisterImage); //把图像保存到特定目录,然后将路径存数据库
		CRect   rect; m_registerImage.GetClientRect(&rect);//获取句柄指向控件区域的大小  
		CDC *pDc = m_registerImage.GetDC();//获取picture的DC  
		image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
		ReleaseDC(pDc);
	}
}