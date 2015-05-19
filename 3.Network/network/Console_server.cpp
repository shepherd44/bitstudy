/**********************************************************
 * SelectEvent ��Ƽ ä��
 * --�氳�� �߰�
 * --client ���� ����üȭ
 * --STL����
 **********************************************************/
#if 1

#include "SocketInfo.h"
#include "chatdef.h"
using namespace std;

// �ܺ�(EXTERN) �������� ����
SOCKET g_ServerSocket;
WSAEVENT g_hEventList[MAX_SOCKET_NUM];
std::vector<ROOMINFO> g_RoomInfo;
SOCKET SockList[MAX_SOCKET_NUM];
int g_EventCnt;

// ��������
std::vector<EVENTSOCKET> g_awaiter;

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
			
			RecvClient(evSockTemp);
			
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
#endif