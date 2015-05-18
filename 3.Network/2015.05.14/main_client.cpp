/**************************************
 * tcp Ŭ���̾�Ʈ 
 ***************************************/
#if 0
#include <winsock2.h>
#include <stdio.h>

#define BUFFERSIZE	1024

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg,
		0,NULL);

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

int main(int argv, char* argc[])
{
	int retval;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa))
	{
		DisplayMessage();	return -1;
	}
	
	SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, 0);
	if(SocketClient == INVALID_SOCKET)
	{
		DisplayMessage();	return -1;
	}
	SOCKADDR_IN serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// ������ ���ۿ�û
	retval = connect(SocketClient, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();	return -1;
	}

	char buf[BUFFERSIZE];
	int len;

	while(1)
	{
		memset(buf,0,sizeof(buf));
		printf("���ڿ� �Է�: ");
		if(fgets(buf, BUFFERSIZE, stdin) == NULL)
			break;
		len = strlen(buf);
		if(buf[len - 1] == '\n')
			buf[len -1] = '\0';
		if(strlen(buf) == 0)
			break;
		//������ ������ ������
		retval = send(SocketClient, buf, len, 0);
		if(retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d ����Ʈ�� ����\n", retval);
	}
	closesocket(SocketClient);
	WSACleanup();
	return 0;

	
}
#endif

#if 0
#include <winsock2.h>
#include <stdio.h>

#define BUFFERSIZE	1024

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pMsg,
		0,NULL);

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

int main(int argv, char* argc[])
{
	int retval;

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa))
	{
		DisplayMessage();	return -1;
	}
	
	SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, 0);
	if(SocketClient == INVALID_SOCKET)
	{
		DisplayMessage();	return -1;
	}
	SOCKADDR_IN serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	// ������ ���ۿ�û
	retval = connect(SocketClient, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();	return -1;
	}

	char buf[BUFFERSIZE];
	int len;

	while(1)
	{
		memset(buf,0,sizeof(buf));
		printf("���ڿ� �Է�: ");
		if(fgets(buf, BUFFERSIZE - 1, stdin) == NULL)
			break;
		len = strlen(buf);
		if(buf[len - 1] == '\n')
			buf[len -1] = '\0';
		if(strlen(buf) == 0)
			break;
		//������ ������ ������
		retval = send(SocketClient, buf, len, 0);
		if(retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d ����Ʈ�� ����\n", retval);
	
		retval = recvn(SocketClient, buf, retval, 0);
		if(retval == SOCKET_ERROR)
		{
			DisplayMessage();	return 0;
		}
		buf[retval] = '\0';
		printf("[TCP Ŭ���̾�Ʈ] %d ����Ʈ�� ����, ������: %s\n", retval, buf);
	}
	closesocket(SocketClient);
	WSACleanup();
	return 0;

	
}
#endif