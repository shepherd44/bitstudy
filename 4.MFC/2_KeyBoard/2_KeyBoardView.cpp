
// 2_KeyBoardView.cpp : CMy2_KeyBoardView Ŭ������ ����
//------------------------------------
//  1) ĳ�� �̵� ũ�� :  ��Ʈ�� ũ�� !! 
//  2) ���ڿ� ���� !! 
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CMy2_KeyBoardView ����/�Ҹ�

CMy2_KeyBoardView::CMy2_KeyBoardView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	pCaret.x = 0; 
	pCaret.y = 0;
}

CMy2_KeyBoardView::~CMy2_KeyBoardView()
{
}

BOOL CMy2_KeyBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy2_KeyBoardView �׸���

void CMy2_KeyBoardView::OnDraw(CDC* pDC)
{
	CMy2_KeyBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	pDoc->m_Text.AllTextOut(pDC);
}


// CMy2_KeyBoardView �μ�

BOOL CMy2_KeyBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy2_KeyBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy2_KeyBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy2_KeyBoardView ����

#ifdef _DEBUG
void CMy2_KeyBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2_KeyBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2_KeyBoardDoc* CMy2_KeyBoardView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2_KeyBoardDoc)));
	return (CMy2_KeyBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2_KeyBoardView �޽��� ó����

int CMy2_KeyBoardView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ�	 �⺻���� ȣ���մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CMy2_KeyBoardView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);
	
	HideCaret();
	DestroyCaret(); 

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

