/**********************************************************
 * SelectEvent ��Ƽ ä��
 * --�氳�� �߰�
 * --client ���� ����üȭ
 * --STL����
 **********************************************************/
#if 1

#include "SocketInfo.h"


using namespace std;
SOCKET g_ServerSocket;
WSAEVENT g_hEventList[MAX_SOCKET_NUM];
std::vector<ROOMINFO> g_RoomInfo;
SOCKET SockList[MAX_SOCKET_NUM];
int g_SockCnt;


int main(int argc, char* argv[])
{
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
	int index = 0;
	WSANETWORKEVENTS neEvents;
	CreateRoom(1, "myroom");
	RoomInfo sss= g_RoomInfo.front();
	puts(sss.cpRoomName);
	while(1)
	{
		// �̺�Ʈ �ñ׳� ����
		index = WSAWaitForMultipleEvents(g_SockCnt, g_hEventList,
			FALSE, WSA_INFINITE, FALSE);
		index -= WSA_WAIT_EVENT_0;
		FindSocket(index);
		// �̺�Ʈ ���� �������� + EventList[index] �̺�Ʈ�� �ͽñ׳��� ����
		WSAEnumNetworkEvents( SockList[index], g_hEventList[index], &neEvents);
		if(neEvents.lNetworkEvents & FD_ACCEPT)
		{
			EVENTERRORCHECK(neEvents, FD_ACCEPT_BIT);
			if(AddClient(index) != true)
				continue;
		}
		else if(neEvents.lNetworkEvents & FD_READ || neEvents.lNetworkEvents & FD_WRITE)
		{
			if(neEvents.iErrorCode[FD_READ_BIT] != 0 && neEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
			RecvClient(index);
			
		}
		else if(neEvents.lNetworkEvents & FD_CLOSE)
		{
			EVENTERRORCHECK(neEvents, FD_CLOSE_BIT);
				DeleteClient(index);
		}
	}
	//===================================================

	WSACleanup();
	return 0;
}
#endif