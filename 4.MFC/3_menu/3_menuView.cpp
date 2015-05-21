
// 3_menuView.cpp : CMy3_menuView Ŭ������ ����
//

#include "stdafx.h"
#include "3_menu.h"

#include "3_menuDoc.h"
#include "3_menuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3_menuView

IMPLEMENT_DYNCREATE(CMy3_menuView, CView)

BEGIN_MESSAGE_MAP(CMy3_menuView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(IDM_BLUE, &CMy3_menuView::OnBlue)
//	ON_COMMAND(IDM_GREEN, &CMy3_menuView::OnGreen)
//	ON_COMMAND(IDM_RED, &CMy3_menuView::OnRed)
	ON_COMMAND_RANGE( IDM_RED, IDM_BLUE, &CMy3_menuView::OnColor)  

END_MESSAGE_MAP()

// CMy3_menuView ����/�Ҹ�

CMy3_menuView::CMy3_menuView()
: m_CheckId(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_color = RGB(0,0,0); 
	m_CheckId = 0; 

}

CMy3_menuView::~CMy3_menuView()
{
}

BOOL CMy3_menuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy3_menuView �׸���

void CMy3_menuView::OnDraw(CDC*  pDC)
{
	CMy3_menuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CRect rt(100,100, 300,300);
	CBrush brush; 
	
    switch( m_CheckId - IDM_RED)
	{
	case 0: 	m_color =	 RGB( 255,0,0); break;
	case 1: 	m_color =	 RGB( 0,255,0); break;
	case 2: 	m_color =	 RGB( 0,0,255); break;
	}

	brush.CreateSolidBrush( m_color);	

	pDC->FillRect( &rt, &brush );



}


// CMy3_menuView �μ�

BOOL CMy3_menuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy3_menuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy3_menuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy3_menuView ����

#ifdef _DEBUG
void CMy3_menuView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3_menuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3_menuDoc* CMy3_menuView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3_menuDoc)));
	return (CMy3_menuDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3_menuView �޽��� ó����

void CMy3_menuView::OnBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(255,0,0);
	Invalidate();
}

void CMy3_menuView::OnGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(0,255,0);
	Invalidate();
}

void CMy3_menuView::OnRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(0,0,255);
	Invalidate();
}

void CMy3_menuView::OnColor(UINT nID)
{
	// Menu�� MainFrame !! 
	CMenu * pMenu = AfxGetMainWnd()->GetMenu();

	pMenu->CheckMenuItem( m_CheckId, MF_UNCHECKED); 
	
	m_CheckId = nID; 
	pMenu->CheckMenuItem( nID, MF_CHECKED);
	
	Invalidate();
}

	
