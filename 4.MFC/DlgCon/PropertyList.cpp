// PropertyList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyList.h"
#include "afxdialogex.h"


// CPropertyList ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPropertyList, CPropertyPage)

CPropertyList::CPropertyList()
	: CPropertyPage(CPropertyList::IDD)
{

}

CPropertyList::~CPropertyList()
{
}

void CPropertyList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyList, CPropertyPage)
END_MESSAGE_MAP()


// CPropertyList �޽��� ó�����Դϴ�.
