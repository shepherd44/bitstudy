#pragma once


// CPropertyList 대화 상자입니다.

class CPropertyList : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyList)

public:
	CPropertyList();
	virtual ~CPropertyList();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPPAGE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
