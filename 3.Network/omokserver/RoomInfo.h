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
	// ���� á����/������� Ȯ��
	bool IsFoolRoom();
	bool IsEmptyRoom();
};

class COmokRoom: public CRoomInfo{
	std::vector<EVENTSOCKET> m_UserList;
public:
	// ����� ã��
	EVENTSOCKET* FindUser(SOCKET);
	EVENTSOCKET* FindUser(WSAEVENT);
	// ����� ����� ���(ClientList) �ޱ�
	std::vector<EventSocket> GetClientList();
	// ����� ������, ����
	int AddUser(EventSocket);
	int OutUser(EventSocket);
public:
	// ����� ��ο��� �޼��� ����
	virtual int SendAll(const char *str, int msglen);
	virtual int RecvClient(EVENTSOCKET si);
};

// �� ����, ����
int CreateRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<ROOMINFO>& v, int rnum, const char* str);
void DeleteRoom(std::vector<ROOMINFO>& v, int index );

void JoinEvent();
// �������� ���� �� ���濡 ���
bool CreateListenSocket();
int ListenClient();
// �� ã��
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, WSAEVENT wsaevent);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);


