/*************************************************
 * tcp �⺻���� 1:1 ���� ����
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
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// ��� ���� ����
	SOCKET listenSock;
	listenSock = socket(AF_INET,		// �ּ�ü��: �������ݸ��� �ּ�ü�� �ٸ�. ���ͳ� ��� IPv4
					SOCK_STREAM,	// �������� ����: TCP/IP ��� ���
					0				//�� �� ���ڷ� �������� ������ ��Ȯ�ϸ� 0��� IPPROTO_TCP, IPPROTO_UDP
					);
	if(listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return 0;
	}

	// ��� ������ ���� �ּ�. ��Ʈ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;	// �ּ�ü��
	serveraddr.sin_port = htons(40100);	// ���� ��Ʈ��ȣ
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
		printf("\n[TCP ����] ũ���̾�Ʈ ����: IP �ּ� = %s, ��Ʈ ��ȣ = %d\n",
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
				printf("[TCP����] IP�ּ� = %s, ��Ʈ��ȣ = %d�� ���� �޽���:%s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					buf);
			}
			
		}
		closesocket(clientsock);
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����");

	}
	closesocket(listenSock);

	WSACleanup();
	return 0;
}


#endif

/***********************************************
 * TCP Server ������ ��� ��
 ***********************************************/
#if 0
#include <stdio.h>
#include <winsock2.h>
#include <process.h>

#define BUFFERSIZE		1024

SOCKET g_listenSock;

// ���� ��� �Լ�
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
			printf("[TCP ����] IP: %s, Port=%d�� �޽���:%s\n",
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
	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s,��Ʈ��ȣ=%d",
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
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
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

	WaitForSingleObject((HANDLE)_beginthreadex(0,0,ListenThread, 0,0,&threadID), INFINITE);
	
	WSACleanup();
	return 0;
}


#endif