
// baltoshopView.h : CbaltoshopView 클래스의 인터페이스
//


#pragma once


class CbaltoshopView : public CView
{
protected: // serialization에서만 만들어집니다.
	CbaltoshopView();
	DECLARE_DYNCREATE(CbaltoshopView)

// 특성입니다.
public:
	CbaltoshopDoc* GetDocument() const;

// 작업입니다.
public:
	Img m_SaveImg;
	Img m_ConvertImg;
	CString m_SavePath;
	double m_ImgRatio;

	CDlgRGBControll* m_Dlg;

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
	virtual ~CbaltoshopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnPeditLrotate();
	afx_msg void OnPeditRrotate();
	afx_msg void OnPeditBdown();
	afx_msg void OnPeditGdown();
	afx_msg void OnPeditRdown();
	afx_msg void OnRgbeditUpB();
	afx_msg void OnRgbeditUpG();
	afx_msg void OnRgbeditUpR();
	afx_msg void OnRgbeditRgbeditdialog();
};

#ifndef _DEBUG  // baltoshopView.cpp의 디버그 버전
inline CbaltoshopDoc* CbaltoshopView::GetDocument() const
   { return reinterpret_cast<CbaltoshopDoc*>(m_pDocument); }
#endif

