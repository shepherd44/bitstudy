// DlgProperty.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "DlgProperty.h"
#include "afxdialogex.h"


// CDlgProperty ��ȭ �����Դϴ�.

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


// CDlgProperty �޽��� ó�����Դϴ�.


BOOL CDlgProperty::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CPropertySheet MySheet;

	CPropertyList Page1;
	CPropertyPreview Page2;
	CPropertyRGB Page3;
	MySheet.AddPage(&Page1);
	MySheet.AddPage(&Page2);
	MySheet.AddPage(&Page3);

	MySheet.DoModal();


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
