// PersonalForm04.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "PersonalForm04.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CPersonalForm04

IMPLEMENT_DYNCREATE(CPersonalForm04, CFormView)

CPersonalForm04::CPersonalForm04()
	: CFormView(CPersonalForm04::IDD)
	, m_Radio7_0(-1)
	, m_Radio8_0(-1)
	, m_Radio9_0(-1)
{
	//LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	//m_fontEdit.CreateFontIndirect(&lf);
	//m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);

	m_FormID = 4;
	int parameters1[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };
	int structure1[8] = { 3, 6, DATEPKR, DATEPKR, EDITBX, EDITBX, EDITBX, EDITBX };

	int parameters2[][6] = { { IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, IDC_EDIT56, IDC_DATETIMEPICKER3 },
	{ IDC_EDIT33, IDC_EDIT48, IDC_EDIT51, IDC_EDIT54, IDC_EDIT57, IDC_DATETIMEPICKER17 },
	{ IDC_EDIT46, IDC_EDIT49, IDC_EDIT52, IDC_EDIT55, IDC_EDIT58, IDC_DATETIMEPICKER18 }};
	int structure2[8] = { 3, 6, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, DATEPKR };

	int parameters3[][6] = { { IDC_EDIT60, IDC_EDIT62, IDC_EDIT65, IDC_EDIT68, IDC_EDIT71, IDC_DATETIMEPICKER19 },
	{ IDC_EDIT59, IDC_EDIT63, IDC_EDIT66, IDC_EDIT69, IDC_EDIT72, IDC_DATETIMEPICKER20 },
	{ IDC_EDIT61, IDC_EDIT64, IDC_EDIT67, IDC_EDIT70, IDC_EDIT73, IDC_DATETIMEPICKER21 } };
	int structure3[8] = { 3, 6, EDITBX, EDITBX, EDITBX, EDITBX, EDITBX, DATEPKR };

	vector<vector<int>> vvPara;
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vector<int> vStr;
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure1[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure2[i]);
	}
	_vvSubformStructure.push_back(vStr);

	vStr.clear();
	for (int i = 0; i < 8; i++) {
		vStr.push_back(structure3[i]);
	}
	_vvSubformStructure.push_back(vStr);

	_vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1); _vHaveDataSubform.push_back(-1);

	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);
	vStr.clear(); vStr.push_back(0); vStr.push_back(3); _vvSubformRecordRange.push_back(vStr);

	//以下是为了打印的预设
	const wchar_t *pBookmarks1[7] = { _T("有无"), _T("起始日期"), _T("截止日期"), _T("所到地区"), _T("事由"), _T("审批机构"), _T("所用证件号码") };
	int structure10[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure11[4 + 7] = { 0, 3, 6, 2, 2, 1,1, 1, 1, 1, 1 };

	const wchar_t *pBookmarks2[7] = { _T("有无"), _T("子女姓名"), _T("配偶姓名"), _T("配偶国家"), _T("配偶单位"), _T("配偶职务"), _T("配偶登记时间") };
	int structure20[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure21[4 + 7] = { 1, 3, 6, 2, 2, 1, 1, 1, 1, 1, 1 };

	const wchar_t *pBookmarks3[7] = { _T("有无"), _T("子女姓名"), _T("配偶姓名"), _T("配偶地区"), _T("配偶单位"), _T("配偶职务"), _T("配偶登记时间") };
	int structure30[7] = { CBookmarkEx::CHKBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX, CBookmarkEx::TXTBOX };
	int structure31[4 + 7] = { 1, 3, 6, 2, 2, 1, 1, 1, 1, 1, 1 };

	vector<CBookmarkEx> vBke;
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure10[i], pBookmarks1[i], structure11[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure20[i], pBookmarks2[i], structure21[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);
	vBke.clear();
	for (int i = 0; i < 7; i++) {
		CBookmarkEx bookmark(structure30[i], pBookmarks3[i], structure31[4 + i]);
		vBke.push_back(bookmark);
	}
	_vvBookmarks.push_back(vBke);

	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure11[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure21[i]);
	_vvSubformFlags.push_back(vStr);
	vStr.clear();
	for (int i = 0; i < 4; i++)
		vStr.push_back(structure31[i]);
	_vvSubformFlags.push_back(vStr);
}

CPersonalForm04::~CPersonalForm04()
{
	//m_fontEdit.DeleteObject();
	//m_bmpClose.DeleteObject();
}

//void CPersonalForm04::SetCurrentFile(CString filePath)
//{
//	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
//	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
//
//	m_isModify = FALSE; for (int i = 0; i < 3; i++) m_modifiedSubform[i] = -1;
//}

void CPersonalForm04::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO12, m_Radio7_0);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio8_0);
	DDX_Radio(pDX, IDC_RADIO17, m_Radio9_0);
}

#if 0
void CPersonalForm04::QueryAndFillFileForm()
{
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);

	std::vector<std::vector<std::vector<int>>>::iterator itVVV = _vvvParameters.begin();

	int subformStructure[][2] = { { 3, 6 }, { 3, 6 }, { 3, 6 } };
	BOOL haveRecords[3] = { TRUE, TRUE, TRUE };
	std::vector<CString> vSubformRecid;
	std::vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[3];
	for (int i = 0; i < 3; i++) {
		std::vector<std::vector<int>>::iterator itVV = itVVV->begin();
		ss.str(""); ss.clear();
		ss << "select * from " << CW2A(vFormByTables[2 + i], CP_UTF8) << " where file_id=" << file_id << ";";
		//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			haveRecords[i] = FALSE;
			GetDlgItem(itVV[0][0])->SetWindowTextW(_T("无"));
			ss.str(""); ss.clear();
			itVVV++;  continue;
		}

		for (int r = 0; r < (row>subformStructure[i][0] ? subformStructure[i][0] : row); r++) {
			std::vector<int>::iterator itV = itVV->begin();
			CString str; str.Format(_T("%s"), CA2W(re[(r + 1) * col + 1], CP_UTF8));
			vSubformRecid.push_back(str);

			if (i == 0) {
				COleDateTime t; t.ParseDateTime(CA2W(re[1 * col + 0 + 2], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(itV[0]))->SetTime(t);
				t.ParseDateTime(CA2W(re[1 * col + 1 + 2], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(itV[1]))->SetTime(t);
				for (int j = 2; j < subformStructure[i][1]; j++)
					GetDlgItem(itV[j])->SetWindowTextW(CA2W(re[(r + 1) * col + j + 2], CP_UTF8));
			}
			if ((i == 1) || (i==2)) {
				for (int j = 0; j < 5; j++)
					GetDlgItem(itV[j])->SetWindowTextW(CA2W(re[(r + 1) * col + j + 2], CP_UTF8));
				COleDateTime t; t.ParseDateTime(CA2W(re[1 * col + 5 + 2], CP_UTF8));
				((CDateTimeCtrl*)GetDlgItem(itV[5]))->SetTime(t);

			}

			itVV++;
		}
		m_vvFormRecid.push_back(vSubformRecid); vSubformRecid.clear();  m_modifiedSubform[i] = 1;
		m_isModify = TRUE;

		itVVV++;
	}

	ss.str(""); ss.clear();
	ss << "select file_7IfHaveThisSituation, file_8IfChange, file_9IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	m_Radio7_0 = atoi(re[1 * col + 0]); m_Radio8_0 = atoi(re[1 * col + 1]); m_Radio9_0 = atoi(re[1 * col + 2]);

	help->closeDB(); delete help;
	ss.str(""); ss.clear();

	UpdateData(FALSE);
}
#endif

BEGIN_MESSAGE_MAP(CPersonalForm04, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm04::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm04::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm04::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm04::OnBnClickedCmdUpdateForm3)
	ON_BN_CLICKED(IDC_CMD_NEXT_FORM, &CPersonalForm04::OnBnClickedCmdNextForm)
END_MESSAGE_MAP()


// CPersonalForm04 诊断

#ifdef _DEBUG
void CPersonalForm04::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm04::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPersonalForm04::ShowEditbox(int nID, char *data)
{
	GetDlgItem(nID)->SetWindowTextW(CA2W(data, CP_UTF8));
}

void CPersonalForm04::ShowRadiobtn(int nWhich, char *data)
{

}

void CPersonalForm04::ShowDatapicker(int nID, char *data)
{
	if (strlen(data) < 8)
		return;
	else {
		COleDateTime t; t.ParseDateTime(CA2W(data, CP_UTF8));
		((CDateTimeCtrl*)GetDlgItem(nID))->SetTime(t);
	}
}

void CPersonalForm04::GetNumber(int nWhich, int &num)
{

}

void CPersonalForm04::GetString(int nID, CString &str)
{
	GetDlgItem(nID)->GetWindowTextW(str); str.Trim();
}

int CPersonalForm04::hasData(int isub, int irow)
{
	CString strText;
	if ((isub == 2) || (isub == 3)) {
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][0])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
		else if (_T("无") == strText)
			return 2;
	}
	else if (isub == 1) {
		if (m_Radio7_0 == -1 || m_Radio7_0 == 1)
			return FALSE;
		vector<vector<int>> vvParam = _vvvParameters[isub - 1];
		GetDlgItem(vvParam[irow][2])->GetWindowTextW(strText); strText.Trim();
		if (strText.IsEmpty())
			return FALSE;
	}

	return TRUE;
}
// CPersonalForm04 消息处理程序


void CPersonalForm04::OnBnClickedCmdSaveForm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	//std::vector<std::vector<std::vector<int>>>::iterator itVVV = _vvvParameters.begin();
	//std::vector<std::vector<int>>::iterator itVV;
	//std::vector<int>::iterator itV;
	//int subformFields[] = { 6, 6, 6 };

	CString strText;

	if (m_Radio7_0 == -1) {
		MessageBox(_T("请选择是否存在 3-2 本人因私往来港澳、台湾的情况 ！"), _T("《廉政档案管理系统》"), MB_ICONSTOP);
		help->closeDB(); delete help;
		ss.str("");  ss.clear();
		return;
	}
	else {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_7IfHaveThisSituation=";
		ss << m_Radio7_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}
#if 0
#pragma region FillForm3_2
	{
		if (((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_7IfHaveThisSituation=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm4;
		}

		ss << "update file_form_flags set file_7IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}


	itVV = itVVV->begin();
	for (int i = 0; i < 3; i++)
	{
		itV = itVV->begin();

		GetDlgItem(itV[2])->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {

			ss.str(""); ss.clear();
			ss << "insert into file_form_07 values(" << file_id << ",";
			strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			for (int j = 0; j < subformFields[1] - 1; j++) {
				GetDlgItem(itV[j])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			}
			GetDlgItem(itV[subformFields[1] - 1])->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
			//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		} else break;
		itVV++;
		/*
		GetDlgItem(IDC_DATETIMEPICKER5)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER6)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT11)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT24)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT27)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT30)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		*/
	}
	/*
	{
		GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";
			strText.ReleaseBuffer();
			strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_DATETIMEPICKER7)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER8)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT22)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT25)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT28)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT31)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm4;

		GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_5 values(" << file_id << ",";
			strText.ReleaseBuffer();
			strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_DATETIMEPICKER9)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER10)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT23)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT26)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT29)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT32)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "') "; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}
	*/

#pragma endregion
	//itVVV++;
#endif


	GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
	ss.str(""); ss.clear();
	if (strText == _T("无"))
		ss << "update file_form_flags set file_8IfHaveThisSituation=1 where file_id=" << file_id;
	else 
		ss << "update file_form_flags set file_8IfHaveThisSituation=0 where file_id=" << file_id;

	help->execSQL(ss.str().c_str());

	if (m_Radio8_0 != -1) {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_8IfChange=";
		ss << m_Radio8_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}

#if 0
#pragma region FillForm4
FillForm4:
	GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_8IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillForm5;
	}

	{
		ss << "update file_form_flags set file_8IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO16))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_8IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillForm5;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO15))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_8IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	itVV = itVVV->begin();
	for (int i = 0; i < 3; i++)
	{
		itV = itVV->begin();

		GetDlgItem(itV[2])->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {

			ss.str(""); ss.clear();
			ss << "insert into file_form_08 values(" << file_id << ",";
			strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			for (int j = 0; j < subformFields[2] - 1; j++) {
				GetDlgItem(itV[j])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			}
			GetDlgItem(itV[subformFields[2] - 1])->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else break;
		itVV++;
	}
	/*
	{
		ss << "insert into file_form_8 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(IDC_EDIT45)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT47)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT50)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT53)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT56)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER3)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_8 values(" << file_id << ",";
			strText.ReleaseBuffer(); strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_EDIT33)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT48)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT51)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT54)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT57)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER17)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm5;

		GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_8 values(" << file_id << ",";
			strText.ReleaseBuffer(); strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_EDIT46)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT49)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT52)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT55)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT58)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER18)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillForm5;
	}
	*/

#pragma endregion
	//itVVV++;
#endif

	GetDlgItem(IDC_EDIT60)->GetWindowTextW(strText);
	ss.str(""); ss.clear();
	if (strText == _T("无"))
		ss << "update file_form_flags set file_9IfHaveThisSituation=1 where file_id=" << file_id;
	else
		ss << "update file_form_flags set file_9IfHaveThisSituation=0 where file_id=" << file_id;

	help->execSQL(ss.str().c_str());

	if (m_Radio9_0 != -1) {
		ss.str(""); ss.clear();
		ss << "update file_form_flags set file_9IfChange=";
		ss << m_Radio9_0 << " where file_id = " << file_id;
		help->execSQL(ss.str().c_str());
	}

#if 0

#pragma region FillForm5
FillForm5:
	GetDlgItem(IDC_EDIT60)->GetWindowTextW(strText);
	if (strText == _T("无"))
	{
		ss << "update file_form_flags set file_9IfHaveThisSituation=0 where file_id=" << file_id;

		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
		goto FillComplete;
	}

	{
		ss << "update file_form_flags set file_9IfHaveThisSituation=1 where file_id=" << file_id;
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		if (((CButton *)GetDlgItem(IDC_RADIO16))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_9IfChange=0 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
			goto FillComplete;
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO15))->GetCheck() == 1)
		{
			ss << "update file_form_flags set file_9IfChange=1 where file_id=" << file_id;
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
	}

	itVV = itVVV->begin();
	for (int i = 0; i < 3; i++)
	{
		itV = itVV->begin();

		GetDlgItem(itV[2])->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {

			ss.str(""); ss.clear();
			ss << "insert into file_form_09 values(" << file_id << ",";
			strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			for (int j = 0; j < subformFields[3] - 1; j++) {
				GetDlgItem(itV[j])->GetWindowTextW(strText);
				ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			}
			GetDlgItem(itV[subformFields[3] - 1])->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else break;
		itVV++;
	}
	/*
	{
		ss << "insert into file_form_9 values(" << file_id << ",";
		strText.ReleaseBuffer(); strText = CUtility::GetGuid();
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

		GetDlgItem(IDC_EDIT60)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT62)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT65)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT68)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_EDIT71)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
		GetDlgItem(IDC_DATETIMEPICKER19)->GetWindowTextW(strText);
		ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

		//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	{
		GetDlgItem(IDC_EDIT59)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_9 values(" << file_id << ",";
			strText.ReleaseBuffer(); strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_EDIT59)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT63)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT66)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT69)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT72)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER20)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;

		GetDlgItem(IDC_EDIT61)->GetWindowTextW(strText);
		strText.Trim();
		if (!strText.IsEmpty()) {
			ss << "insert into file_form_9 values(" << file_id << ",";
			strText.ReleaseBuffer(); strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			GetDlgItem(IDC_EDIT61)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT64)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT67)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT70)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_EDIT73)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();
			GetDlgItem(IDC_DATETIMEPICKER21)->GetWindowTextW(strText);
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "')"; strText.ReleaseBuffer();

			//TRACE(CA2W(ss.str().c_str(), CP_UTF8)); TRACE("\n");
			help->execSQL(ss.str().c_str());
			ss.str(""); ss.clear();
		}
		else
			goto FillComplete;
	}
	*/
#pragma endregion
#endif


FillComplete:
#if 0
	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << "4, " << "'" << CW2A(_T("表2-3"), CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());
#endif

	help->closeDB(); delete help;
	ss.str("");  ss.clear();


	DoSaveForm();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm04::OnBnClickedCmdPrintForm()
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
	ss << "select * from file_form_07 where file_id=" << file_id << " limit 0,3;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_08 where file_id=" << file_id << " limit 0,3;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();
	ss << "select * from file_form_09 where file_id=" << file_id << " limit 0,3;";
	_vSubformQueryString.push_back(ss.str());
	ss.str(""); ss.clear();

	DoPrintForm(CString(_T("表2-3.dotx")));
}


void CPersonalForm04::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	//::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, 0l);
	::PostMessage(pWnd->m_hWnd, WM_SHOW_PERSONAL_SUMMARY, WPARAM(&m_strCurrentFolder), LPARAM(&m_strCurrentFile));

	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm04::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
#if 0
	QueryAndFillFileForm();

	if (m_isModify) {
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM3)->ShowWindow(SW_SHOW);
	}

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM3))->SetBitmap(m_bmpClose);
#endif
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
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM3)->ShowWindow(SW_SHOW);
	}

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
	ss << "select file_7IfHaveThisSituation, file_8IfChange, file_9IfChange from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row < 1) {
		m_Radio7_0 = -1; m_Radio9_0 = -1; m_Radio9_0 = -1;
	}
	else {
		m_Radio7_0 = atoi(re[1 * col + 0]);  //分组的原因, m_Radio7_0=0表示有此类情况，即第一个单选按钮
		m_Radio8_0 = atoi(re[1 * col + 1]);
		m_Radio9_0 = atoi(re[1 * col + 2]);
	}
	help->closeDB(); delete help;

	UpdateData(FALSE);

}

#if 0
void CPersonalForm04::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类

	stringstream ss;
	ss << "select file_id from orgnization_file where file_name='" << CW2A(m_strCurrentFile.GetBuffer(), CP_UTF8) << "' and folder_name='" <<
		CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8) << "';";

	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int file_id = atoi(re[1 * col + 0]);


	#pragma region FillForm4
	FillForm4 :
	{
		

		ss.str(""); ss.clear();
		ss << "select file_8IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}
		//m_Radio14_1_0 = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select * from file_form_08 where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			goto FillForm5;
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}

		COleDateTime t;

		GetDlgItem(IDC_EDIT45)->SetWindowTextW(CA2W(re[ 1 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT47)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT50)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT53)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT56)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[1 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER3)->SetTime(t);

		GetDlgItem(IDC_EDIT33)->SetWindowTextW(CA2W(re[2 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT48)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT51)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT54)->SetWindowTextW(CA2W(re[2 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT57)->SetWindowTextW(CA2W(re[2 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[2 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER17)->SetTime(t);

		GetDlgItem(IDC_EDIT46)->SetWindowTextW(CA2W(re[3 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT49)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT52)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT55)->SetWindowTextW(CA2W(re[3 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT58)->SetWindowTextW(CA2W(re[3 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[3 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER18)->SetTime(t);
	}
	#pragma endregion

	#pragma region FillForm5
	FillForm5 :
	{
		ss.str(""); ss.clear();
		ss << "select file_9IfHaveThisSituation from file_form_flags where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}
		//m_Radio14_1_0 = atoi(re[1 * col + 0]);

		ss.str(""); ss.clear();
		ss << "select * from file_form_09 where file_id=" << file_id << ";";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			goto FillComplete;
			ss.str(""); ss.clear();
			help->closeDB();
			delete help;
			return;
		}

		COleDateTime t;

		GetDlgItem(IDC_EDIT60)->SetWindowTextW(CA2W(re[1 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT62)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT65)->SetWindowTextW(CA2W(re[1 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT68)->SetWindowTextW(CA2W(re[1 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT71)->SetWindowTextW(CA2W(re[1 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[1 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER19)->SetTime(t);

		GetDlgItem(IDC_EDIT59)->SetWindowTextW(CA2W(re[2 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT63)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT66)->SetWindowTextW(CA2W(re[2 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT69)->SetWindowTextW(CA2W(re[2 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT72)->SetWindowTextW(CA2W(re[2 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[2 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER20)->SetTime(t);
			
		GetDlgItem(IDC_EDIT61)->SetWindowTextW(CA2W(re[3 * col + 1], CP_UTF8));
		GetDlgItem(IDC_EDIT64)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT67)->SetWindowTextW(CA2W(re[3 * col + 2], CP_UTF8));
		GetDlgItem(IDC_EDIT70)->SetWindowTextW(CA2W(re[3 * col + 4], CP_UTF8));
		GetDlgItem(IDC_EDIT73)->SetWindowTextW(CA2W(re[3 * col + 5], CP_UTF8));
		//t.ParseDateTime(CA2W(re[3 * col + 6], CP_UTF8));
		//((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER21)->SetTime(t);
	}
	#pragma endregion


	FillComplete:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();


}
#endif

void CPersonalForm04::OnBnClickedCmdUpdateForm3()
{
#if 0
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CKiwiSdiExecDoc* pDoc = pWnd->GetDocument();

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


	std::vector<std::vector<std::vector<int>>>::iterator itVVV = _vvvParameters.begin();

	int subformStructure[][2] = { { 3, 6 }, { 3, 6 }, { 3, 6 } };
	CString strText;
	std::vector<std::vector<CString>>::iterator itSubformRecids = m_vvFormRecid.begin();
	std::vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[3];
	for (int i = 0; i < 3; i++) {
		if (m_modifiedSubform[i] == -1) {
			itVVV++;
			continue;
		}
		std::vector<CString>::const_iterator itcRecid = itSubformRecids->begin();
		std::vector<std::vector<int>>::iterator itVV = itVVV->begin();

		ss.str(""); ss.clear();
		ss << "select * from " << CW2A(vFormByTables[2 + i], CP_UTF8) << " where file_id=" << file_id << " limit 0,1;";
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);

		while (itcRecid != itSubformRecids->end()) {
			std::vector<int>::iterator itV = itVV->begin();
			ss.str(""); ss.clear();
			ss << "update " << CW2A(vFormByTables[2 + i], CP_UTF8) << " set  ";
			for (int k = 0; k < subformStructure[i][1] - 1; k++) {
				GetDlgItem(itV[k])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + k] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
			}
			GetDlgItem(itV[subformStructure[i][1] - 1])->GetWindowTextW(strText); strText.Trim();
			ss << re[2 + subformStructure[i][1] - 1] << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "'  ";
			ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());

			itcRecid++; itVV++;
		}

		itVVV++;

		itSubformRecids++;
	}

	ss.str("");  ss.clear();
	ss << "update personal_form_info set modify_date=";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << " where file_id=" << file_id << " and form_serial=";
	ss << "'" << CW2A(_T("表2-3"), CP_UTF8) << "';";
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB();
	delete help;
	ss.str("");  ss.clear();
#endif
	UpdateData();

	DoUpdateForm();

	DoUpdateFlag(1, 0, m_Radio7_0);
	DoUpdateFlag(2, 1, m_Radio8_0);
	DoUpdateFlag(3, 1, m_Radio9_0);
}


void CPersonalForm04::OnBnClickedCmdNextForm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(5), LPARAM(new CString(m_strCurrentFolder + _T("/") + m_strCurrentFile)));
}
