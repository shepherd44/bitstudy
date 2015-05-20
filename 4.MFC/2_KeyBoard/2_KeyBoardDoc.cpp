
// 2_KeyBoardDoc.cpp : CMy2_KeyBoardDoc 클래스의 구현
//

#include "stdafx.h"
#include "2_KeyBoard.h"

#include "2_KeyBoardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2_KeyBoardDoc

IMPLEMENT_DYNCREATE(CMy2_KeyBoardDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy2_KeyBoardDoc, CDocument)
END_MESSAGE_MAP()


// CMy2_KeyBoardDoc 생성/소멸

CMy2_KeyBoardDoc::CMy2_KeyBoardDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy2_KeyBoardDoc::~CMy2_KeyBoardDoc()
{
}

BOOL CMy2_KeyBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy2_KeyBoardDoc serialization

void CMy2_KeyBoardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{		
		// save 저장
		m_Text.Serialize(ar);
		//POSITION p =  m_list.GetHeadPosition(); 	
		//for( int i = 0; i< m_list.GetCount(); i++) 
		//{	
		//	// ar <<  m_list.GetNext( p );   // << 오버로딩 : 기본 타입, CString
		//	CString str = m_list.GetNext(p); 
		//	str.AppendChar(L"\r\n");
		//	ar.WriteString( str );
		//}
	}
	else
	{
	
	}
}


// CMy2_KeyBoardDoc 진단

#ifdef _DEBUG
void CMy2_KeyBoardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2_KeyBoardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2_KeyBoardDoc 명령
