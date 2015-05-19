// 소켓 정리
#pragma once
#include "amolang.h"

#define MAX_SOCKET_NUM				WSA_MAXIMUM_WAIT_EVENTS

// 소켓 정보 저장 구조체(AsyncSock용)
typedef struct SocketInfo{
	SOCKET sSocket;
	SOCKADDR_IN saSocketAddr;
} SOCKETINFO;

typedef SOCKETINFO ASYNCSOCKET;

//----------------------------------------------------------
// 소켓 정보 저장 구조체(EventSelect용)
typedef struct EventSocket{
	SOCKET sSocket;
	SOCKADDR_IN saSocketAddr;
	WSAEVENT hEvent;
} EVENTSOCKET;
// SelectEvent를 위한 이벤트 배열
extern SOCKET g_ServerSocket;
extern WSAEVENT g_hEventList[MAX_SOCKET_NUM];
extern int g_EventCnt;
