/*****************************************************************
 * IOCP
 * -> IO�񵿱⸦ ���� ��
 * -> Asyncselect, EventSelect ----> ��Ʈ��ũ �̺�Ʈ �񵿱�
 * --> IO�� ����� ó���ȴ�
 * 
 * Complite Port�� ���� �Ϸ� �޽��� ����
 *****************************************************************/

#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

#define BUFFERSIZE			128

typedef struct socketinfo{
	WSAOVERLAPPED Overlapped;
	SOCKET Sock;			// IO�۾��� ������ ����
	char Buf[BUFFERSIZE];	// Ŭ���̾�Ʈ�� io�� �����ϱ� ���� ���� ����
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

	// ����� �Ϸ� ������ ���� compliteport Ŀ�� ������Ʈ ���� 
	HANDLE hCp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(hCp == NULL)
	{ puts("hCp"); return;}

	//������ ����
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

	// listen socket �ʱ�ȭ
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

	// ���� �����带 ���Ʈ ������� �̿�
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
			CreateIoCompletionPort((HANDLE)ClientSock,	// IO�� �Ͼ ����
									hCp,
									(DWORD) ClientSock,	//�Ϸ� Ű��
									0);					// ������ : 0 �⺻
		// IO �۾��� ���� ����ü - �Լ��� ����
		SOCKETINFO* pSockInfo = (SOCKETINFO*) malloc(sizeof(SOCKETINFO));
		memset(pSockInfo, 0, sizeof(SOCKETINFO));

		pSockInfo->Sock = ClientSock;
		pSockInfo->wsaBuf.buf = pSockInfo->Buf;
		pSockInfo->wsaBuf.len = BUFFERSIZE;

		DWORD recvbyte;
		DWORD flag = 0;
		WSARecv(ClientSock,		// recv�� ����
			&pSockInfo->wsaBuf, // recv�� �ϱ����� ����
			1,				//���� ī��Ʈ
			&recvbyte,		//recv����Ʈ
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
		ret = GetQueuedCompletionStatus(hCp,			// ����� �Ϸ���Ʈ
								&tranbyte,		// ���� ����Ʈ
								(LPDWORD)&ClientSocket,	// �Ϸ� Ű��(socket)
								(LPOVERLAPPED*) &pSockInfo,	// �Ϸ� ���� ����
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
			printf("[%s] Ŭ���̾� ����\n", inet_ntoa(ClientAddr.sin_addr));
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