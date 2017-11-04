
// KiwiSdiExecDoc.cpp : CKiwiSdiExecDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KiwiSdiExec.h"
#endif

#include "KiwiSdiExecDoc.h"

#include <propkey.h>

#include "SQLiteHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKiwiSdiExecDoc

IMPLEMENT_DYNCREATE(CKiwiSdiExecDoc, CDocument)

BEGIN_MESSAGE_MAP(CKiwiSdiExecDoc, CDocument)
END_MESSAGE_MAP()


// CKiwiSdiExecDoc 构造/析构

CKiwiSdiExecDoc::CKiwiSdiExecDoc()
{
	// TODO:  在此添加一次性构造代码
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");

	char *sql1 = "select type_serial, type_name from form_type;";
	int row, col;
	char *eee = "i";
	char **result = &eee;
	char **re = help->rawQuery(sql1, &row, &col, result); //row 是查出多少行记录,col是每条记录多少个字段


	std::vector<wchar_t*> vFormByTables;
	
	vFormByTables.push_back(_T("表1"));
	vFormByTables.push_back(CA2W(re[1*col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_01"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	std::vector<int> vFormBySubform; vFormBySubform.push_back(1); m_vvFormBySubform.push_back(vFormBySubform);
	
	vFormByTables.push_back(_T("表2-1"));
	vFormByTables.push_back(CA2W(re[2 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_02"));
	vFormByTables.push_back(_T("file_form_03"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(2); vFormBySubform.push_back(3); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-2"));
	vFormByTables.push_back(CA2W(re[3 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_04"));
	vFormByTables.push_back(_T("file_form_05"));
	vFormByTables.push_back(_T("file_form_06"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(4); vFormBySubform.push_back(5); vFormBySubform.push_back(6); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-3"));
	vFormByTables.push_back(CA2W(re[4 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_07"));
	vFormByTables.push_back(_T("file_form_08"));
	vFormByTables.push_back(_T("file_form_09"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(7); vFormBySubform.push_back(8); vFormBySubform.push_back(9); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-4"));
	vFormByTables.push_back(CA2W(re[5 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_10"));
	vFormByTables.push_back(_T("file_form_11"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(10); vFormBySubform.push_back(11); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-5"));
	vFormByTables.push_back(CA2W(re[6 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_12"));
	vFormByTables.push_back(_T("file_form_12_c"));
	vFormByTables.push_back(_T("file_form_12_cl"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(12); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-6"));
	vFormByTables.push_back(CA2W(re[7 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_12_c"));
	vFormByTables.push_back(_T("file_form_12_cl"));
	vFormByTables.push_back(_T("file_form_13"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(13); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-7"));
	vFormByTables.push_back(CA2W(re[8 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_14"));
	vFormByTables.push_back(_T("file_form_15"));
	vFormByTables.push_back(_T("file_form_16"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(14); vFormBySubform.push_back(15); vFormBySubform.push_back(16); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-8"));
	vFormByTables.push_back(CA2W(re[9 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_16"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(16); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-9"));
	vFormByTables.push_back(CA2W(re[10 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_17"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(17); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-10"));
	vFormByTables.push_back(CA2W(re[11 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_17"));
	vFormByTables.push_back(_T("file_form_17_1"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(17); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-11"));
	vFormByTables.push_back(CA2W(re[12 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_18"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(18); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-12"));
	vFormByTables.push_back(CA2W(re[13 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_19"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(19); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-13"));
	vFormByTables.push_back(CA2W(re[14 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_20"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(20); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-14"));
	vFormByTables.push_back(CA2W(re[15 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_21"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(21); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-15"));
	vFormByTables.push_back(CA2W(re[16 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_22"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(22); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表2-16"));
	vFormByTables.push_back(CA2W(re[17 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_23"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(23); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表3"));
	vFormByTables.push_back(CA2W(re[18 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_24_1"));
	vFormByTables.push_back(_T("file_form_24_2"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(24); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表4"));
	vFormByTables.push_back(CA2W(re[19 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_25"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(25); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表5"));
	vFormByTables.push_back(CA2W(re[20 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_26"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(26); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表6"));
	vFormByTables.push_back(CA2W(re[21 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_27"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(27); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表7"));
	vFormByTables.push_back(CA2W(re[22* col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_28"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(28); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表8"));
	vFormByTables.push_back(CA2W(re[23 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_29"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(29); m_vvFormBySubform.push_back(vFormBySubform);

	vFormByTables.push_back(_T("表9"));
	vFormByTables.push_back(CA2W(re[24 * col + 1], CP_UTF8));
	vFormByTables.push_back(_T("file_form_30_0"));
	vFormByTables.push_back(_T("file_form_30"));
	m_vvFormByTables.push_back(vFormByTables); vFormByTables.clear();
	vFormBySubform.clear(); vFormBySubform.push_back(30); m_vvFormBySubform.push_back(vFormBySubform);

	help->closeDB();
	delete help;

	m_currentUserGroup = 0;
}

CKiwiSdiExecDoc::~CKiwiSdiExecDoc()
{
	std::vector<std::vector<wchar_t *>>::iterator itForm = m_vvFormByTables.begin();
	while (itForm != m_vvFormByTables.end()) {
		itForm->clear();
		itForm++;
	}
	m_vvFormByTables.clear();
}

BOOL CKiwiSdiExecDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CKiwiSdiExecDoc 序列化

void CKiwiSdiExecDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CKiwiSdiExecDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CKiwiSdiExecDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CKiwiSdiExecDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKiwiSdiExecDoc 诊断

#ifdef _DEBUG
void CKiwiSdiExecDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKiwiSdiExecDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKiwiSdiExecDoc 命令
