// 소켓 정리
#include "amolang.h"

#define MAX_SOCKET_NUM				WSA_MAXIMUM_WAIT_EVENTS
#define MAX_CLIENT_NUM_INROOM		10
#define MAX_ROOMNAME				16

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

enum ROOMDESCRIPTOR { };
// 방정보 저장 구조체
typedef struct RoomInfo{
	int iRoomNum;
	char cpRoomName[MAX_ROOMNAME];
	std::vector<SOCKETINFO> ClientList;
} ROOMINFO;

extern std::vector<ROOMINFO> g_RoomInfo;
extern SOCKET SockList[MAX_SOCKET_NUM];
extern int g_SockCnt;

//정의 완료-------------------------------------------------
// 서버소켓 초기화
bool CreateListenSocket();

// 정의 필요-------------------------------------------------

// 방 생성, 삭제
int CreateRoom(std::vector<ROOMINFO>& v, int index, const char* str);
void DeleteRoom(std::vector<ROOMINFO>& v, int index );
// 방이 찼는지/비었는지 확인
bool IsFoolRoom(ROOMINFO& ri);
bool IsEmptyRoom(ROOMINFO& ri);
// 방 찾기
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// RoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);

// 사용자 나가기, 들어가기
int AddClient(RoomInfo& ri, SocketInfo si, int index);
void OutClient(RoomInfo& ri, SocketInfo si);

// 방안의 사용자 목록(ClientList) 받기
std::vector<SocketInfo> GetClientList(RoomInfo& ri);
// 사용자 찾기
SOCKETINFO* FindClient(std::vector<SOCKETINFO> v, SOCKET s);

// 방안의 모두에게 메세지 전송
void SendAll(ROOMINFO& ri, WSAEVENT he, const char *str, int len);

void RecvClient(ROOMINFO& ri, SOCKETINFO si);

