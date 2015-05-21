
// ImgLibView.cpp : CImgLibView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImgLibView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImgLibView::OnFileOpen)
	ON_COMMAND(IDM_BINARY, &CImgLibView::OnBinary)
END_MESSAGE_MAP()

// CImgLibView 생성/소멸

CImgLibView::CImgLibView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImgLibView::~CImgLibView()
{
}

BOOL CImgLibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImgLibView 그리기

void CImgLibView::OnDraw(CDC* pDC)
{
	CImgLibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	m_img.Draw( pDC );


}


// CImgLibView 인쇄


void CImgLibView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CImgLibView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImgLibView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImgLibView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CImgLibView 진단

#ifdef _DEBUG
void CImgLibView::AssertValid() const
{
	CView::AssertValid();
}

void CImgLibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgLibDoc* CImgLibView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgLibDoc)));
	return (CImgLibDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgLibView 메시지 처리기

void CImgLibView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg( true) ; 
	dlg.DoModal(); 
	
	m_img.LoadBMP( "C:\\Users\\bit\\Desktop\\닷넷1차\\MFC\\Img\\splash.bmp") ;
	
	Invalidate(); 


}
// 이미지 이진화 처리 !! 
void CImgLibView::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
