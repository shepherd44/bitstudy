// ���� ����
#include "amolang.h"

#define MAX_SOCKET_NUM				WSA_MAXIMUM_WAIT_EVENTS
#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME				16

#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}

// ���� ���� ���� ����ü
typedef struct SocketInfo{
	SOCKET sSocket;
	SOCKADDR_IN saSocketAddr;
	WSAEVENT hEvent;
} SOCKETINFO;

// SelectEvent�� ���� �̺�Ʈ �迭
extern SOCKET g_ServerSocket;
extern WSAEVENT g_hEventList[MAX_SOCKET_NUM];

enum ROOMDESCRIPTOR { };
// ������ ���� ����ü
typedef struct RoomInfo{
	int iRoomNum;
	char cpRoomName[MAX_ROOMNAME];
	std::vector<SOCKETINFO> ClientList;
} ROOMINFO;

extern std::vector<ROOMINFO> g_RoomInfo;
extern SOCKET SockList[MAX_SOCKET_NUM];
extern int g_SockCnt;

//���� �Ϸ�-------------------------------------------------
// �������� �ʱ�ȭ
bool CreateListenSocket();

// ���� �ʿ�-------------------------------------------------

// �� ����, ����
int CreateRoom(std::vector<ROOMINFO>& v, int index, const char* str);
void DeleteRoom(std::vector<ROOMINFO>& v, int index );
// ���� á����/������� Ȯ��
bool IsFoolRoom(ROOMINFO& ri);
bool IsEmptyRoom(ROOMINFO& ri);
// �� ã��
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);

// ����� ������, ����
int AddClient(RoomInfo& ri, SocketInfo si, int index);
void OutClient(RoomInfo& ri, SocketInfo si);

// ����� ����� ���(ClientList) �ޱ�
std::vector<SocketInfo> GetClientList(RoomInfo& ri);
// ����� ã��
SOCKETINFO* FindClient(std::vector<SOCKETINFO> v, SOCKET s);

// ����� ��ο��� �޼��� ����
void SendAll(ROOMINFO& ri, WSAEVENT he, const char *str, int len);

void RecvClient(ROOMINFO& ri, SOCKETINFO si);

