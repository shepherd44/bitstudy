#if 1
/***********************************************
 *
 ***********************************************/
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

// 매크로
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100

#define GAMESTATUS_WIDTH	30
#define ONEDIGIT_HEIGHT		23
#define MAP_START_X			0
#define MAP_START_Y			ONEDIGIT_HEIGHT
#define MAP_WIDTH			610
#define MAP_HEIGHT			610
#define BLANK				40
#define STONE_SIZE			29

#define ALPHACOLOR			RGB(255,0,0)

#define WINDOW_WIDTH	(MAP_WIDTH+17)
#define WINDOW_HEIGHT	(MAP_HEIGHT + ONEDIGIT_HEIGHT+ BLANK)

#define ROW		20
#define COL		20

#define LIMITEDTIME		30

#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
bool isWin(int, int, double, double);

// Global Instance
HINSTANCE g_hInst;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("game");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("omok");

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
	WndClassEx.hIcon		= LoadIcon(hInstance,(LPCWSTR)IDB_BLACK);
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
		CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
	if(!hWnd)
		return 0;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;

}

#define IDT_GAMETIMERME		1001
#define IDT_GAMETIMERCOM	1002

enum STONE { NOT = 0, BLACK, WHITE, STONENUM};
enum GameState {NOTPLAY = 0, PLAY};

typedef struct GameMap {
	int ChargedStone[ROW][COL];
	bool turn;
	int GameState;
	int GameTurn;
} MAP;
GameMap g_Map;

typedef struct SpriteImage{
	HDC hSpriteDC;
	HBITMAP Sprite;
	int Imagewidth;
	int imageheight;
	int widthlevel;
	int heightlevel;
} SPRITEIMAGE;

bool isWin(int curcol, int currow, double col, double row)
{
	int a = -2%-1;
	if((((col*col)) == 25)||(row*row)==25)
		return true;
	else
	{
	if(g_Map.ChargedStone[curcol][currow] == g_Map.ChargedStone[curcol+(int)col][currow+(int)row])
		return isWin(curcol, currow, col + col*col/col, row+row*row/row);
	else
		return false;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HBITMAP hBitMap, hBitBlack, hBitWhite, hMemBit;
	HBITMAP hOldBit1, hOldBit2;
	HDC hdc, hMapDC, hMemDC, hStoneDC;
	static HANDLE hTimerMe, hTimerCom;

	static int TimeMe, TimeCom;
	time_t mytime;
	static char* strTime;

	static SpriteImage siTimeimage;

	static SYSTEMTIME st;

	//처리시작----------------------------------------
	switch(iMessage) {
	case WM_CREATE:
		{
			//비트맵 생성-----------------------------
			hBitMap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_MAP));
			hBitBlack = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BLACK));
			hBitWhite = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_WHITE));

			// 스프라이트 이미지 구조체 초기화(time)
			siTimeimage.Sprite = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DIGIT));
			siTimeimage.imageheight = 23;
			siTimeimage.Imagewidth = 13;
			siTimeimage.heightlevel = 8;
			siTimeimage.widthlevel = 1;
			//배경 초기화
			hdc = GetWindowDC(hWnd);
			hMemDC = CreateCompatibleDC(hdc);
			hOldBit1 = (HBITMAP)SelectObject(hMemDC, hMemBit);
			hMemBit = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);

			HBRUSH hOldBrush = (HBRUSH)SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
			Rectangle(hMemDC,0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

			SelectObject(hMemDC, hOldBrush);
			SelectObject(hMemDC, hOldBit1);

			DeleteDC(hMemDC);
			ReleaseDC(hWnd, hdc);

			//타이머 셋팅 - 1000 -> 1초
			TimeMe = 300;
			TimeCom = 300;
			MBOX(TEXT("GameStart\n검은돌부터"));
			g_Map.GameTurn = BLACK;
			g_Map.turn = !g_Map.turn; 
		}
		return 0;
	
	case WM_TIMER:
		{
			switch (wParam)
			{
			case IDT_GAMETIMERME:
				if(TimeMe == 0)
				{
					MBOX(TEXT("시간패"));
					memset(g_Map.ChargedStone, 0, sizeof(g_Map.ChargedStone)); 
					TimeMe = 300;
				}
				TimeMe--;
				break;
			case IDT_GAMETIMERCOM:
				if(TimeCom == 0)
				{
					MBOX(TEXT("시간승"));
					memset(g_Map.ChargedStone, 0, sizeof(g_Map.ChargedStone));
					TimeCom = 300;
				}
				TimeCom--;
				break;
			}
			GetSystemTime(&st); 
			InvalidateRect(hWnd, 0, 0); 
		}
		return 0;
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		{
			// 좌표 -> 배열
			POINTS pt  = MAKEPOINTS(lParam); 
			pt.y -= 25; 
			int col = pt.x/30; 
			int row  = pt.y/30;
			// 바둑알 있는지 확인
			if(g_Map.ChargedStone[row][col] != NOT)
			{
				MBOX(TEXT("바둑알이 있습니다."));
				return 0;
			}
			if( g_Map.turn )
				g_Map.ChargedStone[row][col] =  BLACK;
			else 
				g_Map.ChargedStone[row][col] =  WHITE;
			// 승리인지 확인
			for(int i=2; i<ROW-2;i++)
			{
				for(int j=2; j<COL-2;j++)
				{
					if(g_Map.ChargedStone[i][j-2]==BLACK && g_Map.ChargedStone[i][j-1]==BLACK &&g_Map.ChargedStone[i][j]==BLACK && g_Map.ChargedStone[i][j+1]==BLACK && g_Map.ChargedStone[i][j+2]==BLACK) //가로 연속 다섯개 윈
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"BLACK WIN");
						TimeMe=TimeCom = 300;

					}
					else if(g_Map.ChargedStone[i-2][j]==BLACK && g_Map.ChargedStone[i-1][j]==BLACK &&g_Map.ChargedStone[i][j]==BLACK && g_Map.ChargedStone[i+1][j]==BLACK && g_Map.ChargedStone[i+2][j]==BLACK)//가로 연속 다섯개 윈
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"BLACK WIN");
						TimeMe=TimeCom = 300;
					}

					else if(g_Map.ChargedStone[i][j-2]==WHITE && g_Map.ChargedStone[i][j-1]==WHITE &&g_Map.ChargedStone[i][j]==WHITE && g_Map.ChargedStone[i][j+1]==WHITE && g_Map.ChargedStone[i][j+2]==WHITE)
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"WHITE WIN");
						TimeMe=TimeCom = 300;
					}
					else if(g_Map.ChargedStone[i-2][j]==WHITE && g_Map.ChargedStone[i-1][j]==WHITE &&g_Map.ChargedStone[i][j]==WHITE && g_Map.ChargedStone[i+1][j]==WHITE && g_Map.ChargedStone[i+2][j]==WHITE)
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"WHITE WIN");
						TimeMe=TimeCom = 300;
					}

					else if(g_Map.ChargedStone[i-2][j-2]==BLACK && g_Map.ChargedStone[i-1][j-1]==BLACK &&g_Map.ChargedStone[i][j]==BLACK && g_Map.ChargedStone[i+1][j+1]==BLACK && g_Map.ChargedStone[i+2][j+2]==BLACK)
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"BLACK WIN");
						TimeMe=TimeCom = 300;
					}
					else if(g_Map.ChargedStone[i-2][j+2]==BLACK && g_Map.ChargedStone[i-1][j+1]==BLACK &&g_Map.ChargedStone[i][j]==BLACK && g_Map.ChargedStone[i+1][j-1]==BLACK && g_Map.ChargedStone[i+2][j-2]==BLACK)
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"BLACK WIN");
						TimeMe=TimeCom = 300;
					}

					else if(g_Map.ChargedStone[i-2][j-2]==WHITE && g_Map.ChargedStone[i-1][j-1]==WHITE &&g_Map.ChargedStone[i][j]==WHITE && g_Map.ChargedStone[i+1][j+1]==WHITE && g_Map.ChargedStone[i+2][j+2]==WHITE)
					{
						memset(g_Map.ChargedStone,0,sizeof(g_Map.ChargedStone));
						MBOX(L"WHITE WIN");
						TimeMe=TimeCom = 300;
					}
					else if(g_Map.ChargedStone[i-2][j+2]==WHITE && g_Map.ChargedStone[i-1][j+1]==WHITE &&g_Map.ChargedStone[i][j]==WHITE && g_Map.ChargedStone[i+1][j-1]==WHITE && g_Map.ChargedStone[i+2][j-2]==WHITE)
					{
						memset(g_Map.ChargedStone,0,sizeof(MAP));
						MBOX(L"WHITE WIN");
						TimeMe=TimeCom = 300;
					}
				}
			}
			if(!g_Map.turn)
			{
				KillTimer(hWnd, IDT_GAMETIMERCOM);
				SetTimer(hWnd, IDT_GAMETIMERME, 1000,0);
			}
			else
			{
				KillTimer(hWnd, IDT_GAMETIMERME);
				SetTimer(hWnd, IDT_GAMETIMERCOM, 1000, 0);
			}
			g_Map.turn = !g_Map.turn; 
			InvalidateRect( hWnd , 0,0) ;
		}
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			hMemDC = CreateCompatibleDC(hdc);
			hOldBit1 = (HBITMAP)SelectObject(hMemDC, hMemBit);
			
			// time 그리기---------------------------------------------------------
			siTimeimage.hSpriteDC = CreateCompatibleDC(hdc);
			hOldBit2 = (HBITMAP)SelectObject(siTimeimage.hSpriteDC, siTimeimage.Sprite);
 			
			int tm[8] = {st.wHour/10,	st.wHour%10,   10,  
						 st.wMinute/10,	st.wMinute%10, 10,
						 st.wSecond/10,	st.wSecond%10
						}; 
			
			for(int i = 0; i<8; i++) 
			{
				BitBlt(hdc, i*siTimeimage.Imagewidth, 0, siTimeimage.Imagewidth, siTimeimage.imageheight ,
					siTimeimage.hSpriteDC, 0 , siTimeimage.imageheight * (11-tm[i]) ,SRCCOPY); 
			}
			
			// 남은 시간 그리기 --------------------------------------------------
			int tmMe[3] = {(TimeMe/100), (TimeMe%100)/10, (TimeMe%10)}; 
			for(int i = 0; i<3; i++) 
			{
				BitBlt(hdc, 200 + i*siTimeimage.Imagewidth, 0, siTimeimage.Imagewidth, siTimeimage.imageheight ,
					siTimeimage.hSpriteDC, 0 , siTimeimage.imageheight * (11-tmMe[i]) ,SRCCOPY); 
			}
			int tmCom[3] = {(TimeCom/100),	(TimeCom%100)/10, (TimeCom%10)};
			for(int i = 0; i<3; i++) 
			{
				BitBlt(hdc, 250 + i*siTimeimage.Imagewidth, 0, siTimeimage.Imagewidth, siTimeimage.imageheight ,
					siTimeimage.hSpriteDC, 0 , siTimeimage.imageheight * (11-tmCom[i]) ,SRCCOPY); 
			}
			SelectObject(siTimeimage.hSpriteDC, hOldBit2);
			DeleteDC(siTimeimage.hSpriteDC);

			//map그리기----------------------------------------------------------
			hMapDC = CreateCompatibleDC(hdc);
			hOldBit2 = (HBITMAP)SelectObject(hMapDC, hBitMap);

			BitBlt(hdc,MAP_START_X,25,MAP_WIDTH, MAP_HEIGHT,
				hMapDC, 0,0,SRCCOPY);

			SelectObject(hMapDC, hOldBit2);
			DeleteDC(hMapDC);

			// 바둑알 그리기---------------------------------------------------------
			hStoneDC = CreateCompatibleDC(hdc);
			for(int i= 0; i<ROW; i++) 
			{
				for(int j = 0; j < COL; j++) 
				{
					switch(g_Map.ChargedStone[i][j])
					{
					case WHITE:	hOldBit2 = (HBITMAP)SelectObject(hStoneDC, hBitWhite); break;
					case BLACK:	hOldBit2 = (HBITMAP)SelectObject(hStoneDC, hBitBlack); break;
					case NOT:    continue; 
					}
					TransparentBlt(hdc, j*30+5, i*30+25+5, STONE_SIZE,STONE_SIZE,
						hStoneDC, 0,0,STONE_SIZE,STONE_SIZE,ALPHACOLOR);
					SelectObject(hStoneDC, hOldBit2); 					
				}
			}
			DeleteDC(hStoneDC);

			//해제---------------------------------
			SelectObject(hMemDC, hOldBit1);
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_LBUTTONUP:
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_DESTROY:
	{
		KillTimer(hWnd,IDT_GAMETIMERME);
		KillTimer(hWnd,IDT_GAMETIMERCOM);
		DeleteObject(hBitMap);
		DeleteObject(hBitBlack);
		DeleteObject(siTimeimage.Sprite);
		DeleteObject(hBitWhite);
		DeleteObject(hMemBit);
		PostQuitMessage(0);
	}
	return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

#endif