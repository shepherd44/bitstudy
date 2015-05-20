#pragma once

#include "SocketInfo.h"

#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME_LENGTH			32
#define MAX_ROOMUSER				64
#define AWAITER_ROOM				1

class CRoomInfo
{
protected:
	int m_RoomNum;
	char *m_RoomName;
	int m_MaxRoomUser;
	//std::vector<EVENTSOCKET> m_UserList;
public:
	CRoomInfo(void);
	CRoomInfo(int, char*, int);
	~CRoomInfo(void);

public:		// get, set
	int GetRoomNum();
	void SetRoomNum(int);
	char* GetRoomName();
	void SetRoomName(char*);
	int GetMaxRoomUser();
	void SetMaxRoomUser(int);
public:
	// 방이 찼는지/비었는지 확인
	bool IsFoolRoom();
	bool IsEmptyRoom();
};

class COmokRoom: public CRoomInfo{
	std::vector<EVENTSOCKET> m_UserList;
public:
	// 사용자 찾기
	EVENTSOCKET* FindUser(SOCKET);
	EVENTSOCKET* FindUser(WSAEVENT);
	// 방안의 사용자 목록(ClientList) 받기
	std::vector<EventSocket> GetClientList();
	// 사용자 나가기, 들어가기
	int AddUser(EventSocket);
	int OutUser(EventSocket);
public:
	// 방안의 모두에게 메세지 전송
	virtual int SendAll(const char *str, int msglen);
	virtual int RecvClient(EVENTSOCKET si);
};

// 방 생성, 삭제
int CreateRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);
void DeleteRoom(std::vector<ROOMINFO>& v, int index );

void JoinEvent();
// 서버소켓 생성 후 대기방에 등록
bool CreateListenSocket();
int ListenClient();
// 방 찾기
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);


