//----------------------------------------------------------------------------
// TCP EventSelect Server �⺻ �ڵ� !! 
//----------------------------------------------------------------------------
#include <winsock2.h> 
#include <windows.h>
#include <stdio.h> 
#include <conio.h> 

#define BUF_SIZE 128 
//----------------------------------------------------------------------------
// 1) ������ �����ϸ� �����ڵ鿡 ���� �޽����� ���� !! 
// 2) ������ �����ϸ� �����ڵ鿡 ���� �޽����� ���� !!
// -->  �ҽ��ڵ� ���̱� !! 
// -->  �Ϲ�ȭ�� �Լ� ����� !! 
// -->  4~5�� 
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
	SOCKET    SockList[ WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT   EventList[ WSA_MAXIMUM_WAIT_EVENTS];
	     int SockCnt = 0 ;
//----------------------------------------------------------------------------
void RemoveSocket( int index )
{
	SOCKADDR_IN CloseAddr; 
	int len = sizeof(CloseAddr);

	getpeername( SockList[index], (SOCKADDR*)&CloseAddr, &len); 

	printf("[ %s ] ���� ���� !! \n",  inet_ntoa( CloseAddr.sin_addr));	
	
	closesocket(    SockList[index]); 
	WSACloseEvent( EventList[index]);

	for( int i = index ; i<SockCnt; i++) 
	{	
		SockList[i] = SockList[i+1];
		EventList[i] = EventList[i+1];
	}
	SockCnt--; 
}



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
	// 1) ���ϰ� �̺�Ʈ�� �����ϰ� �迭�� ���� 
		
	HANDLE hEvent = WSACreateEvent(); //�̺�Ʈ ��ü ���� !
	// 2) ���� !! 
	WSAEventSelect( ServerSocket,  // �̺�Ʈ�� ó���� ���� 
						  hEvent,			 // ��ȣ�� ������ �̺�Ʈ 
						  FD_ACCEPT|FD_CLOSE); 

	SockList[SockCnt] = ServerSocket; 
	EventList[SockCnt] = hEvent;
	SockCnt++; 

	int index = 0; 
	WSANETWORKEVENTS ne;  
	while(1) 
	{	
		// ���Ͽ��� ��Ʈ��ũ �̺�Ʈ �߻��ϸ� Event��ü�� �ñ׳� �Ǳ⸦ ��ٸ���!!
		index = WSAWaitForMultipleEvents( SockCnt,  // �ñ׳��� ��ٸ��� �̺�Ʈ �� 
										  EventList,  // �̺�Ʈ �迭 
										  FALSE, // 1���� �ñ׳��� �ŵ� ���� !! 
										  WSA_INFINITE, 
										  FALSE); 
		index -= WSA_WAIT_EVENT_0; 
	
		// 1) networkevent ����ü�� �̺�Ʈ ������ �����´� !! 
		// 2) EventList[index] �̺�Ʈ�� �ͽñ׳��� ���� 
		WSAEnumNetworkEvents( SockList[index], // �̺�Ʈ�� �߻��� ���� 
										EventList[index], // �ñ׳� �� �̺�Ʈ 
										&ne); // out put 

		if( ne.lNetworkEvents & FD_ACCEPT) 
		{
			
			if(ne.iErrorCode[FD_ACCEPT_BIT] != 0) 
			{			
				puts("accept error"); 
				return;
			}
			SOCKADDR_IN ClientAddr; 
			int len = sizeof(ClientAddr); 
			SOCKET ClientSocket;

			ClientSocket = accept( SockList[index] , // ����ϴ� ���� 
										 (SOCKADDR*)&ClientAddr, // Ŭ���̾�Ʈ�� �ּҸ� ������ ����ü
										 &len); 

			if ( ClientSocket == INVALID_SOCKET) 
			{
				puts("accept error "); return ;
			}	
			printf("[ %s ] : %d �� ����\n" ,   inet_ntoa( ClientAddr.sin_addr),
			ntohs( ClientAddr.sin_port )  ); 
			// ������ ���ϰ� ����� �̺�Ʈ ���� !! 
			WSAEVENT hClientEvent = WSACreateEvent(); 
			// socket + event 
			WSAEventSelect( ClientSocket, hClientEvent, FD_READ|FD_WRITE|FD_CLOSE); 
				
			SockList[SockCnt] = ClientSocket; 
			EventList[SockCnt] = hClientEvent; 
			SockCnt++; 
		}
		
		if( ne.lNetworkEvents & FD_READ || ne.lNetworkEvents & FD_WRITE) 
		{
			if( ne.lNetworkEvents & FD_READ && 
								ne.iErrorCode[FD_READ_BIT] != 0 ) 
			{			
				puts("FD_READ_BIT"); 
				return;
			}
			if( ne.lNetworkEvents & FD_WRITE && ne.iErrorCode[FD_WRITE_BIT] != 0) 
			{			
				puts("FD_WRITE_BIT"); 
				return;
			}
			char buf[BUF_SIZE] = {0};	
			
			recv( SockList[index], buf , BUF_SIZE, 0); 
			SOCKADDR_IN SenderAddr; 
			int len = sizeof(SenderAddr);

			getpeername( SockList[index], (SOCKADDR*)&SenderAddr, &len); 

			printf("[ %s ] %s\n",  inet_ntoa( SenderAddr.sin_addr) ,buf );	
			
			for( int i = 1; i< SockCnt; i++) 
			{
				if( i != index) 
				send( SockList[i], buf, BUF_SIZE, 0);
			}
		}
		if( ne.lNetworkEvents & FD_CLOSE) 
		{
			if(ne.iErrorCode[FD_CLOSE_BIT] != 0) 
			{			
				puts("FD_CLOSE_BIT"); 
				return;
			}
			RemoveSocket( index );
		
		}

	}
	/*
	
	// ȭ�鿡 ������ Ŭ���̾�Ʈ�� IP�� ��� !! 


	*/
	WSACleanup(); // DLL ���� 

}
//----------------------------------------------------------------------------
