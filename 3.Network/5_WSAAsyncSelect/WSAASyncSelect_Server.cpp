#include <windows.h>
//----------------------------------------------------------------------------
// 다중 Echo Server !! 
//----------------------------------------------------------------------------

#define MBox(x) MessageBox( 0, x, "", MB_OK)
// 사용자 정의 메시지 !! 
#define UM_SOCKET WM_USER + 1
#define UM_CLIENT  WM_USER + 2

#define BUF_SIZE 128

SOCKET CreateServerSocket();	//  소켓 생성 !! 


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case UM_SOCKET:	// wParam : socket핸들  lparam :  네트워크 이벤트 
		{
			switch(  WSAGETSELECTEVENT( lParam) ) 
			{
			case FD_ACCEPT: 
				{				
					SOCKADDR_IN ClientAddr;
					int len = sizeof(ClientAddr); 
					SOCKET ClientSocket  = accept(  (SOCKET)wParam   , (SOCKADDR*)&ClientAddr, &len); 
					// ClientSocket + hwnd + send.recv  
					WSAAsyncSelect( ClientSocket, hwnd, UM_CLIENT , FD_WRITE|FD_READ|FD_CLOSE); 	
				} break; 
			}
		}
		return 0; 
	case UM_CLIENT: 
		{
			SOCKET ClientSocket = (SOCKET)wParam;
			char buf[BUF_SIZE] = {0};

			switch( WSAGETSELECTEVENT(lParam)) 
			{
			case FD_READ:
				{
					
					recv( ClientSocket, buf, BUF_SIZE, 0); 
					SetWindowText( hwnd, buf); 

						
				} 
			case FD_WRITE: 
				{
					send( ClientSocket, buf, BUF_SIZE, 0); 
				}
				break;
			case FD_CLOSE:  break;
			}
		}
				
		return 0; 
	case WM_LBUTTONDOWN:
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
	//-------------------------------------------------------------------------
	// Socket 관련 작업 !! 
	//-------------------------------------------------------------------------
	SOCKET ListenSocket  = CreateServerSocket(); 

	WSAAsyncSelect(  ListenSocket, // 네트워크 이벤트 발생하는 소켓 
							hwnd,			 // 네트워크 이벤트를 처리해줄 윈도우 
							UM_SOCKET,	  // 전달받을 메시지 
							FD_ACCEPT|FD_CLOSE ); // 처리할 이벤트  







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


SOCKET CreateServerSocket( )
{
	WSADATA wsa; // 버전정보   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL 로딩 
	{
		MBox("WSAStartup Error !! "); return INVALID_SOCKET ;
	}
	//1) 핸드폰 단말기 구입 -->  SOCKET : 통신을 하기위한 매개체 !! 
	SOCKET ServerSocket;  
	//2) 소켓 생성 !!		   // TCP/UDP   TCP   
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		MBox("socket() error!!");	return INVALID_SOCKET; 
	}
	//3) Usim 
	SOCKADDR_IN ServerAddr; 
	ServerAddr.sin_family		  = AF_INET;		    // TCP/UDP 
	ServerAddr.sin_port		  = htons(20000);	// 포트번호 
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	// 4) socket + sockaddr  ==   핸드폰 + Usim 	
	int ret =	bind( ServerSocket, // 소켓 
		(SOCKADDR*)&ServerAddr, //주소 구조체 
		sizeof(ServerAddr));		    // 주소의 크기 

	if( ret == SOCKET_ERROR) 
	{
		MBox("bind() error !! "); return INVALID_SOCKET; 
	}
	// 4) 통화 대기 !! 
	ret = 	  listen( ServerSocket,  // 기다릴 소켓 
		SOMAXCONN);	// 가능한 최대값 

	if( ret == SOCKET_ERROR ) 
	{
		MBox("listen() error !!"); return INVALID_SOCKET; 
	}
	return ServerSocket; 
}
