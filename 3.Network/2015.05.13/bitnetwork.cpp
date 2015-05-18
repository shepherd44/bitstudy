/***************************************************************
 * Windows Socket Programing ( Network Programing)
 ***************************************************************
 * ex) 게임서버, 일반적인 윈도우즈 네트워크, 실시간 스트리밍
 * 추가 종속성 - ws2_32.lib
 * #include <winsock.h>
 *
 ***************************************************************/
// 기본 코드
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{

	WSADATA wsa;	// 소켓 버전 정보 구조체
	// 1) Windows DLL 파일을 로딩
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("실패!!\n");
		return -1;
	}
	//----------------------------------------------
	printf("윈속 초기화 !!\n");
	printf("%d, %s, %d\n", wsa.wVersion, wsa.szDescription, wsa.iMaxSockets);

	
	//----------------------------------------------
	WSACleanup();	// DLL 언로딩
	return 0;
}

#endif

/***************************************************************
 * 기본 설명
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{

	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		puts("실패!!\n");
		return -1;
	}
	//----------------------------------------------
	printf("버전: %d, %s, %d\n", wsa.wVersion, wsa.szDescription, wsa.iMaxSockets);

	char* addr = "127.0.0.1";
	printf("문자열 주소 : %s \n", addr);
	// 4byte의 정수로 표현
	// 1byte단위로 저장
	// [127][0][0][1]
	// 문자열 ip주소 --> 정수형태의 ip주소로 변환
	int iIP = inet_addr(addr);
	printf("0x%08x\n", iIP);
	// ipv4 주소체계용 변수
	IN_ADDR in_addr;
	in_addr.s_addr = iIP;
	//정수형태의 주소 --> 문자열
	puts(inet_ntoa(in_addr));

	// 바이트 정렬법
	// --> 빅인디안: 네트워크 통신 표준 방식!!
	// --> 리틀인디안: 로컬에서 사용되는 방식!!
	// 변환법 
	unsigned short us = 0x1234;
	printf("0x%08x\n", us);
	printf("0x%08x\n", htons(us));
	printf("0x%08x\n", htonl(us));
	/***************************************
	 * 주소 정보 구조체
	 ****************************************/
	// SOCKADDR addr; 이건 잘 안쓰는듯
	SOCKADDR_IN addrin;							// 주소정보 구조체
	addrin.sin_addr.s_addr = inet_addr(addr);	// 
	addrin.sin_port = 2000;						// 실제 서비스 포트 : 2000 이상
	addrin.sin_family = AF_INET; // 주소체계 설정internetwork(AF_INET = TCP, UDP)

	//----------------------------------------------
	WSACleanup();	// DLL 언로딩
	return 0;
}

#endif

/***************************************************************
 * TCP Server 기본 코드
 ***************************************************************/
#if 0
#include <stdio.h>
#include <winsock.h>

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)	// 0) DLL 로딩
	{
		puts("WSAStartup Error !!\n");
		return -1;
	}
	// 1) 핸드폰 단말기 구입 --> SOCKET : 통신을 하기 위한 매개체 !!
	SOCKET ServerSocket;
	// 2) 소켓 생성 !!(통신방식, 소켓타입, 프로토콜)
	// 연결지향 : TCP, 비연결지향 : UDP
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if( ServerSocket == INVALID_SOCKET)
	{
		puts("Socket() error!\n"); return -1;
	}

	// 3) 유심 
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(20000);
	ServerAddr.sin_addr.s_addr = htons(INADDR_ANY);

	// 4) socket + sockaddr == 핸드폰 + 유심
	int ret = bind(ServerSocket,			//소켓
				(SOCKADDR*)&ServerAddr,	// 주소 구조체
				sizeof(ServerAddr));	// 주소의 크기
	if( ret == SOCKET_ERROR)
	{
		puts("bind() error !!");	return -1;
	}

	// 5) 통화 대기
	ret = listen(ServerSocket, // 기다릴 소켓
				SOMAXCONN);		// 가능한 최대값
	if(ret == SOCKET_ERROR)
	{
		puts("listen() error\n"); return -1;
	}
	
	// 6)
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(ServerSocket, //대기하는 소켓
							(SOCKADDR*)&ClientAddr, //클라이언트의 주소를 가져올 구조체
							&len);	// 구조체의 크기
	if(ClientSocket == INVALID_SOCKET)
	{
		puts("accept error"); return -1;
	}
	
	// 화면에 접속한 클라이언트의 IP를 출력
	printf("[%s] %d 접속\n", inet_ntoa(ClientAddr.sin_addr)
		, ntohs(ClientAddr.sin_port));

	char buf[128] = "접속했네? 어서와 이런곳은 처음이지";
	send(ServerSocket, buf, 128, 0);
	memset(buf, 0, 128);
	// 에코 : 메아리
	while(1)
	{
		recv(ClientSocket, buf, 128, 0);
		puts(buf);
		send(ServerSocket, buf, 128, 0);
	}



	WSACleanup();	// !0) DLL 정리
}

#endif

/***************************************************************
 * TCP Server 기본 코드 주석 제거
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
	
	printf("[%s] %d 접속\n", inet_ntoa(ClientAddr.sin_addr)
		, ntohs(ClientAddr.sin_port));

	closesocket(ServerSock);
	closesocket(ClientSock);
	WSACleanup();	// !0) DLL 정리
}

#endif