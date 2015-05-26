#pragma once
#include "resource.h"
#include "afxwin.h"

// CDlgModalessex 대화 상자입니다.

class CDlgModalessex : public CDialog
{
	DECLARE_DYNAMIC(CDlgModalessex)

public:
	CDlgModalessex(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgModalessex();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MODALESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_EditX;
	int m_EditY;
	UINT m_EditRed;
	UINT m_EditGreen;
	UINT m_EditBlue;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	COLORREF m_color;
	CStatic m_PBRGB;
};
