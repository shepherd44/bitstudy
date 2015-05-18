#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCWSTR lpszClass=L"First";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_CROSS);
	WndClass.hIcon=LoadIcon(g_hInst,(LPCWSTR)IDI_ICON1);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,
					  lpszClass,
					  WS_OVERLAPPEDWINDOW,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  NULL,
					  (HMENU)NULL,
					  hInstance,
					  NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
//----------------------------------------------
//1) 배경을 검은색
//2) 커서를 +로
//3) 아이콘을 원하는걸로
//4) WM_CHAR 입력받은 문자를 윈도우 텍스트로 변경
//5) 윈도우 크기를 CW_USEDDEFAULT
//6) HINSTANCE 를 전역변수로

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static TCHAR buf[256];
	int len;
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			TCHAR buf[256];
			wsprintf(buf, L"x : %d, y : %d", x, y);
			SetWindowText(hWnd, buf);
			return 0;
		}
	case WM_CHAR:
		{
			len = wcslen(buf);
			buf[len]=(TCHAR)wParam;
			buf[len+1]=0;
			InvalidateRect(hWnd,NULL,FALSE);
			SetWindowText(hWnd, buf);
			return 0;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}