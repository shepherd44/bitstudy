// PropertyPreview.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyPreview.h"
#include "afxdialogex.h"


// CPropertyPreview 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPropertyPreview, CPropertyPage)

CPropertyPreview::CPropertyPreview()
	: CPropertyPage(CPropertyPreview::IDD)
	, m_EditSpin(0)
{

}

CPropertyPreview::~CPropertyPreview()
{
}

void CPropertyPreview::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SPIN, m_EditSpin);
	DDX_Control(pDX, IDC_SPIN, m_Spin);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}


BEGIN_MESSAGE_MAP(CPropertyPreview, CPropertyPage)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SPIN, &CPropertyPreview::OnNMReleasedcaptureSpin)
	ON_EN_CHANGE(IDC_EDIT_SPIN, &CPropertyPreview::OnEnChangeEditSpin)
END_MESSAGE_MAP()


// CPropertyPreview 메시지 처리기입니다.


BOOL CPropertyPreview::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Progress.SetRange(0, 20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPropertyPreview::OnNMReleasedcaptureSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	*pResult = 0;
}


void CPropertyPreview::OnEnChangeEditSpin()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	UpdateData(false);
}
