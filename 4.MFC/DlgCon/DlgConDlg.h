
// DlgConDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CDlgConDlg ��ȭ ����
class CDlgConDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CDlgConDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLGCON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModal();
	CString m_EditMovieHit;
	CStatic m_PBRGBMain;
	afx_msg void OnBnClickedBtnModaless();
	CDlgModalessex* m_pDlgModless;
	afx_msg void OnDestroy();
	POINTS m_pt;
	afx_msg void OnBnClickedBtnRes();
	afx_msg void OnBnClickedBtnWizard();
};
