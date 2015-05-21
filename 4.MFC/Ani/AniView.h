
// AniView.h : CAniView 클래스의 인터페이스
//


#pragma once


class CAniView : public CView
{
protected: // serialization에서만 만들어집니다.
	CAniView();
	DECLARE_DYNCREATE(CAniView)

// 특성입니다.
public:
	CAniDoc* GetDocument() const;

// 작업입니다.
public:
	double View; 
	int interval; 
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
	virtual ~CAniView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawBitmap(CDC* dc, UINT nID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// // 현재 타이머 정보 
	int m_Snap;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // AniView.cpp의 디버그 버전
inline CAniDoc* CAniView::GetDocument() const
   { return reinterpret_cast<CAniDoc*>(m_pDocument); }
#endif

