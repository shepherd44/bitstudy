
// baltoshopDoc.h : CbaltoshopDoc Ŭ������ �������̽�
//


#pragma once


class CbaltoshopDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CbaltoshopDoc();
	DECLARE_DYNCREATE(CbaltoshopDoc)

// Ư���Դϴ�.
public:
	Img m_SaveImg;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CbaltoshopDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFileOpen();
};


