/***************************************************************
 * 커널 오브젝트를 활용한 network 프로그래밍 !!
 ***************************************************************
 * - Kernel Object --> 커널에서 관리하고 커널에 존재하는 객체 !!
 *		OS의 내부 kernel 영역에 저장되어지는 객체 !!
 *		--> Process, Thread, ComplitePort, pipe, Event, lock
 ***************************************************************
 * thread : 독립적으로 실행되는 하나의 실행의 흐름 !!
 * process VS thread
 * - cpu에 의해 처리되어지는 단위 
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
// Thread 함수
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
	char * str = "생성된 쓰레드";
	HANDLE hThread;
	hThread = CreateThread(0,			//보안 속성 0 -> 부모의 속성을 따라감
						  0,			// stack(쓰레드 함수의 스택메모리 사이즈) 0 -> 기본사이즈 1M
						  (LPTHREAD_START_ROUTINE)ThreadFnc, //함수의 주소
						  (LPVOID)str,
						  0,			// 초기상태 --> 생성과 동시에 쓰레드 시작
						  (LPDWORD)Threadid);	//생성된 쓰레드의 아이디값
		hThread = CreateThread(0,			//보안 속성 0 -> 부모의 속성을 따라감
						  0,			// stack(쓰레드 함수의 스택메모리 사이즈) 0 -> 기본사이즈 1M
						  (LPTHREAD_START_ROUTINE)ThreadFnc, //함수의 주소
						  (LPVOID)str,
						  0,			// 초기상태 --> 생성과 동시에 쓰레드 시작
						  (LPDWORD)Threadid);	//생성된 쓰레드의 아이디값
	while(1)
	{
		printf("[ %d ] 메인 쓰레드 !!\n" );
		busy();

	}
}

#endif

/***************************************************************
 * 멀티 쓰레드 - 레이스 컨디션
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
// 1) 배열에 값을 삽입하는 쓰레드!!
DWORD WINAPI InsertThreadFunc(LPVOID p)
{
	while(1)
	{
		g_Array[g_Count++] = 1;
		busy();
	}
	return 0;
}

// 2) 배열에 값을 삭제하는 쓰레드!!
DWORD WINAPI DeleteThreadFunc(LPVOID p)
{

	while(1)
	{
		g_Array[--g_Count] = 0;
		busy();
	}
	return 0;
}

// 3) 메인 쓰레드 배열의 값을 출력
int main(int argc, char* argv[])
{
	int Threadid = 0;
	char * str = "생성된 쓰레드";
	//HANDLE hThreadInsert, hThreadDelete;
	HANDLE hThread[2];

	hThread[0] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)InsertThreadFunc, //함수의 주소
						  0,0,0);	//생성된 쓰레드의 아이디값
	hThread[1] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)DeleteThreadFunc, //함수의 주소
						  0,0,0);
	while(1)
	{
		printf("[%d]-", g_Count);
		for(int i = 0; i<10; i++)
		{
			printf("[%d]", g_Array[i]);
		}
		printf("[ %d ] 메인 쓰레드 !!\n" );
		puts("");
		busy();
	}
}

#endif

/***************************************************************
 * Critical Section(임계영역)
 * --> 동기화 오브젝트
 * --> 공유된 자원에 접근을 하나의 쓰레드에서만 접근할 수 있도록 설정
 * --> 영역을 설정하고 영역안에서 공유 메모리는 하나의 쓰레드만 접근
 * --> Kernel 오브젝트는 아님
 * --> 하나의 프로세스안에서만 사용이 가능하다
 * --> Kernel object는 여러 프로세스에서 사용 가능
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

// critical section 객체 생성
CRITICAL_SECTION cs;

int g_Array[10];
int g_Count;

void busy()
{
	for(int i = 0; i<10000; i++)
		for(int j=0; j<10000;j++)
			;
}
// 1) 배열에 값을 삽입하는 쓰레드!!
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

// 2) 배열에 값을 삭제하는 쓰레드!!
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

// 3) 메인 쓰레드 배열의 값을 출력
int main(int argc, char* argv[])
{
	InitializeCriticalSection(&cs);
	int Threadid = 0;
	char * str = "생성된 쓰레드";
	//HANDLE hThreadInsert, hThreadDelete;
	HANDLE hThread[2];

	hThread[0] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)InsertThreadFunc, //함수의 주소
						  0,0,0);	//생성된 쓰레드의 아이디값
	hThread[1] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)DeleteThreadFunc, //함수의 주소
						  0,0,0);
	while(1)
	{
		EnterCriticalSection(&cs);
		printf("[%d]-", g_Count);
		for(int i = 0; i<10; i++)
		{
			printf("[%d]", g_Array[i]);
		}
		printf("[ %d ] 메인 쓰레드 !!\n" );
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
// 전역변수 !!
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
			printf("Client 종료\n"); break;
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
		
		printf("[%s] %d 접속\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
		CreateThread(0,0,ClientThread,(void *)&ClientSocket,0,0);
		char buf[MAX_BUFSIZE] = "접속을 환영합니다.";
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