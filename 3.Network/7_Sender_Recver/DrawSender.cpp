//---------------------------------------------------------------
//  ��Ʈ��ũ �׸���  
//---------------------------------------------------------------

#include <windows.h>

#define MBox(x) MessageBox( 0, x, "", MB_OK)
//-------------------------------------------------------------------
typedef struct Draw
{
	int   Width; 
	COLORREF color; 
	POINTS Spt;
	POINTS Ept; 
}DRAW;
//--------------------------------------------------------------------
DRAW  DrawList[4096]; 
int cnt = 0; 
//--------------------------------------------------------------------

SOCKET CreateServerSocket( ); 
DWORD AcceptThread( LPVOID p);
//  ���� ���� 
SOCKET SockList[32]; 
int SockCnt = 0; 

//--------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static COLORREF color ; 
	static int width;  
	static bool mode = false; 
	switch( msg )
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps); 

			for( int i = 0; i<cnt; i++) 
			{
				HPEN hpen =  CreatePen( PS_SOLID, DrawList[i].Width, DrawList[i].color); 
				HPEN old = (HPEN)SelectObject(hdc, hpen); 
				MoveToEx( hdc, DrawList[i].Spt.x, DrawList[i].Spt.y,0); 
				LineTo( hdc,   DrawList[i].Ept.x, DrawList[i].Ept.y); 
				for( int j = 0; j< SockCnt ; j++)
				{
					send( SockList[i],  (char*)&DrawList[i], sizeof(DrawList[i]), 0); 
				}
				DeleteObject( hpen);
				SelectObject( hdc, old);
			}
			EndPaint(hwnd, &ps); 
		}
		return 0;
	case WM_LBUTTONUP: 
		mode =false; 

		return 0; 
	case WM_MOUSEMOVE: 
		if( mode == true) 
		{
			DrawList[cnt].Ept = MAKEPOINTS(lParam); 
			DrawList[cnt].color  = RGB( rand()%255, rand()%255,rand()%255); 
			DrawList[cnt].Width = rand()%10+1;
			cnt++; 
			DrawList[cnt].Spt = MAKEPOINTS(lParam); 
			InvalidateRect( hwnd, 0, 0 );
			
		}
		return 0; 
	case WM_LBUTTONDOWN:
		mode = true; 
		DrawList[cnt].Spt = MAKEPOINTS(lParam); 	
		return 0;
		
	case WM_RBUTTONDOWN:
		return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE,
				   PSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;		
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	
	wc.hCursor			= LoadCursor( 0, IDC_ARROW );
	wc.hIcon			= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance		= hInstance; 
	wc.lpfnWndProc		= WndProc;
	wc.lpszClassName	= "First";
	wc.lpszMenuName		= 0;
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	
	RegisterClass( &wc);
	
	HWND hwnd = CreateWindowEx( 0, "first",	"Hello", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, 0, 
		hInstance,
		0);  
	// ���� ���� ���� !! 
	SOCKET ListenSocket =	 CreateServerSocket();

	HANDLE hThread = CreateThread( 0, 0, 
											   (LPTHREAD_START_ROUTINE)AcceptThread, 
											   (LPVOID)ListenSocket, 
											   0,0); 

	ShowWindow( hwnd, SW_SHOW );
	UpdateWindow( hwnd );
	
	MSG msg;
	while( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
	return 0;
}
//----------------------------------------------------------------------------
DWORD AcceptThread( LPVOID p)
{
	SOCKADDR_IN ClientAddr; 
	int len = sizeof(ClientAddr); 
	SOCKET ListenSocket = (SOCKET)p; 
	while(1) 
	{
		SockList[SockCnt] = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &len); 
		SockCnt++; 
	}
}
//----------------------------------------------------------------------------
SOCKET CreateServerSocket( )
{
	WSADATA wsa; // ��������   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL �ε� 
	{
		MBox("WSAStartup Error !! "); return INVALID_SOCKET ;
	}
	//1) �ڵ��� �ܸ��� ���� -->  SOCKET : ����� �ϱ����� �Ű�ü !! 
	SOCKET ServerSocket;  
	//2) ���� ���� !!		   // TCP/UDP   TCP   
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		MBox("socket() error!!");	return INVALID_SOCKET; 
	}
	//3) Usim 
	SOCKADDR_IN ServerAddr; 
	ServerAddr.sin_family		  = AF_INET;		    // TCP/UDP 
	ServerAddr.sin_port		  = htons(20000);	// ��Ʈ��ȣ 
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	// 4) socket + sockaddr  ==   �ڵ��� + Usim 	
	int ret =	bind( ServerSocket, // ���� 
		(SOCKADDR*)&ServerAddr, //�ּ� ����ü 
		sizeof(ServerAddr));		    // �ּ��� ũ�� 

	if( ret == SOCKET_ERROR) 
	{
		MBox("bind() error !! "); return INVALID_SOCKET; 
	}
	// 4) ��ȭ ��� !! 
	ret = 	  listen( ServerSocket,  // ��ٸ� ���� 
		SOMAXCONN);	// ������ �ִ밪 

	if( ret == SOCKET_ERROR ) 
	{
		MBox("listen() error !!"); return INVALID_SOCKET; 
	}
	return ServerSocket; 
}
