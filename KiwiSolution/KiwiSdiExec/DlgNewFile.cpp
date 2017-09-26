// DlgNewFile.cpp : 实现文件
//

#include "stdafx.h"
#include "KiwiSdiExec.h"
#include "DlgNewFile.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include "MainFrm.h"

// CDlgNewFile 对话框

IMPLEMENT_DYNAMIC(CDlgNewFile, CDialogEx)

CDlgNewFile::CDlgNewFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewFile::IDD, pParent)
	, m_strFileName(_T(""))
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
}


BEGIN_MESSAGE_MAP(CDlgNewFile, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewFile 消息处理程序


BOOL CDlgNewFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboFolderName.AddString(m_strCurrentFolder.GetBuffer());
	m_comboFolderName.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgNewFile::OnOK()
{
	if (m_strCurrentFolder.IsEmpty()) {
		AfxMessageBox(_T("人员所属单位为空!"));
		return;
	}
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();

	m_strFileName.Trim();
	if (m_strFileName.GetLength() > 1) {
		CSQLiteHelper *help = new CSQLiteHelper();
		help->openDB("kiwi.db3");
		char value[500];
		//sprintf_s(value, 500, "insert into orgnization_file(file_id, file_name, folder_name) values (null, '%s', '%s')", CW2A(m_strFileName.GetBuffer(0), CP_UTF8), CW2A(m_strCurrentFolder.GetBuffer(), CP_UTF8));
		USES_CONVERSION;
		sprintf_s(value, 500, "insert into orgnization_file(file_id, file_name, folder_name) values (null, '%s', '%s')", G2U(W2A(m_strFileName.GetBuffer())), G2U(W2A(m_strCurrentFolder.GetBuffer())));
		help->execSQL(value);
		help->closeDB();
		delete help;

		//更新组织结构
		CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		::PostMessage(pWnd->m_hWnd, WM_UPDATE_ORGNIZATION, 0l, 0l);
	}

	CDialogEx::OnOK();
}
