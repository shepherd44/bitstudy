
// 2_KeyBoardView.h : CMy2_KeyBoardView Ŭ������ �������̽�
//
#pragma once


class CMy2_KeyBoardView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy2_KeyBoardView();
	DECLARE_DYNCREATE(CMy2_KeyBoardView)

// Ư���Դϴ�.
public:
	CMy2_KeyBoardDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CPoint pCaret; 

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy2_KeyBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

#ifndef _DEBUG  // 2_KeyBoardView.cpp�� ����� ����
inline CMy2_KeyBoardDoc* CMy2_KeyBoardView::GetDocument() const
   { return reinterpret_cast<CMy2_KeyBoardDoc*>(m_pDocument); }
#endif


