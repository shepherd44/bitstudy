
// baltoshopView.h : CbaltoshopView Ŭ������ �������̽�
//


#pragma once


class CbaltoshopView : public CView
{
protected: // serialization������ ��������ϴ�.
	CbaltoshopView();
	DECLARE_DYNCREATE(CbaltoshopView)

// Ư���Դϴ�.
public:
	CbaltoshopDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	Img m_SaveImg;
	Img m_ConvertImg;
	CString m_SavePath;
	double m_ImgRatio;

	CDlgRGBControll* m_Dlg;

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
	virtual ~CbaltoshopView();
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

#ifndef _DEBUG  // baltoshopView.cpp�� ����� ����
inline CbaltoshopDoc* CbaltoshopView::GetDocument() const
   { return reinterpret_cast<CbaltoshopDoc*>(m_pDocument); }
#endif

