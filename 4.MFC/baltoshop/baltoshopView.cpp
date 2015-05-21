
// baltoshopView.cpp : CbaltoshopView Ŭ������ ����
//

#include "stdafx.h"
#include "baltoshop.h"

#include "baltoshopDoc.h"
#include "baltoshopView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbaltoshopView

IMPLEMENT_DYNCREATE(CbaltoshopView, CView)

BEGIN_MESSAGE_MAP(CbaltoshopView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CbaltoshopView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CbaltoshopView::OnFileOpen)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CbaltoshopView ����/�Ҹ�

CbaltoshopView::CbaltoshopView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_ImgRatio = 1;
}

CbaltoshopView::~CbaltoshopView()
{
}

BOOL CbaltoshopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CbaltoshopView �׸���

void CbaltoshopView::OnDraw(CDC* pDC)
{
	CbaltoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CRect rect;
	this->GetWindowRect(&rect);
	int x = rect.Width()/2 - (m_ConvertImg.GetWidth()/2)*m_ImgRatio;
	int y = rect.Height()/2 - (m_ConvertImg.GetHeight()/2)*m_ImgRatio;
	m_ConvertImg.LeftR();
	m_ConvertImg.Draw(pDC, x, y, m_ConvertImg.GetWidth()*m_ImgRatio, m_ConvertImg.GetHeight()*m_ImgRatio);
	
}


// CbaltoshopView �μ�


void CbaltoshopView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CbaltoshopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CbaltoshopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CbaltoshopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CbaltoshopView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CbaltoshopView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CbaltoshopView ����

#ifdef _DEBUG
void CbaltoshopView::AssertValid() const
{
	CView::AssertValid();
}

void CbaltoshopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbaltoshopDoc* CbaltoshopView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbaltoshopDoc)));
	return (CbaltoshopDoc*)m_pDocument;
}
#endif //_DEBUG


// CbaltoshopView �޽��� ó����

void CbaltoshopView::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CbaltoshopDoc* pDoc = GetDocument();

	CFileDialog fdlg(true);
	fdlg.DoModal(); 
	
	m_ConvertImg.LoadBMP(fdlg.GetPathName()) ;
	pDoc->m_SaveImg = m_ConvertImg;
	Invalidate();
}


BOOL CbaltoshopView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(MK_CONTROL == nFlags)
	{
		if(zDelta > 0 && m_ImgRatio <= 5.0)
		{
			m_ImgRatio += 0.1;
		}
		else if(zDelta <= 0 && m_ImgRatio > 0.5)
		{
			m_ImgRatio -= 0.1;
		}
	}
	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
