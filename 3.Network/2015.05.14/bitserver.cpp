/***************************************************************
 * Ŀ�� ������Ʈ�� Ȱ���� network ���α׷��� !!
 ***************************************************************
 * - Kernel Object --> Ŀ�ο��� �����ϰ� Ŀ�ο� �����ϴ� ��ü !!
 *		OS�� ���� kernel ������ ����Ǿ����� ��ü !!
 *		--> Process, Thread, ComplitePort, pipe, Event, lock
 ***************************************************************
 * thread : ���������� ����Ǵ� �ϳ��� ������ �帧 !!
 * process VS thread
 * - cpu�� ���� ó���Ǿ����� ���� 
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

void busy()
{
	for(int i = 0; i<10000; i++)
		for(int j=0; j<10000;j++)
			;
}
// Thread �Լ�
DWORD WINAPI ThreadFnc(LPVOID p)
{

	while(1)
	{
		puts((char*)p);
		busy();
	}
	return 0;
}
int main(int argc, char* argv[])
{
	int Threadid = 0;
	char * str = "������ ������";
	HANDLE hThread;
	hThread = CreateThread(0,			//���� �Ӽ� 0 -> �θ��� �Ӽ��� ����
						  0,			// stack(������ �Լ��� ���ø޸� ������) 0 -> �⺻������ 1M
						  (LPTHREAD_START_ROUTINE)ThreadFnc, //�Լ��� �ּ�
						  (LPVOID)str,
						  0,			// �ʱ���� --> ������ ���ÿ� ������ ����
						  (LPDWORD)Threadid);	//������ �������� ���̵�
		hThread = CreateThread(0,			//���� �Ӽ� 0 -> �θ��� �Ӽ��� ����
						  0,			// stack(������ �Լ��� ���ø޸� ������) 0 -> �⺻������ 1M
						  (LPTHREAD_START_ROUTINE)ThreadFnc, //�Լ��� �ּ�
						  (LPVOID)str,
						  0,			// �ʱ���� --> ������ ���ÿ� ������ ����
						  (LPDWORD)Threadid);	//������ �������� ���̵�
	while(1)
	{
		printf("[ %d ] ���� ������ !!\n" );
		busy();

	}
}

#endif

/***************************************************************
 * ��Ƽ ������ - ���̽� �����
 ***************************************************************/

#if 0
#include <stdio.h>
#include <winsock.h>

int g_Array[10];
int g_Count;

void busy()
{
	for(int i = 0; i<10000; i++)
		for(int j=0; j<10000;j++)
			;
}
// 1) �迭�� ���� �����ϴ� ������!!
DWORD WINAPI InsertThreadFunc(LPVOID p)
{
	while(1)
	{
		g_Array[g_Count++] = 1;
		busy();
	}
	return 0;
}

// 2) �迭�� ���� �����ϴ� ������!!
DWORD WINAPI DeleteThreadFunc(LPVOID p)
{

	while(1)
	{
		g_Array[--g_Count] = 0;
		busy();
	}
	return 0;
}

// 3) ���� ������ �迭�� ���� ���
int main(int argc, char* argv[])
{
	int Threadid = 0;
	char * str = "������ ������";
	//HANDLE hThreadInsert, hThreadDelete;
	HANDLE hThread[2];

	hThread[0] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)InsertThreadFunc, //�Լ��� �ּ�
						  0,0,0);	//������ �������� ���̵�
	hThread[1] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)DeleteThreadFunc, //�Լ��� �ּ�
						  0,0,0);
	while(1)
	{
		printf("[%d]-", g_Count);
		for(int i = 0; i<10; i++)
		{
			printf("[%d]", g_Array[i]);
		}
		printf("[ %d ] ���� ������ !!\n" );
		puts("");
		busy();
	}
}

#endif

/***************************************************************
 * Critical Section(�Ӱ迵��)
 * --> ����ȭ ������Ʈ
 * --> ������ �ڿ��� ������ �ϳ��� �����忡���� ������ �� �ֵ��� ����
 * --> ������ �����ϰ� �����ȿ��� ���� �޸𸮴� �ϳ��� �����常 ����
 * --> Kernel ������Ʈ�� �ƴ�
 * --> �ϳ��� ���μ����ȿ����� ����� �����ϴ�
 * --> Kernel object�� ���� ���μ������� ��� ����
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

// critical section ��ü ����
CRITICAL_SECTION cs;

int g_Array[10];
int g_Count;

void busy()
{
	for(int i = 0; i<10000; i++)
		for(int j=0; j<10000;j++)
			;
}
// 1) �迭�� ���� �����ϴ� ������!!
DWORD WINAPI InsertThreadFunc(LPVOID p)
{
	while(1)
	{
		EnterCriticalSection(&cs);
		g_Array[g_Count++] = 1;
		busy();
		LeaveCriticalSection(&cs);
	}
	return 0;
}

// 2) �迭�� ���� �����ϴ� ������!!
DWORD WINAPI DeleteThreadFunc(LPVOID p)
{

	while(1)
	{
		EnterCriticalSection(&cs);
		g_Array[--g_Count] = 0;
		busy();
		LeaveCriticalSection(&cs);
	}
	return 0;
}

// 3) ���� ������ �迭�� ���� ���
int main(int argc, char* argv[])
{
	InitializeCriticalSection(&cs);
	int Threadid = 0;
	char * str = "������ ������";
	//HANDLE hThreadInsert, hThreadDelete;
	HANDLE hThread[2];

	hThread[0] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)InsertThreadFunc, //�Լ��� �ּ�
						  0,0,0);	//������ �������� ���̵�
	hThread[1] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)DeleteThreadFunc, //�Լ��� �ּ�
						  0,0,0);
	while(1)
	{
		EnterCriticalSection(&cs);
		printf("[%d]-", g_Count);
		for(int i = 0; i<10; i++)
		{
			printf("[%d]", g_Array[i]);
		}
		printf("[ %d ] ���� ������ !!\n" );
		busy();
		LeaveCriticalSection(&cs);
	}

	DeleteCriticalSection(&cs);
}

#endif

#if 0
#include <windows.h>
#include <stdio.h>
#include <winsock.h>
#include <process.h>

#define MAX_BUFSIZE	1024
// �������� !!
SOCKET ServerSocket;

DWORD WINAPI ClientThread(void* pParam)
{
	SOCKET ClientSocket = *(SOCKET*)pParam;
	SOCKADDR_IN ClientAddr;

	while(1)
	{
		char buf[MAX_BUFSIZE] = {0,};
		int retVal = recv(ClientSocket,buf, MAX_BUFSIZE, 0);
		if(retVal == 0)
		{
			printf("Client ����\n"); break;
		}
		else if(retVal == SOCKET_ERROR)
		{
			puts("socket error"); break;
		}
		else
		{
			puts(buf);
			send(ClientSocket, buf, retVal, 0);
		}
	}



	return 0;
}
DWORD WINAPI AcceptThread(void* pParam)
{
	while(1)
	{
		SOCKADDR_IN ClientAddr;
		int len = sizeof(ClientAddr);
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &len);

		if(ClientSocket == SOCKET_ERROR)
		{
			puts("accept error"); continue;
		}
		
		printf("[%s] %d ����\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
		CreateThread(0,0,ClientThread,(void *)&ClientSocket,0,0);
		char buf[MAX_BUFSIZE] = "������ ȯ���մϴ�.";
		send(ClientSocket,buf,MAX_BUFSIZE,0);
	
	}
	closesocket(ServerSocket);
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("WSAStartup Error !!\n");
		return -1;
	}
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if( ServerSocket == INVALID_SOCKET)
	{
		puts("Socket() error!\n"); return -1;
	}

	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(40100);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if( ret == SOCKET_ERROR)
	{
		puts("bind() error !!");	return -1;
	}

	ret = listen(ServerSocket, SOMAXCONN);
	if(ret == SOCKET_ERROR)
	{
		puts("listen() error\n"); return -1;
	}
	//---------------------------------------------

	HANDLE hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)AcceptThread,0,0,0);
	//----------------------------------------------

	WaitForSingleObject(hThread, INFINITE);
	WSACleanup();
}

#endif