/***********************************************
 *
 ***********************************************/
#if 1

#include "amolang.h"
#include "resource.h"
#include <commctrl.h>
#pragma comment(lib, "Msimg32.lib")
// 매크로

// 함수
ATOM MyRegisterClass(HINSTANCE);
HWND InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK ConnectDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);

// Global Instance
HINSTANCE g_hInst;
HWND g_hWnd;
TCHAR szWindowClass[MAX_LOADSTRING] = TEXT("game");
TCHAR szTitle[MAX_LOADSTRING] = TEXT("omok");
GAMEMAP g_Map;
SOCKET g_ServerSocket;

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HBITMAP hBitMap, hBitBlack, hBitWhite, hMemBit;
	HBITMAP hOldBit1, hOldBit2;
	HDC hdc, hMapDC, hMemDC, hStoneDC;
	static HANDLE hTimerMe, hTimerCom;

	static int TimeMe, TimeCom;
	static char* strTime;
	static SpriteImage siTimeimage;
	static SYSTEMTIME st;

	static ASYNCSOCKET ServerSock;
	static char buf[GAMEBUFFERSIZE];

	static OMOKMESSAGE omokmsg;

	
	//처리시작----------------------------------------
	switch(iMessage) {
	case UM_CLIENT:
		{
			SOCKET ClientSocket = (SOCKET)wParam;			
			switch( WSAGETSELECTEVENT(lParam)) 
			{
			case FD_READ:
				{
					recv(ClientSocket, (char*)&omokmsg, BUFFERSIZE, 0);
					if(omokmsg.OmokMsg == PTMSG)
					{
						
					}
					else if(omokmsg.OmokMsg == WINMSG)
					{
						// 필요 없을듯
					}
					else if(omokmsg.OmokMsg == CHATMSG)
					{
						//추후 구현
					}
					else if(omokmsg.OmokMsg == TURNMSG)
					{
						g_Map.GameState = WAITING;
					}
				}
				break;
			case FD_WRITE:
				{
					if(g_Map.GameState == ROOMMAKING)
					{
						omokmsg.OmokMsg = ROOMMSG;
						omokmsg.room.roomindex = g_Map.RoomIndex;
						strcpy(omokmsg.room.roomname,g_Map.RoomName);
					}
					send( ClientSocket, (char*)&omokmsg, BUFFERSIZE, 0);
				}
				break;
			case FD_CLOSE:
				{
					MessageBox(hWnd,TEXT("서버가 종료됨"), TEXT("서버 종료"),MB_OK);
					g_Map.GameState = NOTPLAY;
				}
				break;
			}
		}	
		return 0; 

	case WM_LBUTTONDOWN:
		{
			if(g_Map.GameState == PLAY)
			{
				if(g_Map.turn == TURN1)
				{
					// 좌표 -> 배열
					OMOKMATRIX pt = PointToMatrix(MAKEPOINTS(lParam));

					// 바둑알 두기
					if(PutStone(&g_Map, pt) == false)
						return 0;
					// 내가 둔 수를 상대에게 전송
					omokmsg.OmokMsg = PTMSG;
					omokmsg.PT.pt = pt;
					omokmsg.PT.turn = TURN1;
					SendMessage(hWnd, UM_CLIENT, g_ServerSocket, FD_WRITE);
					// 타이머 셋팅
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

					// 승리인지 확인
					if(IsWin(&g_Map) == BLACK)
						g_Map.GameState = BLACKWIN;
					else if(IsWin(&g_Map) == WHITE)
						g_Map.GameState = WHITEWIN;

					InvalidateRect(hWnd , 0,0);
				}
			}
			else if(g_Map.GameState == WHITEWIN)	//게임이 플레이중이 아닐경우
			{
				SendMessage(hWnd, UM_CLIENT, g_ServerSocket, FD_WRITE);


			}
			else if(g_Map.GameState == INIT)
			{

				SendMessage(hWnd, UM_CLIENT, g_ServerSocket, FD_WRITE);

			}
			else
			{}
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
			for(int i= 0; i<PANROW; i++) 
			{
				for(int j = 0; j < PANCOL; j++) 
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
	case WM_CREATE:
		{
			memset(&omokmsg, 0, sizeof(omokmsg));
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
			// 버퍼 초기화
			memset(buf, 0, GAMEBUFFERSIZE);
			// dialog 박스로 접속
		}
		return 0;
	case WM_DESTROY:
	{
		closesocket(g_ServerSocket);
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


BOOL CALLBACK ConnectDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	SOCKET ServerSocket;
	static HWND hEditIp, hEditPort, hEditRoom;
	DWORD ip = 0;
	switch(iMessage) {
	case WM_INITDIALOG:
		hEditIp = GetDlgItem(hDlg, IDC_IPADDRESS);
		hEditPort = GetDlgItem(hDlg, IDC_EDIT_PORT);
		hEditRoom = GetDlgItem(hDlg, IDC_EDIT_ROOM);
		return TRUE;
	case WM_COMMAND:
		{
			switch(wParam)
			{
			case IDOK:
				//TCHAR bufIp[BUFFERSIZE];
				
				int Port;
				//TCHAR bufPort[BUFFERSIZE];
				TCHAR bufRoom[BUFFERSIZE];
				//memset(bufIp, 0, BUFFERSIZE);
				//memset(bufPort, 0, BUFFERSIZE);
				memset(bufRoom, 0, BUFFERSIZE);
				
				SendMessage(hEditIp, IPM_GETADDRESS, 0, (LPARAM)&ip);
				//네트워크에 쓰일 경우에 아래와 같이 쓴다-----------

				Port = GetDlgItemInt(hDlg, IDC_EDIT_PORT,NULL,0);
				GetDlgItemText(hDlg, IDC_EDIT_ROOM,bufRoom,BUFFERSIZE);
			
				SOCKADDR_IN ServerAddr;
				ServerAddr.sin_family = AF_INET;		    // TCP/UDP 
				ServerAddr.sin_port = htons(Port);	// 포트번호 
				ServerAddr.sin_addr.s_addr =  htonl(ip);
				ServerAddr.sin_port = htons(40100);	// 포트번호 
				ServerAddr.sin_addr.s_addr =  inet_addr("127.0.0.1");
				ServerSocket = CreateClientSocket(&ServerAddr);
				
				g_ServerSocket = ServerSocket;
				//send(
				if(WSAAsyncSelect(ServerSocket, g_hWnd, UM_CLIENT, FD_WRITE|FD_READ|FD_CLOSE) != 0)
				{
					MBOX("select() error!!");	return INVALID_SOCKET; 
				}
				g_Map.RoomIndex = atoi(bufRoom);
				
				EndDialog(hDlg, 0);
				break;

			case IDCANCEL:
				EndDialog(hDlg, 0);
			}
		}
		return false;
	case WM_KEYDOWN:
		return 0;
	case WM_CHAR:
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);

			EndPaint(hDlg, &ps);
			break;
		}
	}
	return FALSE;

}
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
					 ,LPSTR lpszCmdParam,int nCmdShow)
{
	g_hInst=hInstance;
	MyRegisterClass(hInstance);
	HWND hWnd = InitInstance(hInstance, nCmdShow);
	if(hWnd == 0)
		return FALSE;
	g_hWnd = hWnd;
	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_CONNECT), hWnd, ConnectDlgProc);
	g_Map.GameState = ROOMMSG;
	SendMessage(g_hWnd, UM_CLIENT, g_ServerSocket, FD_WRITE);
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
	WndClassEx.hIcon		= LoadIcon(hInstance,(LPCSTR)IDB_BLACK);
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



#endif