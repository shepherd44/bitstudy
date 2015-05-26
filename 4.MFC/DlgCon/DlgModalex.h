#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"


// CDlgModalex 대화 상자입니다.

class CDlgModalex : public CDialog
{
	DECLARE_DYNAMIC(CDlgModalex)

public:
	CDlgModalex(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgModalex();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MODAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditMo1;
	CString m_EditMo2;
	CString m_EditMo3;
	CString m_EditMo4;
	CString m_EditMo5;
	CString m_EditMo6;
	CString m_EditMo7;
	CString m_EditMo8;
	afx_msg void OnBnClickedBtnMo1();
	afx_msg void OnBnClickedBtnMo2();
	afx_msg void OnBnClickedBtnMo3();
	afx_msg void OnBnClickedBtnMo4();
	CString m_EditCombo;
	CString m_EditList;
	afx_msg void OnBnClickedBtnAddcombo();
	CComboBox m_Combo;
	CListBox m_List;
	afx_msg void OnBnClickedBtnAddlist();
	CString m_EditMovieHit2;
	CSliderCtrl m_SliderMoviehit;
	afx_msg void OnLbnDblclkList();
	afx_msg void OnTRBNThumbPosChangingSliderMovie(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderMovie(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderMovie(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	CStatic m_PBBat;
	int m_RadioBat1;
	void SetRadioStatus(UINT value);
};
