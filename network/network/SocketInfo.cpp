#include "SocketInfo.h"

// ���� �Ϸ�------------------------------------------------
// �������� �ʱ�ȭ
bool CreateListenSocket()
{
	int retval;
	
	g_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(g_ServerSocket == INVALID_SOCKET)
	{
		DisplayMessage();	return false;
	}
	SOCKADDR_IN serveraddr;
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
	HANDLE hEvent = WSACreateEvent();
	WSAEventSelect( g_ServerSocket, hEvent, FD_ACCEPT | FD_CLOSE);
	g_hEventList[0] = hEvent;
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

// ����� ������, ����
int AddClient(ROOMINFO& ri, SOCKETINFO si, int index)
{
	SOCKETINFO siTemp;
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
	
	g_hEventList[g_SockCnt] = hClientEvent;
	g_SockCnt++;
	// Ŭ���̾�Ʈ ����Ʈ�� ���
	siTemp.hEvent = hClientEvent;
	ri.ClientList.push_back(siTemp);
	
	// ���Ӹ޼��� ����
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(sockaddr->sin_addr), ntohs(sockaddr->sin_port));
	// send all ���� �� ���� �ʿ�
	SendAll(ri,0, buf, retByte);

	return true;

}
void OutClient(ROOMINFO& ri, SOCKETINFO si)
{
	for(int i = 0; i<ri.ClientList.size(); i++)
	{
		if(ri.ClientList.at(i).sSocket == si.sSocket)
		{
			ri.ClientList.erase(ri.ClientList.begin() + i);
			break;
		}
	}
}

// ����� ����� ���(ClientList) �ޱ�
std::vector<SOCKETINFO> GetClientList(ROOMINFO& ri)
{
	return ri.ClientList;
}
// ����� ã��
SOCKETINFO* FindClient(std::vector<SOCKETINFO> v, SOCKET s)
{
	for(int i=0; i<v.size(); i++)
	{
		if(v.at(i).sSocket == s)
			return &v.at(i);
	}
	return NULL;
}

// ����� ��ο��� �޼��� ����
void SendAll(ROOMINFO& ri, WSAEVENT he, const char *str, int len)
{
	for(int i=0; i<ri.ClientList.size(); i++)
	{
		if(ri.ClientList.at(i).hEvent != he)
			send(ri.ClientList.at(i).sSocket , str, len, 0);
	}
}
void RecvClient(ROOMINFO& ri, SOCKETINFO si)
{
	char buf[BUFFERSIZE];
	memset(buf, 0, BUFFERSIZE);
	int addrlen = sizeof(si.saSocketAddr);

	SOCKET ClientSocket = si.sSocket;

	int retByte = recv(ClientSocket, buf, BUFFERSIZE, 0);
	printf("[%s:%d] %s\n", inet_ntoa(si.saSocketAddr.sin_addr), htons(si.saSocketAddr.sin_port), buf);

	SendAll(ri, si.hEvent, buf, retByte);
}
