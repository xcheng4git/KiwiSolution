#include "stdafx.h"
#include "PersonalFormInterface.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"
#include "resource.h"

CPersonalFormInterface::CPersonalFormInterface()
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 25;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("仿宋体"), 3); lf.lfWeight = 400;
	m_fontEdit.CreateFontIndirect(&lf);
	m_bmpClose.LoadBitmap(IDB_BITMAP_CLOSE);
}


CPersonalFormInterface::~CPersonalFormInterface()
{
	m_fontEdit.DeleteObject();
	m_bmpClose.DeleteObject();
}

void CPersonalFormInterface::SetCurrentFile(CString filePath)
{
	m_strCurrentFolder = filePath.Left(filePath.Find(_T("/"), 0));
	m_strCurrentFile = filePath.Right(filePath.GetLength() - filePath.Find(_T("/"), 0) - 1);
}

void CPersonalFormInterface::DoSaveForm()
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

	CString strText;

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();

	int numSubform = _vvSubformStructure.size();
	vector<vector<CString>>::iterator itSubformRecids = _vvSubformRecid.begin();
	vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[m_FormID - 1];
	for (int i = 0; i < numSubform; i++) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();

		int numSubformRow = _vvSubformStructure[i][0]; int numSubformColumn = _vvSubformStructure[i][1];
		for (int r = 0; r < numSubformRow; r++) {
			if (!hasData(i+1, r)) break;

			std::vector<int>::iterator itV = itVVparameter->begin();

			ss.str(""); ss.clear();
			ss << "insert into " << CW2A(vFormByTables[2 + i], CP_UTF8) << " values(" << file_id << ", ";
			strText.ReleaseBuffer(); strText = CUtility::GetGuid();
			ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "',"; strText.ReleaseBuffer();

			for (int j = 0; j < numSubformColumn; j++) {
				if (_vvSubformStructure[i][2 + j] == RADIOBTN) {
					int iData;
					GetData(_vvSubformStructure[i][2 + j], itV[j], iData);
					ss << iData;

				}
				else if (_vvSubformStructure[i][2 + j] == EDITNUM) {
					double dData;
					GetData(_vvSubformStructure[i][2 + j], itV[j], dData);
					ss << dData;

				}
				else if ((_vvSubformStructure[i][2 + j] == EDITBX) || (_vvSubformStructure[i][2 + j] == DATEPKR)){
					CString strText;
					GetData(_vvSubformStructure[i][2 + j], itV[j], strText);
					ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
				}
				if (j != numSubformColumn - 1)
					ss << ", ";
			}
			ss << ");";

			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());

			itVVparameter++;

		}
		itVVVparameter++;
	}

	ss.str("");  ss.clear();
	ss << "insert into personal_form_info values (" << file_id << ",";
	ss << m_FormID << ", " << "'" << CW2A(vFormByTables[0], CP_UTF8) << "',";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');"; strText.ReleaseBuffer();
	//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

}

void CPersonalFormInterface::DoShowForm()
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

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();

	int numSubform = _vvSubformStructure.size();
	vector<CString> vSubformRecid;
	vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[m_FormID-1];
	for (int i = 0; i < numSubform; i++) {
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();

		ss.str(""); ss.clear();
		ss << "select * from " << CW2A(vFormByTables[2 + i], CP_UTF8) << " where file_id=" << file_id;
		ss << " limit " << _vvSubformRecordRange[i][0] << "," << _vvSubformRecordRange[i][1] << ";";
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			itVVVparameter++;  continue;
		}

		int numSubformRow = _vvSubformStructure[i][0], numSubformColumn = _vvSubformStructure[i][1];
		for (int r = 0; r < (row>numSubformRow ? numSubformRow : row); r++) {
			std::vector<int>::iterator itV = itVVparameter->begin();
			CString str; str.Format(_T("%s"), CA2W(re[(r + 1) * col + 1], CP_UTF8));
			vSubformRecid.push_back(str);

			for (int j = 0; j < numSubformColumn; j++) {
				ShowData(_vvSubformStructure[i][2 + j], itV[j], re[(r + 1) * col + j + 2]);
			}


			itVVparameter++;
		}
		_vvSubformRecid.push_back(vSubformRecid); vSubformRecid.clear(); 
		_vHaveDataSubform[i] = 1;

		itVVVparameter++;
	}

	help->closeDB(); 
	delete help;
	ss.str(""); ss.clear();
}

void CPersonalFormInterface::DoPrintForm(CString &templateName)
{
#if 0
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


	COleVariant covZero((short)0), covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		covDocxType((short)0), start_line, end_line, dot(CUtility::GetModuleDirectory() + _T("\\template\\表2-4.dotx"));

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

	wordApp.put_Visible(FALSE);
	CString wordVersion = wordApp.get_Version();
	docs = wordApp.get_Documents();
	docx = docs.Add(dot, covOptional, covOptional, covOptional);
	bookmarks = docx.get_Bookmarks();

	wchar_t szBookmark[50];


	vector<vector<vector<CString>>>::iterator itVVVbookmark = _vvvBookmarks.begin();

	int numSubform = _vvSubformStructure.size();
	vector<CString> vSubformRecid;
	vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[m_FormID - 1];
	vector<int> vFormBySubform = pDoc->m_vvFormBySubform[m_FormID - 1];

	for (int i = 0; i < numSubform; i++) {
		vector<vector<CString>>::iterator itVVbookmark = itVVVbookmark->begin();

#pragma region 打印子表头边的勾选框

		int has_or_no = -1;
		ss << "select ";
		ss << "file_" << vFormBySubform[i] << "IfHaveThisSituation, ";
		ss << "file_" << vFormBySubform[i] << "IfChange" << " from file_form_flags where file_id = " << file_id << "; ";
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row >= 1) {
			has_or_no = atoi(re[1 * col + _vSubformFlags[i]]);
		}
		std::vector<CString>::iterator itVbookmark = itVVbookmark->begin();
		for (int j = 0; j < 2; j++) {
			swprintf_s(szBookmark, 50, _T("%s%d"), itVbookmark[0], i + 1);
			bookmark = bookmarks.Item(&_variant_t(szBookmark));
			range = bookmark.get_Range();
			if (i == has_or_no)
				range.put_Text(_T("R"));
			else
				range.put_Text(_T("\x00A3"));
		}
#pragma endregion


		ss.str(""); ss.clear();
		ss << "select * from " << CW2A(vFormByTables[2 + i], CP_UTF8) << " where file_id=" << file_id;
		ss << " limit " << _vvSubformRecordRange[i][0] << "," << _vvSubformRecordRange[i][1] << ";";
		TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));

		re = help->rawQuery(ss.str().c_str(), &row, &col, result);
		if (row < 1) {
			itVVVbookmark++;  continue;
		}

		int numSubformRow = _vvSubformStructure[i][0], numSubformColumn = _vvSubformStructure[i][1];
		for (int r = 0; r < (row>numSubformRow ? numSubformRow : row); r++) {

			for (int j = 0; j < numSubformColumn; j++) {
				ShowData(_vvSubformStructure[i][2 + j], itV[j], re[(r + 1) * col + j + 2]);
			}


			itVVbookmark++;
		}
		_vvSubformRecid.push_back(vSubformRecid); vSubformRecid.clear();
		_vHaveDataSubform[i] = 1;

		itVVVparameter++;
	}

	help->closeDB(); delete help;
	ss.str(""); ss.clear();
#endif
}

void CPersonalFormInterface::ShowData(int type, int nID, char *data)
{
	switch (type) {
	case EDITBX:
	case EDITNUM:
		ShowEditbox(nID, data);
		break;
	case DATEPKR:
		ShowDatapicker(nID, data);
		break;
	case RADIOBTN:
		ShowRadiobtn(nID, data);
		break;
	}
}

void CPersonalFormInterface::GetData(int type, int nID, CString &data)
{
	GetString(nID, data);
}

void CPersonalFormInterface::GetData(int type, int nID, int &data)
{
	GetNumber(nID, data);
}

void CPersonalFormInterface::GetData(int type, int nID, double &data)
{
	CString str;
	GetString(nID, str);
	data = wcstod(str.GetBuffer(), NULL);
}

void CPersonalFormInterface::DoUpdateForm()
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

	CString strText;

	vector<vector<vector<int>>>::iterator itVVVparameter = _vvvParameters.begin();

	int numSubform = _vvSubformStructure.size();
	vector<vector<CString>>::iterator itSubformRecids = _vvSubformRecid.begin();
	vector<wchar_t *> vFormByTables = pDoc->m_vvFormByTables[m_FormID - 1];
	for (int i = 0; i < numSubform; i++) {
		if (_vHaveDataSubform[i] == -1) {
			itVVVparameter++; continue;
		}
		vector<CString>::const_iterator itcRecid = itSubformRecids->begin();
		vector<vector<int>>::iterator itVVparameter = itVVVparameter->begin();
		ss.str(""); ss.clear();
		ss << "select * from " << CW2A(vFormByTables[2 + i], CP_UTF8) << " where file_id=" << file_id << " limit 0,1;";
		//TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
		re = help->rawQuery(ss.str().c_str(), &row, &col, result);

		int numSubformColumn = _vvSubformStructure[i][1];
		while (itcRecid != itSubformRecids->end()) {
			std::vector<int>::iterator itV = itVVparameter->begin();
			ss.str(""); ss.clear();
			ss << "update " << CW2A(vFormByTables[2 + i], CP_UTF8) << " set  ";

			for (int j = 0; j < numSubformColumn; j++) {
				//GetDlgItem(itV[k])->GetWindowTextW(strText); strText.Trim();
				ss << re[2 + j];
				if (_vvSubformStructure[i][2 + j] == RADIOBTN) {
					int iData;
					GetData(_vvSubformStructure[i][2 + j], itV[j], iData);
					ss << "=" << iData;

				} else if (_vvSubformStructure[i][2 + j] == EDITNUM) {
					double dData;
					GetData(_vvSubformStructure[i][2 + j], itV[j], dData);
					ss << "=" << dData;

				} else if ((_vvSubformStructure[i][2 + j] == EDITBX) || (_vvSubformStructure[i][2 + j] == DATEPKR)){
					CString strText;
					GetData(_vvSubformStructure[i][2 + j], itV[j], strText);
					ss << "='" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
				}

				if (j != numSubformColumn - 1)
					ss << ", ";
			}
			ss << " where form_recid='" << CW2A(CString(*itcRecid).GetBuffer(), CP_UTF8) << "';";

			TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
			help->execSQL(ss.str().c_str());

			itcRecid++; itVVparameter++;
		}

		itVVVparameter++;

		itSubformRecids++;
	}

	ss.str("");  ss.clear();
	ss << "update personal_form_info set modify_date=";
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "', ";
	ss << " where file_id=" << file_id << " and form_serial=";
	ss << "'" << CW2A(vFormByTables[0], CP_UTF8) << "';";
	TRACE(_T("%s\n"), CA2W(ss.str().c_str(), CP_UTF8));
	help->execSQL(ss.str().c_str());

	help->closeDB();
	delete help;
	ss.str("");  ss.clear();

}
