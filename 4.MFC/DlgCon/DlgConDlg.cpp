
// DlgConDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "DlgCon.h"
#include "DlgConDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDlgConDlg 대화 상자



CDlgConDlg::CDlgConDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConDlg::IDD, pParent)
	, m_EditMovieHit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgConDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOVIEHIT, m_EditMovieHit);
	DDX_Control(pDX, IDC_PBRGBMAIN, m_PBRGBMain);
}

BEGIN_MESSAGE_MAP(CDlgConDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MODAL, &CDlgConDlg::OnBnClickedBtnModal)
	ON_BN_CLICKED(IDC_BTN_MODALESS, &CDlgConDlg::OnBnClickedBtnModaless)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_RES, &CDlgConDlg::OnBnClickedBtnRes)
	ON_BN_CLICKED(IDC_BTN_WIZARD, &CDlgConDlg::OnBnClickedBtnWizard)
END_MESSAGE_MAP()


// CDlgConDlg 메시지 처리기

BOOL CDlgConDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pDlgModless = NULL;
	RECT rect;
	GetWindowRect(&rect);
	m_pt.x = rect.top + 400;
	m_pt.y = rect.left + 400;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDlgConDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDlgConDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDlgConDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlgConDlg::OnBnClickedBtnModal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDlgModalex Dlg;
	if (Dlg.DoModal() == IDOK)
	{
		m_EditMovieHit = Dlg.m_EditMovieHit2;
	}
	else
	{
	}
}


void CDlgConDlg::OnBnClickedBtnModaless()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDlgModless == NULL)
	{
		m_pDlgModless = new CDlgModalessex();
		m_pDlgModless->Create(IDD_DLG_MODALESS);
		m_pDlgModless->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pDlgModless->ShowWindow(SW_SHOW);
		m_pDlgModless->SetFocus();
	}
}


void CDlgConDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pDlgModless != NULL)
	{
		delete m_pDlgModless;
	}
}


void CDlgConDlg::OnBnClickedBtnRes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPropertySheet dlg;
	CPropertyPreview page1;
	CPropertyRGB page2;
	CPropertyList page3;
	dlg.AddPage(&page1);
	dlg.AddPage(&page2);
	dlg.AddPage(&page3);
	if (dlg.DoModal() == IDOK)
	{ }
	else
	{
	}
}


void CDlgConDlg::OnBnClickedBtnWizard()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
