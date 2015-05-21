
// 3_menu.h : 3_menu 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CMy3_menuApp:
// 이 클래스의 구현에 대해서는 3_menu.cpp을 참조하십시오.
//

class CMy3_menuApp : public CWinApp
{
public:
	CMy3_menuApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3_menuApp theApp;
