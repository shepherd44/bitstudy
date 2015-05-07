#if 0
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING 100

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_CROSS);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
// 계산기의 핸들을 받아와서 제어해보기
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING 100

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_CROSS);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND h;
	static RECT rect;
	static int x, y;

	switch(iMessage) {
	case WM_DESTROY:
		//SendMessage(h, WM_DESTROY, 0, 0);
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:	//윈도우가 생성될 때 발생하는 이벤트
		// 핸들 --> 각각의 윈도우를 구별하기 위한 고유의 식별자
		//	--> 윈도우 생성시 (CreateWindow) OS에 의해 부여받는다.
		h = FindWindow(TEXT("CalcFrame"), TEXT("계산기"));
		GetWindowRect(h, &rect);
		x = rect.left;
		y = rect.top;
		//	--> 생성된 윈도우의 핸들을 리턴
		return 0;
	case WM_LBUTTONDOWN:
		ShowWindow(h, SW_SHOW);
		return 0;
	case WM_RBUTTONDOWN:
		ShowWindow(h, SW_HIDE);
		return 0;
	case WM_KEYDOWN:	// 기타 나머지 자판
		{
			switch(wParam)
			{
			case VK_LEFT:
				x -= 10;
				MoveWindow(h,x, y, rect.right - rect.left, rect.bottom - rect.top, FALSE); 
				break;
			case VK_RIGHT:
				x += 10;
				MoveWindow(h,x, y, rect.right - rect.left, rect.bottom - rect.top, FALSE); 
				break;
			case VK_UP:
				y -= 10;
				MoveWindow(h,x, y, rect.right - rect.left, rect.bottom - rect.top, FALSE); 
				break;
			case VK_DOWN:
				y += 10;
				MoveWindow(h,x, y, rect.right - rect.left, rect.bottom - rect.top, FALSE); 
				break;
			}
		}
		return 0;
	case WM_CHAR:		// A~Z 문자 처리
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
// 실행 시간중에 윈도우 속성 바꾸기
//----------------------------------------------
// SetClassLong : WNDCLASS의 속성을 변결
// GetClassLong : WNDCLASS의 속성 가져오기
//----------------------------------------------
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static long preview;

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		{
			preview = GetClassLong(hWnd, GCL_HCURSOR);
			HCURSOR hCursor = LoadCursor(NULL, IDC_CROSS);
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)hCursor);
		}
		return 0;
	case WM_RBUTTONDOWN:
		{
			SetClassLong(hWnd, GCL_HCURSOR, preview);
		}
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
// 실행 시간중에 윈도우 속성 바꾸기
//----------------------------------------------
// GetWindowLong : 윈도우의 속성을 변경
// SetWindowLong : 윈도우의 속성 가져오기
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void ModifyStyle(HWND, long, long);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

void ModifyStyle(HWND hWnd, long add, long remove)
{
	long style;
	style = GetWindowLong(hWnd, GWL_STYLE);
	style = style & !remove;
	style = style | add;
	SetWindowLong(hWnd, GWL_STYLE, style);
	SetWindowPos(hWnd, 0, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		ModifyStyle(hWnd, WS_CAPTION, 0);
		return 0;
	case WM_RBUTTONDOWN:
		ModifyStyle(hWnd, 0, WS_CAPTION);
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
//  스파이 아류작 샘플
//----------------------------------------------
//
//
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static int x, y;
	static TCHAR buf[256];

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		{
			if(GetCapture() == hWnd)
			{
				POINTS pt = MAKEPOINTS(lParam);
				wsprintf(buf, TEXT("x:%d, y:%d"), pt.x, pt.y);
				SetWindowText(hWnd, buf);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		{
			SetCapture(hWnd);
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();

			HDC hdc = GetDC(hWnd);

			POINT pt;
			//현재 마우스 커서의 좌표 얻기
			GetCursorPos(&pt);
			// 해당 좌표에 있는 윈도우의 핸들을 리턴
			HWND hTemp = WindowFromPoint(pt);
			TCHAR buf[128] = {0};
			TCHAR str[128] = {0};
			wcscpy(buf, 0);
			wcscpy(str, 0);
			GetWindowText(hTemp, buf, 128);
			wsprintf(str, TEXT("핸들 : 0x%x\n캡션 : %s"), hTemp, buf);
			TextOut(hdc, 100, 100, buf, 128);
			TextOut(hdc, 100, 200, str, 128);

			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//------------------------------------------------------------------------
// windows 구성요소 !!
// - Kernel32.dll	- 메모리관리, 프로세스관리, 멀티스레딩 --> System prog
// - User32.dll		- 사용자 메뉴, 리소스들 관리
// - GDI32.dll		- UI, drawing, image 처리
//------------------------------------------------------------------------
// GDI(Graphic Device Interface)
// - OS에서 그래픽(Drawing, Image(bitmap), UI관련 컨트롤
// - GDI OBJECT: PEN, BRUSH, FONT, RGN, 
//------------------------------------------------------------------------
// DC(Device Context)
// --> 출력하고자하는 윈도우(대상)의 모든 정보를 갖는 추상화된 구조체!!
//------------------------------------------------------------------------
// DC를 얻는 방법 !!
// 1) GetDC(hwnd) : 윈도우 핸들을 넘겨서 해당 핸들의 DC를 받아온다. 
//	  ReleaseDC(hwnd, hdc) : DC 반납
// 2) BeginPaint(hwnd, PAINTSTRUCT*) : WM_PAINT에서만 사용. 나머지는 GetDC
//	  EndPaint(hwnd, PAINTSTRUCT*) : DC 반납
// 3) CreateDC() : 다른 프로그램의 DC 가져오기
//	  DeleteDC()
//------------------------------------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		{
			HDC hdc = GetDC(hWnd);	//DC 얻기
			//------------------------------------------------
			//그리기 시작
			POINTS pt = MAKEPOINTS(lParam);
			Rectangle(hdc, pt.x, pt.y, pt.x+300, pt.y+300);	// 사각형 그리기
			//------------------------------------------------
			ReleaseDC(hWnd, hdc);	//DC 반납
		}
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:	
		// 윈도우가 다시 그려야할 상황 발생 --> 무효화 영역!!
		// 무효하 영역 --> 다시 그려져야하는 영역
		// 1) 처음 윈도우가 showWindow 될때
		// 2) 최소화, 최대화(사이즈 변경이 일어날 때)
		// 3) 윈도우에서 사라졌다가 다시 나올때!!
		// 4) 스크롤이 일어날때
		// -----> 그리기 작업은 WM_PAINT에서 작성하는 경우가 대부분이다.
		// WM_PAINT를 제외한 모든 경우 GetDC
		// WM_PAINT에서만 BeginPaint, EndPaint 함수로 dc 사용
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			//ps.rcPaint --> 다시 그려져야할 영역 사각형
			
			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
// 
//----------------------------------------------
//
//
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		{
			HDC hdc = CreateDC("DISPLAY", 0, 0, 0);
			Rectangle(hdc, 100, 100, 300, 300);
			DeleteDC(hdc);
		}
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif
#if 0
//----------------------------------------------
// 실행 시간중에 윈도우 속성 바꾸기
//----------------------------------------------
//
//
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);

	if(hWnd == 0)
	{
		return FALSE;
	}

	MSG Message;
	while(1) {
		if(PeekMessage(&Message,0,0,0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
		}
	}
	return Message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX WndClassEx;
	WndClassEx.cbSize		= sizeof(WNDCLASSEX);
	WndClassEx.cbClsExtra	= 0;
	WndClassEx.cbWndExtra	= 0;
	WndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClassEx.hCursor		= LoadCursor(NULL,IDC_ARROW);
	WndClassEx.hIcon		= LoadIcon(NULL,(LPCWSTR)IDI_APPLICATION);
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= NULL;
	WndClassEx.style		= CS_HREDRAW | CS_VREDRAW;
	WndClassEx.hIconSm		= 0;
	return RegisterClassEx(&WndClassEx); 
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif