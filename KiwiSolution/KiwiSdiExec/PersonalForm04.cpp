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
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);

	int parameters1[][6] = { { IDC_DATETIMEPICKER5, IDC_DATETIMEPICKER6, IDC_EDIT11, IDC_EDIT24, IDC_EDIT27, IDC_EDIT30 },
	{ IDC_DATETIMEPICKER7, IDC_DATETIMEPICKER8, IDC_EDIT22, IDC_EDIT25, IDC_EDIT28, IDC_EDIT31 },
	{ IDC_DATETIMEPICKER9, IDC_DATETIMEPICKER10, IDC_EDIT23, IDC_EDIT26, IDC_EDIT29, IDC_EDIT32 } };

	int parameters2[][6] = { { IDC_EDIT45, IDC_EDIT47, IDC_EDIT50, IDC_EDIT53, IDC_EDIT56, IDC_DATETIMEPICKER3 },
	{ IDC_EDIT33, IDC_EDIT48, IDC_EDIT51, IDC_EDIT54, IDC_EDIT57, IDC_DATETIMEPICKER17 },
	{ IDC_EDIT46, IDC_EDIT49, IDC_EDIT52, IDC_EDIT55, IDC_EDIT58, IDC_DATETIMEPICKER18 }};

	int parameters3[][6] = { { IDC_EDIT60, IDC_EDIT62, IDC_EDIT65, IDC_EDIT68, IDC_EDIT71, IDC_DATETIMEPICKER19 },
	{ IDC_EDIT59, IDC_EDIT63, IDC_EDIT66, IDC_EDIT69, IDC_EDIT72, IDC_DATETIMEPICKER20 },
	{ IDC_EDIT61, IDC_EDIT64, IDC_EDIT67, IDC_EDIT70, IDC_EDIT73, IDC_DATETIMEPICKER21 } };

	std::vector<std::vector<int>> vvPara;
	for (int i = 0; i < 3; i++) {
		std::vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters1[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters2[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	vvPara.clear();
	for (int i = 0; i < 3; i++) {
		std::vector<int> vPara;
		for (int j = 0; j < 6; j++)
			vPara.push_back(parameters3[i][j]);
		vvPara.push_back(vPara);
	}
	_vvvParameters.push_back(vvPara);

	m_isModify = FALSE; for (int i = 0; i < 3; i++) m_modifiedSubform[i] = -1;
}

CPersonalForm04::~CPersonalForm04()
{
	m_fontEdit.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalForm04::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);

	m_isModify = FALSE; for (int i = 0; i < 3; i++) m_modifiedSubform[i] = -1;
}

void CPersonalForm04::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO12, m_Radio7_0);
	DDX_Radio(pDX, IDC_RADIO15, m_Radio8_0);
	DDX_Radio(pDX, IDC_RADIO17, m_Radio9_0);
}

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

BEGIN_MESSAGE_MAP(CPersonalForm04, CFormView)
	ON_BN_CLICKED(IDC_CMD_SAVE_FORM, &CPersonalForm04::OnBnClickedCmdSaveForm)
	ON_BN_CLICKED(IDC_CMD_PRINT_FORM, &CPersonalForm04::OnBnClickedCmdPrintForm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FORM3, &CPersonalForm04::OnBnClickedButtonCloseForm3)
	ON_BN_CLICKED(IDC_CMD_UPDATE_FORM3, &CPersonalForm04::OnBnClickedCmdUpdateForm3)
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


// CPersonalForm04 消息处理程序


void CPersonalForm04::OnBnClickedCmdSaveForm()
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

	ss << "select count(*) from file_form_flags where file_id=" << file_id << ";";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (!hasRecord) {
		ss << "insert into file_form_flags(file_id) values(" << file_id << ")";
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();
	}

	std::vector<std::vector<std::vector<int>>>::iterator itVVV = _vvvParameters.begin();
	std::vector<std::vector<int>>::iterator itVV;
	std::vector<int>::iterator itV;
	int subformFields[] = { 6, 6, 6 };

	CString strText;
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
	itVVV++;
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
	itVVV++;
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


FillComplete:
	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << "4, " << "'" << CW2A(_T("表2-3"), CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB(); delete help;
	ss.str("");  ss.clear();
	GetDlgItem(IDC_CMD_SAVE_FORM)->EnableWindow(FALSE);
}


void CPersonalForm04::OnBnClickedCmdPrintForm()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CPersonalForm04::OnBnClickedButtonCloseForm3()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	::PostMessage(pWnd->m_hWnd, WM_SHOW_DEFAULT_SUMMARY, 0l, LPARAM(&m_strCurrentFolder));
	::PostMessage(this->m_hWnd, WM_DESTROY, 0L, 0L);
}


void CPersonalForm04::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	QueryAndFillFileForm();

	if (m_isModify) {
		GetDlgItem(IDC_CMD_SAVE_FORM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMD_UPDATE_FORM3)->ShowWindow(SW_SHOW);
	}

	((CButton*)GetDlgItem(IDC_BUTTON_CLOSE_FORM3))->SetBitmap(m_bmpClose);
}

void CPersonalForm04::OnBnClickedCmdUpdateForm3()
{
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
}

