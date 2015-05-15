// 소켓 정리
#include "amolang.h"

#define MAX_SOCKET_NUM		WSA_MAXIMUM_WAIT_EVENTS
#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}

// 소켓 정보 저장 구조체
typedef struct SocketInfo{
	SOCKET sSocket;
	SOCKADDR_IN saSocketAddr;
	WSAEVENT hEvent;
} SOCKETINFO;

// SelectEvent를 위한 이벤트 배열
extern SOCKET g_ServerSocket;
extern WSAEVENT g_hEventList[MAX_SOCKET_NUM];

// 방정보 저장 구조체
typedef struct RoomInfo{
	int iRoomNum;
	char* cpRoomName;
	std::vector<SocketInfo> ClientList;
} ROOMINFO;

extern std::vector<ROOMINFO> g_RoomInfo;
extern SOCKET SockList[MAX_SOCKET_NUM];
extern int g_SockCnt;

// 서버소켓 초기화
bool CreateListenSocket();

SOCKET FindSocket(int);
void CreateRoom(int, const char*);
// 오류메시지 출력
void DisplayMessage();

void SendAll(int index, const char *str, int len);

void RecvClient(int index);

bool AddClient(int index);

void DeleteClient(int index);