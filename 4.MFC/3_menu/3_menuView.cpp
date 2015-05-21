
// 3_menuView.cpp : CMy3_menuView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(IDM_BLUE, &CMy3_menuView::OnBlue)
//	ON_COMMAND(IDM_GREEN, &CMy3_menuView::OnGreen)
//	ON_COMMAND(IDM_RED, &CMy3_menuView::OnRed)
	ON_COMMAND_RANGE( IDM_RED, IDM_BLUE, &CMy3_menuView::OnColor)  

END_MESSAGE_MAP()

// CMy3_menuView 생성/소멸

CMy3_menuView::CMy3_menuView()
: m_CheckId(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_color = RGB(0,0,0); 
	m_CheckId = 0; 

}

CMy3_menuView::~CMy3_menuView()
{
}

BOOL CMy3_menuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy3_menuView 그리기

void CMy3_menuView::OnDraw(CDC*  pDC)
{
	CMy3_menuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


// CMy3_menuView 인쇄

BOOL CMy3_menuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy3_menuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy3_menuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy3_menuView 진단

#ifdef _DEBUG
void CMy3_menuView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3_menuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3_menuDoc* CMy3_menuView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3_menuDoc)));
	return (CMy3_menuDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3_menuView 메시지 처리기

void CMy3_menuView::OnBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(255,0,0);
	Invalidate();
}

void CMy3_menuView::OnGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0,255,0);
	Invalidate();
}

void CMy3_menuView::OnRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0,0,255);
	Invalidate();
}

void CMy3_menuView::OnColor(UINT nID)
{
	// Menu는 MainFrame !! 
	CMenu * pMenu = AfxGetMainWnd()->GetMenu();

	pMenu->CheckMenuItem( m_CheckId, MF_UNCHECKED); 
	
	m_CheckId = nID; 
	pMenu->CheckMenuItem( nID, MF_CHECKED);
	
	Invalidate();
}

	
