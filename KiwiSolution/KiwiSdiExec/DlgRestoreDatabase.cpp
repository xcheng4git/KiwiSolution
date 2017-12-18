// DlgRestoreDatabase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgRestoreDatabase.h"
#include "afxdialogex.h"


// CDlgRestoreDatabase �Ի���

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


// CDlgRestoreDatabase ��Ϣ�������


void CDlgRestoreDatabase::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CString strPath;
	m_editPath.GetWindowTextW(strPath); strPath.Trim();
	if (strPath.IsEmpty()) {
		GetDlgItem(IDC_STATIC_WRONG)->ShowWindow(SW_SHOW);
	}
	else {
		BOOL bRtc1 = DeleteFile(_T("kiwi.db3.temp")); BOOL bRtc2 = CopyFile(_T("kiwi.db3"), _T("kiwi.db3.temp"), FALSE);
		BOOL bRtc3 = DeleteFile(_T("kiwi.db3"));
		if (CopyFile(strPath, _T("kiwi.db3"), FALSE)) {
			MessageBox(_T("���ݿ��Ѿ����룡"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);

			CWnd* pMain = AfxGetApp()->GetMainWnd();
			::PostMessage(pMain->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
		}
		else {
			if (bRtc3 && bRtc2) {
				MessageBox(_T("���ݿ⵼��ʧ�ܣ�ȷ�ϻָ�ԭ���ݿ⣡"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
				if (CopyFile(_T("kiwi.db3.temp"), _T("kiwi.db3"), FALSE)) {
					MessageBox(_T("���ݿ�ָ��ɹ���"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
				}
				else
					MessageBox(_T("���ݿ�ָ�ʧ�ܣ����ֹ��ָ����ݿ⣬����ѯ����Ա��"), _T("��������������ϵͳ��"), MB_ICONEXCLAMATION);
			}
		}

		CDialogEx::OnOK();
	}
}


HBRUSH CDlgRestoreDatabase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_WRONG)
		pDC->SetTextColor(RGB(255, 0, 0));//�޸��������ɫ

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CDlgRestoreDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editPath.Initialize(this, BES_XTP_CHOOSEFILE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
