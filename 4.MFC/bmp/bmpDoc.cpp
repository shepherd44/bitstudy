
// bmpDoc.cpp : CbmpDoc Ŭ������ ����
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


// CbmpDoc ����/�Ҹ�

CbmpDoc::CbmpDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CbmpDoc::~CbmpDoc()
{
}

BOOL CbmpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CbmpDoc serialization

void CbmpDoc::Serialize(CArchive& ar)
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


// CbmpDoc ����

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


// CbmpDoc ���
