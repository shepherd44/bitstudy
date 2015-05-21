
// ImgLibView.h : CImgLibView Ŭ������ �������̽�
//


#pragma once

#include "img.h"

class CImgLibView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImgLibView();
	DECLARE_DYNCREATE(CImgLibView)

// Ư���Դϴ�.
public:
	CImgLibDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	Img m_img;

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
	virtual ~CImgLibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnBinary();
};

#ifndef _DEBUG  // ImgLibView.cpp�� ����� ����
inline CImgLibDoc* CImgLibView::GetDocument() const
   { return reinterpret_cast<CImgLibDoc*>(m_pDocument); }
#endif

