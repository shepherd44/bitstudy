
// 3_menu.h : 3_menu ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy3_menuApp:
// �� Ŭ������ ������ ���ؼ��� 3_menu.cpp�� �����Ͻʽÿ�.
//

class CMy3_menuApp : public CWinApp
{
public:
	CMy3_menuApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3_menuApp theApp;
