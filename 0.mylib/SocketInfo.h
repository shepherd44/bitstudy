// ���� ����
#pragma once
#include "amolang.h"

#define MAX_SOCKET_NUM				WSA_MAXIMUM_WAIT_EVENTS

// ���� ���� ���� ����ü
typedef struct EventSocket{
	SOCKET sSocket;
	SOCKADDR_IN saSocketAddr;
	WSAEVENT hEvent;
} EVENTSOCKET;

// SelectEvent�� ���� �̺�Ʈ �迭
extern SOCKET g_ServerSocket;
extern WSAEVENT g_hEventList[MAX_SOCKET_NUM];
extern int g_EventCnt;

//���� �Ϸ�-------------------------------------------------
// �������� �ʱ�ȭ
