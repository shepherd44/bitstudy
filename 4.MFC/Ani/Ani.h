
// Ani.h : Ani ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CAniApp:
// �� Ŭ������ ������ ���ؼ��� Ani.cpp�� �����Ͻʽÿ�.
//

class CAniApp : public CWinApp
{
public:
	CAniApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAniApp theApp;
