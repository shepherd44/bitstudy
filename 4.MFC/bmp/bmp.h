
// bmp.h : bmp ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CbmpApp:
// �� Ŭ������ ������ ���ؼ��� bmp.cpp�� �����Ͻʽÿ�.
//

class CbmpApp : public CWinApp
{
public:
	CbmpApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CbmpApp theApp;
