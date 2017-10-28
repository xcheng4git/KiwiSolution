// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"


// CDlgLogin �Ի���

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
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
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
	else {
		m_isLogined = false;
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}

LoginEnd:
	help->closeDB(); delete help;
	ss.str("");  ss.clear();

	if (m_isLogined)
		CDialogEx::OnOK();
}


void CDlgLogin::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	exit(0);
	CDialogEx::OnCancel();
}


void CDlgLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!m_bitmap.LoadBitmap(IDB_BMP_SPLASH))
		return FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
