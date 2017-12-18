// DlgRestoreDatabase.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgRestoreDatabase.h"
#include "afxdialogex.h"


// CDlgRestoreDatabase 对话框

IMPLEMENT_DYNAMIC(CDlgRestoreDatabase, CDialogEx)

CDlgRestoreDatabase::CDlgRestoreDatabase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRestoreDatabase::IDD, pParent)
{

}

CDlgRestoreDatabase::~CDlgRestoreDatabase()
{
}

void CDlgRestoreDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME_BACKUP, m_editPath);
}


BEGIN_MESSAGE_MAP(CDlgRestoreDatabase, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgRestoreDatabase 消息处理程序


void CDlgRestoreDatabase::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CString strPath;
	m_editPath.GetWindowTextW(strPath); strPath.Trim();
	if (strPath.IsEmpty()) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}
	else {
		BOOL bRtc1 = DeleteFile(_T("kiwi.db3.temp")); BOOL bRtc2 = CopyFile(_T("kiwi.db3"), _T("kiwi.db3.temp"), FALSE);
		BOOL bRtc3 = DeleteFile(_T("kiwi.db3"));
		if (CopyFile(strPath, _T("kiwi.db3"), FALSE)) {
			MessageBox(_T("数据库已经导入！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);

			CWnd* pMain = AfxGetApp()->GetMainWnd();
			::PostMessage(pMain->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
		}
		else {
			if (bRtc3 && bRtc2) {
				MessageBox(_T("数据库导入失败，确认恢复原数据库！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
				if (CopyFile(_T("kiwi.db3.temp"), _T("kiwi.db3"), FALSE)) {
					MessageBox(_T("数据库恢复成功！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
				}
				else
					MessageBox(_T("数据库恢复失败，请手工恢复数据库，或咨询管理员！"), _T("《廉政档案管理系统》"), MB_ICONEXCLAMATION);
			}
		}

		CDialogEx::OnOK();
	}
}


HBRUSH CDlgRestoreDatabase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//修改字体的颜色

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CDlgRestoreDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_editPath.Initialize(this, BES_XTP_CHOOSEFILE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
