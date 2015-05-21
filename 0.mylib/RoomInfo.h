#pragma once

#include "SocketInfo.h"

#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME_LENGTH			32
#define MAX_ROOMUSER				64
#define AWAITER_ROOM				1

enum ROOMERROR {DONTFIND = -1, NOTERROR = 0, FULLROOM, EMPTYROOM };
class CRoomInfo
{
protected:
	int m_RoomNum;
	char *m_RoomName;
	int m_MaxRoomUser;
	//std::vector m_UserList;
public:
	CRoomInfo(void);
	CRoomInfo(int, char*, int);
	~CRoomInfo(void);

public:		// get, set
	int GetRoomNum() { return this->m_RoomNum; }
	void SetRoomNum(int roomnum) { this->m_RoomNum = roomnum; }
	char* GetRoomName() { return this->m_RoomName; }
	void SetRoomName(char* roomname) {
		if(m_RoomName == NULL) {this->m_RoomName = new char[strlen(roomname)]; strcpy(this->m_RoomName, roomname);}
		else {delete this->m_RoomName; this->m_RoomName = new char[strlen(roomname)]; strcpy(this->m_RoomName, roomname);}	}
	int GetMaxRoomUser() { return this->m_MaxRoomUser; }
	void SetMaxRoomUser(int maxnum) { this->m_MaxRoomUser = maxnum; }
public:
	// 방이 찼는지/비었는지 확인
	virtual bool IsFoolRoom() = 0;
	virtual bool IsEmptyRoom() = 0;
};

class COmokRoom: public CRoomInfo{
	std::vector<EVENTSOCKET> m_UserList;
public:
	// 사용자 찾기
	EVENTSOCKET* FindUser(SOCKET);
	EVENTSOCKET* FindUser(WSAEVENT);
	EVENTSOCKET* FindUser(SOCKET, UINT*);
	EVENTSOCKET* FindUser(WSAEVENT, UINT*);
	UINT FindUserIndex(SOCKET);
	UINT FindUserIndex(WSAEVENT);
	// 방안의 사용자 목록(ClientList) 받기
	std::vector<EventSocket> GetClientList() { return this->m_UserList; }
	// 사용자 나가기, 들어가기
	int AddUser(EventSocket);
	int OutUser(EventSocket);
public:
	// 방안의 모두에게 메세지 전송
	void SendAll(const char* str, int msglen);
	void SendAllExceptMe(SOCKET me, const char* str, int msglen);
	void SendTo(SOCKET you, const char* str, int msglen);
	int RecvClient(EVENTSOCKET si);
public:
	bool IsFoolRoom();
	bool IsEmptyRoom();

};

// 방 생성, 삭제
int CreateRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
void DeleteRoom(std::vector<CRoomInfo>& v, int index );

void JoinEvent();
// 서버소켓 생성 후 대기방에 등록
bool CreateListenSocket();
int ListenClient();
// 방 찾기
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, int index);
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, WSAEVENT wsaevent);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);


