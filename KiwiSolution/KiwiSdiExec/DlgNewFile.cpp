// DlgNewFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgNewFile.h"
#include "afxdialogex.h"

#include <sstream>
using namespace std;
#include "Utility.h"
#include "SQLiteHelper.h"
#include "msword/msword.h"
#include "MainFrm.h"


// CDlgNewFile �Ի���

IMPLEMENT_DYNAMIC(CDlgNewFile, CDialogEx)

CDlgNewFile::CDlgNewFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewFile::IDD, pParent)
	, m_strFileName(_T(""))
	, m_strFilePhone(_T(""))
{

}

CDlgNewFile::~CDlgNewFile()
{
}

void CDlgNewFile::SetCurrentFolderName(CString& folderName)
{
	m_strCurrentFolder = folderName;
}

void CDlgNewFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Control(pDX, IDC_COMBO_FOLDER_NAME, m_comboFolderName);
	DDX_Text(pDX, IDC_EDIT_FILE_PHONE, m_strFilePhone);
}


BEGIN_MESSAGE_MAP(CDlgNewFile, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewFile ��Ϣ�������


BOOL CDlgNewFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_comboFolderName.AddString(m_strCurrentFolder.GetBuffer());
	m_comboFolderName.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgNewFile::OnOK()
{
	if (m_strCurrentFolder.IsEmpty()) {
		AfxMessageBox(_T("��Ա������λΪ��!"));
		return;
	}
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData();

	m_strFileName.Trim(); m_strFilePhone.Trim();
	if (m_strFileName.GetLength() > 1) {
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		stringstream ss;
		ss << "insert into orgnization_file values (null, ";
		ss << "'" << CW2A(m_strFileName.GetBuffer(0), CP_UTF8) << "', ";
		ss << "'" << CW2A(m_strFilePhone.GetBuffer(0), CP_UTF8) << "', ";
		ss << "'" << CW2A(m_strCurrentFolder.GetBuffer(0), CP_UTF8) << "'); ";
		//char value[500];
		////sprintf_s(value, 500, "insert into orgnization_file(file_id, file_name, folder_name) values (null, '%s', '%s')", CW2A(m_strFileName.GetBuffer(0), CP_UTF8), CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8));
		//USES_CONVERSION;
		//sprintf_s(value, 500, "insert into orgnization_file(file_id, file_name, folder_name) values (null, '%s', '%s')", G2U(W2A(m_strFileName.GetBuffer())), G2U(W2A(m_strCurrentFolder.GetBuffer())));
		//help->execSQL(value);
		help->execSQL(ss.str().c_str());

		help->closeDB(); delete help;
		ss.str(""); ss.clear();

		//������֯�ṹ
		CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		::PostMessage(pWnd->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
	}

	CDialogEx::OnOK();
}
