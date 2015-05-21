
// ImgLibDoc.cpp : CImgLibDoc 클래스의 구현
//

#include "stdafx.h"
#include "ImgLib.h"

#include "ImgLibDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgLibDoc

IMPLEMENT_DYNCREATE(CImgLibDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgLibDoc, CDocument)
END_MESSAGE_MAP()


// CImgLibDoc 생성/소멸

CImgLibDoc::CImgLibDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImgLibDoc::~CImgLibDoc()
{
}

BOOL CImgLibDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImgLibDoc serialization

void CImgLibDoc::Serialize(CArchive& ar)
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


// CImgLibDoc 진단

#ifdef _DEBUG
void CImgLibDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgLibDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImgLibDoc 명령
