// PropertyPreview.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyPreview.h"
#include "afxdialogex.h"


// CPropertyPreview ��ȭ �����Դϴ�.

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


// CPropertyPreview �޽��� ó�����Դϴ�.


BOOL CPropertyPreview::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Progress.SetRange(0, 20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CPropertyPreview::OnNMReleasedcaptureSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	*pResult = 0;
}


void CPropertyPreview::OnEnChangeEditSpin()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CPropertyPage::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();

	UpdateData(false);
}
