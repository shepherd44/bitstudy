
// AniView.cpp : CAniView Ŭ������ ����
//

#include "stdafx.h"
#include "Ani.h"

#include "AniDoc.h"
#include "AniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAniView

IMPLEMENT_DYNCREATE(CAniView, CView)

BEGIN_MESSAGE_MAP(CAniView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, &CAniView::OnFileOpen)
END_MESSAGE_MAP()

// CAniView ����/�Ҹ�

CAniView::CAniView()
: m_Snap(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	View = 1.0; 
	m_Snap = 1; 
	interval = 300; 
}

CAniView::~CAniView()
{
	
	


}

BOOL CAniView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CAniView �׸���

void CAniView::OnDraw(CDC* pDC)
{
	CAniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	DrawBitmap( pDC, IDB_MAN );
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CAniView �μ�

BOOL CAniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CAniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CAniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CAniView ����

#ifdef _DEBUG
void CAniView::AssertValid() const
{
	CView::AssertValid();
}

void CAniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAniDoc* CAniView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAniDoc)));
	return (CAniDoc*)m_pDocument;
}
#endif //_DEBUG


// CAniView �޽��� ó����

void CAniView::DrawBitmap(CDC* dc, UINT nID)
{
	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CBitmap bmp ,  *old; 
	
	CDC memDC; // �޸�DC 
	
	
	BITMAP bm; 
	
	// 1) ��Ʈ�� �ҷ����� !! 
	bmp.LoadBitmap(  nID  ); 
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

	dc->StretchBlt( x ,y , bm.bmWidth/4 *View, bm.bmHeight *View, 
		&memDC, (bm.bmWidth/4) * m_Snap , 0, bm.bmWidth/4, bm.bmHeight, SRCCOPY);
	
	memDC.SelectObject( old );

}

void CAniView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_Snap++; 
	m_Snap = m_Snap%4;
	

	Invalidate(); // ȭ�� ���� !! 

	CView::OnTimer(nIDEvent);
}

int CAniView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	SetTimer( 1, interval  , NULL);
	
	return 0;
}

void CAniView::OnFileOpen()
{



}
