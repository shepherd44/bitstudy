
// AniDoc.h : CAniDoc Ŭ������ �������̽�
//


#pragma once


class CAniDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAniDoc();
	DECLARE_DYNCREATE(CAniDoc)

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
	virtual ~CAniDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


