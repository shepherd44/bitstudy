// DlgModalessex.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "DlgModalessex.h"
#include "afxdialogex.h"


// CDlgModalessex 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgModalessex, CDialog)

CDlgModalessex::CDlgModalessex(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModalessex::IDD, pParent)
	, m_EditX(0)
	, m_EditY(0)
	, m_EditRed(0)
	, m_EditGreen(0)
	, m_EditBlue(0)
{

}

CDlgModalessex::~CDlgModalessex()
{
}

void CDlgModalessex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_EditX);
	DDX_Text(pDX, IDC_EDIT_Y, m_EditY);
	DDX_Text(pDX, IDC_EDIT_RED, m_EditRed);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_EditGreen);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_EditBlue);
	DDX_Control(pDX, IDC_PB_RGB, m_PBRGB);
}


BEGIN_MESSAGE_MAP(CDlgModalessex, CDialog)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgModalessex 메시지 처리기입니다.


void CDlgModalessex::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_EditX = point.x;
	m_EditY = point.y;

	CClientDC dc(this);
	m_color = dc.GetPixel(point);
	
	m_EditRed = (m_color & 0x00FF0000) >> 16;
	m_EditGreen = (m_color & 0x0000FF00) >> 8;
	m_EditBlue = (m_color & 0x000000FF);

	CDC* cdc = m_PBRGB.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	CBrush br(m_color);
	cdc->FillRect(&rect, &br);


	CWnd* hWnd = GetParent()->GetDlgItem(IDC_PBRGBMAIN);

	CDC* pdc = GetParent()->GetDlgItem(IDC_PBRGBMAIN)->GetWindowDC();
	pdc->FillRect(&rect, &br);
	
	
	UpdateData(false);
	CDialog::OnMouseMove(nFlags, point);
}
