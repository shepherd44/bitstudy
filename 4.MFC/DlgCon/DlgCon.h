
// DlgCon.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDlgConApp:
// �� Ŭ������ ������ ���ؼ��� DlgCon.cpp�� �����Ͻʽÿ�.
//

class CDlgConApp : public CWinApp
{
public:
	CDlgConApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDlgConApp theApp;