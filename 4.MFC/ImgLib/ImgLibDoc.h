
// ImgLibDoc.h : CImgLibDoc Ŭ������ �������̽�
//


#pragma once


class CImgLibDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImgLibDoc();
	DECLARE_DYNCREATE(CImgLibDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CImgLibDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


