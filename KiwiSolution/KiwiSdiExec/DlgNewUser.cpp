// DlgNewUser.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgNewUser.h"
#include "afxdialogex.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "MainFrm.h"

// CDlgNewUser 对话框

IMPLEMENT_DYNAMIC(CDlgNewUser, CDialogEx)

CDlgNewUser::CDlgNewUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewUser::IDD, pParent)
	, m_strUserName(_T(""))
	, m_strUserPwd(_T(""))
	, m_strUserPwd2(_T(""))
{

}

CDlgNewUser::~CDlgNewUser()
{
}

void CDlgNewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_NEW_USER_PWD, m_strUserPwd);
	DDX_Text(pDX, IDC_EDIT_NEW_USER_PWD2, m_strUserPwd2);
}


BEGIN_MESSAGE_MAP(CDlgNewUser, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_EN_SETFOCUS(IDC_EDIT_NEW_USER_PWD, &CDlgNewUser::OnSetfocusEditNewUserPwd)
	ON_EN_SETFOCUS(IDC_EDIT_NEW_USER_PWD2, &CDlgNewUser::OnSetfocusEditNewUserPwd2)
END_MESSAGE_MAP()


// CDlgNewUser 消息处理程序


void CDlgNewUser::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();
	m_strUserName.Trim(); m_strUserPwd.Trim(); m_strUserPwd2.Trim();

	if (m_strUserPwd != m_strUserPwd2) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
		return;
	}
	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re;

	ss << "select * from kiwi_users where user_name='" << CW2A(m_strUserName.GetBuffer(), CP_UTF8) << "';";
	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row > 0) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
		help->closeDB(); delete help;
		ss.str("");  ss.clear();
		return;
	}

	ss << "insert into kiwi_users values( ";
	ss << "'" << CW2A(m_strUserName.GetBuffer(), CP_UTF8) << "', ";
	ss << "'" << CW2A(m_strUserName.GetBuffer(), CP_UTF8) << "', ";
	ss << "3, ";
	CString strText;
	CTime today = CTime::GetCurrentTime();
	strText = today.Format("%Y-%m-%d");
	ss << "'" << CW2A(strText.GetBuffer(), CP_UTF8) << "');";
	help->execSQL(ss.str().c_str());
	ss.str(""); ss.clear();

	help->closeDB(); delete help;
	CDialogEx::OnOK();
}


HBRUSH CDlgNewUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CDlgNewUser::OnSetfocusEditNewUserPwd()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_HIDE);
}


void CDlgNewUser::OnSetfocusEditNewUserPwd2()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_HIDE);
}
