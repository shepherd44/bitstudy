#pragma once


// CPropertyList ��ȭ �����Դϴ�.

class CPropertyList : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyList)

public:
	CPropertyList();
	virtual ~CPropertyList();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROPPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
