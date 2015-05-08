#if 1
//----------------------------------------------
//  �׸���
//----------------------------------------------
// �߰��� ���
// 1) �׷ȴ� ���� ����
// �߰��� ���
// -���� ���� ����
// -brush ���� 
// -move ���� �׸� ����������
// -����
// -�߰��Ұ�
// -�޴� �߰� --> �ڴ� --> �޴�
// -�ǵ�����
// -���찳

// ����߰�
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <commctrl.h>
#include "resource.h"

// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

#define IsKeyPressed(vk)	(GetKeyState(vk) & 0xFF00)
#define IsKeyToggle(vk)		(GetKeyState(vk) & 0x00FF)

enum SHAPEMODE {LINE = 0, RECTAN, ELLIPSE, TRI, SHAPEMODENUM};
typedef struct DrawInfo {
	int ShapeMode;
//	SHAPEMODE ShapeMode;	//���� ���
	int penW;				//������
	COLORREF PenColor;		//�� ��
	COLORREF BrushColor;	//�귯�� ��
	int R2Mode;				//ROP2 ���
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


HBITMAP hBit;
HWND hToolBar;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc, hMemdc;	//������ dc, memory dc
	static DRAWINFO DrawList[4096];	//���� ���� �迭
	static int cnt = 0;				//���� ����
	static bool bDraw = false;
	static POINTS movePt;

	TBBUTTON ToolBtn[5] = {
		{0,10,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{1,11,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{5,0,0,TBSTYLE_SEP,0,0,0,0},
		{2,12,TBSTATE_ENABLED | TBSTATE_CHECKED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{3,13,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,0}
   };

	HBITMAP OldBitmap;
	static RECT ClientRect;
	PAINTSTRUCT ps;

	switch(iMessage) {
	case WM_CREATE:
		{
			//InitCommonControls();
			//���� ���
			hToolBar = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | WS_BORDER,
				IDR_COLOR_TB, 4, g_hInst, IDR_COLOR_TB, ToolBtn, 5,
				16, 15, 16, 15, sizeof(TBBUTTON));
			//-----------------------------------------------
			hdc = GetDC(hWnd);
			GetWindowRect(hWnd,&ClientRect);
			hBit = CreateCompatibleBitmap(hdc, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
			hMemdc = CreateCompatibleDC(hdc);
			OldBitmap = (HBITMAP)SelectObject(hMemdc, hBit);
			//--------------------------------------------
			SelectObject(hMemdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hMemdc, 0, 0, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
			//---------------------------------------------
			SelectObject(hMemdc, OldBitmap);
			DeleteDC(hMemdc);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_DESTROY:
		DeleteObject(hBit);
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 10:
					MessageBox(hWnd,L"ù��° ��ư�� �����߽��ϴ�",L"�˸�",MB_OK);
					break;
				case 11:
					MessageBox(hWnd,L"�ι�° ��ư�� �����߽��ϴ�",L"�˸�",MB_OK);
					break;
			}
		}
		return 0;
	case WM_SIZE:
		{
			SendMessage(hToolBar,TB_AUTOSIZE,0,0);
		}
		return 0;
	case WM_MOUSEMOVE:
		{
			if(GetCapture() == hWnd)
			{
				if(bDraw)
				{
					movePt = MAKEPOINTS(lParam);
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
			//���� �׸��� ���� ���� ����
			//������ ����Ʈ�� WM_LBUTTONUP���� ó��
			DrawList[cnt].EndPos = DrawList[cnt].StartPos = MAKEPOINTS(lParam);
			DrawList[cnt].ShapeMode = rand()%3;
			DrawList[cnt].PenColor = RGB(rand()%255, rand()%255, rand()%255);
			DrawList[cnt].BrushColor = RGB(rand()%255, rand()%255, rand()%255);
			DrawList[cnt].penW = rand()%10 + 1;
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			bDraw = FALSE;
			// ������ ���� ����
			DrawList[cnt++].EndPos = MAKEPOINTS(lParam);
			InvalidateRect(hWnd, NULL, false);
		}
		return 0;
	case WM_KEYDOWN:
		{
			
		}
		return 0;
	case WM_CHAR:
		{
			// ctrl + z
			if((wParam == 26) && IsKeyPressed(VK_CONTROL))
			{
				if(cnt == 0)
					return 0;
				cnt--;
				InvalidateRect(hWnd, NULL, false);
			}
		}
		return 0;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			hMemdc = CreateCompatibleDC(hdc);
			OldBitmap = (HBITMAP)SelectObject(hMemdc, hBit);
			// ------------------------------------------------
			// SetROP2(hdc, R2_MASKPEN);
			
			//--------------------------
			// memoryDC�� ���� �׸���
			if(1)	// ctrl + z �� ��� ����� ������� �ٽ� �׸� �� �׸��� ����
			{
				SelectObject(hMemdc, GetStockObject(WHITE_BRUSH));
				Rectangle(hMemdc, 0, 0, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
			}
			for(int i = 0; i<cnt; i++)
			{
				HPEN hPen = CreatePen( PS_SOLID, DrawList[i].penW, DrawList[i].PenColor);
				HPEN oldPen = (HPEN) SelectObject(hMemdc, hPen);
				HBRUSH hBrush = CreateSolidBrush(DrawList[i].BrushColor);
				HBRUSH oldBrush = (HBRUSH) SelectObject(hMemdc, hBrush);

				if(DrawList[i].ShapeMode == LINE)
				{
					MoveToEx(hMemdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y,NULL);
					LineTo(hMemdc, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == RECTAN)
				{
					Rectangle(hMemdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == ELLIPSE)
				{
					Ellipse(hMemdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				SelectObject(hMemdc, oldPen);
				SelectObject(hMemdc, oldBrush);
				DeleteObject(hPen);
				DeleteObject(hBrush);
			}
			 //Ŭ���� ������ ��� ó��
			if(bDraw == true)
			{
				HPEN hPen = CreatePen( PS_SOLID, DrawList[cnt].penW, DrawList[cnt].PenColor);
				HPEN oldPen = (HPEN) SelectObject(hdc, hPen);
				HBRUSH hBrush = CreateSolidBrush(DrawList[cnt].BrushColor);
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if(DrawList[cnt].ShapeMode == LINE)
				{
					MoveToEx(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y,NULL);
					LineTo(hdc, movePt.x, movePt.y);
				}
				else if(DrawList[cnt].ShapeMode == RECTAN)
				{
					Rectangle(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y, movePt.x, movePt.y);
				}
				else if(DrawList[cnt].ShapeMode == ELLIPSE)
				{
					Ellipse(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y, movePt.x, movePt.y);
				}
				SelectObject(hdc, oldPen);
				SelectObject(hdc, oldBrush);
				DeleteObject(hPen);
				DeleteObject(hBrush);
			}
			else;

			// hMemdc���� dc�� ����
			BOOL ret = BitBlt(hdc, 0, 0, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top, 
				hMemdc, 0, 0, SRCCOPY); 
			
			/*
			HDC hMemdc = CreateCompatibleDC(hdc);

			for(int i = 0; i<cnt; i++)
			{
				HPEN hPen = CreatePen( PS_SOLID, DrawList[i].penW, DrawList[i].PenColor);
				HPEN oldPen = (HPEN) SelectObject(hdc, hPen);
				HBRUSH hBrush = CreateSolidBrush(DrawList[i].BrushColor);
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

				if(DrawList[i].ShapeMode == LINE)
				{
					MoveToEx(hdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y,NULL);
					LineTo(hdc, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == RECTAN)
				{
					Rectangle(hdc, DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}
				else if(DrawList[i].ShapeMode == ELLIPSE)
				{
					Ellipse(hdc,  DrawList[i].StartPos.x, DrawList[i].StartPos.y, DrawList[i].EndPos.x, DrawList[i].EndPos.y);
				}

				SelectObject(hdc, oldPen);
				SelectObject(hdc, oldBrush);
				
			}
			if(bDraw == true)
			{
				HPEN hPen = CreatePen( PS_SOLID, DrawList[cnt].penW, DrawList[cnt].PenColor);
				HPEN oldPen = (HPEN) SelectObject(hdc, hPen);
				HBRUSH hBrush = CreateSolidBrush(DrawList[cnt].BrushColor);
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if(DrawList[cnt].ShapeMode == LINE)
				{
					MoveToEx(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y,NULL);
					LineTo(hdc, movePt.x, movePt.y);
				}
				else if(DrawList[cnt].ShapeMode == RECTAN)
				{
					Rectangle(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y, movePt.x, movePt.y);
				}
				else if(DrawList[cnt].ShapeMode == ELLIPSE)
				{
					Ellipse(hdc, DrawList[cnt].StartPos.x, DrawList[cnt].StartPos.y, movePt.x, movePt.y);
				}
				SelectObject(hdc, oldPen);
				SelectObject(hdc, oldBrush);
			}
			else;
			*/
			//-------------------------------

			SelectObject(hMemdc, hBit);
			DeleteDC(hMemdc);
			EndPaint(hWnd, &ps);
			return 0;
		}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif