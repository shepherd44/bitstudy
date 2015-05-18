#include <windows.h>
//----------------------------------------------------------------------------
// ���� Echo Server !! 
//----------------------------------------------------------------------------

#define MBox(x) MessageBox( 0, x, "", MB_OK)
// ����� ���� �޽��� !! 
#define UM_SOCKET WM_USER + 1
#define UM_CLIENT  WM_USER + 2

#define BUF_SIZE 128

SOCKET CreateServerSocket();	//  ���� ���� !! 


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case UM_SOCKET:	// wParam : socket�ڵ�  lparam :  ��Ʈ��ũ �̺�Ʈ 
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
	// Socket ���� �۾� !! 
	//-------------------------------------------------------------------------
	SOCKET ListenSocket  = CreateServerSocket(); 

	WSAAsyncSelect(  ListenSocket, // ��Ʈ��ũ �̺�Ʈ �߻��ϴ� ���� 
							hwnd,			 // ��Ʈ��ũ �̺�Ʈ�� ó������ ������ 
							UM_SOCKET,	  // ���޹��� �޽��� 
							FD_ACCEPT|FD_CLOSE ); // ó���� �̺�Ʈ  







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
