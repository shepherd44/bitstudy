#pragma once


// CDlgProperty 대화 상자입니다.

class CDlgProperty : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgProperty)

public:
	CDlgProperty();
	virtual ~CDlgProperty();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
