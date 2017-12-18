// DlgBackupDatabase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgBackupDatabase.h"
#include "afxdialogex.h"


// CDlgBackupDatabase �Ի���

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


// CDlgBackupDatabase ��Ϣ�������


BOOL CDlgBackupDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editPath.Initialize(this, BES_XTP_CHOOSEDIR);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgBackupDatabase::OnSetfocusEditNameBackup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ����ר�ô����/����û���
	CString strPath;
	m_editPath.GetWindowTextW(strPath); strPath.Trim();
	if (strPath.IsEmpty()) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}
	else {
		if (CopyFile(_T("kiwi.db3"), strPath.GetBuffer(), FALSE)) {
			MessageBox(_T("���ݿ��Ѿ��ɹ��ر����ˣ�"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
			CDialogEx::OnOK();
		}
		else
			MessageBox(_T("���ݿⱸ��Ϊ��")+strPath+_T("��ʧ����!"), _T("��������������ϵͳ��"), MB_ICONERROR);

	}
}


HBRUSH CDlgBackupDatabase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//�޸��������ɫ

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
