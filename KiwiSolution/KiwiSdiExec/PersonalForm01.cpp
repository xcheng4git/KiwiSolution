// PersonalForm01.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KiwiSdiExec.h"

#include "PersonalForm01.h"


// CPersonalForm01

IMPLEMENT_DYNCREATE(CPersonalForm01, CFormView)

CPersonalForm01::CPersonalForm01()
//	: CAutoFocusWnd<CFormView>(CPersonalForm01::IDD)
	: CFormView(CPersonalForm01::IDD)
{

}

CPersonalForm01::~CPersonalForm01()
{
}

void CPersonalForm01::DrawFormHeader(CDC* pDC, CRect* pBox)
{
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 40;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); lf.lfWeight = 700;
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	//CFont font; font.CreatePointFont(120, _T("������"));
	CFont* pOldFont = pDC->SelectObject(&font); pDC->SetBkMode(TRANSPARENT);

	int lenText = 11 * (lf.lfHeight*0.87);
	int len = pBox->right - pBox->left;
	pDC->TextOutW(pBox->left + len*0.5 - lenText *0.5, pBox->top, _T("�Ƽ��ɲ���������ǼǱ�"));
	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	//pDC->MoveTo(pBox->left + len*0.5 - lenText *0.5, pBox->top + 13);
	//pDC->LineTo(pBox->left + len*0.5 - lenText *0.5 + 11 * (lf.lfHeight*0.895), pBox->top + 20);   //40*0.87, 30*0.895
	//pDC->MoveTo(pBox->left + len*0.25, pBox->top);
	//pDC->LineTo(pBox->left + len*0.25, pBox->top + lf.lfHeight);
}

void CPersonalForm01::DrawForm(CDC* pDC, CRect* pBox)
{
	pDC->Rectangle(pBox);
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 30;  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3); //lf.lfWeight = 700;
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	//CFont font; font.CreatePointFont(120, _T("������"));
	CFont* pOldFont = pDC->SelectObject(&font); pDC->SetBkMode(TRANSPARENT);

	int len = pBox->right - pBox->left;
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("����")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("�Ա�")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("����")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("����")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("��������")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("������ò")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 1 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("�뵳ʱ��")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("����ʱ��")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("�к�ר��")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 2 * CELL_HEIGHT, pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
		DrawTextCell(pDC, CRect(pBox->left + 6 * len*CELL_WIDTH_RATIO, pBox->top + 0 * CELL_HEIGHT, pBox->right, pBox->top + 3 * CELL_HEIGHT), CString(_T("")), BorderLeft | BorderBottom);
	//
		DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("ѧ��ѧλ")), BorderRight | BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT), CString(_T("ȫ���ƽ���")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 3 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 4 * CELL_HEIGHT), CString(_T("��ҵԺУ��רҵ")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 3 * CELL_HEIGHT, pBox->right, pBox->top + 4 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("��ְ����")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 4 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 5 * CELL_HEIGHT), CString(_T("��ҵԺУ��רҵ")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO*1.1, pBox->top + 4 * CELL_HEIGHT, pBox->right, pBox->top + 5 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("�Ƿ񵳴���")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("�Ƿ��˴����")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT), CString(_T("�Ƿ���ЭίԱ")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 5 * CELL_HEIGHT, pBox->right, pBox->top + 6 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("������λ")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 3 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT), CString(_T("����ְ����ְʱ��")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 6 * CELL_HEIGHT, pBox->right, pBox->top + 7 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("��ͥסַ")), BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 4 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT), CString(_T("��ϵ�绰")), BorderLeft | BorderRight | BorderBottom);
	DrawTextCell(pDC, CRect(pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 7 * CELL_HEIGHT, pBox->right, pBox->top + 8 * CELL_HEIGHT), CString(_T("")), BorderBottom);
	//
	DrawTextCell(pDC, CRect(pBox->left + 2 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT, pBox->left + 5 * len*CELL_WIDTH_RATIO, pBox->top + 9 * CELL_HEIGHT), CString(_T("��ֹʱ�估��λְ��")), 0);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 8 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 12 * CELL_HEIGHT), CString(_T("")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 12 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 13 * CELL_HEIGHT), CString(_T("��Ҫ��")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 13 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->top + 14 * CELL_HEIGHT), CString(_T("������")), BorderRight);
	DrawTextCell(pDC, CRect(pBox->left + 0 * len*CELL_WIDTH_RATIO, pBox->top + 14 * CELL_HEIGHT, pBox->left + 1 * len*CELL_WIDTH_RATIO, pBox->bottom), CString(_T("")), BorderRight);
	

	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	delete pBox;
}

void CPersonalForm01::DrawTextCell(CDC* pDC, CRect& box, CString& strText, int enumBorder)
{
	const int TextHeight = 30;
	if (!strText.IsEmpty()){
		int width = box.right - box.left;
		int height = box.bottom - box.top;
		int lenText = strText.GetLength() * TextHeight * 0.895;
		pDC->TextOutW(box.left + width*0.5 - lenText *0.5, box.top + height*0.5 - TextHeight * 0.5, strText);
	}
	if (enumBorder == 0)
		return;

	if (enumBorder & BorderLeft) {
		pDC->MoveTo(box.TopLeft()); pDC->LineTo(box.left, box.bottom);
	};
	if (enumBorder & BorderTop) {
		pDC->MoveTo(box.TopLeft()); pDC->LineTo(box.right, box.top);
	}
	if (enumBorder & BorderRight) {
		pDC->MoveTo(box.BottomRight()); pDC->LineTo(box.right, box.top);
	}
	if (enumBorder & BorderBottom) {
		pDC->MoveTo(box.BottomRight()); pDC->LineTo(box.left, box.bottom);
	}
}

void CPersonalForm01::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BIRTHDAY, m_comboBirthday);
}

BEGIN_MESSAGE_MAP(CPersonalForm01, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPersonalForm01 ���

#ifdef _DEBUG
void CPersonalForm01::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonalForm01::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonalForm01 ��Ϣ�������


void CPersonalForm01::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	SetScaleToFitSize(CSize(1, 1));
	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(m_strCurrentFile);
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_PARTY);
	pCombo->AddString(_T("�й�������")); pCombo->AddString(_T("��������")); pCombo->AddString(_T("�޵���"));
}


void CPersonalForm01::OnDraw(CDC* /*pDC*/)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CClientDC dc(this);

	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC(NULL);
	CRect rt; GetClientRect(&rt);
	memBitmap.CreateCompatibleBitmap(&dc, rt.Width(), rt.Height());
	CBitmap *pOldBit = memDC.SelectObject(&memBitmap);

	//CPen dotPen; dotPen.CreatePen(PS_DOT, 1, RGB(0x33, 0x66, 0x99));
	//CGdiObject* pOldPen = memDC.SelectObject(&dotPen);
	memDC.Rectangle(new CRect(rt.left + MARGIN_X, rt.top + MARGIN_Y, rt.right - MARGIN_X, rt.bottom - MARGIN_Y));
	//memDC.SelectObject(pOldPen); dotPen.DeleteObject();

	memDC.TextOutW(rt.right - 200, rt.top + MARGIN_Y + 10, _T("��1"));
	DrawFormHeader(&memDC, new CRect(rt.left + MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X,
								  rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y, 
								  rt.right - MARGIN_X - PAGE_START_OFFSET_X - HEADER_START_OFFSET_X, 
								  rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT));
	DrawForm(&memDC, new CRect(rt.left + MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X,
		rt.top + MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT + 1, 
		rt.right - MARGIN_X - PAGE_START_OFFSET_X, rt.bottom - MARGIN_Y - PAGE_START_OFFSET_Y));

	
	dc.BitBlt(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, &memDC, 0, 0, SRCCOPY);

	memBitmap.DeleteObject();
	memDC.DeleteDC();
	/*
	LOGFONT lf; memset(&lf, 0, sizeof(LOGFONT)); lf.lfHeight = 26; _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("������"), 3);
	CFont font; VERIFY(font.CreateFontIndirect(&lf));
	CFont* pOldFont = dc.SelectObject(&font); dc.SetBkMode(TRANSPARENT);
	*/
	//dc.DeleteDC();
}


void CPersonalForm01::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	CRect rt; GetClientRect(&rt);
	rt.left += (MARGIN_X + PAGE_START_OFFSET_X + HEADER_START_OFFSET_X);
	rt.top += (MARGIN_Y + PAGE_START_OFFSET_Y + HEADER_START_OFFSET_Y + HEADER_HEIGHT + 1);
	rt.right -= (MARGIN_X + PAGE_START_OFFSET_X);
	rt.bottom -= (MARGIN_Y + PAGE_START_OFFSET_Y);

	int len = rt.right - rt.left;

	CWnd *pWnd; CRect *pRt;
	if (pWnd = GetDlgItem(IDC_EDIT_NAME)) {
		pRt = new CRect(rt.left + int(1 * len*CELL_WIDTH_RATIO + 5), rt.top + 0 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
		pWnd->MoveWindow(pRt, FALSE); delete pRt;
	}
	//if (pWnd = GetDlgItem(IDC_EDIT_NAME)) {
	//	pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
	//	pWnd->MoveWindow(pRt, FALSE); delete pRt;
	//}
		if (pWnd = GetDlgItem(IDC_EDIT_GENDER)) {
			pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
			pWnd->MoveWindow(pRt, FALSE); delete pRt;
		}
			if (pWnd = GetDlgItem(IDC_EDIT_NATION)) {
				pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 0 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 1 * CELL_HEIGHT - 5);
				pWnd->MoveWindow(pRt, FALSE); delete pRt;
			}
				if (pWnd = GetDlgItem(IDC_EDIT_BIRTH_PLACE)) {
					pRt = new CRect(rt.left + 1 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 2 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
					pWnd->MoveWindow(pRt, FALSE); delete pRt;
				}
	if (pWnd = GetDlgItem(IDC_COMBO_BIRTHDAY)) {
		pRt = new CRect(rt.left + 3 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 4 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
		pWnd->MoveWindow(pRt, FALSE); delete pRt;
	}
	if (pWnd = GetDlgItem(IDC_COMBO_PARTY)) {
		pRt = new CRect(rt.left + 5 * len*CELL_WIDTH_RATIO + 5, rt.top + 1 * CELL_HEIGHT + 5, rt.left + 6 * len*CELL_WIDTH_RATIO - 5, rt.top + 2 * CELL_HEIGHT - 5);
		pWnd->MoveWindow(pRt, FALSE); delete pRt;
	}

}
