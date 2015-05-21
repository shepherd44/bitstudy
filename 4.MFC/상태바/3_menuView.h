
// 3_menuView.h : CMy3_menuView Ŭ������ �������̽�
//


#pragma once


class CMy3_menuView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy3_menuView();
	DECLARE_DYNCREATE(CMy3_menuView)

// Ư���Դϴ�.
public:
	CMy3_menuDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	
	COLORREF m_color; 

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
	virtual ~CMy3_menuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBlue();
	afx_msg void OnGreen();
	afx_msg void OnRed();
	void OnColor(UINT nID);
	int m_CheckId;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 3_menuView.cpp�� ����� ����
inline CMy3_menuDoc* CMy3_menuView::GetDocument() const
   { return reinterpret_cast<CMy3_menuDoc*>(m_pDocument); }
#endif

