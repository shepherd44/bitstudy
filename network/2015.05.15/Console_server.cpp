/**********************************************************
 * �ܼ� ���� �⺻ �ڵ�
 **********************************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>

#define BUFFERSIZE			1024

// ���� ����
#define MAX_SOCKET_NUM		WSA_MAXIMUM_WAIT_EVENTS
#define g_ServerSocket		g_ServerSocket
#define EventList[0]	EventList[0]

SOCKET SockList[MAX_SOCKET_NUM];
WSAEVENT EventList[MAX_SOCKET_NUM];
int SockCnt;

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
}

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
	WSAEventSelect( g_ServerSock, hEvent, FD_ACCEPT | FD_CLOSE);
	g_ServerSockEvent = hEvent;
	g_sockcnt++;
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
			printf("end client \n");
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
			printf("[TCP ����] IP: %s, Port=%d�� �޽���:%s\n",
				inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port),buf);
			
		}
	}
	closesocket(clientsock);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s,��Ʈ��ȣ=%d", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	return 0;
}

unsigned int WINAPI ListenThread(void* pParam)
{
	while(1)
	{
		SOCKET ClientSocket;
		SOCKADDR_IN SocketAddr;
		int addrlen = sizeof(SocketAddr);
		ClientSocket = accept(g_ServerSocket, (SOCKADDR *)&SocketAddr, &addrlen);
		if(ClientSocket == SOCKET_ERROR)
		{
			DisplayMessage();	continue;
		}
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(SocketAddr.sin_addr), ntohs(SocketAddr.sin_port));
		unsigned int threadID;
		CloseHandle((HANDLE)_beginthreadex(0,0,ComThread,(void*)ClientSocket, 0,&threadID));
	}
	closesocket(g_ServerSocket);
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}


	//===================================================

	WSAWaitForMultipleEvents((HANDLE)_beginthreadex(0,0,ListenThread, 0,0,0), INFINITE);
	//===================================================

	WSACleanup();
	return 0;
}
#endif
/**********************************************************
 * SelectEvnet() ä��
 **********************************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>

#define BUFFERSIZE			1024

// ���� ����
#define MAX_SOCKET_NUM		WSA_MAXIMUM_WAIT_EVENTS
#define g_ServerSocket		g_ServerSocket
#define EventList[0]	EventList[0]

SOCKET SockList[MAX_SOCKET_NUM];
WSAEVENT EventList[MAX_SOCKET_NUM];
int g_SockCnt;

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
}

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
	EventList[0] = hEvent;
	g_SockCnt++;
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
			printf("end client \n");
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
			printf("[TCP ����] IP: %s, Port=%d�� �޽���:%s\n",
				inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port),buf);
			
		}
	}
	closesocket(clientsock);

	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s,��Ʈ��ȣ=%d", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	return 0;
}

unsigned int WINAPI ListenThread(void* pParam)
{
	while(1)
	{
		SOCKET ClientSocket;
		SOCKADDR_IN SocketAddr;
		int addrlen = sizeof(SocketAddr);
		ClientSocket = accept(g_ServerSocket, (SOCKADDR *)&SocketAddr, &addrlen);
		if(ClientSocket == SOCKET_ERROR)
		{
			DisplayMessage();	continue;
		}
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(SocketAddr.sin_addr), ntohs(SocketAddr.sin_port));
		unsigned int threadID;
		CloseHandle((HANDLE)_beginthreadex(0,0,ComThread,(void*)ClientSocket, 0,&threadID));
	}
	closesocket(g_ServerSocket);
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// ����ó��
	//===================================================
	int index = 0;
	WSANETWORKEVENTS neEvents;
	char buf[BUFFERSIZE];
	memset(buf, 0, BUFFERSIZE);
	while(1)
	{
		// �̺�Ʈ �ñ׳� ����
		index = WSAWaitForMultipleEvents(g_SockCnt, EventList,
			FALSE, WSA_INFINITE, FALSE);
		index -= WSA_WAIT_EVENT_0;
		// �̺�Ʈ ���� �������� + EventList[index] �̺�Ʈ�� �ͽñ׳��� ����
		WSAEnumNetworkEvents( SockList[index], EventList[index], &neEvents);
		if(neEvents.lNetworkEvents & FD_ACCEPT)
		{
			if(neEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
			SOCKET ClientSocket;
			SOCKADDR_IN sockaddr;
			int addrlen = sizeof(sockaddr);
			ClientSocket = accept(SockList[index], (SOCKADDR*)&sockaddr, &addrlen);
			if(ClientSocket == SOCKET_ERROR)
			{
				DisplayMessage();	continue;
			}
			printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
				inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));
			WSAEVENT hClientEvent = WSACreateEvent();
			WSAEventSelect(ClientSocket, hClientEvent, FD_WRITE | FD_READ | FD_CLOSE);

			SockList[g_SockCnt] = ClientSocket;
			EventList[g_SockCnt] = hClientEvent;
			g_SockCnt++;
		}
		else if(neEvents.lNetworkEvents & FD_READ || neEvents.lNetworkEvents & FD_WRITE)
		{
			if(neEvents.iErrorCode[FD_READ_BIT] != 0 && neEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
			SOCKET ClientSocket = SockList[index];
			SOCKADDR_IN senderaddr;
			int addrlen = sizeof(senderaddr);
			recv(ClientSocket, buf, BUFFERSIZE, 0);
			getpeername(ClientSocket, (SOCKADDR *)&senderaddr, &addrlen);
			printf("[%s] %s\n", inet_ntoa(senderaddr.sin_addr), buf);
			for(int i = 1; i<g_SockCnt; i++)
			{
				if(i != index)
					send(SockList[i], buf, sizeof(buf), 0);
			}
		}
		else if(neEvents.lNetworkEvents & FD_CLOSE)
		{
			if(neEvents.iErrorCode[FD_CLOSE_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
		}
		

		

	
	}
	//===================================================

	WSACleanup();
	return 0;
}
#endif
/**********************************************************
 * SelectEvent ��Ƽ ä��
 * ������ �����ϸ� �����ڵ鿡 ���� �޽��� ����
 * ������ �����ϸ� ���� �޽��� ����
 * -- �ҽ��ڵ� ���̱�
 * -- �Լ�ȭ
 **********************************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>

#define BUFFERSIZE			1024

// ���� ����
#define MAX_SOCKET_NUM		WSA_MAXIMUM_WAIT_EVENTS
#define g_ServerSocket		g_ServerSocket
#define EventList[0]	EventList[0]

#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}

SOCKET SockList[MAX_SOCKET_NUM];
WSAEVENT EventList[MAX_SOCKET_NUM];
int g_SockCnt;

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&pMsg, 0, NULL);
	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
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
	
	// �̺�Ʈ ���
	WSAEVENT hClientEvent = WSACreateEvent();
	WSAEventSelect(ClientSocket, hClientEvent, FD_WRITE | FD_READ | FD_CLOSE);
	// ���������� ����
	SockList[g_SockCnt] = ClientSocket;
	EventList[g_SockCnt] = hClientEvent;
	g_SockCnt++;
	// ���Ӹ޼��� ����
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
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
	EventList[0] = hEvent;
	g_SockCnt++;
	return true;
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// ����ó��
	//===================================================
	int index = 0;
	WSANETWORKEVENTS neEvents;
	
	while(1)
	{
		// �̺�Ʈ �ñ׳� ����
		index = WSAWaitForMultipleEvents(g_SockCnt, EventList,
			FALSE, WSA_INFINITE, FALSE);
		index -= WSA_WAIT_EVENT_0;
		// �̺�Ʈ ���� �������� + EventList[index] �̺�Ʈ�� �ͽñ׳��� ����
		WSAEnumNetworkEvents( SockList[index], EventList[index], &neEvents);
		if(neEvents.lNetworkEvents & FD_ACCEPT)
		{
			EVENTERRORCHECK(neEvents, FD_ACCEPT_BIT);
			if(AddClient(index) != true)
				continue;
		}
		else if(neEvents.lNetworkEvents & FD_READ || neEvents.lNetworkEvents & FD_WRITE)
		{
			if(neEvents.iErrorCode[FD_READ_BIT] != 0 && neEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
			RecvClient(index);
			
		}
		else if(neEvents.lNetworkEvents & FD_CLOSE)
		{
			EVENTERRORCHECK(neEvents, FD_CLOSE_BIT);
				DeleteClient(index);
		}
	}
	//===================================================

	WSACleanup();
	return 0;
}
#endif
