#pragma once
#include "resource.h"
#include "afxwin.h"

// CDlgModalessex ��ȭ �����Դϴ�.

class CDlgModalessex : public CDialog
{
	DECLARE_DYNAMIC(CDlgModalessex)

public:
	CDlgModalessex(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgModalessex();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_MODALESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
