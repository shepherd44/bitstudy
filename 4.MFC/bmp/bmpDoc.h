
// bmpDoc.h : CbmpDoc Ŭ������ �������̽�
//


#pragma once


class CbmpDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CbmpDoc();
	DECLARE_DYNCREATE(CbmpDoc)

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
	virtual ~CbmpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


