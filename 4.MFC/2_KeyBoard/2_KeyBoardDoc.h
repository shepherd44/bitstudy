
// 2_KeyBoardDoc.h : CMy2_KeyBoardDoc Ŭ������ �������̽�
//


#pragma once


class CMy2_KeyBoardDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMy2_KeyBoardDoc();
	DECLARE_DYNCREATE(CMy2_KeyBoardDoc)

// Ư���Դϴ�.
public:
	CList<CString> m_list;
	CText m_Text;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CMy2_KeyBoardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


