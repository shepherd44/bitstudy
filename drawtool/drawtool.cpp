#if 1
#pragma comment(lib,"comctl32")

//----------------------------------------------
//  그림판
//----------------------------------------------
// 추가된 기능
// 1) 그렸던 정보 저장
// 추가할 기능
// -도형 정보 저장
// -brush 랜덤 
// -move 도중 그림 보여지도록
// -영역
// -추가할것
// -메뉴 추가 --> 핸덤 --> 메뉴
// -되돌리기
// -지우개

// 기능추가
// 1) 메뉴 -> 파일 열기, 파일 저장(bmp파일로만)
// 2) 툴바 -> 도형모양(펜, 라인, 붓기, 텍스트박스, 지우개, 색깔선택),  
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <commctrl.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

#define IsKeyPressed(vk)	(GetKeyState(vk) & 0xFF00)
#define IsKeyToggle(vk)		(GetKeyState(vk) & 0x00FF)

#define COLORBLACK		RGB(0, 0, 0)
#define COLORWHITE		RGB(255, 255, 255)
#define COLORRED		RGB(255, 0, 0)
#define COLORGREEN		RGB(0, 255, 0)
#define COLORBLUE		RGB(0, 0, 255)

// 도형모양
enum SHAPEMODE {LINE = 0, RECTAN, ELLIPSE, TRI, SHAPEMODENUM};


typedef struct DrawInfo {
	int ShapeMode;			//도형 모양
	int penW;				//선굵기
	COLORREF PenColor;		//선 색
	COLORREF BrushColor;	//브러쉬 색
	int RopMode;			//ROP2 모드
	POINTS StartPos;		//시작좌표
	POINTS EndPos;			//끝좌표
} DRAWINFO, *PDRAWINFO;

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
	WndClassEx.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU_DARWTOOL);
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
HWND hToolBarColor;
HWND hToolBarShape;

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc, hMemdc;	//윈도우 dc, memory dc
	static DRAWINFO DrawList[4096];	//도형 저장 배열
	static int cnt = 0;				//도형 갯수
	static bool bDraw = false;
	static POINTS movePt;

	// 컬러 툴바 메뉴
	TBBUTTON ToolBtn_Color[6] = {
		{0,ID_COLOR_RED,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{1,ID_COLOR_BLACK,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{2,ID_COLOR_WHITE,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{3,ID_COLOR_GREEN,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{4,ID_COLOR_BLUE,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
		{5,0,0,TBSTYLE_SEP,0,0,0,0},
	};
	TBBUTTON ToolBtn_SHAPE[6] = {
		{0,ID_SHAPE_LINE,TBSTATE_ENABLED | TBSTATE_CHECKED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{1,ID_SHAPE_RECT,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{2,ID_SHAPE_ELLIPS,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{3,ID_SHAPE_TRI,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{4,ID_SHAPE_FILLRECT,TBSTATE_ENABLED,TBSTYLE_CHECKGROUP,0,0,0,0},
		{5,0,0,TBSTYLE_SEP,0,0,0,0},
	};
	
	// 현재 선택 사항
	static int CurrentShape				= LINE;			//도형 모양
	static int CurrentPenW				= 1;				//선굵기
	static COLORREF CurrentPenColor		= RGB(0, 0, 0);		//선 색
	static COLORREF CurrentBrushColor	= RGB(0, 0, 0);	//브러쉬 색
	static int CurrentRopMode			= R2_COPYPEN;					//ROP2 모드

	HBITMAP OldBitmap;
	static RECT ClientRect;
	PAINTSTRUCT ps;

	switch(iMessage) {
	case WM_CREATE:
		{
			//InitCommonControls();
			//툴바 등록
			
			hToolBarShape = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | WS_BORDER,
				IDR_TB_SHAPE, 5, g_hInst, IDR_TB_SHAPE, ToolBtn_SHAPE, 5,
				16, 15, 16, 15, sizeof(TBBUTTON));


			hToolBarColor = CreateWindow(TOOLBARCLASSNAME,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,
				0,0,0,0,hWnd,0,g_hInst,NULL);
			SendMessage(hToolBarColor,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
			TBADDBITMAP colorbit;
			colorbit.hInst=g_hInst;
			colorbit.nID=IDR_TB_COLOR;
			SendMessage(hToolBarColor,TB_ADDBITMAP,5,(LPARAM)&colorbit);
			SendMessage(hToolBarColor,TB_ADDBUTTONS,(WPARAM)6,(LPARAM)ToolBtn_Color);

			//-----------------------------------------------
			hdc = GetDC(hWnd);
			GetWindowRect(hWnd,&ClientRect);
			hBit = CreateCompatibleBitmap(hdc, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
			hMemdc = CreateCompatibleDC(hdc);
			OldBitmap = (HBITMAP)SelectObject(hMemdc, hBit);
			//-----------------------------------------------
			SelectObject(hMemdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hMemdc, 0, 0, ClientRect.right - ClientRect.left, ClientRect.bottom - ClientRect.top);
			//-----------------------------------------------
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
				//툴바처리(color)
				case ID_COLOR_RED:
					CurrentPenColor = COLORRED;
					break;
				case ID_COLOR_BLACK:
					CurrentPenColor = COLORBLACK;
					break;
				case ID_COLOR_WHITE:
					CurrentPenColor = COLORWHITE;
					break;
				case ID_COLOR_GREEN:
					CurrentPenColor = COLORGREEN;
					break;
				case ID_COLOR_BLUE:
					CurrentPenColor = COLORBLUE;
					break;
				//툴바처리(shape)
				case ID_SHAPE_LINE:
					CurrentShape = LINE;
					break;
				case ID_SHAPE_RECT:
					CurrentShape = RECTAN;
					break;
				case ID_SHAPE_ELLIPS:
					CurrentShape = ELLIPSE;
					break;
				case ID_SHAPE_TRI:
					CurrentShape = TRI;
					break;
				case ID_SHAPE_FILLRECT:
					CurrentShape = RECTAN;
					CurrentBrushColor = CurrentPenColor;
					break;
				//메뉴처리
				case ID_MYFILE_OPEN:
					MBOX(TEXT("open"));
					break;
				case ID_MYFILE_CLOSE:
					MBOX(TEXT("close"));
					break;
			}
		}
		return 0;
	case WM_SIZE:
		{
			SendMessage(hToolBarColor,TB_AUTOSIZE,0,0);
			SendMessage(hToolBarShape,TB_AUTOSIZE,0,0);
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
			//현재 그리는 도형 정보 저장
			//마지막 포인트는 WM_LBUTTONUP에서 처리
			DrawList[cnt].EndPos = DrawList[cnt].StartPos = MAKEPOINTS(lParam);
			DrawList[cnt].ShapeMode = CurrentShape;
			DrawList[cnt].PenColor = CurrentPenColor;
			DrawList[cnt].BrushColor = CurrentBrushColor;
			DrawList[cnt].penW = CurrentPenW;
		}
		return 0;
	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			bDraw = FALSE;
			// 도형의 끝점 지정
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
			// memoryDC에 도형 그리기
			if(1)	// ctrl + z 의 경우 배경을 흰색으로 다시 그린 뒤 그리기 시작
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
			 //클릭된 상태일 경우 처리
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

			// hMemdc에서 dc로 전송
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