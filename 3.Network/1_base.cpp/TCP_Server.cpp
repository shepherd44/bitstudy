//----------------------------------------------------------------------------
// TCP Server �⺻ �ڵ� !! 
//----------------------------------------------------------------------------
#include <winsock2.h> 
#include <windows.h>
#include <stdio.h> 
#include <conio.h> 
//----------------------------------------------------------------------------
DWORD WINAPI AcceptThread( LPVOID p);	// accept thread �Լ�
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
		puts("socket() error!!");	return ; 
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


	// Accept
	// --> ����ؼ� �����尡 ������ ó��!!


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
		ClientSocket = accept( ServerSocket, // ����ϴ� ���� 
			(SOCKADDR*)&ClientAddr, // Ŭ���̾�Ʈ�� �ּҸ� ������ ����ü
			&len); 


		if ( ClientSocket == INVALID_SOCKET) 
		{
			puts("accept error "); return ;
		}
		// ȭ�鿡 ������ Ŭ���̾�Ʈ�� IP�� ��� !! 

		printf("[ %s ] : %d �� ����\n" ,   inet_ntoa( ClientAddr.sin_addr),
			ntohs( ClientAddr.sin_port )  ); 
	}
	return 0;
}
