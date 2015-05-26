#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPropertyRGB 대화 상자입니다.

class CPropertyRGB : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyRGB)

public:
	CPropertyRGB();
	virtual ~CPropertyRGB();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPPAGE_RGB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderR2;
	CSliderCtrl m_SliderG2;
	CSliderCtrl m_SliderB2;
	UINT m_EditR2;
	UINT m_EditG2;
	UINT m_EditB2;
	CStatic m_PBRGBBox2;
	afx_msg void OnNMReleasedcaptureSliderR2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderG2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderB2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderR2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderG2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderB2(NMHDR *pNMHDR, LRESULT *pResult);
};
