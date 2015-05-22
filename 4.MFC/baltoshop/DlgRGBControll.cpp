// DlgRGBControll.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "baltoshop.h"
#include "DlgRGBControll.h"


// CDlgRGBControll 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRGBControll, CDialog)

CDlgRGBControll::CDlgRGBControll(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRGBControll::IDD, pParent)
	, m_Red(0)
	, m_Green(0)
	, m_Blue(0)
{

}

CDlgRGBControll::~CDlgRGBControll()
{
}

void CDlgRGBControll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RED, m_Red);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_Green);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_Blue);
	DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
}


BEGIN_MESSAGE_MAP(CDlgRGBControll, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDlgRGBControll::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRGBControll 메시지 처리기입니다.

int CDlgRGBControll::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

void CDlgRGBControll::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
