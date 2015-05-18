/*****************************************************************
 * IOCP
 * -> IO비동기를 위한 모델
 * -> Asyncselect, EventSelect ----> 네트워크 이벤트 비동기
 * --> IO는 동기로 처리된다
 * 
 * Complite Port를 통해 완료 메시지 전송
 *****************************************************************/

#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

#define BUFFERSIZE			128

typedef struct socketinfo{
	WSAOVERLAPPED Overlapped;
	SOCKET Sock;			// IO작업을 수행할 소켓
	char Buf[BUFFERSIZE];	// 클라이언트와 io를 수행하기 위한 실제 버퍼
	WSABUF wsaBuf;
	int recvbyte;
	int sendbyte;
} SOCKETINFO;

DWORD WorkThread(LPVOID p);

void main()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) !=0)
	{
		puts("WSAStartup"); return ;
	}

	// 입출력 완료 통지를 위한 compliteport 커널 오브젝트 생성 
	HANDLE hCp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(hCp == NULL)
	{ puts("hCp"); return;}

	//쓰레드 생성
	SYSTEM_INFO si;
	HANDLE hThread;
	DWORD ThreadId;
	GetSystemInfo(&si);
	for(int i=0; i < si.dwNumberOfProcessors * 2; i++)
	{
		hThread = CreateThread(0, 0,(LPTHREAD_START_ROUTINE) WorkThread, (LPVOID)hCp, 0, &ThreadId);
		if(hThread == NULL)
		{
			puts("CreateThread"); return ;
		}
		CloseHandle(hThread);
	}

	// listen socket 초기화
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(ListenSocket == INVALID_SOCKET)
	{
		puts("socket"); return ;
	}
	SOCKADDR_IN ListenAddr;
	memset(&ListenAddr, 0, sizeof(ListenAddr));
	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_port = htons(20000);
	ListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(ListenSocket, (SOCKADDR*)&ListenAddr, sizeof(ListenAddr)) == SOCKET_ERROR)
	{
		puts("bind"); return;
	}
	if(listen(ListenSocket,SOMAXCONN) == SOCKET_ERROR)
	{
		puts("listen()");return;
	}

	// 메인 스레드를 어셉트 스레드로 이용
	int ret;
	SOCKET ClientSock;
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	memset(&ClientAddr, 0, len);
	while(1)
	{
		ClientSock = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &len);
		if(ClientSock == INVALID_SOCKET)
		{
			puts("accept"); return;
		}

		HANDLE hResult = // socket + cp
			CreateIoCompletionPort((HANDLE)ClientSock,	// IO가 일어날 소켓
									hCp,
									(DWORD) ClientSock,	//완료 키값
									0);					// 스레드 : 0 기본
		// IO 작업을 위한 구조체 - 함수로 빼기
		SOCKETINFO* pSockInfo = (SOCKETINFO*) malloc(sizeof(SOCKETINFO));
		memset(pSockInfo, 0, sizeof(SOCKETINFO));

		pSockInfo->Sock = ClientSock;
		pSockInfo->wsaBuf.buf = pSockInfo->Buf;
		pSockInfo->wsaBuf.len = BUFFERSIZE;

		DWORD recvbyte;
		DWORD flag = 0;
		WSARecv(ClientSock,		// recv할 소켓
			&pSockInfo->wsaBuf, // recv를 하기위한 버퍼
			1,				//버퍼 카운트
			&recvbyte,		//recv바이트
			&flag,			// 
			&pSockInfo->Overlapped,
			NULL);



	}

}

DWORD WorkThread(LPVOID p)
{
	HANDLE hCp = (HANDLE)p;
	DWORD tranbyte;
	int ret;
	SOCKET ClientSocket;
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKETINFO* pSockInfo;

	while(1)
	{
		ret = GetQueuedCompletionStatus(hCp,			// 대기할 완료포트
								&tranbyte,		// 전송 바이트
								(LPDWORD)&ClientSocket,	// 완료 키값(socket)
								(LPOVERLAPPED*) &pSockInfo,	// 완료 소켓 정보
								INFINITE);

		getpeername(pSockInfo->Sock, (SOCKADDR*)&ClientAddr, &len);

		if(ret == 0 || tranbyte == 0)
		{
			if(ret == 0)
			{
				puts("GetQueuedCompletionStatus()");
				DWORD t1, t2;
				WSAGetOverlappedResult(ClientSocket, &pSockInfo->Overlapped,
									&t1, FALSE, &t2);
			}

			closesocket(pSockInfo->Sock);
			printf("[%s] 클라이언 종료\n", inet_ntoa(ClientAddr.sin_addr));
			free(pSockInfo);
			continue;
			if(tranbyte == 0)
				break;
		}
		//Echo
		DWORD sendbyte;
		printf("[%s]%s\n", inet_ntoa(ClientAddr.sin_addr), pSockInfo->wsaBuf.buf);
		WSASend(pSockInfo->Sock, &pSockInfo->wsaBuf, 1, &sendbyte, 0, &pSockInfo->Overlapped, NULL);

		//

		
		DWORD id = GetCurrentThreadId();
		printf("Thread ID : %d\n", id);
		Sleep(500);

	}
}