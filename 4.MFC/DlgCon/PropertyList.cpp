// PropertyList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgCon.h"
#include "PropertyList.h"
#include "afxdialogex.h"


// CPropertyList 대화 상자입니다.

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


// CPropertyList 메시지 처리기입니다.
