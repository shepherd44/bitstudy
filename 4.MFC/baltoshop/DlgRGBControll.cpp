// DlgRGBControll.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "baltoshop.h"
#include "DlgRGBControll.h"


// CDlgRGBControll ��ȭ �����Դϴ�.

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


// CDlgRGBControll �޽��� ó�����Դϴ�.

int CDlgRGBControll::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}

void CDlgRGBControll::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}
