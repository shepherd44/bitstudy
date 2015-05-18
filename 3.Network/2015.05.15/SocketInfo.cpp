#include "SocketInfo.h"

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
}
// 서버소켓 초기화
bool CreateListenSocket()
{
	int retval;
	
	g_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(g_ServerSocket == INVALID_SOCKET)
	{
		DisplayMessage();	return false;
	}
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	retval = bind(g_ServerSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	retval = listen(g_ServerSocket,SOMAXCONN);
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	HANDLE hEvent = WSACreateEvent();
	WSAEventSelect( g_ServerSocket, hEvent, FD_ACCEPT | FD_CLOSE);
	g_hEventList[0] = hEvent;
	return true;
}

SOCKET FindSocket(int index)
{
	//g_RoomInfo.push_back(

	return 0;
}

void CreateRoom(int num, const char* str)
{
	RoomInfo riTemp;
	int len = strlen(str);
	riTemp.cpRoomName = (char*)malloc(len);
	strcpy(riTemp.cpRoomName, str);
	riTemp.iRoomNum = num;
	g_RoomInfo.push_back(riTemp);
}

void SendAll(int index, const char *str, int len)
{
	for(int i = 1; i<g_SockCnt; i++)
	{
		if(i != index)
			send(SockList[i], str, len, 0);
	}
}
void RecvClient(int index)
{
	char buf[BUFFERSIZE];
	memset(buf, 0, BUFFERSIZE);
	SOCKADDR_IN senderaddr;
	int addrlen = sizeof(senderaddr);

	SOCKET ClientSocket = SockList[index];
	int retByte = recv(ClientSocket, buf, BUFFERSIZE, 0);
	getpeername(ClientSocket, (SOCKADDR *)&senderaddr, &addrlen);
	printf("[%s:%d] %s\n", inet_ntoa(senderaddr.sin_addr), htons(senderaddr.sin_port), buf);

	SendAll(index, buf, retByte);
}

bool AddClient(int index)
{
	SOCKET ClientSocket;
	SOCKADDR_IN sockaddr;
	int addrlen = sizeof(sockaddr);
	ClientSocket = accept(SockList[index], (SOCKADDR*)&sockaddr, &addrlen);
	if(ClientSocket == SOCKET_ERROR)
	{
		DisplayMessage();	return false;
	}
	
	// 이벤트 등록
	WSAEVENT hClientEvent = WSACreateEvent();
	WSAEventSelect(ClientSocket, hClientEvent, FD_WRITE | FD_READ | FD_CLOSE);
	// 전역변수에 저장
	SockList[g_SockCnt] = ClientSocket;
	g_hEventList[g_SockCnt] = hClientEvent;
	g_SockCnt++;
	// 접속메세지 전송
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP 서버] 클라이언트 접속: IP주소=%s, 포트 번호=%d\n",
		inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));
	SendAll(0, buf, retByte);

	return true;

}
void DeleteClient(int index)
{
	for(int i=0; i<g_SockCnt; i++)
	{
		if(i == index)
		{
			closesocket(SockList[i]);
			for(int j=i; j<g_SockCnt-1; j++)
				SockList[j] = SockList[j+1];
			g_SockCnt--;
			break;
		}
	}
}