// DlgModalex.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "DlgModalex.h"
#include "afxdialogex.h"


// CDlgModalex 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgModalex, CDialog)

CDlgModalex::CDlgModalex(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModalex::IDD, pParent)
	, m_EditMo1(_T(""))
	, m_EditMo2(_T(""))
	, m_EditMo3(_T(""))
	, m_EditMo4(_T(""))
	, m_EditMo5(_T(""))
	, m_EditMo6(_T(""))
	, m_EditMo7(_T(""))
	, m_EditMo8(_T(""))
	, m_EditCombo(_T(""))
	, m_EditList(_T(""))
	, m_EditMovieHit2(_T(""))
	, m_RadioBat1(0)
{
	
}

CDlgModalex::~CDlgModalex()
{
}

void CDlgModalex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MO1, m_EditMo1);
	DDX_Text(pDX, IDC_EDIT_MO2, m_EditMo2);
	DDX_Text(pDX, IDC_EDIT_MO3, m_EditMo3);
	DDX_Text(pDX, IDC_EDIT_MO4, m_EditMo4);
	DDX_Text(pDX, IDC_EDIT_MO5, m_EditMo5);
	DDX_Text(pDX, IDC_EDIT_MO6, m_EditMo6);
	DDX_Text(pDX, IDC_EDIT_MO7, m_EditMo7);
	DDX_Text(pDX, IDC_EDIT_MO8, m_EditMo8);
	DDX_Text(pDX, IDC_EDIT_COMBO, m_EditCombo);
	DDX_Text(pDX, IDC_EDIT_LIST, m_EditList);
	DDX_Control(pDX, IDC_COMBO, m_Combo);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT_MOVIEHIT2, m_EditMovieHit2);
	DDX_Control(pDX, IDC_SLIDER_MOVIE, m_SliderMoviehit);
	DDX_Control(pDX, IDC_PB_BAT, m_PBBat);
	DDX_Radio(pDX, IDC_RADIO_BAT1, m_RadioBat1);
}


BEGIN_MESSAGE_MAP(CDlgModalex, CDialog)
	ON_BN_CLICKED(IDC_BTN_MO1, &CDlgModalex::OnBnClickedBtnMo1)
	ON_BN_CLICKED(IDC_BTN_MO2, &CDlgModalex::OnBnClickedBtnMo2)
	ON_BN_CLICKED(IDC_BTN_MO3, &CDlgModalex::OnBnClickedBtnMo3)
	ON_BN_CLICKED(IDC_BTN_MO4, &CDlgModalex::OnBnClickedBtnMo4)
	ON_BN_CLICKED(IDC_BTN_ADDCOMBO, &CDlgModalex::OnBnClickedBtnAddcombo)
	ON_BN_CLICKED(IDC_BTN_ADDLIST, &CDlgModalex::OnBnClickedBtnAddlist)
	ON_LBN_DBLCLK(IDC_LIST, &CDlgModalex::OnLbnDblclkList)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_MOVIE, &CDlgModalex::OnTRBNThumbPosChangingSliderMovie)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MOVIE, &CDlgModalex::OnNMCustomdrawSliderMovie)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_MOVIE, &CDlgModalex::OnNMReleasedcaptureSliderMovie)
	ON_BN_CLICKED(IDOK, &CDlgModalex::OnBnClickedOk)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_BAT1, IDC_RADIO_BAT2, CDlgModalex::SetRadioStatus)
END_MESSAGE_MAP()


// CDlgModalex 메시지 처리기입니다.


void CDlgModalex::OnBnClickedBtnMo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditMo5 = m_EditMo1;
	UpdateData(false);
	
}


void CDlgModalex::OnBnClickedBtnMo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditMo6 = m_EditMo2;
	UpdateData(false);
}


void CDlgModalex::OnBnClickedBtnMo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditMo7 = m_EditMo3;
	UpdateData(false);
}


void CDlgModalex::OnBnClickedBtnMo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_EditMo8 = m_EditMo4;
	UpdateData(false);
}


void CDlgModalex::OnBnClickedBtnAddcombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_Combo.AddString(m_EditMo5);
	m_Combo.AddString(m_EditMo6);
	m_Combo.AddString(m_EditMo7);
	m_Combo.AddString(m_EditMo8);
	UpdateData(false);
}



void CDlgModalex::OnBnClickedBtnAddlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	m_List.AddString(m_EditMo5);
	m_List.AddString(m_EditMo6);
	m_List.AddString(m_EditMo7);
	m_List.AddString(m_EditMo8);
	UpdateData(false);
}


void CDlgModalex::OnLbnDblclkList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	int index = m_List.GetCaretIndex();
	m_List.GetText(index, m_EditList);
	UpdateData(false);
}


void CDlgModalex::OnTRBNThumbPosChangingSliderMovie(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	m_EditMovieHit2.Format(L"%d%", m_SliderMoviehit.GetPos());
	UpdateData(false);

}


BOOL CDlgModalex::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
	m_SliderMoviehit.SetRange(0, 100);

	UpdateData();
}


void CDlgModalex::OnNMCustomdrawSliderMovie(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	int a = m_SliderMoviehit.GetPos();
	m_EditMovieHit2.Format(L"%d%%", a);
	UpdateData(false);
}


void CDlgModalex::OnNMReleasedcaptureSliderMovie(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	int a = m_SliderMoviehit.GetPos();
	m_EditMovieHit2.Format(L"%d%%", a);
	UpdateData(false);
}


void CDlgModalex::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* hWnd = GetParent();
	hWnd->SetDlgItemTextW(IDC_EDIT_MOVIEHIT, m_EditMovieHit2);

	CDialog::OnOK();
}


void CDlgModalex::SetRadioStatus(UINT value)
{
	UpdateData(TRUE);
	CBitmap temp;
	switch (m_RadioBat1)
	{
	case 0:
		temp.LoadBitmap(IDB_BMP_BATMAN);
		m_PBBat.SetBitmap(temp);
		break;
	case 1:
		temp.LoadBitmap(IDB_BMP_BATGIRL);
		m_PBBat.SetBitmap(temp);
		break;
	}
	UpdateData(false);
}