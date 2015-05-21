
// bmpView.h : CbmpView Ŭ������ �������̽�
//


#pragma once


class CbmpView : public CView
{
protected: // serialization������ ��������ϴ�.
	CbmpView();
	DECLARE_DYNCREATE(CbmpView)

// Ư���Դϴ�.
public:
	CbmpDoc* GetDocument() const;
	
// �۾��Դϴ�.
public:
	double View; 

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
	virtual ~CbmpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawBitmap(CDC* dc);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // bmpView.cpp�� ����� ����
inline CbmpDoc* CbmpView::GetDocument() const
   { return reinterpret_cast<CbmpDoc*>(m_pDocument); }
#endif

