
// ImgLibDoc.cpp : CImgLibDoc Ŭ������ ����
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


// CImgLibDoc ����/�Ҹ�

CImgLibDoc::CImgLibDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImgLibDoc::~CImgLibDoc()
{
}

BOOL CImgLibDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImgLibDoc serialization

void CImgLibDoc::Serialize(CArchive& ar)
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


// CImgLibDoc ����

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


// CImgLibDoc ���
