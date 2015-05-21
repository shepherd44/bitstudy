
// ImgLibView.cpp : CImgLibView Ŭ������ ����
//

#include "stdafx.h"
#include "ImgLib.h"

#include "ImgLibDoc.h"
#include "ImgLibView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgLibView

IMPLEMENT_DYNCREATE(CImgLibView, CView)

BEGIN_MESSAGE_MAP(CImgLibView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImgLibView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImgLibView::OnFileOpen)
	ON_COMMAND(IDM_BINARY, &CImgLibView::OnBinary)
END_MESSAGE_MAP()

// CImgLibView ����/�Ҹ�

CImgLibView::CImgLibView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImgLibView::~CImgLibView()
{
}

BOOL CImgLibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImgLibView �׸���

void CImgLibView::OnDraw(CDC* pDC)
{
	CImgLibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	m_img.Draw( pDC );


}


// CImgLibView �μ�


void CImgLibView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CImgLibView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImgLibView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImgLibView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CImgLibView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImgLibView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CImgLibView ����

#ifdef _DEBUG
void CImgLibView::AssertValid() const
{
	CView::AssertValid();
}

void CImgLibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgLibDoc* CImgLibView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgLibDoc)));
	return (CImgLibDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgLibView �޽��� ó����

void CImgLibView::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg( true) ; 
	dlg.DoModal(); 
	
	m_img.LoadBMP( "C:\\Users\\bit\\Desktop\\���1��\\MFC\\Img\\splash.bmp") ;
	
	Invalidate(); 


}
// �̹��� ����ȭ ó�� !! 
void CImgLibView::OnBinary()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int w = m_img.GetWidth(); 
	int h = m_img.GetHeight(); 
	
	for(int i =0; i< w;i++) 
	{
		for(int j = 0; j<h; j++) 
		{
			//	m_img.GetColor(i,j)
			if( m_img.GetGray(i,j) > 128) 
			{
				m_img.SetColor(i,j, RGB(255,255,255));
			}
			else 
			{
				m_img.SetColor(i,j, RGB(0,0,0));
			}
		}
	}
	Invalidate();
}
