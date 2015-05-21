
// 3_menuView.h : CMy3_menuView 클래스의 인터페이스
//


#pragma once


class CMy3_menuView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy3_menuView();
	DECLARE_DYNCREATE(CMy3_menuView)

// 특성입니다.
public:
	CMy3_menuDoc* GetDocument() const;

// 작업입니다.
public:
	
	COLORREF m_color; 

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy3_menuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // 3_menuView.cpp의 디버그 버전
inline CMy3_menuDoc* CMy3_menuView::GetDocument() const
   { return reinterpret_cast<CMy3_menuDoc*>(m_pDocument); }
#endif

