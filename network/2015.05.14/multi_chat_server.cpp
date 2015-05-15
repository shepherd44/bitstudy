#if 1
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#define BUFFERSIZE			1024
#define MAX_CLIENT_NUM		10

typedef struct SocketInfo {
	//static CRITICAL_SECTION cs;
	SOCKET Socket;
	SOCKADDR_IN SocketAddr;
	int index;
} SOCKETINFO;

SocketInfo g_ClientInfo[MAX_CLIENT_NUM];
int g_cnt;
SOCKET g_listenSock;

//critical section �ʱ�ȭ �Լ�
void InitCritcalSection()
{
	//InitializeCriticalSection(&(g_ClientInfo->cs));
}

void DeleteSocketInfo()
{
	
	for(int i=0 ; i<MAX_CLIENT_NUM; i++)
	{
		closesocket(g_ClientInfo[i].Socket);
	}
	memset(g_ClientInfo, 0, sizeof(g_ClientInfo));
	
}

// ���� ��� �Լ�
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
	SOCKET clientsock = ((SocketInfo*)pParam)->Socket;
	SOCKADDR_IN clientaddr = ((SocketInfo*)pParam)->SocketAddr;
	int index = ((SocketInfo*)pParam)->index;

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
			for(int i = 0; i< g_cnt; i++) 
			{	
				if(i == index)
					continue;
				retval = send(g_ClientInfo[i].Socket, buf, recvByte, 0);
				if(retval == SOCKET_ERROR)
				{
					DisplayMessage();
					continue;
				}
			}
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
		int addrlen = sizeof(g_ClientInfo[g_cnt].SocketAddr);
		g_ClientInfo[g_cnt].index = g_cnt;
		g_ClientInfo[g_cnt].Socket = accept(g_listenSock, (SOCKADDR *)&g_ClientInfo[g_cnt].SocketAddr, &addrlen);
		if(g_ClientInfo[g_cnt].Socket == SOCKET_ERROR)
		{
			DisplayMessage();	continue;
		}
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(g_ClientInfo[g_cnt].SocketAddr.sin_addr), ntohs(g_ClientInfo[g_cnt].SocketAddr.sin_port));
		unsigned int threadID;
		CloseHandle((HANDLE)_beginthreadex(0,0,ComThread,(void*)&g_ClientInfo[g_cnt], 0,&threadID));
		g_cnt++;
	}
	closesocket(g_listenSock);
}

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// (socket + bind + listen
	if(!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	unsigned int threadID;

	//InitCritcalSection();

	WaitForSingleObject((HANDLE)_beginthreadex(0,0,ListenThread, 0,0,&threadID), INFINITE);
	DeleteSocketInfo();
	//DeleteCriticalSection(&(g_ClientInfo->cs));
	WSACleanup();
	return 0;
}


#endif