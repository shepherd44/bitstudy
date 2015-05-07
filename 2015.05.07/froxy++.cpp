#if 1
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

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define OBJECTNUM		7
#define OBJECTX			10
#define OBJECTY			50
#define OBJECTHWND		tcObject[0]
#define OBJECTTEXT		tcObject[1]
#define OBJECTCLASS		tcObject[2]
#define OBJECTSTYLE		tcObject[3]
#define OBJECTAREA		tcObject[4]
#define OBJECTTID		tcObject[5]
#define OBJECTPID		tcObject[6]
#define STRINGLENGTH	128

#define MYSTRING(str, vars)		{TCHAR buf[128] = {0,};\
								wsprintf(buf, str, vars); }
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

#define CARROW			LoadCursor(NULL, (LPCWSTR)IDC_ARROW)
#define CTARGET			LoadCursor(g_hInst, (LPCWSTR)IDC_TARGET)

// �Լ�
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void PrintObject(wchar_t**,HWND, HWND, RECT);

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
	WndClassEx.hIcon		= LoadIcon(hInstance,(LPCWSTR)IDI_FILL);
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
		200, 200, 500, 500,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

void PrintObject(wchar_t** tchar, HWND hWnd, HWND h, RECT rect)
{
	//----------------------------------------
	// ������Ʈ ���� �Է� �� �׷��ֱ�
	HDC hdc = GetDC(hWnd);

	TCHAR buf[64] = {0,};
	wsprintf((LPWSTR)tchar[0], TEXT("â:\t\t0x%08x"), h);
	//memcpy(OBJECTHWND+11, buf, wcslen(buf));
	//TextOut(hdc, OBJECTX+120, OBJECTY, buf, wcslen(buf));
	TextOut(hdc, OBJECTX+10, OBJECTY, tchar[0], wcslen(buf));
	
	GetWindowText(h, buf, sizeof(buf));
	wsprintf((LPWSTR)tchar[1], TEXT("�ؽ�Ʈ:\t\t%s"), buf);
	//TextOut(hdc, OBJECTX+120, OBJECTY + 20, buf, wcslen(buf));
	TextOut(hdc, OBJECTX+10, OBJECTY + 20, tchar[1], wcslen(buf));
	
	GetClassName(h, buf, sizeof(buf));
	//memcpy(OBJECTCLASS+11, buf, wcslen(buf));
	TextOut(hdc, OBJECTX+120, OBJECTY + 40, buf, wcslen(buf));
	
	wsprintf(buf, TEXT("��Ÿ��:\t\t0x%08x"), GetClassLong(h, GCL_STYLE));
	//memcpy(OBJECTSTYLE+11, buf, wcslen(buf));
	TextOut(hdc, OBJECTX+120, OBJECTY + 60, buf, wcslen(buf));

	wsprintf(buf, TEXT("����: \t\t(%d,%d)-(%d,%d)"), rect.top, rect.left, rect.right, rect.bottom);
	//memcpy(OBJECTAREA+11, buf, wcslen(buf));
	TextOut(hdc, OBJECTX+120, OBJECTY + 80, buf, wcslen(buf));

	ReleaseDC(hWnd, hdc);
	//----------------------------------------
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND preh;
	static int x, y;
	static TCHAR tcObject[OBJECTNUM][STRINGLENGTH]
	 = {TEXT("â:"),
		TEXT("�ؽ�Ʈ:"),
		TEXT("Ŭ����:"),
		TEXT("��Ÿ��:"),
		TEXT("����:"),
		TEXT("������ID:"),
		TEXT("���μ��� ID:") };

	static HICON hIconFill, hIconEmpty;
	static RECT rTarget = {0,};

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		{
			//icon ����
			hIconFill = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_FILL));
			hIconEmpty = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_EMPTY));
		}
		return 0;
	case WM_MOUSEMOVE:
		{
			if(GetCapture() == hWnd)
			{
				//Ŀ�� ����
				SetCursor(CTARGET);
				//Ŀ���κ��� ����Ʈ �޾ƿ���
				POINT pt;
				GetCursorPos(&pt);
				// �����ͷκ��� ������޾ƿ���
				HWND h = WindowFromPoint(pt);
				
				if(h == preh)
					return 0;
				
				//----------------------------------------
				// �ش� �������� �簢���� ��������
				RECT rect;
				GetWindowRect(h, &rect);

				//----------------------------------------
				// ������Ʈ ���� �Է�
				//PrintObject((TCHAR**)tcObject, hWnd, h, rect);
				HDC hdc = GetDC(hWnd);
				TCHAR buf[64] = {0,};
				//������
				wsprintf(OBJECTHWND,	TEXT("â:            0x%08x"), h);
				//�ؽ�Ʈ
				GetWindowText(h, buf, sizeof(buf));
				wsprintf(OBJECTTEXT,	TEXT("�ؽ�Ʈ:    %s"), buf);
				//Ŭ��������
				GetClassName(h, buf, sizeof(buf));
				wsprintf(OBJECTCLASS,	TEXT("Ŭ����:    %s"), buf);
				//��Ÿ��
				wsprintf(OBJECTSTYLE,	TEXT("��Ÿ��:    0x%08x"), GetClassLong(h, GCL_STYLE));
				//����
				wsprintf(OBJECTAREA,	TEXT("����:        (%d,%d)-(%d,%d)"), rect.top, rect.left, rect.right, rect.bottom);
				
				ReleaseDC(hWnd, hdc);

				InvalidateRect(preh, NULL, true);
				InvalidateRect(hWnd, NULL, true);

				//----------------------------------------
				// �ٸ� �������� dc ��������
				hdc = GetDC(h);
				// pen ����
				HPEN hPen = (HPEN)CreatePen(PS_SOLID, 5, RGB(100,255,100));
				HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
				// brush ����
				HBRUSH hBrush = (HBRUSH) GetStockObject(NULL_BRUSH);
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

				// ������ �ܰ� �׸���
				OffsetRect(&rect, -rect.left, -rect.top);
				Rectangle(hdc, rect.top, rect.left, rect.right - rect.left, rect.bottom - rect.top);
				//dc pen, brush ������� ����
				SelectObject(hdc, hOldPen);
				SelectObject(hdc, hOldPen);

				ReleaseDC(GetCapture(),hdc);

				preh = h;
				
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		{
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(g_hInst, (LPCWSTR)IDC_TARGET));
			SetCapture(hWnd);
			HDC hdc = GetDC(hWnd);
			DrawIcon(hdc, 10, 10, hIconEmpty);
			ReleaseDC(hWnd, hdc);
			
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();

			
			HDC hdc = GetDC(hWnd);
			DrawIcon(hdc, 10, 10, hIconFill);
			
			ReleaseDC(hWnd, hdc);
			SetClassLong(hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, (LPCWSTR)IDC_ARROW));
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
			// ������ �׸���
			DrawIcon(hdc, 10, 10, hIconFill);

			//������Ʈ ���
			for(int i=0; i<OBJECTNUM; i++)
				TextOut(hdc, OBJECTX, OBJECTY + i*20, tcObject[i], wcslen(tcObject[i]));
		
			EndPaint(hWnd, &ps);
			break;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif