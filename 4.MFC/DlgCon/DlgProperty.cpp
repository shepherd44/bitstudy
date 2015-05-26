// DlgProperty.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "DlgProperty.h"
#include "afxdialogex.h"


// CDlgProperty 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgProperty, CPropertyPage)

CDlgProperty::CDlgProperty()
	: CPropertyPage(CDlgProperty::IDD)
{

}

CDlgProperty::~CDlgProperty()
{
}

void CDlgProperty::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProperty, CPropertyPage)
END_MESSAGE_MAP()


// CDlgProperty 메시지 처리기입니다.


BOOL CDlgProperty::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CPropertySheet MySheet;

	CPropertyList Page1;
	CPropertyPreview Page2;
	CPropertyRGB Page3;
	MySheet.AddPage(&Page1);
	MySheet.AddPage(&Page2);
	MySheet.AddPage(&Page3);

	MySheet.DoModal();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
