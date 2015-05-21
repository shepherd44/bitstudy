
// AniDoc.cpp : CAniDoc 클래스의 구현
//

#include "stdafx.h"
#include "Ani.h"

#include "AniDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAniDoc

IMPLEMENT_DYNCREATE(CAniDoc, CDocument)

BEGIN_MESSAGE_MAP(CAniDoc, CDocument)
END_MESSAGE_MAP()


// CAniDoc 생성/소멸

CAniDoc::CAniDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CAniDoc::~CAniDoc()
{
}

BOOL CAniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CAniDoc serialization

void CAniDoc::Serialize(CArchive& ar)
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


// CAniDoc 진단

#ifdef _DEBUG
void CAniDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAniDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAniDoc 명령
