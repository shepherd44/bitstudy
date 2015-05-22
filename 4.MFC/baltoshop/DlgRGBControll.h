#pragma once
#include "afxcmn.h"
#include "baltoshop.h"


// CDlgRGBControll 대화 상자입니다.

class CDlgRGBControll : public CDialog
{
	DECLARE_DYNAMIC(CDlgRGBControll)

public:
	CDlgRGBControll(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgRGBControll();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_GRBCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
