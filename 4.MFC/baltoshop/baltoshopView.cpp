
// baltoshopView.cpp : CbaltoshopView Ŭ������ ����
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
	// ǥ�� �μ� ����Դϴ�.
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

// CbaltoshopView ����/�Ҹ�

CbaltoshopView::CbaltoshopView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CbaltoshopView �׸���

void CbaltoshopView::OnDraw(CDC* pDC)
{
	CbaltoshopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CRect rect;
	this->GetWindowRect(&rect);
	int x = rect.Width()/2 - (m_ConvertImg.GetWidth()/2)*m_ImgRatio;
	int y = rect.Height()/2 - (m_ConvertImg.GetHeight()/2)*m_ImgRatio;
	m_ConvertImg.Draw(pDC, x, y, m_ConvertImg.GetWidth()*m_ImgRatio, m_ConvertImg.GetHeight()*m_ImgRatio);
	
}


// CbaltoshopView �μ�


void CbaltoshopView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CbaltoshopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CbaltoshopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CbaltoshopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CbaltoshopView ����

#ifdef _DEBUG
void CbaltoshopView::AssertValid() const
{
	CView::AssertValid();
}

void CbaltoshopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbaltoshopDoc* CbaltoshopView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbaltoshopDoc)));
	return (CbaltoshopDoc*)m_pDocument;
}
#endif //_DEBUG


// CbaltoshopView �޽��� ó����


BOOL CbaltoshopView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog fdlg(true);
	fdlg.DoModal(); 
	m_SavePath = fdlg.GetPathName();
	m_SaveImg.LoadBMP(fdlg.GetPathName());
	m_ConvertImg = m_SaveImg;

	Invalidate();
	
}

void CbaltoshopView::OnFileSave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_SaveImg = m_ConvertImg;
	m_SaveImg.WriteBMP(m_SavePath);
}

void CbaltoshopView::OnFileSaveAs()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_SaveImg = m_ConvertImg;
	CFileDialog fdlg(true);
	fdlg.DoModal(); 
	if(m_SaveImg.WriteBMP(fdlg.GetPathName()))
		m_SavePath = fdlg.GetPathName();
	else
		AfxMessageBox(TEXT("���� ����"));
	
}

void CbaltoshopView::OnPeditLrotate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.LeftR();
	Invalidate();
}

void CbaltoshopView::OnPeditRrotate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.RightR();
	Invalidate();

}

void CbaltoshopView::OnPeditBdown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.DownBlue();
	Invalidate();
}

void CbaltoshopView::OnPeditGdown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.DownGreen();
	Invalidate();
}

void CbaltoshopView::OnPeditRdown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.DownRed();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpB()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.UpBlue();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpG()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.UpGreen();
	Invalidate();
}

void CbaltoshopView::OnRgbeditUpR()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_ConvertImg.UpRed();
	Invalidate();
}
void CbaltoshopView::OnRgbeditRgbeditdialog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
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
