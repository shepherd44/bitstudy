#pragma once
#include "afxcmn.h"


// CPropertyPreview ��ȭ �����Դϴ�.

class CPropertyPreview : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyPreview)

public:
	CPropertyPreview();
	virtual ~CPropertyPreview();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROPPAGE_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_EditSpin;
	CSpinButtonCtrl m_Spin;
	CProgressCtrl m_Progress;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSpin();
};
