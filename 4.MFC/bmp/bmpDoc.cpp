
// bmpDoc.cpp : CbmpDoc 클래스의 구현
//

#include "stdafx.h"
#include "bmp.h"

#include "bmpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbmpDoc

IMPLEMENT_DYNCREATE(CbmpDoc, CDocument)

BEGIN_MESSAGE_MAP(CbmpDoc, CDocument)
END_MESSAGE_MAP()


// CbmpDoc 생성/소멸

CbmpDoc::CbmpDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CbmpDoc::~CbmpDoc()
{
}

BOOL CbmpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CbmpDoc serialization

void CbmpDoc::Serialize(CArchive& ar)
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


// CbmpDoc 진단

#ifdef _DEBUG
void CbmpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CbmpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CbmpDoc 명령
