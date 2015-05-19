
#pragma once
#include "SocketInfo.h"

#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME				16
#define MAX_GAMEROOM				2

#define AWAITER_ROOM				1


enum ROOMDESCRIPTOR { };
// ������ ���� ����ü
typedef struct RoomInfo{
	int iRoomNum;
	char cpRoomName[MAX_ROOMNAME];
	std::vector<EVENTSOCKET> ClientList;
	int MaxRoomUser;
} ROOMINFO;

//���� ����
extern std::vector<ROOMINFO> g_RoomInfo;


void JoinEvent();
// �������� ���� �� ���濡 ���
bool CreateListenSocket();
// �� ����, ����
int CreateRoom(std::vector<ROOMINFO>& v, int index, const char* str);
void DeleteRoom(std::vector<ROOMINFO>& v, int index );
// ���� á����/������� Ȯ��
bool IsFoolRoom(ROOMINFO& ri);
bool IsEmptyRoom(ROOMINFO& ri);
// �� ã��
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);
SOCKET FindSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
EVENTSOCKET FindEventSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
int ListenClient();
// ����� ������, ����
int AddClient(RoomInfo& ri, EventSocket si);
void OutClient(RoomInfo& ri, EventSocket si);
// ����� ����� ���(ClientList) �ޱ�
std::vector<EventSocket> GetClientList(RoomInfo& ri);
// ����� ã��
EVENTSOCKET* FindClient(std::vector<EVENTSOCKET> v, SOCKET s);
// ����� ��ο��� �޼��� ����
void SendAll(ROOMINFO* ri, WSAEVENT he, const char *str, int len);
// �޼��� �ޱ�
void RecvClient(EVENTSOCKET si);