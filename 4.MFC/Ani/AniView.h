
// AniView.h : CAniView Ŭ������ �������̽�
//


#pragma once


class CAniView : public CView
{
protected: // serialization������ ��������ϴ�.
	CAniView();
	DECLARE_DYNCREATE(CAniView)

// Ư���Դϴ�.
public:
	CAniDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	double View; 
	int interval; 
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
	virtual ~CAniView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawBitmap(CDC* dc, UINT nID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// // ���� Ÿ�̸� ���� 
	int m_Snap;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // AniView.cpp�� ����� ����
inline CAniDoc* CAniView::GetDocument() const
   { return reinterpret_cast<CAniDoc*>(m_pDocument); }
#endif

