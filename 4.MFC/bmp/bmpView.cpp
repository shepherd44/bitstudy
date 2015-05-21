
// bmpView.cpp : CbmpView Ŭ������ ����
//

#include "stdafx.h"
#include "bmp.h"

#include "bmpDoc.h"
#include "bmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbmpView

IMPLEMENT_DYNCREATE(CbmpView, CView)

BEGIN_MESSAGE_MAP(CbmpView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CbmpView ����/�Ҹ�

CbmpView::CbmpView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	View = 1.0;
}

CbmpView::~CbmpView()
{
}

BOOL CbmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CbmpView �׸���

void CbmpView::OnDraw(CDC* pDC )
{
	CbmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawBitmap( pDC );
	
}


// CbmpView �μ�

BOOL CbmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CbmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CbmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CbmpView ����

#ifdef _DEBUG
void CbmpView::AssertValid() const
{
	CView::AssertValid();
}

void CbmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbmpDoc* CbmpView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbmpDoc)));
	return (CbmpDoc*)m_pDocument;
}
#endif //_DEBUG


// CbmpView �޽��� ó����

void CbmpView::DrawBitmap(CDC* dc)
{

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CBitmap bmp ,  *old; 
	
	CDC memDC; // �޸�DC 
	
	
	BITMAP bm; 
	
	// 1) ��Ʈ�� �ҷ����� !! 
	bmp.LoadBitmap(  IDB_BITMAP1 ); 
	// 2) ��Ʈ�� ���� ���� !! 
	bmp.GetObject( sizeof(bm) ,  &bm); // ũ�� !! 
	// 3) ȭ�� ȣȯ DC���� !! 
	memDC.CreateCompatibleDC( dc ); 
	// 4)�޸� DC�� ��Ʈ�� �ε� !! 
	old = memDC.SelectObject( &bmp ); 
	
	CRect rt; 
	
	GetClientRect( &rt); 
	
	int x = (rt.right/2)-(bm.bmWidth*View/2); 
	int y = (rt.bottom/2)-(bm.bmHeight*View/2);
	// ���� ��� 
	//dc->BitBlt( x,y, bm.bmWidth, bm.bmHeight, &memDC, 0,0, SRCCOPY );
	// Ȯ�� ��� !! 



	dc->StretchBlt( x ,y , bm.bmWidth *View, bm.bmHeight *View, 
					&memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);


	memDC.SelectObject( old );



}

BOOL CbmpView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	CString str;  
//	str.Format(L"delta : %d", zDelta);
//	AfxMessageBox(str); 

	if( MK_CONTROL & nFlags) 
	{
		if(zDelta > 0 )
		{ // Ȯ�� 
			if( View <=3.0)
			  View += 0.1;
		}
		else
		{ // ��� 
			if( View >= 0.5 )
			   View -= 0.1;
		}
	}
	
	Invalidate(); // OnDraw 

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
