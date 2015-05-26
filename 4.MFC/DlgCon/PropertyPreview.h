#pragma once
#include "afxcmn.h"


// CPropertyPreview 대화 상자입니다.

class CPropertyPreview : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPreview)

public:
	CPropertyPreview();
	virtual ~CPropertyPreview();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPPAGE_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_EditSpin;
	CSpinButtonCtrl m_Spin;
	CProgressCtrl m_Progress;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSpin();
};
