
// baltoshopDoc.cpp : CbaltoshopDoc Ŭ������ ����
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


// CbaltoshopDoc ����/�Ҹ�

CbaltoshopDoc::CbaltoshopDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CbaltoshopDoc::~CbaltoshopDoc()
{
}

BOOL CbaltoshopDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CbaltoshopDoc serialization

void CbaltoshopDoc::Serialize(CArchive& ar)
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


// CbaltoshopDoc ����

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


// CbaltoshopDoc ���

//void CbaltoshopDoc::OnFileOpen()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	CFileDialog fdlg(true);
//	fdlg.DoModal(); 
//	
//	m_LoadImg.LoadBMP(fdlg.GetPathName()) ;
//	m_ConvertImg = m_LoadImg;
//	
//}
