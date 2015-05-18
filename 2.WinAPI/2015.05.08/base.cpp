#if 0
//----------------------------------------------
// ���̷��� �ڵ�
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

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
	case WM_LBUTTONUP:
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
//  �׸��� ver0.1
//----------------------------------------------
// �ҿ����� �����
// 
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
	static POINTS pts[4096];
	static int cnt = 0;
//	static POINTS spt;	//���� ��ǥ
//	static POINTS ept;	//�� ��ǥ
	static bool bDraw;

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		{

			if(GetCapture() == hWnd)
			{
				if(bDraw)
				{
					pts[cnt++] = MAKEPOINTS(lParam);
					InvalidateRect(hWnd, NULL, false);
					
				}
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		{
			SetCapture(hWnd);
			//cnt = 0;
			pts[cnt++] = MAKEPOINTS(lParam);
			bDraw = true;
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			bDraw = FALSE;
			//HDC hdc = GetDC(hWnd);
			//�����׸���-------------------------
			//ept = MAKEPOINTS(lParam);
			//MoveToEx(hdc, spt.x, spt.y, NULL);
			//LineTo(hdc, ept.x, ept.y);
			//ReleaseDC(hWnd, hdc);
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

			for(int i = 0; i<cnt-1; i++)
			{
				MoveToEx(hdc, pts[i].x, pts[i].y, NULL);
				LineTo(hdc, pts[i+1].x, pts[i+1].y);	
			}

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
//  �׸��� ver0.2
//----------------------------------------------
// ���� ���� ����
// 
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)
#define LINE	0
#define RECTAN	1
#define TRI		2

//enum SHAPEMODE {LINE, RECTAN, TRI};
typedef struct DrawInfo {
	int ShapeMode;
//	SHAPEMODE ShapeMode;	//���� ���
	int penW;				//������
	COLORREF PenColor;		//�� ��
	POINTS StartPos;		//������ǥ
	POINTS EndPos;			//����ǥ
} DRAWINFO, *PDRAWINFO;

// �Լ�
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
	static DRAWINFO DrawList[4096];	//���� ���� �迭
	static int cnt = 0;				//���� ����
	static bool bDraw = false;

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		{
			if(GetCapture() == hWnd)
			{
				if(bDraw)
				{
					InvalidateRect(hWnd, NULL, false);
					
				}
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		{
			srand((unsigned)time(NULL));
			SetCapture(hWnd);
			bDraw = true;

			DrawList[cnt].EndPos = DrawList[cnt].StartPos = MAKEPOINTS(lParam);
			DrawList[cnt].ShapeMode = rand()%3;
			DrawList[cnt].PenColor = RGB(rand()%255, rand()%255, rand()%255);
			DrawList[cnt].penW = rand()%10 + 1;
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			bDraw = FALSE;
			DrawList[cnt++].EndPos = MAKEPOINTS(lParam);
			InvalidateRect(hWnd, NULL, FALSE);
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

			for(int i = 0; i<cnt-1; i++)
			{
				SetROP2(hdc, R2_MASKPEN);
				HPEN hPen = CreatePen( PS_SOLID, DrawList[i].penW, DrawList[i].PenColor);
				HPEN oldPen = (HPEN) SelectObject(hdc, hPen);
				if(DrawList[i].ShapeMode == LINE)
				{
					MoveToEx(hdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y,NULL);
					LineTo(hdc, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == RECTAN)
				{
					Rectangle(hdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == TRI)
				{
					Ellipse(hdc,  DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				
			}

			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif

#if 0
//----------------------------------------------
// SetROP2
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

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
	static HWND hEdit;
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		{
			HDC hdc = GetDC(hWnd);
			POINTS pt = MAKEPOINTS(lParam);
			RECT rt;
			rt.left = pt.x - 50;
			rt.top = pt.y+ 50;
			rt.right = pt.x + 50;
			rt.bottom = pt.y - 50;

			SetROP2(hdc, R2_MASKPEN);
			//HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			HBRUSH brush = (HBRUSH)CreateHatchBrush(HS_BDIAGONAL,RGB(10,33,100));
			SelectObject(hdc, brush);
			//FillRect(hdc, &rt, brush);
			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);

			hEdit = CreateWindowEx(0, TEXT("edit"), TEXT(""), WS_VISIBLE|WS_CHILD|WS_BORDER,
				rt.left, rt.top, 100, 100, hWnd, 0, g_hInst, 0);
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
//----------------------------------------------
// -���ҽ�
//   - ���α׷����� �ʿ��� �ڵ��̿��� �ڿ���
//   - ������, Ŀ��, �޴�, ���� ���
//----------------------------------------------
// ������
//----------------------------------------------
// ���콺 Ŀ��
//----------------------------------------------
// �޴� ��Ϲ��
// 1) WndClassEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
// 2) CreateWindow�� ���ڷ� ���� 
//    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1);
//     -> createwindow�� ���ڷ� ����
// 3) SetMenu(hWnd, hMenu)
// �޴� ó��
// WM_COMMAND ���� ó��
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "resource.h"

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
	WndClassEx.hIcon		= LoadIcon(g_hInst,(LPCWSTR)MAKEINTRESOURCE( IDI_ICON1));
	WndClassEx.hInstance	= hInstance;
	WndClassEx.lpfnWndProc	= (WNDPROC)WndProc;
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);
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
	case WM_LBUTTONUP:
		return 0;
	case WM_RBUTTONDOWN:
		{
			HMENU hMenu = GetMenu(hWnd);
			HMENU hSub = GetSubMenu(hMenu, 0);

			AppendMenu(hSub, MF_SEPARATOR, 4885, TEXT("�Ÿ޴�"));
			AppendMenu(hSub, MF_STRING, 4885, TEXT("�Ÿ޴�"));
			AppendMenu(hSub, MF_POPUP, 4885, TEXT("�Ÿ޴�"));

			//RemoveMenu(hSub, 0, );
			//DrawMenuBar(hWnd);

		}
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_COMMAND:	//�޴�, �ڽ� �����쿡�� �߻��� �̺�Ʈ ó��
		{
			switch(LOWORD(wParam))	//Menu ID
			{
			case ID_MYFILE_OPEN:
				MBOX(TEXT("open"));
				break;
			case ID_MYFILE_CLOSE:
				MBOX(TEXT("close"));
				break;
			case 4885:
				MBOX(TEXT("4885"));
				break;
			}

		}
		return 0;
	case WM_SIZE:
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
// �޸� DC�� �̿��Ͽ� bitmap ���.
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

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
			HDC hdc = GetDC(hWnd);
			// ȭ�� DC�� ȣȯ�Ǵ� �޸� DC�� ����
			HDC memDC = CreateCompatibleDC(hdc);
			HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
			BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm);
			//�޸� DC�� ��Ʈ�� ����
			SelectObject(memDC, hBitmap);
			//��Ʈ������ ���
			TextOut(memDC, 5, 5, TEXT("��Ʈ������ ���"), 15);
			//�޸� DC -> ȭ�� DC
			POINTS pt = MAKEPOINTS(lParam);
			BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
			DeleteDC(memDC);
			ReleaseDC(hWnd, hdc);
			DeleteObject(hBitmap);
		}
		return 0;
	case WM_LBUTTONUP:
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
// ���̷��� �ڵ�
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

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// �Լ�
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
	case WM_LBUTTONUP:
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