//----------------------------------------------------------------------------
// TCP Server �⺻ �ڵ� !! 
//----------------------------------------------------------------------------

#include <winsock2.h> 
#include <windows.h> 
#include <stdio.h> 
#include <conio.h>

#define BUF_SIZE 128 

//----------------------------------------------------------------------------
DWORD WINAPI AcceptThread( LPVOID p);  // accept thread �Լ� 
DWORD WINAPI EchoThread( LPVOID p)  ;   // Echo Server �Լ� !! 
//----------------------------------------------------------------------------
void main()
{
	WSADATA wsa; // ��������   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL �ε� 
	{
		puts("WSAStartup Error !! "); return ;
	}
	//1) �ڵ��� �ܸ��� ���� -->  SOCKET : ����� �ϱ����� �Ű�ü !! 
	SOCKET ServerSocket;  
	//2) ���� ���� !!		   // TCP/UDP   TCP   
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  
	
	if( ServerSocket == INVALID_SOCKET)
	{
		puts("socket() error!!");	return; 
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
		puts("bind() error !! "); return ; 
	}
	// 4) ��ȭ ��� !! 
	ret = 	  listen( ServerSocket,  // ��ٸ� ���� 
				  	   SOMAXCONN);	// ������ �ִ밪 
		
	if( ret == SOCKET_ERROR ) 
	{
		puts("listen() error !!"); return ; 
	}
	// AcceptThread �ۼ��ؼ� �������� �����Ҽ� �ִ� ������ ���� !! 
	// --> ����ؼ� �����尡 ������ ó�� !! 
	HANDLE hAccept = CreateThread( 0 , 0, AcceptThread,
										     (LPVOID)ServerSocket, 0, 0);  
	// ����Լ� !! 
	// Ŀ�� ������Ʈ�� �ñ׳��� ��ٸ��� �Լ� !! 
	// -  �ñ׳�, �ͽñ׳�  
	WaitForSingleObject( hAccept , INFINITE); 
	
	WSACleanup(); // DLL ���� 

}
//----------------------------------------------------------------------------
DWORD WINAPI AcceptThread( LPVOID p)
{
	SOCKADDR_IN ClientAddr; 
	int len = sizeof(ClientAddr); 
	SOCKET ClientSocket;
	
	while(1)
	{	
		ClientSocket = accept( (SOCKET)p , // ����ϴ� ���� 
			(SOCKADDR*)&ClientAddr, // Ŭ���̾�Ʈ�� �ּҸ� ������ ����ü
			&len); 

		if ( ClientSocket == INVALID_SOCKET) 
		{
			puts("accept error "); return 0 ;
		}
		// ȭ�鿡 ������ Ŭ���̾�Ʈ�� IP�� ��� !! 
		printf("[ %s ] : %d �� ����\n" ,   inet_ntoa( ClientAddr.sin_addr),
			ntohs( ClientAddr.sin_port )  ); 
		
		HANDLE hEchoThread = CreateThread( 0,0, EchoThread, (LPVOID)ClientSocket, 0, 0);

	}
	return 0; 
}

DWORD WINAPI EchoThread( LPVOID p)
{
	
	SOCKET ClientSocket = (SOCKET)p; 
	SOCKADDR_IN ClientAddr; 
	int len = sizeof(ClientAddr); 
	// socket �ּҰ������� !! 
	getpeername( ClientSocket, (SOCKADDR*)&ClientAddr, &len);

	char buf[BUF_SIZE] = {0}; 
	while(1) 
	{
		recv( ClientSocket, buf, BUF_SIZE, 0); 
		printf("[%s] %s\n", inet_ntoa( ClientAddr.sin_addr) , buf );
		send( ClientSocket, buf, BUF_SIZE ,0);	
	}
}