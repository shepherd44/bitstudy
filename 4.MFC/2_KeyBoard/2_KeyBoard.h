
// 2_KeyBoard.h : 2_KeyBoard ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy2_KeyBoardApp:
// �� Ŭ������ ������ ���ؼ��� 2_KeyBoard.cpp�� �����Ͻʽÿ�.
//

class CMy2_KeyBoardApp : public CWinApp
{
public:
	CMy2_KeyBoardApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2_KeyBoardApp theApp;
