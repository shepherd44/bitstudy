#pragma once


// CDlgProperty ��ȭ �����Դϴ�.

class CDlgProperty : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgProperty)

public:
	CDlgProperty();
	virtual ~CDlgProperty();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
