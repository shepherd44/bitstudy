/**********************************************************
 * SelectEvent ��Ƽ ä��
 * --�氳�� �߰�
 * --client ���� ����üȭ
 * --STL����
 **********************************************************/
#if 1

#include "SocketInfo.h"
#include "chatdef.h"
#include "omokdef.h"
using namespace std;

// �ܺ�(EXTERN) �������� ����
SOCKET g_ServerSocket;
WSAEVENT g_hEventList[MAX_SOCKET_NUM];
std::vector<ROOMINFO> g_RoomInfo;
SOCKET SockList[MAX_SOCKET_NUM];
int g_EventCnt;

// ��������
std::vector<EVENTSOCKET> g_awaiter;

void RecvClient(EVENTSOCKET si, OMOKMESSAGE* msg);

// �����Լ�
int main(int argc, char* argv[])
{
	//����ڿ� �� ����
	CreateRoom(g_RoomInfo, AWAITER_ROOM, "awaiter_room");

	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("��� ���� ���� ����\n");
		return -1;
	}

	// ����ó��
	//===================================================
	int eventindex = 0;
	WSANETWORKEVENTS neEvents;
	//�߻��� �̺�Ʈ ��� ����

	EVENTSOCKET evSockTemp;
	while(1)
	{
		// �̺�Ʈ �ñ׳� ����
		eventindex = WSAWaitForMultipleEvents(g_EventCnt, g_hEventList,
			FALSE, WSA_INFINITE, FALSE);
		// �ε��� ����
		eventindex -= WSA_WAIT_EVENT_0;
		// �̺�Ʈ ���� ��������
		// EventList[eventindex] �̺�Ʈ�� �ͽñ׳��� ����
		evSockTemp = FindEventSocket(g_RoomInfo, g_hEventList[eventindex]);
		WSAEnumNetworkEvents(evSockTemp.sSocket, g_hEventList[eventindex], &neEvents);

		// �̺�Ʈ ó��
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
	
	// ä���� ��� �ڱ����� ��ο��� ����
	int retByte = recv(si.sSocket,(char*) msg, sizeof(OMOKMESSAGE), 0);
	// ���� �ֿܼ� ����Ʈ
	//printf("[%s][%s:%d] %s\n", FindRoom(g_RoomInfo, si.hEvent)->cpRoomName,
	//	inet_ntoa(si.saSocketAddr.sin_addr), htons(si.saSocketAddr.sin_port), buf);
	//ROOMINFO* ri = FindRoom(g_RoomInfo, si.hEvent);
	//SendAll(ri, si.hEvent, buf, retByte);
}

#endif