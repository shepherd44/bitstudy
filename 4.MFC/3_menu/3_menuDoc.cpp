
// 3_menuDoc.cpp : CMy3_menuDoc Ŭ������ ����
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


// CMy3_menuDoc ����/�Ҹ�

CMy3_menuDoc::CMy3_menuDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMy3_menuDoc::~CMy3_menuDoc()
{
}

BOOL CMy3_menuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMy3_menuDoc serialization

void CMy3_menuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CMy3_menuDoc ����

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


// CMy3_menuDoc ���
