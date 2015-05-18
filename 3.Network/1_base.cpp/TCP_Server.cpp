//----------------------------------------------------------------------------
// TCP Server 기본 코드 !! 
//----------------------------------------------------------------------------
#include <winsock2.h> 
#include <windows.h>
#include <stdio.h> 
#include <conio.h> 
//----------------------------------------------------------------------------
DWORD WINAPI AcceptThread( LPVOID p);	// accept thread 함수
//----------------------------------------------------------------------------
void main()
{
	WSADATA wsa; // 버전정보   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL 로딩 
	{
		puts("WSAStartup Error !! "); return ;
	}
	//1) 핸드폰 단말기 구입 -->  SOCKET : 통신을 하기위한 매개체 !! 
	SOCKET ServerSocket;  
	//2) 소켓 생성 !!		   // TCP/UDP   TCP   
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		puts("socket() error!!");	return ; 
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
		puts("bind() error !! "); return ; 
	}
	// 4) 통화 대기 !! 
	ret = 	  listen( ServerSocket,  // 기다릴 소켓 
		SOMAXCONN);	// 가능한 최대값 

	if( ret == SOCKET_ERROR ) 
	{
		puts("listen() error !!"); return ; 
	}


	// Accept
	// --> 계속해서 쓰레드가 접속자 처리!!


	WSACleanup(); // DLL 정리 

}
//----------------------------------------------------------------------------
DWORD WINAPI AcceptThread( LPVOID p)
{

	SOCKADDR_IN ClientAddr; 
	int len = sizeof(ClientAddr); 
	SOCKET ClientSocket;

	while(1)
	{
		ClientSocket = accept( ServerSocket, // 대기하는 소켓 
			(SOCKADDR*)&ClientAddr, // 클라이언트의 주소를 가져올 구조체
			&len); 


		if ( ClientSocket == INVALID_SOCKET) 
		{
			puts("accept error "); return ;
		}
		// 화면에 접속한 클라이언트의 IP를 출력 !! 

		printf("[ %s ] : %d 님 접속\n" ,   inet_ntoa( ClientAddr.sin_addr),
			ntohs( ClientAddr.sin_port )  ); 
	}
	return 0;
}
