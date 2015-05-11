#if 1
#pragma comment(lib,"comctl32")

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
// 1) �޴� -> ���� ����, ���� ����(bmp���Ϸθ�)
// 2) ���� -> �������(��, ����, �ױ�, �ؽ�Ʈ�ڽ�, ���찳, ������),  
//----------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <commctrl.h>
#include "resource.h"

//---------------------------------------------------------------------
// ��ũ��
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100
#define MBOX(x)			MessageBox(0, x, TEXT(""), MB_OK)

#define IsKeyPressed(vk)	(GetKeyState(vk) & 0xFF00)
#define IsKeyToggle(vk)		(GetKeyState(vk) & 0x00FF)

#define COLORRED		RGB(255, 0, 0)
#define COLORBLACK		RGB(0, 0, 0)
#define COLORWHITE		RGB(255, 255, 255)
#define COLORGREEN		RGB(0, 255, 0)
#define COLORBLUE		RGB(0, 0, 255)

// �������
enum DRAWINGTOOL {PEN = 0, ERASE, SHAPE, DRAWINGTOOLNUM};
enum SHAPEMODE {LINE = 0, RECTAN, ELLIPSE, TRI, SHAPEMODENUM};


typedef struct DrawInfo {
	int ShapeMode;			//���� ���
	int penW;				//������
	COLORREF PenColor;		//�� ��
	COLORREF BrushColor;	//�귯�� ��
	int RopMode;			//ROP2 ���
	POINTS StartPos;		//������ǥ
	POINTS EndPos;			//����ǥ
} DRAWINFO, *PDRAWINFO;

// �Լ�
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void DrawTriangle(HDC hdc, POINTS pt1, POINTS pt2);
LRESULT CALLBACK MyEditIdProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK MyEditPassProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK DrawingToolDlgProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam);

//------------------------------------------------------------
// Global Instance
// �α��� ����
TCHAR gId[13] = {0,};
TCHAR gPass[13] = {0,};
HINSTANCE g_hInst;
WNDPROC OldProcId;
WNDPROC OldProcPass;
HWND g_hDrawingToolDlgWnd = NULL;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("Bit");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("First Sample");
// �÷� ���� �޴�
TBBUTTON ToolBtn_Color[6] = {
	{0,ID_COLOR_RED,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
	{1,ID_COLOR_BLACK,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
	{2,ID_COLOR_WHITE,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
	{3,ID_COLOR_GREEN,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
	{4,ID_COLOR_BLUE,TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0,0,0},
	{5,0,0,TBSTYLE_SEP,0,0,0,0},
};
//--------------------------------------------------------------
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
	WndClassEx.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU_DRAWTOOL);
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
HWND g_hMainWnd;

void DrawTriangle(HDC hdc, POINTS pt1, POINTS pt2)
{
	MoveToEx(hdc, (pt1.x + pt2.x)/2, pt1.y, NULL);
	LineTo(hdc, (pt1.x), pt2.y);
	MoveToEx(hdc, pt1.x, pt2.y, NULL);
	LineTo(hdc, pt2.x, pt2.y);
	MoveToEx(hdc, (pt1.x + pt2.x)/2, pt1.y, NULL);
	LineTo(hdc, pt2.x, pt2.y);
}
//id ó��
LRESULT CALLBACK MyEditIdProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static int i=0;
	switch(iMessage)
	{
	case WM_SETFOCUS:
		wcscpy(gId, TEXT(""));
		i = 0;
		SetWindowText(hWnd, L"");
		return 0;
	case WM_CHAR:
		{
			if((wParam >= 65 && wParam <= 90))
			{
				if(!(i<12 && i >= 0))
					return 0;
				gId[i++] = wParam;
				return CallWindowProc(OldProcId, hWnd, iMessage, wParam, lParam);
			}
			else if(wParam == 8)
			{
				if(i != 0)
				{
					gId[i--] = 0;
				}
				return CallWindowProc(OldProcId, hWnd, iMessage, wParam, lParam);
			}
			else
				return 0;
		}
		return 0;
	}

	return CallWindowProc(OldProcId, hWnd, iMessage, wParam, lParam);
}
// pass ó��
LRESULT CALLBACK MyEditPassProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static int i = 0;
	switch(iMessage) {
	case WM_SETFOCUS:
		wcscpy(gPass, TEXT(""));
		i = 0;
		SetWindowText(hWnd, L"");
		return 0;	
	case WM_CHAR:
		{
			if(wParam == 8)
			{
				if(i != 0)
				{	
					gPass[i--] = 0;
				}
				return CallWindowProc(OldProcId, hWnd, iMessage, wParam, lParam);
			}
			else
			{
				if(!(i<12 && i >= 0))
					return 0;
				gPass[i++] = wParam;
				TCHAR buf[16] ={0,};
				SetWindowText(hWnd, buf);
				for(int j=0; j<i; j++)
					wcscat(buf, TEXT("@"));
				SetWindowText(hWnd, buf);
				return 0;
			}
			
		}
		return CallWindowProc(OldProcId, hWnd, iMessage, wParam, lParam);
	}
	return CallWindowProc(OldProcPass, hWnd, iMessage, wParam, lParam);
}

// �α��� dlg �޼��� ó��
BOOL CALLBACK DlgProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static int idNum=0, passNum=0;
	static HWND hEditId;
	static HWND hEditPass;

	switch(iMessage)
	{
	case WM_INITDIALOG:
		hEditId = GetDlgItem(hWnd, IDC_EDIT_LOGINID);
		OldProcId = (WNDPROC)SetWindowLong(hEditId, GWL_WNDPROC, (long)MyEditIdProc);
		hEditPass = GetDlgItem(hWnd, IDC_EDIT_LOGINPASS);
		OldProcPass = (WNDPROC)SetWindowLong(hEditPass, GWL_WNDPROC, (long)MyEditPassProc);
		return 0;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDB_OK:
				//GetDlgItemText(hWnd, IDC_EDIT_LOGINID, gId, 12);
				//GetDlgItemText(hWnd, IDC_EDIT_LOGINPASS, gPass, 12);
				
				EndDialog(hWnd, IDB_OK);
				break;
			case IDB_CANCLE:
				EndDialog(hWnd, IDB_CANCLE);
				break;
			}
			return false;
		}	
	}
	return false;
}
BOOL CALLBACK DrawingToolDlgProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static int idNum=0, passNum=0;
	static HWND hEditId;
	static HWND hEditPass;

	switch(iMessage)
	{
	case WM_INITDIALOG:
		
		return 0;
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BTN_BLACK:
			case IDC_BTN_GREEN:
			case IDC_BTN_BLUE: 
			case IDC_BTN_WHITE:  
			case IDC_BTN_RED: 
			case IDC_BTN_LINE:  
			case IDC_BTN_TRI:  
			case IDC_BTN_RECT:  
			case IDC_BTN_ELLIPSE:
			case IDC_BTN_PEN:
				SendMessage(g_hMainWnd, WM_COMMAND, wParam, lParam);
				break;
			case IDC_BTN_ERASE:
				SendMessage(g_hMainWnd, WM_COMMAND, wParam, lParam);
				break;
			case IDB_OK:
				break;
			case IDB_CANCLE:
				break;
			}
			return false;
		}	
	}
	return false;
}

// ���α׷� ���ν���
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc, hMemdc;	//������ dc, memory dc
	static DRAWINFO DrawList[4096];	//���� ���� �迭
	static int cnt = 0;				//���� ����
	static bool bDraw = false;
	static POINTS movePt;
	
	// ���� ���� ����
	static int CurrentShape				= LINE;			//���� ���
	static int CurrentPenW				= 1;				//������
	static COLORREF CurrentPenColor		= RGB(0, 0, 0);		//�� ��
	static COLORREF CurrentBrushColor	= RGB(0, 0, 0);	//�귯�� ��
	static int CurrentRopMode			= R2_COPYPEN;					//ROP2 ���
	static int CurrentDrawingTool		= PEN;

	HBITMAP OldBitmap;
	static RECT ClientRect;
	PAINTSTRUCT ps;

	switch(iMessage) {
	case WM_CREATE:
		{
			g_hMainWnd = hWnd;
			//InitCommonControls();
			//���� ���
			
			hToolBarShape = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | WS_BORDER,
				IDR_TB_SHAPE, 5, g_hInst, IDR_TB_COLOR, ToolBtn_Color, 5,
				16, 15, 16, 15, sizeof(TBBUTTON));

			//hToolBarColor = CreateWindow(TOOLBARCLASSNAME,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER,
			//	0,0,0,0,hWnd,0,g_hInst,NULL);
			//SendMessage(hToolBarColor,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
			//TBADDBITMAP colorbit;
			//colorbit.hInst=g_hInst;
			//colorbit.nID=IDR_TB_COLOR;
			//SendMessage(hToolBarColor,TB_ADDBITMAP,5,(LPARAM)&colorbit);
			//SendMessage(hToolBarColor,TB_ADDBUTTONS,(WPARAM)6,(LPARAM)ToolBtn_Color);
			
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
			// �α��� dlg����
			DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_LOGIN), hWnd, DlgProc);
			TCHAR buf[128];
			wsprintf(buf,TEXT("id: %s, pass:%s"), gId, gPass);
			//MBOX(buf);
			SetWindowText(hWnd, buf);
			//
			g_hDrawingToolDlgWnd = CreateDialog(GetModuleHandle(0), MAKEINTRESOURCE(IDD_TOOL), hWnd, DrawingToolDlgProc);
			ShowWindow(g_hDrawingToolDlgWnd, SW_SHOW);

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
			case IDC_BTN_PEN:
				CurrentShape = LINE;
				break;
			case IDC_BTN_ERASE:
				CurrentShape = RECTAN;
				CurrentPenColor = COLORWHITE;
				CurrentBrushColor = COLORWHITE;
				break;
			//����ó��(color)
			case ID_COLOR_RED:
			case IDC_BTN_RED:
				CurrentPenColor = COLORRED;
				break;
			case ID_COLOR_BLACK:
			case IDC_BTN_BLACK:
				CurrentPenColor = COLORBLACK;
				break;
			case ID_COLOR_WHITE:
			case IDC_BTN_WHITE: 
				CurrentPenColor = COLORWHITE;
				break;
			case ID_COLOR_GREEN:
			case IDC_BTN_GREEN:
				CurrentPenColor = COLORGREEN;
				break;
			case ID_COLOR_BLUE:
			case IDC_BTN_BLUE:
				CurrentPenColor = COLORBLUE;
				break;
			//����ó��(shape)
				
			case ID_SHAPE_LINE:
			case IDC_BTN_LINE:
				CurrentShape = LINE;
				break;
			case ID_SHAPE_RECT:
			case IDC_BTN_RECT:
				CurrentShape = RECTAN;
				break;
			case ID_SHAPE_ELLIPS:
			case IDC_BTN_ELLIPSE:
				CurrentShape = ELLIPSE;
				break;
			case ID_SHAPE_TRI:
			case IDC_BTN_TRI: 
				CurrentShape = TRI;
				break;
			case ID_SHAPE_FILLRECT:
				CurrentShape = RECTAN;
				CurrentBrushColor = CurrentPenColor;
				break;
				
			//�޴�ó��
			case ID_MYFILE_OPEN:
				MBOX(TEXT("open"));
				break;
			case ID_MYFILE_CLOSE:
				MBOX(TEXT("close"));
				break;
			case ID_TOOL_PEN :
				break;
			case ID_TOOL_ERASE:
				
				break;
			case ID_MYMENU_LINE:
				CurrentShape = LINE;
				break;
			case ID_MYMENU_RECT:
				CurrentShape = RECTAN;
				break;
			case ID_MYMENU_ELLIPSE:
				CurrentShape = ELLIPSE;
				break;
			case ID_MYMENU_TRI:
				CurrentShape = TRI;
				break;
			case ID_MYMENU_FILLRECT:
				CurrentShape = RECTAN;
				CurrentBrushColor = CurrentPenColor;
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
			//���� �׸��� ���� ���� ����
			//������ ����Ʈ�� WM_LBUTTONUP���� ó��
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
				else if(DrawList[i].ShapeMode == TRI)
				{
					DrawTriangle(hMemdc, DrawList[i].StartPos, DrawList[i].EndPos);
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