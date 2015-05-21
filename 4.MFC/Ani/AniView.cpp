
// AniView.cpp : CAniView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, &CAniView::OnFileOpen)
END_MESSAGE_MAP()

// CAniView 생성/소멸

CAniView::CAniView()
: m_Snap(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	View = 1.0; 
	m_Snap = 1; 
	interval = 300; 
}

CAniView::~CAniView()
{
	
	


}

BOOL CAniView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAniView 그리기

void CAniView::OnDraw(CDC* pDC)
{
	CAniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	DrawBitmap( pDC, IDB_MAN );
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAniView 인쇄

BOOL CAniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAniView 진단

#ifdef _DEBUG
void CAniView::AssertValid() const
{
	CView::AssertValid();
}

void CAniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAniDoc* CAniView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAniDoc)));
	return (CAniDoc*)m_pDocument;
}
#endif //_DEBUG


// CAniView 메시지 처리기

void CAniView::DrawBitmap(CDC* dc, UINT nID)
{
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBitmap bmp ,  *old; 
	
	CDC memDC; // 메모리DC 
	
	
	BITMAP bm; 
	
	// 1) 비트맵 불러오기 !! 
	bmp.LoadBitmap(  nID  ); 
	// 2) 비트맵 파일 정보 !! 
	bmp.GetObject( sizeof(bm) ,  &bm); // 크기 !! 
	// 3) 화면 호환 DC생성 !! 
	memDC.CreateCompatibleDC( dc ); 
	// 4)메모리 DC에 비트맵 로딩 !! 
	old = memDC.SelectObject( &bmp ); 
	
	CRect rt; 
	
	GetClientRect( &rt); 
	
	int x = (rt.right/2)-(bm.bmWidth*View/2); 
	int y = (rt.bottom/2)-(bm.bmHeight*View/2);
	// 원본 출력 
	//dc->BitBlt( x,y, bm.bmWidth, bm.bmHeight, &memDC, 0,0, SRCCOPY );
	// 확대 출소 !! 

	dc->StretchBlt( x ,y , bm.bmWidth/4 *View, bm.bmHeight *View, 
		&memDC, (bm.bmWidth/4) * m_Snap , 0, bm.bmWidth/4, bm.bmHeight, SRCCOPY);
	
	memDC.SelectObject( old );

}

void CAniView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_Snap++; 
	m_Snap = m_Snap%4;
	

	Invalidate(); // 화면 갱신 !! 

	CView::OnTimer(nIDEvent);
}

int CAniView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer( 1, interval  , NULL);
	
	return 0;
}

void CAniView::OnFileOpen()
{



}
