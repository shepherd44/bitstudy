
// AniDoc.cpp : CAniDoc Ŭ������ ����
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


// CAniDoc ����/�Ҹ�

CAniDoc::CAniDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CAniDoc::~CAniDoc()
{
}

BOOL CAniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CAniDoc serialization

void CAniDoc::Serialize(CArchive& ar)
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


// CAniDoc ����

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


// CAniDoc ���
