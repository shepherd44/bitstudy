/**********************************************************
 * SelectEvent 멀티 채팅
 * --방개념 추가
 * --client 정보 구조체화
 * --STL적용
 **********************************************************/
#if 1

#include "SocketInfo.h"
#include "chatdef.h"
#include "omokdef.h"
using namespace std;

// 외부(EXTERN) 전역변수 선언
SOCKET g_ServerSocket;
WSAEVENT g_hEventList[MAX_SOCKET_NUM];
std::vector<ROOMINFO> g_RoomInfo;
SOCKET SockList[MAX_SOCKET_NUM];
int g_EventCnt;

// 전역변수
std::vector<EVENTSOCKET> g_awaiter;

void RecvClient(EVENTSOCKET si, OMOKMESSAGE* msg);

// 메인함수
int main(int argc, char* argv[])
{
	//대기자용 방 생성
	CreateRoom(g_RoomInfo, AWAITER_ROOM, "awaiter_room");

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}

	// 서버처리
	//===================================================
	int eventindex = 0;
	WSANETWORKEVENTS neEvents;
	//발생한 이벤트 대상 소켓

	EVENTSOCKET evSockTemp;
	while(1)
	{
		// 이벤트 시그널 감지
		eventindex = WSAWaitForMultipleEvents(g_EventCnt, g_hEventList,
			FALSE, WSA_INFINITE, FALSE);
		// 인덱스 설정
		eventindex -= WSA_WAIT_EVENT_0;
		// 이벤트 내용 가져오기
		// EventList[eventindex] 이벤트를 넌시그날로 변경
		evSockTemp = FindEventSocket(g_RoomInfo, g_hEventList[eventindex]);
		WSAEnumNetworkEvents(evSockTemp.sSocket, g_hEventList[eventindex], &neEvents);

		// 이벤트 처리
		if(neEvents.lNetworkEvents & FD_ACCEPT)
		{
			EVENTSOCKET siTemp;
			if(neEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				puts("[ERROR] accept error");
				DisplayMessage();
				return -1;
			}
			if(ListenClient() != true)
			{
				puts("[ERROR] ListenClient error");
				continue;
			}
			
		}
		else if(neEvents.lNetworkEvents & FD_READ || neEvents.lNetworkEvents & FD_WRITE)
		{
			if(neEvents.iErrorCode[FD_READ_BIT] != 0 && neEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				puts("[ERROR] read or write error");
				DisplayMessage();
				return -1;
			}
			OMOKMESSAGE msg;
			RecvClient(evSockTemp, &msg);
			if(msg.OmokMsg == PTMSG)
			{

			}
			else if(msg.OmokMsg == WINMSG)
			{

			}
			else if(msg.OmokMsg == CHATMSG)
			{
				//SendAll(

			}
			else if(msg.OmokMsg == ROOMMSG)
			{
				if(FindRoom(g_RoomInfo, msg.room.roomindex) == NULL)
				{
					CreateRoom(g_RoomInfo, msg.room.roomindex, msg.room.roomname);
					AddClient(*FindRoom(g_RoomInfo, msg.room.roomindex), evSockTemp);
					OMOKMESSAGE msgTemp;
					msgTemp.OmokMsg = TURNMSG;
					msgTemp.PT.turn = 0;
					msgTemp.PT.pt.col = -1;
					msgTemp.PT.pt.row = -1;
					send(evSockTemp.sSocket, (char*)&msgTemp,sizeof(msgTemp),0);
				}
			}
			else
			{

			}

			
		}
		else if(neEvents.lNetworkEvents & FD_CLOSE)
		{
			EVENTERRORCHECK(neEvents, FD_CLOSE_BIT);
				//OutClient(eventindex);
			OutClient(*FindRoom(g_RoomInfo, evSockTemp.hEvent),evSockTemp);
		}
	}
	
	
	//===================================================

	WSACleanup();
	return 0;
}
void RecvClient(EVENTSOCKET si, OMOKMESSAGE* msg)
{
	int addrlen = sizeof(si.saSocketAddr);
	
	// 채팅일 경우 자기제외 모두에게 전송
	int retByte = recv(si.sSocket,(char*) msg, sizeof(OMOKMESSAGE), 0);
	// 서버 콘솔에 프린트
	//printf("[%s][%s:%d] %s\n", FindRoom(g_RoomInfo, si.hEvent)->cpRoomName,
	//	inet_ntoa(si.saSocketAddr.sin_addr), htons(si.saSocketAddr.sin_port), buf);
	//ROOMINFO* ri = FindRoom(g_RoomInfo, si.hEvent);
	//SendAll(ri, si.hEvent, buf, retByte);
}

#endif