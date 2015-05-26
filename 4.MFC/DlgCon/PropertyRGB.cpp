// PropertyRGB.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyRGB.h"
#include "afxdialogex.h"


// CPropertyRGB ��ȭ �����Դϴ�.

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


// CPropertyRGB �޽��� ó�����Դϴ�.


void CPropertyRGB::OnNMReleasedcaptureSliderR2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_SliderR2.SetRange(0, 255);
	m_SliderG2.SetRange(0, 255);
	m_SliderB2.SetRange(0, 255);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CPropertyRGB::OnNMCustomdrawSliderR2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.UpdateData();
	m_EditB2 = m_SliderB2.GetPos();
	UpdateData(false);
	*pResult = 0;
	CDC* pDC = m_PBRGBBox2.GetWindowDC();
	RECT rect = { 0, 0, 100, 100 };
	COLORREF cr = RGB(m_EditR2, m_EditG2, m_EditB2);

	CBrush br(cr);
	pDC->FillRect(&rect, &br);
}
