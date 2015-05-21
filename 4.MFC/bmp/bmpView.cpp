
// bmpView.cpp : CbmpView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CbmpView 생성/소멸

CbmpView::CbmpView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	View = 1.0;
}

CbmpView::~CbmpView()
{
}

BOOL CbmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CbmpView 그리기

void CbmpView::OnDraw(CDC* pDC )
{
	CbmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawBitmap( pDC );
	
}


// CbmpView 인쇄

BOOL CbmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CbmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CbmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CbmpView 진단

#ifdef _DEBUG
void CbmpView::AssertValid() const
{
	CView::AssertValid();
}

void CbmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbmpDoc* CbmpView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbmpDoc)));
	return (CbmpDoc*)m_pDocument;
}
#endif //_DEBUG


// CbmpView 메시지 처리기

void CbmpView::DrawBitmap(CDC* dc)
{

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBitmap bmp ,  *old; 
	
	CDC memDC; // 메모리DC 
	
	
	BITMAP bm; 
	
	// 1) 비트맵 불러오기 !! 
	bmp.LoadBitmap(  IDB_BITMAP1 ); 
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



	dc->StretchBlt( x ,y , bm.bmWidth *View, bm.bmHeight *View, 
					&memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);


	memDC.SelectObject( old );



}

BOOL CbmpView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CString str;  
//	str.Format(L"delta : %d", zDelta);
//	AfxMessageBox(str); 

	if( MK_CONTROL & nFlags) 
	{
		if(zDelta > 0 )
		{ // 확대 
			if( View <=3.0)
			  View += 0.1;
		}
		else
		{ // 축소 
			if( View >= 0.5 )
			   View -= 0.1;
		}
	}
	
	Invalidate(); // OnDraw 

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
