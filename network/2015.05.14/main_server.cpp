/*************************************************
 * tcp 기본서버 1:1 연결 예제
 *************************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>

#define BUFFERSIZE		1024

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, WSAGetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패! \n");
		return -1;
	}

	// 대기 소켓 생성
	SOCKET listenSock;
	listenSock = socket(AF_INET,		// 주소체계: 프로토콜마다 주소체계 다름. 인터넷 사용 IPv4
					SOCK_STREAM,	// 프로토콜 유형: TCP/IP 기반 사용
					0				//앞 두 인자로 프로토콜 결정이 명확하면 0사용 IPPROTO_TCP, IPPROTO_UDP
					);
	if(listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return 0;
	}

	// 대기 소켓의 로컬 주소. 포트 설정
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;	// 주소체계
	serveraddr.sin_port = htons(40100);	// 지역 포트번호
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}


	retval = listen(listenSock,
				SOMAXCONN);
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	SOCKET clientsock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFFERSIZE];

	while(1)
	{
		addrlen = sizeof(clientaddr);
		clientsock = accept(listenSock,
						(SOCKADDR *)&clientaddr,
						&addrlen);
		if(clientsock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}
		printf("\n[TCP 서버] 크라이언트 접속: IP 주소 = %s, 포트 번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
		while(1)
		{
			retval = recv(clientsock,
						buf,
						BUFFERSIZE,
						0);
			if(retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
			else if(retval == 0)
			{
				DisplayMessage();
				break;
			}
			else
			{
				buf[retval] = '\0';
				printf("[TCP서버] IP주소 = %s, 포트번호 = %d의 받은 메시지:%s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					buf);
			}
			
		}
		closesocket(clientsock);
		printf("\n[TCP 서버] 클라이언트 종료");

	}
	closesocket(listenSock);

	WSACleanup();
	return 0;
}


#endif

/***********************************************
 * TCP Server 쓰레드 사용 모델
 ***********************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>
#include <process.h>

#define BUFFERSIZE		1024

SOCKET g_listenSock;

// 오류 출력 함수
void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

bool CreateListenSocket()
{
	int retval;
	
	g_listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if(g_listenSock == INVALID_SOCKET)
	{
		DisplayMessage();	return false;
	}
	
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(g_listenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	retval = listen(g_listenSock,SOMAXCONN);
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}

unsigned int WINAPI ComThread(void* pParam)
{
	SOCKET clientsock = (SOCKET) pParam;
	SOCKADDR_IN clientaddr;
	int recvByte;
	char buf[BUFFERSIZE];
	while(1)
	{
		recvByte = recv(clientsock, buf, sizeof(buf), 0);
		if(recvByte == SOCKET_ERROR)
		{
			DisplayMessage();	break;
		}
		else if(recvByte == 0)
		{
			DisplayMessage();	break;
		}
		else
		{
			int addrlen = sizeof(clientaddr);
			int retval = getpeername(clientsock, (SOCKADDR*)&clientaddr, &addrlen);
			if(retval == SOCKET_ERROR)
			{
				DisplayMessage();	continue;
			}
			buf[recvByte] = '\0';
			printf("[TCP 서버] IP: %s, Port=%d의 메시지:%s\n",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port),
				buf);
			retval = send(clientsock, buf, recvByte, 0);
			if(retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
			
		}
	}
	closesocket(clientsock);
	printf("\n[TCP 서버] 클라이언트 종료: IP주소=%s,포트번호=%d",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port));
	return 0;
}

unsigned int WINAPI ListenThread(void* pParam)
{
	while(1)
	{
		SOCKET clientsock;
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);

		clientsock = accept(g_listenSock, (SOCKADDR *)&clientaddr, &addrlen);
		if(clientsock == SOCKET_ERROR)
		{
			DisplayMessage();	continue;
		}
		printf("\n[TCP 서버] 클라이언트 접속: IP주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
		unsigned int threadID;
		CloseHandle((HANDLE)_beginthreadex(0,0,ComThread,
			(void*)clientsock, 0,&threadID));
	}

	closesocket(g_listenSock);
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패! \n");
		return -1;
	}

	// (socket + bind + listen
	if(!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}

	unsigned int threadID;

	WaitForSingleObject((HANDLE)_beginthreadex(0,0,ListenThread, 0,0,&threadID), INFINITE);
	
	WSACleanup();
	return 0;
}


#endif