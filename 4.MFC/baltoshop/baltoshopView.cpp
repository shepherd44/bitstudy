
// baltoshopView.cpp : CbaltoshopView 클래스의 구현
//

#include "stdafx.h"
#include "baltoshop.h"

#include "baltoshopDoc.h"
#include "baltoshopView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbaltoshopView

IMPLEMENT_DYNCREATE(CbaltoshopView, CView)

BEGIN_MESSAGE_MAP(CbaltoshopView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CbaltoshopView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_FILE_SAVE, &CbaltoshopView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CbaltoshopView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CbaltoshopView::OnFileOpen)
	ON_COMMAND(ID_PEDIT_LROTATE, &CbaltoshopView::OnPeditLrotate)
	ON_COMMAND(ID_PEDIT_RROTATE, &CbaltoshopView::OnPeditRrotate)
	ON_COMMAND(ID_PEDIT_BDOWN, &CbaltoshopView::OnPeditBdown)
	ON_COMMAND(ID_PEDIT_GDOWN, &CbaltoshopView::OnPeditGdown)
	ON_COMMAND(ID_PEDIT_RDOWN, &CbaltoshopView::OnPeditRdown)
	ON_COMMAND(ID_RGBEDIT_UP_B, &CbaltoshopView::OnRgbeditUpB)
	ON_COMMAND(ID_RGBEDIT_UP_G, &CbaltoshopView::OnRgbeditUpG)
	ON_COMMAND(ID_RGBEDIT_UP_R, &CbaltoshopView::OnRgbeditUpR)
	ON_COMMAND(ID_RGBEDIT_RGBEDITDIALOG, &CbaltoshopView::OnRgbeditRgbeditdialog)
END_MESSAGE_MAP()

// CbaltoshopView 생성/소멸

CbaltoshopView::CbaltoshopView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ImgRatio = 1;
	m_Dlg = NULL;
}

CbaltoshopView::~CbaltoshopView()
{
	if(m_Dlg != NULL)
		delete m_Dlg;
}

BOOL CbaltoshopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CbaltoshopView 그리기

void CbaltoshopView::OnDraw(CDC* pDC)
{
	CbaltoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	this->GetWindowRect(&rect);
	int x = rect.Width()/2 - (m_ConvertImg.GetWidth()/2)*m_ImgRatio;
	int y = rect.Height()/2 - (m_ConvertImg.GetHeight()/2)*m_ImgRatio;
	m_ConvertImg.Draw(pDC, x, y, m_ConvertImg.GetWidth()*m_ImgRatio, m_ConvertImg.GetHeight()*m_ImgRatio);
	
}


// CbaltoshopView 인쇄


void CbaltoshopView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CbaltoshopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CbaltoshopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CbaltoshopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CbaltoshopView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CbaltoshopView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CbaltoshopView 진단

#ifdef _DEBUG
void CbaltoshopView::AssertValid() const
{
	CView::AssertValid();
}

void CbaltoshopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbaltoshopDoc* CbaltoshopView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbaltoshopDoc)));
	return (CbaltoshopDoc*)m_pDocument;
}
#endif //_DEBUG


// CbaltoshopView 메시지 처리기


BOOL CbaltoshopView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(MK_CONTROL == nFlags)
	{
		if(zDelta > 0 && m_ImgRatio <= 5.0)
		{
			m_ImgRatio += 0.1;
		}
		else if(zDelta <= 0 && m_ImgRatio > 0.5)
		{
			m_ImgRatio -= 0.1;
		}
	}
	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



void CbaltoshopView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog fdlg(true);
	fdlg.DoModal(); 
	m_SavePath = fdlg.GetPathName();
	m_SaveImg.LoadBMP(fdlg.GetPathName());
	m_ConvertImg = m_SaveImg;

	Invalidate();
	
}

void CbaltoshopView::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_SaveImg = m_ConvertImg;
	m_SaveImg.WriteBMP(m_SavePath);
}

void CbaltoshopView::OnFileSaveAs()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_SaveImg = m_ConvertImg;
	CFileDialog fdlg(true);
	fdlg.DoModal(); 
	if(m_SaveImg.WriteBMP(fdlg.GetPathName()))
		m_SavePath = fdlg.GetPathName();
	else
		AfxMessageBox(TEXT("저장 실패"));
	
}

void CbaltoshopView::OnPeditLrotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.LeftR();
	Invalidate();
}

void CbaltoshopView::OnPeditRrotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.RightR();
	Invalidate();

}

void CbaltoshopView::OnPeditBdown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.DownBlue();
	Invalidate();
}

void CbaltoshopView::OnPeditGdown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.DownGreen();
	Invalidate();
}

void CbaltoshopView::OnPeditRdown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.DownRed();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpB()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.UpBlue();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpG()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.UpGreen();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpR()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ConvertImg.UpRed();
	Invalidate();
}
void CbaltoshopView::OnRgbeditRgbeditdialog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	/*if(m_Dlg ==  NULL)
	{
		m_Dlg = new CDlgRGBControll();
		m_Dlg->Create(IDD_DIALOG_GRBCONTROL);
		m_Dlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Dlg->ShowWindow(SW_SHOW);
	}

	m_ConvertImg.AddColor(m_Dlg->m_Red, m_Dlg->m_Green, m_Dlg->m_Blue);
	Invalidate();*/

	if(m_Dlg == NULL)
	{
		m_Dlg = new CDlgRGBControll();
	}
	if(m_Dlg->DoModal() == IDOK)
	{
		m_ConvertImg.AddColor(m_Dlg->m_Red, m_Dlg->m_Green, m_Dlg->m_Blue);
		Invalidate();
	}
}
