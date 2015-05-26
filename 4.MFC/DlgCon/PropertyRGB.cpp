// PropertyRGB.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyRGB.h"
#include "afxdialogex.h"


// CPropertyRGB 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyRGB, CPropertyPage)

CPropertyRGB::CPropertyRGB()
	: CPropertyPage(CPropertyRGB::IDD)
	, m_EditR2(0)
	, m_EditG2(0)
	, m_EditB2(0)
{

}

CPropertyRGB::~CPropertyRGB()
{
}

void CPropertyRGB::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_R2, m_SliderR2);
	DDX_Control(pDX, IDC_SLIDER_G2, m_SliderG2);
	DDX_Control(pDX, IDC_SLIDER_B2, m_SliderB2);
	DDX_Text(pDX, IDC_EDIT_R2, m_EditR2);
	DDX_Text(pDX, IDC_EDIT_G2, m_EditG2);
	DDX_Text(pDX, IDC_EDIT_B2, m_EditB2);
	DDX_Control(pDX, IDC_PB_RECT2, m_PBRGBBox2);
}


BEGIN_MESSAGE_MAP(CPropertyRGB, CPropertyPage)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_R2, &CPropertyRGB::OnNMReleasedcaptureSliderR2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_G2, &CPropertyRGB::OnNMReleasedcaptureSliderG2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_B2, &CPropertyRGB::OnNMReleasedcaptureSliderB2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_R2, &CPropertyRGB::OnNMCustomdrawSliderR2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_G2, &CPropertyRGB::OnNMCustomdrawSliderG2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_B2, &CPropertyRGB::OnNMCustomdrawSliderB2)
END_MESSAGE_MAP()


// CPropertyRGB 메시지 처리기입니다.


void CPropertyRGB::OnNMReleasedcaptureSliderR2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData();
	m_EditR2 = m_SliderR2.GetPos();
	UpdateData(false);
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);
	
	CBrush br(cr);
	pDC->FillRect(&rect, &br);
}


void CPropertyRGB::OnNMReleasedcaptureSliderG2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	m_EditG2 = m_SliderG2.GetPos();
	UpdateData(false);
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
}


void CPropertyRGB::OnNMReleasedcaptureSliderB2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditB2 = m_SliderB2.GetPos();
	UpdateData(false);
	*pResult = 0;
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
}


BOOL CPropertyRGB::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_SliderR2.SetRange(0, 255);
	m_SliderG2.SetRange(0, 255);
	m_SliderB2.SetRange(0, 255);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPropertyRGB::OnNMCustomdrawSliderR2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditR2 = m_SliderR2.GetPos();
	UpdateData(false);
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
	*pResult = 0;
}


void CPropertyRGB::OnNMCustomdrawSliderG2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditG2 = m_SliderG2.GetPos();
	UpdateData(false);
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
	*pResult = 0;
}


void CPropertyRGB::OnNMCustomdrawSliderB2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.UpdateData();
	m_EditB2 = m_SliderB2.GetPos();
	UpdateData(false);
	*pResult = 0;
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
}
