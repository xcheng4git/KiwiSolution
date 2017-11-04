// PaneShortcut.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "KiwiSdiExec.h"
#include "PaneShortcut.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "DlgNewFolder.h"
#include "DlgNewFile.h"
#include "DlgNewForm.h"

// CPaneShortcut �Ի���
static UINT listIcons[] =
{
	IDI_MY_DOCUMENTS,
	IDI_CONTACTS,
	IDI_NOTES,
	IDI_DELETED_ITEMS
};

IMPLEMENT_DYNAMIC(CPaneShortcut, CDialogEx)

CPaneShortcut::CPaneShortcut(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaneShortcut::IDD, pParent)
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK | ILC_COLOR32, 1, 1);

	for (int i = 0; i < _countof(listIcons); i++)
	{


		HICON hIcon = AfxGetApp()->LoadIcon(listIcons[i]);
		ASSERT(hIcon);

		m_ilTreeIcons.Add(hIcon);
	}

	m_strCurrentFolder.Empty(); m_strCurrentFile.Empty(); m_bClicked = false;
}

CPaneShortcut::~CPaneShortcut()
{
}

void CPaneShortcut::InvokeNewFolderDialog()
{
	CDlgNewFolder dlg;
	dlg.DoModal();
}

void CPaneShortcut::InvokeNewFileDialog()
{
	CDlgNewFile dlg;
	dlg.SetCurrentFolderName(m_strCurrentFolder);
	dlg.DoModal();
}

void CPaneShortcut::InvokeNewFormDialog()
{
	CDlgNewForm dlg;
	dlg.m_strCurrentFolder = m_strCurrentFolder;
	dlg.m_strCurrentFile = m_strCurrentFile;
	dlg.DoModal();
}

void CPaneShortcut::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHORTCUT, m_listShortcut);
}


BEGIN_MESSAGE_MAP(CPaneShortcut, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHORTCUT, &CPaneShortcut::OnItemchangedListShortcut)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHORTCUT, &CPaneShortcut::OnClickListShortcut)
END_MESSAGE_MAP()


// CPaneShortcut ��Ϣ�������


BOOL CPaneShortcut::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//return true;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listShortcut.SetImageList(&m_ilTreeIcons, LVSIL_SMALL);
	m_listShortcut.InsertColumn(0, _T("Column One"), LVCFMT_LEFT, 125);
	m_listShortcut.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);

	int iItem=0;
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 0;
		lvitem.pszText = _T("1��������λ");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 1;
		lvitem.pszText = _T("2��������Ա");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 2;
		lvitem.pszText = _T("3���½���������");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	{
		LV_ITEM lvitem;
		memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
		lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvitem.iItem = iItem;
		lvitem.iSubItem = 0;
		lvitem.stateMask = 0;
		lvitem.iImage = 3;
		lvitem.pszText = _T("4��ɾ����λ����Ա");
		m_listShortcut.InsertItem(&lvitem);
		iItem++;
	}
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 20;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 400;
	CFont font1; font1.CreateFontIndirect(&lf);
	m_listShortcut.SetFont(&font1); font1.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CPaneShortcut::OnItemchangedListShortcut(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	return;
	/*
	int row = m_listShortcut.GetNextItem(-1, LVIS_SELECTED);

	CMainFrame* pWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	::PostMessage(pWnd->m_hWnd, WM_CREATE_PERSONAL_FORM, WPARAM(action), 0l);
	*/
}

void CPaneShortcut::OnClickListShortcut(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect rt;
	int nCount = m_listShortcut.GetItemCount();
	for (int i = 0; i < nCount; i++) {
		m_listShortcut.GetItemRect(i, &rt, LVIR_BOUNDS);
		if (rt.PtInRect(pNMItemActivate->ptAction)) {
			CString strText = m_listShortcut.GetItemText(i, -1);
			int action = _ttoi(strText.Left(1));

			switch (action) {
			case 1:
				InvokeNewFolderDialog();
				break;
			case 2:
				if (!m_strCurrentFolder.IsEmpty())
					InvokeNewFileDialog();
				break;
			case 3:
				if (!m_strCurrentFile.IsEmpty())
					InvokeNewFormDialog();
				break;
			}

		}
	}
}
