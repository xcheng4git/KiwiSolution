// DlgBackupDatabase.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgBackupDatabase.h"
#include "afxdialogex.h"


// CDlgBackupDatabase 对话框

IMPLEMENT_DYNAMIC(CDlgBackupDatabase, CDialogEx)

CDlgBackupDatabase::CDlgBackupDatabase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBackupDatabase::IDD, pParent)
{
	hasEncodedName = false;
}

CDlgBackupDatabase::~CDlgBackupDatabase()
{
}

void CDlgBackupDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME_BACKUP, m_editPath);
}


BEGIN_MESSAGE_MAP(CDlgBackupDatabase, CDialogEx)
	ON_EN_SETFOCUS(IDC_EDIT_NAME_BACKUP, &CDlgBackupDatabase::OnSetfocusEditNameBackup)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgBackupDatabase 消息处理程序


BOOL CDlgBackupDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_editPath.Initialize(this, BES_XTP_CHOOSEDIR);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgBackupDatabase::OnSetfocusEditNameBackup()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_HIDE);

	if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck()) {
		CString str;
		m_editPath.GetWindowTextW(str);
		str.Trim();
		if (!str.IsEmpty() && !hasEncodedName) {
			CString strPath;
			CTime today = CTime::GetCurrentTime();
			strPath.Format(_T("%s\\kiwi%s.db3"), str, today.Format("%Y%m%d"));
			m_editPath.SetWindowTextW(strPath);

			hasEncodedName = true;
		}
	}
}


void CDlgBackupDatabase::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CString strPath;
	m_editPath.GetWindowTextW(strPath); strPath.Trim();
	if (strPath.IsEmpty()) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}
	else {
		if (CopyFile(_T("kiwi.db3"), strPath.GetBuffer(), FALSE)) {
			MessageBox(_T("数据库已经成功地备份了！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
			CDialogEx::OnOK();
		}
		else
			MessageBox(_T("数据库备份为“")+strPath+_T("”失败了!"), _T("《廉政档案管理系统》"), MB_ICONERROR);

	}
}


HBRUSH CDlgBackupDatabase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
