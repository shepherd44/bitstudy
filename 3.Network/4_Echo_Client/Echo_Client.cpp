//-----------------------------------------------------------
// 1) 1:1 채팅 서버 
//-----------------------------------------------------------
// 2) 멀티쓰레드 다중 채팅 서버 !! 
//-----------------------------------------------------------

#include <winsock2.h> 
#include <stdio.h>

#define BUF_SIZE 128 

void main() 
{	
	int ret; 
	WSADATA wsa; 
	
	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) 
	{ puts("WSAStartup");	return;                } 
	
	SOCKET Socket = socket( AF_INET, SOCK_STREAM, 0); 
	if( Socket == INVALID_SOCKET) 
	{ puts("socket"); return;}
	// 접속 서버 주소 !! 
	SOCKADDR_IN ServerAddr; 
	ServerAddr.sin_family = AF_INET; 
	ServerAddr.sin_port = htons(20000); 
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	ret = connect( Socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)); 
	if( ret == SOCKET_ERROR) 
	{ puts("connect"); return ; }
		
	char buf[ BUF_SIZE ] = {0};
	
	while(1)
	{	
		printf("[ 보낼 메시지 ] ");
		gets( buf); 
		send( Socket , buf, BUF_SIZE, 0); 
		memset(buf, 0, BUF_SIZE); 
		recv( Socket, buf, BUF_SIZE,0); 
		printf("[ 받은 메시지 ] %s \n", buf); 
	}
	WSACleanup();
}