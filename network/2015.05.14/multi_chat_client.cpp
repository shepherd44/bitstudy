/**************************************
 * tcp 클라이언트 
 ***************************************/
#if 1
#include <winsock2.h>
#include <stdio.h>
#include <process.h>

#define BUFFERSIZE	1024

SOCKET g_ServerSocket;
void DisplayMessage()
{
	wchar_t* pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg, 0, NULL);

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while(left > 0)
	{
		received = recv(s, ptr, left, flags);
		if(received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if(received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}
unsigned int WINAPI SendThread(void* pParam)
{
	return 0;
}

unsigned int WINAPI RecvThread(void* pParam)
{
	int retval = 0;
	char buf[BUFFERSIZE] = {0,};
	while(1)
	{
		retval = recv(g_ServerSocket,buf , BUFFERSIZE, 0);
		if(retval == SOCKET_ERROR)
		{
			DisplayMessage();	return 0;
		}
		buf[retval] = '\0';
		
		printf("[TCP 클라이언트][%d]데이터: %s\n", retval, buf);
	}
}
int main(int argv, char* argc[])
{
	int retval;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa))
	{
		DisplayMessage();	return -1;
	}
	
	g_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(g_ServerSocket == INVALID_SOCKET)
	{
		DisplayMessage();	return -1;
	}
	SOCKADDR_IN serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	// 서버에 전송요청
	retval = connect(g_ServerSocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();	return -1;
	}
	// 연결 완료
	//-----------------------------------------
	char buf[BUFFERSIZE];
	CloseHandle((HANDLE)_beginthreadex(0,0,RecvThread,0,0,0));
	
	int len;

	while(1)
	{
		memset(buf,0,sizeof(buf));
		printf("문자열 입력: ");
		if(fgets(buf, BUFFERSIZE - 1, stdin) == NULL)
			break;
		len = strlen(buf);
		if(buf[len - 1] == '\n')
			buf[len -1] = '\0';
		if(strlen(buf) == 0)
			break;
		//서버에 데이터 보내기
		retval = send(g_ServerSocket, buf, len, 0);
		if(retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}
		printf("[TCP 클라이언트] %d 바이트를 전송\n", retval);
	}

	//-------------------------------------------
	closesocket(g_ServerSocket);
	WSACleanup();
	return 0;

	
}
#endif