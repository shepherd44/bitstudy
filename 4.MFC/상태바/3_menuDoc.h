
// 3_menuDoc.h : CMy3_menuDoc Ŭ������ �������̽�
//


#pragma once


class CMy3_menuDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMy3_menuDoc();
	DECLARE_DYNCREATE(CMy3_menuDoc)

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
	virtual ~CMy3_menuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


