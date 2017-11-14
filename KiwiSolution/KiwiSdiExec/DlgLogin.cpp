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
#include "MainFrm.h"


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
	m_bitmap.DeleteObject();
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strUserpwd);
	DDX_Control(pDX, IDC_STATIC_LOGIN_ICON, m_picLoginIcon);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序


void CDlgLogin::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();


	m_strUsername.Trim(); m_strUserpwd.Trim();
	if (m_strUsername.IsEmpty() || m_strUserpwd.IsEmpty()) {
		m_isLogined = false;
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
		return;
	}

	stringstream ss;
	CSQLiteHelper *help = new CSQLiteHelper();
	help->openDB("kiwi.db3");
	int row, col;
	char *eee = "i"; char **result = &eee;
	char **re;

	CString cpwd = CUtility::Crypt(m_strUserpwd);
	ss << "select user_group from kiwi_users where user_name='" << CW2A(m_strUsername.GetBuffer(), CP_UTF8) << "' and ";
	ss << "user_pwd='" << CW2A(cpwd.GetBuffer(), CP_UTF8) << "';";
	
	OutputDebugString(CA2W(ss.str().c_str(), CP_UTF8));

	re = help->rawQuery(ss.str().c_str(), &row, &col, result);
	if (row>0) {
		CString strText;
		CTime today = CTime::GetCurrentTime();
		strText = today.Format("%Y-%m-%d");
		ss << "update kiwi_users set last_login_date='" << CW2A(strText.GetBuffer(), CP_UTF8) << "' ";
		ss << " where user_name='" << CW2A(m_strUsername.GetBuffer(), CP_UTF8) << "'";
		//TRACE(_T("\r\n%s"), CA2W(ss.str().c_str(), CP_UTF8));
		help->execSQL(ss.str().c_str());
		ss.str(""); ss.clear();

		m_isLogined = true;
		((CKiwiSdiExecApp*)AfxGetApp())->m_currentUserGroup = atoi(re[1 * col + 0]);
	}
	else {
		m_isLogined = false;
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}

	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	if (m_isLogined)
		CDialogEx::OnOK();
}


void CDlgLogin::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	exit(0);
	CDialogEx::OnCancel();
}


void CDlgLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CDC dcImg;

	if (!dcImg.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	// paint the image
	CBitmap* pOldBit = dcImg.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImg, 0, 0, SRCCOPY);
	dcImg.SelectObject(pOldBit);

}


BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  在此添加额外的初始化
	//CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//pWnd->ShowWindow(SW_HIDE);

	if (!m_bitmap.LoadBitmap(IDB_BMP_SPLASH))
		return FALSE;

	//HICON hIcon = (HICON)LoadImage(NULL, _T("res\\User_login_128px_500811_easyicon.net.ico"), IMAGE_ICON, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//CDC *pDC = m_picLoginIcon.GetDC();
	//pDC->DrawIcon(0, 0, hIcon);
	HICON hicon = AfxGetApp()->LoadIcon(IDI_ICON_EXIT);
	m_btnCancel.SetIcon(CSize(32, 32), hicon); DestroyIcon(hicon); m_btnCancel.SetFlatStyle();
	hicon = AfxGetApp()->LoadIcon(IDI_ICON_LOGIN_IN);
	m_btnOk.SetIcon(CSize(32, 32), hicon); DestroyIcon(hicon); m_btnOk.SetFlatStyle();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CDlgLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
