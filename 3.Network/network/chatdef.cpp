#include "chatdef.h"

void JoinEvent(EVENTSOCKET& serversocket)
{
	CreateListenSocket();
	//�̺�Ʈ ���
	HANDLE hEvent = WSACreateEvent();
	WSAEventSelect( g_ServerSocket, hEvent, FD_ACCEPT | FD_CLOSE);
	g_hEventList[0] = hEvent;
	g_EventCnt++;
}

bool CreateListenSocket()
{
	EVENTSOCKET esTemp;
	int retval;
	g_ServerSocket = esTemp.sSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(g_ServerSocket == INVALID_SOCKET)
	{
		DisplayMessage();	return false;
	}
	SOCKADDR_IN& serveraddr = esTemp.saSocketAddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40100);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	retval = bind(g_ServerSocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	retval = listen(g_ServerSocket,SOMAXCONN);
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	//�̺�Ʈ ���
	HANDLE hEvent = WSACreateEvent();
	WSAEventSelect( g_ServerSocket, hEvent, FD_ACCEPT | FD_CLOSE);
	g_hEventList[0] = esTemp.hEvent = hEvent;
	g_EventCnt++;
	//����ڹ濡 ���
	(*FindRoom(g_RoomInfo, AWAITER_ROOM)).ClientList.push_back(esTemp);
	return true;
}
// �� ����, ����
int CreateRoom(std::vector<ROOMINFO>& v, int rnum, const char* str)
{
	for(int i=0; i < v.size(); i++)
	{
		if(v.at(i).iRoomNum == rnum)
			return -1;
	}
	ROOMINFO riTemp;
	int len = strlen(str);
	strcpy(riTemp.cpRoomName, str);
	riTemp.iRoomNum = rnum;
	
	v.push_back(riTemp);
}
void DeleteRoom(std::vector<ROOMINFO>& v, int index )
{
	for(int i=0;i<v.size();i++)
	{
		if(v.at(i).iRoomNum == index)
		{
			v.erase(v.begin()+i);
			return;
		}
	}
}

// ���� á����/������� Ȯ��
bool IsFoolRoom(ROOMINFO& ri)
{
	if(ri.ClientList.size() == 0)
		return false;
	return true;
}
bool IsEmptyRoom(ROOMINFO& ri)
{
	if(ri.ClientList.size() ==0 )
		return true;
	return false;
}
// �� ã��
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index)
{
	for(int i = 0; i< v.size(); i++)
	{
		if(v.at(i).iRoomNum == index)
			return &v.at(i);
	}
	return NULL;
}

// ���� �ʿ�-------------------------------------------------

// ROOMINFO& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
/*
ROOMINFO& FindRoom(std::vector<ROOMINFO>& v, const char* str)
{
	for(int i = 0; i< v.size(); i++)
	{
		if(strcat(v.at(i).ClientList. == 0)
			return v.at(i);
	}
	return 0;
}
*/

// accept ���� - ��⿭���� ��ٸ���
int ListenClient()
{
	EVENTSOCKET siTemp;
	SOCKET* ClientSocket = &siTemp.sSocket;
	SOCKADDR_IN* sockaddr = &siTemp.saSocketAddr;
	int addrlen = sizeof(*sockaddr);
	*ClientSocket = accept(g_ServerSocket, (SOCKADDR*)sockaddr, &addrlen);
	if(*ClientSocket == SOCKET_ERROR)
	{
		DisplayMessage();	return false;
	}
	// �̺�Ʈ ���
	WSAEVENT hClientEvent = WSACreateEvent();
	WSAEventSelect(*ClientSocket, hClientEvent, FD_WRITE | FD_READ | FD_CLOSE);
	
	g_hEventList[g_EventCnt] = hClientEvent;
	g_EventCnt++;
	// Ŭ���̾�Ʈ ����Ʈ�� ���
	siTemp.hEvent = hClientEvent;
	// ��⿭�� ���- �������

	FindRoom(g_RoomInfo, AWAITER_ROOM)->ClientList.push_back(siTemp);
	
	// ���Ӹ޼��� ����
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP ����][%s:%d]������ ȯ���մϴ�.\n",
		inet_ntoa(sockaddr->sin_addr), ntohs(sockaddr->sin_port));
	send(siTemp.sSocket, buf, strlen(buf), 0);
	return true;
}
// ������ ������ ����
int AddClient(ROOMINFO& ri, const EVENTSOCKET& si, int index)
{

	// ���Ӹ޼��� ����
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP ����][%s:%d]�� ����\n",
		inet_ntoa(si.saSocketAddr.sin_addr), ntohs(si.saSocketAddr.sin_port));

	SendAll(&ri, si.hEvent, buf, retByte);

	return true;

}
void OutClient(ROOMINFO& ri, EVENTSOCKET si)
{
	// ���� �޼��� ����
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP ����][%s:%d]�� ����\n",
		inet_ntoa(si.saSocketAddr.sin_addr), ntohs(si.saSocketAddr.sin_port));
	SendAll(&ri, si.hEvent, buf, retByte);

	for(int i=0; i< ri.ClientList.size(); i++)
		if(ri.ClientList.at(i).sSocket == si.sSocket)
			ri.ClientList.erase(ri.ClientList.begin() + i);
}

// ����� ����� ���(ClientList) �ޱ�
std::vector<EVENTSOCKET> GetClientList(ROOMINFO& ri)
{
	return ri.ClientList;
}
// ����� ã��
EVENTSOCKET* FindClient(std::vector<EVENTSOCKET> v, SOCKET s)
{
	for(int i=0; i<v.size(); i++)
	{
		if(v.at(i).sSocket == s)
			return &v.at(i);
	}
	return NULL;
}

ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, WSAEVENT wsaevent)
{
	for(int i = 0; i < v.size(); i++)
	{
		for(int j=0; j<v.at(i).ClientList.size(); j++)
		{
			if(v.at(i).ClientList.at(j).hEvent == wsaevent)
				return &v.at(i);
		}
	}
	return NULL;
}

SOCKET FindSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent)
{
	for(int i = 0; i < v.size(); i++)
	{
		for(int j=0; j<v.at(i).ClientList.size(); j++)
		{
			if(v.at(i).ClientList.at(j).hEvent == wsaevent)
				return v.at(i).ClientList.at(j).sSocket;
		}
	}
	return NULL;
}
EVENTSOCKET FindEventSocket(std::vector<ROOMINFO>& v, WSAEVENT wsaevent)
{
	for(int i = 0; i < v.size(); i++)
	{
		for(int j=0; j<v.at(i).ClientList.size(); j++)
		{
			if(v.at(i).ClientList.at(j).hEvent == wsaevent)
				return v.at(i).ClientList.at(j);
		}
	}
	EVENTSOCKET esTemp = {0,};
	return esTemp;
}

// ����� ��ο��� �޼��� ����
void SendAll(ROOMINFO* ri, WSAEVENT he, const char *str, int len)
{
	for(int i=0; i<ri->ClientList.size(); i++)
	{
		if(ri->ClientList.at(i).hEvent != he)
			send(ri->ClientList.at(i).sSocket , str, len, 0);
	}
}

void RecvClient(EVENTSOCKET si)
{
	char buf[BUFFERSIZE];
	memset(buf, 0, BUFFERSIZE);
	int addrlen = sizeof(si.saSocketAddr);
	
	// ä���� ��� �ڱ����� ��ο��� ����
	int retByte = recv(si.sSocket, buf, BUFFERSIZE, 0);
	printf("[%s][%s:%d] %s\n", FindRoom(g_RoomInfo, si.hEvent)->cpRoomName,
		inet_ntoa(si.saSocketAddr.sin_addr), htons(si.saSocketAddr.sin_port), buf);
	ROOMINFO* ri = FindRoom(g_RoomInfo, si.hEvent);
	SendAll(ri, si.hEvent, buf, retByte);
}
