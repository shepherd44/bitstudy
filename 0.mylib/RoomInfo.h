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
	// ���� á����/������� Ȯ��
	virtual bool IsFoolRoom() = 0;
	virtual bool IsEmptyRoom() = 0;
};

class COmokRoom: public CRoomInfo{
	std::vector<EVENTSOCKET> m_UserList;
public:
	// ����� ã��
	EVENTSOCKET* FindUser(SOCKET);
	EVENTSOCKET* FindUser(WSAEVENT);
	EVENTSOCKET* FindUser(SOCKET, UINT*);
	EVENTSOCKET* FindUser(WSAEVENT, UINT*);
	UINT FindUserIndex(SOCKET);
	UINT FindUserIndex(WSAEVENT);
	// ����� ����� ���(ClientList) �ޱ�
	std::vector<EventSocket> GetClientList() { return this->m_UserList; }
	// ����� ������, ����
	int AddUser(EventSocket);
	int OutUser(EventSocket);
public:
	// ����� ��ο��� �޼��� ����
	void SendAll(const char* str, int msglen);
	void SendAllExceptMe(SOCKET me, const char* str, int msglen);
	void SendTo(SOCKET you, const char* str, int msglen);
	int RecvClient(EVENTSOCKET si);
public:
	bool IsFoolRoom();
	bool IsEmptyRoom();

};

// �� ����, ����
int CreateRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
void DeleteRoom(std::vector<CRoomInfo>& v, int index );

void JoinEvent();
// �������� ���� �� ���濡 ���
bool CreateListenSocket();
int ListenClient();
// �� ã��
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, int index);
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, WSAEVENT wsaevent);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);


