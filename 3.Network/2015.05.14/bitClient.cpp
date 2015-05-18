#if 0
#include <winsock2.h>
#include <stdio.h>

#define MAX_BUFSIZE	1024
int main()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("WSAStartup error"); return -1;
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(ServerSocket == INVALID_SOCKET)
	{
		puts("socket error"); return -1;
	}
	SOCKADDR_IN serveraddr;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);

	int ret = connect(ServerSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if(ret != 0)
	{
		puts("connect error");	return -1;
	}

	char buf[MAX_BUFSIZE] = {0,};;
	while(1)
	{
		ret = recv(ServerSocket, buf, MAX_BUFSIZE, 0);
		puts(buf);
		if(fgets(buf, MAX_BUFSIZE, stdin) == NULL)
		{
			break;
		}
		ret = send(ServerSocket, buf, sizeof(buf), 0);
	}
}
#endif