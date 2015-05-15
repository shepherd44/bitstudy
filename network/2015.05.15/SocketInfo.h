// ���� ����
#include "amolang.h"

#define MAX_SOCKET_NUM		WSA_MAXIMUM_WAIT_EVENTS
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

// ������ ���� ����ü
typedef struct RoomInfo{
	int iRoomNum;
	char* cpRoomName;
	std::vector<SocketInfo> ClientList;
} ROOMINFO;

extern std::vector<ROOMINFO> g_RoomInfo;
extern SOCKET SockList[MAX_SOCKET_NUM];
extern int g_SockCnt;

// �������� �ʱ�ȭ
bool CreateListenSocket();

SOCKET FindSocket(int);
void CreateRoom(int, const char*);
// �����޽��� ���
void DisplayMessage();

void SendAll(int index, const char *str, int len);

void RecvClient(int index);

bool AddClient(int index);

void DeleteClient(int index);