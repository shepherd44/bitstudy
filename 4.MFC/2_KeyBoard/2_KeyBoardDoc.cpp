
// 2_KeyBoardDoc.cpp : CMy2_KeyBoardDoc Ŭ������ ����
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


// CMy2_KeyBoardDoc ����/�Ҹ�

CMy2_KeyBoardDoc::CMy2_KeyBoardDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMy2_KeyBoardDoc::~CMy2_KeyBoardDoc()
{
}

BOOL CMy2_KeyBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMy2_KeyBoardDoc serialization

void CMy2_KeyBoardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{		
		// save ����
		m_Text.Serialize(ar);
		//POSITION p =  m_list.GetHeadPosition(); 	
		//for( int i = 0; i< m_list.GetCount(); i++) 
		//{	
		//	// ar <<  m_list.GetNext( p );   // << �����ε� : �⺻ Ÿ��, CString
		//	CString str = m_list.GetNext(p); 
		//	str.AppendChar(L"\r\n");
		//	ar.WriteString( str );
		//}
	}
	else
	{
	
	}
}


// CMy2_KeyBoardDoc ����

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


// CMy2_KeyBoardDoc ���
