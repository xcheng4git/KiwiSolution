// PersonalForm22.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm22.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm22

IMPLEMENT_DYNCREATE(CPersonalForm22, CFormView)

CPersonalForm22::CPersonalForm22()
: CFormView(CPersonalForm22::IDD)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	m_FormID = 22;
	int parameters1[16][6] = { { IDC_EDIT264, IDC_EDIT248, IDC_EDIT236, IDC_EDIT237, IDC_DATETIMEPICKER25, IDC_EDIT259 },
	{ IDC_EDIT253, IDC_EDIT238, IDC_EDIT260, IDC_EDIT226, IDC_DATETIMEPICKER27, IDC_EDIT249 },
	{ IDC_EDIT254, IDC_EDIT239, IDC_EDIT261, IDC_EDIT227, IDC_DATETIMEPICKER28, IDC_EDIT250 },
	{ IDC_EDIT255, IDC_EDIT240, IDC_EDIT262, IDC_EDIT228, IDC_DATETIMEPICKER28, IDC_EDIT251 },
	{ IDC_EDIT256, IDC_EDIT241, IDC_EDIT263, IDC_EDIT229, IDC_DATETIMEPICKER30, IDC_EDIT252 },
	{ IDC_EDIT267, IDC_EDIT274, IDC_EDIT302, IDC_EDIT308, IDC_DATETIMEPICKER31, IDC_EDIT318 },
	{ IDC_EDIT257, IDC_EDIT242, IDC_EDIT279, IDC_EDIT230, IDC_DATETIMEPICKER32, IDC_EDIT314 },
	{ IDC_EDIT258, IDC_EDIT243, IDC_EDIT280, IDC_EDIT231, IDC_DATETIMEPICKER33, IDC_EDIT315 },
	{ IDC_EDIT265, IDC_EDIT244, IDC_EDIT281, IDC_EDIT232, IDC_DATETIMEPICKER34, IDC_EDIT316 },
	{ IDC_EDIT266, IDC_EDIT245, IDC_EDIT282, IDC_EDIT233, IDC_DATETIMEPICKER34, IDC_EDIT317 },
	{ IDC_EDIT272, IDC_EDIT277, IDC_EDIT303, IDC_EDIT334, IDC_DATETIMEPICKER36, IDC_EDIT323 },
	{ IDC_EDIT268, IDC_EDIT246, IDC_EDIT284, IDC_EDIT313, IDC_DATETIMEPICKER37, IDC_EDIT319 },
	{ IDC_EDIT269, IDC_EDIT247, IDC_EDIT304, IDC_EDIT309, IDC_DATETIMEPICKER37, IDC_EDIT320 },
	{ IDC_EDIT270, IDC_EDIT275, IDC_EDIT305, IDC_EDIT310, IDC_DATETIMEPICKER39, IDC_EDIT321 },
	{ IDC_EDIT271, IDC_EDIT276, IDC_EDIT306, IDC_EDIT311, IDC_DATETIMEPICKER40, IDC_EDIT322 },
	{ IDC_EDIT273, IDC_EDIT278, IDC_EDIT307, IDC_EDIT312, IDC_DATETIMEPICKER41, IDC_EDIT324 } };
	int structure1[8] = { 16, 6, EDITNUM, EDITBX, EDITNUM, EDITNUM,DATEPKR, EDITBX};


	vector<vector<int>> vvPara;
	for (int i = 0; i < 16; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); 

	vStr.clear(); vStr.push_back(0); vStr.push_back(16); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[6] = { _T("有无"), _T("上交礼金"), _T("数量"), _T("折合价值"), _T("上交时间"), _T("上交部门") };
	int structure10[6] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure11[3 + 1 + 6] = { -1, 16, 5, 2,  1, 1, 1, 1, 1 }; //有无，行，列，跳过查询结果字段数，每个单元格内的标签数目....



	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 6; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);


	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm22::~CPersonalForm22()
{
	//m_fontEdit.DeleteObject();
}

//void CPersonalForm22::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//}


void CPersonalForm22::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPersonalForm22, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm22::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm22::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm22::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM, &CPersonalForm22::OnBnClickedCmdUpdateForm)
END_MESSAGE_MAP()


// CPersonalForm22 诊断

#ifdef _DEBUG
void CPersonalForm22::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm22::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CPersonalForm22::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm22::ShowRadiobtn(int nWhich, char *data)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm22::ShowDatapicker(int nID, char *data)
{
	COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
	((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
}

void CPersonalForm22::GetNumber(int nWhich, int &num)
{
	int nSub = nWhich & 0xFF00; nSub >>= 8;
	int nSWhich = nWhich & 0xF;

}

void CPersonalForm22::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

BOOL CPersonalForm22::hasData(int isub, int irow)
{
	CString strText;

	if (isub == 1) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][5])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}
// CPersonalForm22 消息处理程序


void CPersonalForm22::OnBnClickedCmdSaveForm()
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

	int Parameters[16][6] = { { IDC_EDIT264, IDC_EDIT248, IDC_EDIT236, IDC_EDIT237, IDC_DATETIMEPICKER25, IDC_EDIT259  },
	{ IDC_EDIT253, IDC_EDIT238, IDC_EDIT260, IDC_EDIT226, IDC_DATETIMEPICKER27, IDC_EDIT249 }, 
	{ IDC_EDIT254, IDC_EDIT239, IDC_EDIT261, IDC_EDIT227, IDC_DATETIMEPICKER28, IDC_EDIT250 },
	{ IDC_EDIT255, IDC_EDIT240, IDC_EDIT262, IDC_EDIT228, IDC_DATETIMEPICKER28, IDC_EDIT251 },
	{ IDC_EDIT256, IDC_EDIT241, IDC_EDIT263, IDC_EDIT229, IDC_DATETIMEPICKER30, IDC_EDIT252 },
	{ IDC_EDIT267, IDC_EDIT274, IDC_EDIT302, IDC_EDIT308, IDC_DATETIMEPICKER31, IDC_EDIT318 },
	{ IDC_EDIT257, IDC_EDIT242, IDC_EDIT279, IDC_EDIT230, IDC_DATETIMEPICKER32, IDC_EDIT314 },
	{ IDC_EDIT258, IDC_EDIT243, IDC_EDIT280, IDC_EDIT231, IDC_DATETIMEPICKER33, IDC_EDIT315 },
	{ IDC_EDIT265, IDC_EDIT244, IDC_EDIT281, IDC_EDIT232, IDC_DATETIMEPICKER34, IDC_EDIT316 },
	{ IDC_EDIT266, IDC_EDIT245, IDC_EDIT282, IDC_EDIT233, IDC_DATETIMEPICKER34, IDC_EDIT317 },
	{ IDC_EDIT272, IDC_EDIT277, IDC_EDIT303, IDC_EDIT334, IDC_DATETIMEPICKER36, IDC_EDIT323 },
	{ IDC_EDIT268, IDC_EDIT246, IDC_EDIT284, IDC_EDIT313, IDC_DATETIMEPICKER37, IDC_EDIT319 },
	{ IDC_EDIT269, IDC_EDIT247, IDC_EDIT304, IDC_EDIT309, IDC_DATETIMEPICKER37, IDC_EDIT320 },
	{ IDC_EDIT270, IDC_EDIT275, IDC_EDIT305, IDC_EDIT310, IDC_DATETIMEPICKER39, IDC_EDIT321 },
	{ IDC_EDIT271, IDC_EDIT276, IDC_EDIT306, IDC_EDIT311, IDC_DATETIMEPICKER40, IDC_EDIT322 },
	{ IDC_EDIT273, IDC_EDIT278, IDC_EDIT307, IDC_EDIT312, IDC_DATETIMEPICKER41, IDC_EDIT324 }};

	for (int i = 0; i < 16; i++) {
		GetDlgItem(Parameters[i][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty()) {
			strText.ReleaseBuffer();
			break;
		}

		ss << "insert into file_form_28 values(" << file_id << ",";
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][1])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][2])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][3])->GetWindowTextW(strText); strText.Trim();
		ss << wcstod(strText.GetBuffer(), NULL) << ","; strText.ReleaseBuffer();

		GetDlgItem(Parameters[i][4])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(Parameters[i][5])->GetWindowTextW(strText); strText.Trim();
		ss << "'" << strText << "')"; strText.ReleaseBuffer();

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();
#endif
	DoSaveForm();

	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm22::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_28 where file_id=" << file_id << " limit 0,16;";
	_vSubformQueryString.push_back(ss.str());
	
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表7.dotx")));
}


void CPersonalForm22::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(this->m_hWnd, WM_DESTROY, 0l, 0l);
}


void CPersonalForm22::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	
#if 0
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
	ss << "select * from file_form_28 where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		ss.str(""); ss.clear();
		help->closeDB();
		delete help;
		return;
	}

	int Parameters[16][6] = { { IDC_EDIT264, IDC_EDIT248, IDC_EDIT236, IDC_EDIT237, IDC_DATETIMEPICKER25, IDC_EDIT259 },
	{ IDC_EDIT253, IDC_EDIT238, IDC_EDIT260, IDC_EDIT226, IDC_DATETIMEPICKER27, IDC_EDIT249 },
	{ IDC_EDIT254, IDC_EDIT239, IDC_EDIT261, IDC_EDIT227, IDC_DATETIMEPICKER28, IDC_EDIT250 },
	{ IDC_EDIT255, IDC_EDIT240, IDC_EDIT262, IDC_EDIT228, IDC_DATETIMEPICKER28, IDC_EDIT251 },
	{ IDC_EDIT256, IDC_EDIT241, IDC_EDIT263, IDC_EDIT229, IDC_DATETIMEPICKER30, IDC_EDIT252 },
	{ IDC_EDIT267, IDC_EDIT274, IDC_EDIT302, IDC_EDIT308, IDC_DATETIMEPICKER31, IDC_EDIT318 },
	{ IDC_EDIT257, IDC_EDIT242, IDC_EDIT279, IDC_EDIT230, IDC_DATETIMEPICKER32, IDC_EDIT314 },
	{ IDC_EDIT258, IDC_EDIT243, IDC_EDIT280, IDC_EDIT231, IDC_DATETIMEPICKER33, IDC_EDIT315 },
	{ IDC_EDIT265, IDC_EDIT244, IDC_EDIT281, IDC_EDIT232, IDC_DATETIMEPICKER34, IDC_EDIT316 },
	{ IDC_EDIT266, IDC_EDIT245, IDC_EDIT282, IDC_EDIT233, IDC_DATETIMEPICKER34, IDC_EDIT317 },
	{ IDC_EDIT272, IDC_EDIT277, IDC_EDIT303, IDC_EDIT334, IDC_DATETIMEPICKER36, IDC_EDIT323 },
	{ IDC_EDIT268, IDC_EDIT246, IDC_EDIT284, IDC_EDIT313, IDC_DATETIMEPICKER37, IDC_EDIT319 },
	{ IDC_EDIT269, IDC_EDIT247, IDC_EDIT304, IDC_EDIT309, IDC_DATETIMEPICKER37, IDC_EDIT320 },
	{ IDC_EDIT270, IDC_EDIT275, IDC_EDIT305, IDC_EDIT310, IDC_DATETIMEPICKER39, IDC_EDIT321 },
	{ IDC_EDIT271, IDC_EDIT276, IDC_EDIT306, IDC_EDIT311, IDC_DATETIMEPICKER40, IDC_EDIT322 },
	{ IDC_EDIT273, IDC_EDIT278, IDC_EDIT307, IDC_EDIT312, IDC_DATETIMEPICKER41, IDC_EDIT324 } };
	COleDateTime t;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 6; j++){
			if (j == 4){
				t.ParseDateTime(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(Parameters[i][j]))->SetTime(t);
				continue;
			}
			GetDlgItem(Parameters[i][j])->SetWindowTextW(CA2W(re[(i + 1) * col + j + 1], CP_UTF8));
		}
		if (i + 1 >= row) break;
	}

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
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM)->ShowWindow(SW_SHOW);
	}

}


void CPersonalForm22::OnBnClickedCmdUpdateForm()
{
	// TODO:  在此添加控件通知处理程序代码
	DoUpdateForm();
}
