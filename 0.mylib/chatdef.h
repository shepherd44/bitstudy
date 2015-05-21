
#pragma once
#include "SocketInfo.h"

#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME				16
#define MAX_GAMEROOMUSER				2
#define MAX_ROOMUSER				64
#define AWAITER_ROOM				1


//enum ROOMDESCRIPTOR { };
// 방정보 저장 구조체
typedef struct RoomInfo{
	int iRoomNum;
	char cpRoomName[MAX_ROOMNAME];
	std::vector<EVENTSOCKET> ClientList;
	int MaxRoomUser;
} ROOMINFO;

//전역 변수
extern std::vector<ROOMINFO> g_RoomInfo;


void JoinEvent();
// 서버소켓 생성 후 대기방에 등록
bool CreateListenSocket();
// 방 생성, 삭제
int CreateRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);

void DeleteRoom(std::vector<ROOMINFO>& v, int index );
// 방이 찼는지/비었는지 확인
bool IsFoolRoom(ROOMINFO& ri);
bool IsEmptyRoom(ROOMINFO& ri);
// 방 찾기
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);
SOCKET FindSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
EVENTSOCKET FindEventSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
int ListenClient();
// 사용자 나가기, 들어가기
int AddClient(RoomInfo& ri, EventSocket si);
void OutClient(RoomInfo& ri, EventSocket si);
// 방안의 사용자 목록(ClientList) 받기
std::vector<EventSocket> GetClientList(RoomInfo& ri);
// 사용자 찾기
EVENTSOCKET* FindClient(std::vector<EVENTSOCKET> v, SOCKET s);
// 방안의 모두에게 메세지 전송
void SendAll(ROOMINFO* ri, WSAEVENT he, const char *str, int len);
// 메세지 받기
void RecvClient(EVENTSOCKET si);