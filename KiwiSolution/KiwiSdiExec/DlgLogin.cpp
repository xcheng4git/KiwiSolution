// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"


// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
	, m_strUsername(_T(""))
	, m_strUserpwd(_T(""))
{
	m_isLogined = false;
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strUserpwd);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序


void CDlgLogin::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();

	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re;

	m_strUsername.Trim(); m_strUserpwd.Trim();
	if (m_strUsername.IsEmpty() || m_strUserpwd.IsEmpty()) {
		m_isLogined = false;
		goto LoginEnd;
	}

	ss << "select count(*) from kiwi_users where user_name='" << CW2A(m_strUsername.GetBuffer(), CP_UTF8) << "' and ";
	ss << "user_pwd='" << CW2A(m_strUserpwd.GetBuffer(), CP_UTF8) << "';";
	
	OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8));

	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	int hasRecord = atoi(re[1 * col + 0]);
	if (hasRecord) {
		m_isLogined = true;
		//ss << "update kiwi_users set last_login_date='" << strTime << "' ";
		//ss << " where user_name='" << m_strUsername << "'";
		//help->execSQL(ss.str().c_str());
		//ss.str(""); ss.clear();
	}
	else
		m_isLogined = false;

LoginEnd:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	CDialogEx::OnOK();
}


void CDlgLogin::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	exit(0);
	CDialogEx::OnCancel();
}
