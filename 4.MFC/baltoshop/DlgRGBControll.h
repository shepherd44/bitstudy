#pragma once
#include "afxcmn.h"
#include "baltoshop.h"


// CDlgRGBControll ��ȭ �����Դϴ�.

class CDlgRGBControll : public CDialog
{
	DECLARE_DYNAMIC(CDlgRGBControll)

public:
	CDlgRGBControll(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgRGBControll();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_GRBCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_Red;
	int m_Green;
	int m_Blue;
	CSliderCtrl m_SliderRed;
	CSliderCtrl m_SliderGreen;
	CSliderCtrl m_SliderBlue;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
};
