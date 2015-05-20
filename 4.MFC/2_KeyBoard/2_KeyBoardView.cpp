
// 2_KeyBoardView.cpp : CMy2_KeyBoardView 클래스의 구현
//------------------------------------
//  1) 캐럿 이동 크기 :  폰트의 크기 !! 
//  2) 문자열 저장 !! 
//-----------------------------------
//

#include "stdafx.h"
#include "2_KeyBoard.h"

#include "2_KeyBoardDoc.h"
#include "2_KeyBoardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2_KeyBoardView

IMPLEMENT_DYNCREATE(CMy2_KeyBoardView, CView)

BEGIN_MESSAGE_MAP(CMy2_KeyBoardView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CMy2_KeyBoardView 생성/소멸

CMy2_KeyBoardView::CMy2_KeyBoardView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	pCaret.x = 0; 
	pCaret.y = 0;
}

CMy2_KeyBoardView::~CMy2_KeyBoardView()
{
}

BOOL CMy2_KeyBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy2_KeyBoardView 그리기

void CMy2_KeyBoardView::OnDraw(CDC* pDC)
{
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDoc->m_Text.AllTextOut(pDC);
}


// CMy2_KeyBoardView 인쇄

BOOL CMy2_KeyBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy2_KeyBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy2_KeyBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy2_KeyBoardView 진단

#ifdef _DEBUG
void CMy2_KeyBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2_KeyBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2_KeyBoardDoc* CMy2_KeyBoardView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2_KeyBoardDoc)));
	return (CMy2_KeyBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2_KeyBoardView 메시지 처리기

int CMy2_KeyBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CClientDC dc(this); 
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	pDoc->m_Text.InitText(&dc);

	/*CreateSolidCaret( 3 , pDoc->m_Text.GetPTextmetric()->tmHeight ); 
	SetCaretPos( pDoc->m_Text.GetCurrentCaretPos());
	ShowCaret();*/

	return 0;
}

void CMy2_KeyBoardView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	
	switch( nChar ) 
	{
	case VK_UP:		pDoc->m_Text.InputArrow(nChar); break;
	case VK_DOWN:	pDoc->m_Text.InputArrow(nChar); break;
	case VK_LEFT:	pDoc->m_Text.InputArrow(nChar); break;
	case VK_RIGHT:	pDoc->m_Text.InputArrow(nChar); break;
	}
	SetCaretPos( pDoc->m_Text.GetCurrentCaretPos() );

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy2_KeyBoardView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는	 기본값을 호출합니다.
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	if( nChar  == VK_RETURN) 
	{
		pDoc->m_Text.InputReturn();
		SetCaretPos( pDoc->m_Text.GetCurrentCaretPos() );
		Invalidate();
		return ;
	}
	else
	{
		pDoc->m_Text.InputChar(nChar);
		HideCaret();
		ShowCaret();
		SetCaretPos( pDoc->m_Text.GetCurrentCaretPos() );
		Invalidate();
		return ;
	}
	
	CView::OnChar(nChar, nRepCnt, nFlags);

}

void CMy2_KeyBoardView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	CreateSolidCaret( 3 ,  pDoc->m_Text.GetPTextmetric()->tmHeight); 
	SetCaretPos( pDoc->m_Text.GetCurrentCaretPos());
	ShowCaret();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMy2_KeyBoardView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);
	
	HideCaret();
	DestroyCaret(); 

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

