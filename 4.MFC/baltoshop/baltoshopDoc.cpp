
// baltoshopDoc.cpp : CbaltoshopDoc 클래스의 구현
//

#include "stdafx.h"
#include "baltoshop.h"

#include "baltoshopDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbaltoshopDoc

IMPLEMENT_DYNCREATE(CbaltoshopDoc, CDocument)

BEGIN_MESSAGE_MAP(CbaltoshopDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CbaltoshopDoc::OnFileOpen)
END_MESSAGE_MAP()


// CbaltoshopDoc 생성/소멸

CbaltoshopDoc::CbaltoshopDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CbaltoshopDoc::~CbaltoshopDoc()
{
}

BOOL CbaltoshopDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CbaltoshopDoc serialization

void CbaltoshopDoc::Serialize(CArchive& ar)
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


// CbaltoshopDoc 진단

#ifdef _DEBUG
void CbaltoshopDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CbaltoshopDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CbaltoshopDoc 명령

//void CbaltoshopDoc::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CFileDialog fdlg(true);
//	fdlg.DoModal(); 
//	
//	m_LoadImg.LoadBMP(fdlg.GetPathName()) ;
//	m_ConvertImg = m_LoadImg;
//	
//}
