/***************************************************************
 * Windows Socket Programing ( Network Programing)
 ***************************************************************
 * ex) ���Ӽ���, �Ϲ����� �������� ��Ʈ��ũ, �ǽð� ��Ʈ����
 * �߰� ���Ӽ� - ws2_32.lib
 * #include <winsock.h>
 *
 ***************************************************************/
// �⺻ �ڵ�
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{

	WSADATA wsa;	// ���� ���� ���� ����ü
	// 1) Windows DLL ������ �ε�
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("����!!\n");
		return -1;
	}
	//----------------------------------------------
	printf("���� �ʱ�ȭ !!\n");
	printf("%d, %s, %d\n", wsa.wVersion, wsa.szDescription, wsa.iMaxSockets);

	
	//----------------------------------------------
	WSACleanup();	// DLL ��ε�
	return 0;
}

#endif

/***************************************************************
 * �⺻ ����
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{

	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("����!!\n");
		return -1;
	}
	//----------------------------------------------
	printf("����: %d, %s, %d\n", wsa.wVersion, wsa.szDescription, wsa.iMaxSockets);

	char* addr = "127.0.0.1";
	printf("���ڿ� �ּ� : %s \n", addr);
	// 4byte�� ������ ǥ��
	// 1byte������ ����
	// [127][0][0][1]
	// ���ڿ� ip�ּ� --> ���������� ip�ּҷ� ��ȯ
	int iIP = inet_addr(addr);
	printf("0x%08x\n", iIP);
	// ipv4 �ּ�ü��� ����
	IN_ADDR in_addr;
	in_addr.s_addr = iIP;
	//���������� �ּ� --> ���ڿ�
	puts(inet_ntoa(in_addr));

	// ����Ʈ ���Ĺ�
	// --> ���ε��: ��Ʈ��ũ ��� ǥ�� ���!!
	// --> ��Ʋ�ε��: ���ÿ��� ���Ǵ� ���!!
	// ��ȯ�� 
	unsigned short us = 0x1234;
	printf("0x%08x\n", us);
	printf("0x%08x\n", htons(us));
	printf("0x%08x\n", htonl(us));
	/***************************************
	 * �ּ� ���� ����ü
	 ****************************************/
	// SOCKADDR addr; �̰� �� �Ⱦ��µ�
	SOCKADDR_IN addrin;							// �ּ����� ����ü
	addrin.sin_addr.s_addr = inet_addr(addr);	// 
	addrin.sin_port = 2000;						// ���� ���� ��Ʈ : 2000 �̻�
	addrin.sin_family = AF_INET; // �ּ�ü�� ����internetwork(AF_INET = TCP, UDP)

	//----------------------------------------------
	WSACleanup();	// DLL ��ε�
	return 0;
}

#endif

/***************************************************************
 * TCP Server �⺻ �ڵ�
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)	// 0) DLL �ε�
	{
		puts("WSAStartup Error !!\n");
		return -1;
	}
	// 1) �ڵ��� �ܸ��� ���� --> SOCKET : ����� �ϱ� ���� �Ű�ü !!
	SOCKET ServerSocket;
	// 2) ���� ���� !!(��Ź��, ����Ÿ��, ��������)
	// �������� : TCP, �񿬰����� : UDP
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if( ServerSocket == INVALID_SOCKET)
	{
		puts("Socket() error!\n"); return -1;
	}

	// 3) ���� 
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(20000);
	ServerAddr.sin_addr.s_addr = htons(INADDR_ANY);

	// 4) socket + sockaddr == �ڵ��� + ����
	int ret = bind(ServerSocket,			//����
				(SOCKADDR*)&ServerAddr,	// �ּ� ����ü
				sizeof(ServerAddr));	// �ּ��� ũ��
	if( ret == SOCKET_ERROR)
	{
		puts("bind() error !!");	return -1;
	}

	// 5) ��ȭ ���
	ret = listen(ServerSocket, // ��ٸ� ����
				SOMAXCONN);		// ������ �ִ밪
	if(ret == SOCKET_ERROR)
	{
		puts("listen() error\n"); return -1;
	}
	
	// 6)
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(ServerSocket, //����ϴ� ����
							(SOCKADDR*)&ClientAddr, //Ŭ���̾�Ʈ�� �ּҸ� ������ ����ü
							&len);	// ����ü�� ũ��
	if(ClientSocket == INVALID_SOCKET)
	{
		puts("accept error"); return -1;
	}
	
	// ȭ�鿡 ������ Ŭ���̾�Ʈ�� IP�� ���
	printf("[%s] %d ����\n", inet_ntoa(ClientAddr.sin_addr)
		, ntohs(ClientAddr.sin_port));

	char buf[128] = "�����߳�? ��� �̷����� ó������";
	send(ServerSocket, buf, 128, 0);
	memset(buf, 0, 128);
	// ���� : �޾Ƹ�
	while(1)
	{
		recv(ClientSocket, buf, 128, 0);
		puts(buf);
		send(ServerSocket, buf, 128, 0);
	}



	WSACleanup();	// !0) DLL ����
}

#endif

/***************************************************************
 * TCP Server �⺻ �ڵ� �ּ� ����
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("WSAStartup Error !!\n");
		return -1;
	}
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if( ServerSocket == INVALID_SOCKET)
	{
		puts("Socket() error!\n"); return -1;
	}

	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(20000);
	ServerAddr.sin_addr.s_addr = htons(INADDR_ANY);

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
	
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(ServerSocket,
							(SOCKADDR*)&ClientAddr,
							&len);
	if(ClientSocket == INVALID_SOCKET)
	{
		puts("accept error"); return -1;
	}
	
	printf("[%s] %d ����\n", inet_ntoa(ClientAddr.sin_addr)
		, ntohs(ClientAddr.sin_port));

	closesocket(ServerSock);
	closesocket(ClientSock);
	WSACleanup();	// !0) DLL ����
}

#endif