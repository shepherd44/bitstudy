
// 3_menuDoc.cpp : CMy3_menuDoc 클래스의 구현
//

#include "stdafx.h"
#include "3_menu.h"

#include "3_menuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3_menuDoc

IMPLEMENT_DYNCREATE(CMy3_menuDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3_menuDoc, CDocument)
END_MESSAGE_MAP()


// CMy3_menuDoc 생성/소멸

CMy3_menuDoc::CMy3_menuDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy3_menuDoc::~CMy3_menuDoc()
{
}

BOOL CMy3_menuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy3_menuDoc serialization

void CMy3_menuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CMy3_menuDoc 진단

#ifdef _DEBUG
void CMy3_menuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3_menuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy3_menuDoc 명령
