// DlgNewFolder.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgNewFolder.h"
#include "afxdialogex.h"

#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"

// CDlgNewFolder 对话框


IMPLEMENT_DYNAMIC(CDlgNewFolder, CDialogEx)

CDlgNewFolder::CDlgNewFolder(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewFolder::IDD, pParent)
	, m_strFolderName(_T(""))
	, m_strContactTel(_T(""))
	, m_strContactPhone(_T(""))
	, m_strContactName(_T(""))
{

}

CDlgNewFolder::~CDlgNewFolder()
{
}

void CDlgNewFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strFolderName);
	DDX_Text(pDX, IDC_EDIT_TEL, m_strContactTel);
	DDX_Text(pDX, IDC_EDIT_CONTACT_PHONE, m_strContactPhone);
	DDX_Text(pDX, IDC_EDIT_CONTACT_NAME, m_strContactName);
}


BEGIN_MESSAGE_MAP(CDlgNewFolder, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewFolder 消息处理程序


void CDlgNewFolder::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();

	m_strFolderName.Trim(); m_strContactTel.Trim(); m_strContactName.Trim(); m_strContactPhone.Trim();
	if (m_strFolderName.GetLength() > 1) {
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");

		stringstream ss;
		ss << "insert into orgnization_folder values (null, ";
		ss << "'" << CW2A(m_strFolderName.GetBuffer(), CP_UTF8) << "', ";
		ss << "'" << CW2A(m_strContactName.GetBuffer(), CP_UTF8) << "', ";
		ss << "'" << CW2A(m_strContactTel.GetBuffer(), CP_UTF8) << "', ";
		ss << "'" << CW2A(m_strContactPhone.GetBuffer(), CP_UTF8) << "',";
		ss << 0 << "); ";
		//char value[500];
		////USES_CONVERSION;
		////sprintf_s(value, 500, "insert into orgnization_folder(folder_id, folder_name) values (null, '%s')", G2U(W2A(m_strFolderName.GetBuffer())));
		//sprintf_s(value, 500, "insert into orgnization_folder values (null, '%s')", CW2A(m_strFolderName.GetBuffer(), CP_UTF8));
		//help->execSQL(value);
		help->execSQL(ss.str().c_str());
		help->closeDB(); delete help;
		ss.str(""); ss.clear();

		//更新组织结构
		CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		::PostMessage(pWnd->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
	}

	CDialogEx::OnOK();
}
