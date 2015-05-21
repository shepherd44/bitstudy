#include "chatdef.h"

void JoinEvent(EVENTSOCKET& serversocket)
{
	CreateListenSocket();
	//이벤트 등록
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
	//이벤트 등록
	HANDLE hEvent = WSACreateEvent();
	WSAEventSelect( g_ServerSocket, hEvent, FD_ACCEPT | FD_CLOSE);
	g_hEventList[0] = esTemp.hEvent = hEvent;
	g_EventCnt++;
	//대기자방에 등록
	(*FindRoom(g_RoomInfo, AWAITER_ROOM)).ClientList.push_back(esTemp);
	return true;
}
// 방 생성, 삭제
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
	riTemp.MaxRoomUser = MAX_ROOMUSER;
	v.push_back(riTemp);
	return 0;
}
int CreateGameRoom(std::vector<ROOMINFO>& v, int rnum, const char* str)
{
	for(int i=0; i < v.size(); i++)
	{
		if(v.at(i).iRoomNum == rnum)
			return -1;
	}
	ROOMINFO riTemp;
	int len = strlen(str);
	strcpy(riTemp.cpRoomName, str);
	riTemp.MaxRoomUser = MAX_GAMEROOMUSER;
	riTemp.iRoomNum = rnum;
	
	v.push_back(riTemp);
	printf("[TCP서버][%d:%s] 방생성\n", riTemp.iRoomNum, riTemp.cpRoomName);
	return 0;
}
void DeleteRoom(std::vector<ROOMINFO>& v, int index )
{
	for(int i=0;i<v.size();i++)
	{
		if(v.at(i).iRoomNum == index)
		{
			printf("[TCP서버][%d:%s] 방삭제\n", v.at(i).iRoomNum, v.at(i).cpRoomName);
			v.erase(v.begin()+i);

			return;
		}
	}
}

// 방이 찼는지/비었는지 확인
bool IsFoolRoom(ROOMINFO& ri)
{
	if(ri.ClientList.size() == ri.MaxRoomUser)
		return true;
	return false;
}
bool IsEmptyRoom(ROOMINFO& ri)
{
	if(ri.ClientList.size() == 0 )
		return true;
	return false;
}
// 방 찾기
ROOMINFO* FindRoom(std::vector<ROOMINFO>& v, int index)
{
	for(int i = 0; i< v.size(); i++)
	{
		if(v.at(i).iRoomNum == index)
			return &v.at(i);
	}
	return NULL;
}

// 정의 필요-------------------------------------------------

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

// accept 대응 - 대기열에서 기다리기
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
	// 이벤트 등록
	WSAEVENT hClientEvent = WSACreateEvent();
	WSAEventSelect(*ClientSocket, hClientEvent, FD_WRITE | FD_READ | FD_CLOSE);
	
	g_hEventList[g_EventCnt] = hClientEvent;
	g_EventCnt++;
	// 클라이언트 리스트에 등록
	siTemp.hEvent = hClientEvent;
	// 대기열에 등록- 방들어가기전(awaiter_room)

	AddClient(*FindRoom(g_RoomInfo,AWAITER_ROOM),siTemp);
	// 접속메세지 전송
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP 서버][%s:%d]님 접속을 환영합니다.\n",
		inet_ntoa(sockaddr->sin_addr), ntohs(sockaddr->sin_port));
	
	send(siTemp.sSocket, buf, strlen(buf), 0);
	return true;
}
// 선택한 방으로 입장
int AddClient(ROOMINFO& ri, const EVENTSOCKET si)
{
	if(ri.ClientList.size() == ri.MaxRoomUser)
		return false;
	ri.ClientList.push_back(si);
	// 접속메세지 전송
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP 서버][%s][%s:%d]님 접속\n", ri.cpRoomName,
		inet_ntoa(si.saSocketAddr.sin_addr), ntohs(si.saSocketAddr.sin_port));
	// 서버 콘솔에 프린트
	puts(buf);
	SendAll(&ri, si.hEvent, buf, retByte);

	return true;

}
void OutClient(ROOMINFO& ri, EVENTSOCKET si)
{
	// 퇴장 메세지 전송
	char buf[BUFFERSIZE];
	int retByte = sprintf(buf, "\n[TCP 서버][%s:%d]님 퇴장\n",
		inet_ntoa(si.saSocketAddr.sin_addr), ntohs(si.saSocketAddr.sin_port));
	SendAll(&ri, si.hEvent, buf, retByte);
	// 서버 콘솔에 프린트
	puts(buf);
	for(int i=0; i< ri.ClientList.size(); i++)
		if(ri.ClientList.at(i).sSocket == si.sSocket)
			ri.ClientList.erase(ri.ClientList.begin() + i);
}

// 방안의 사용자 목록(ClientList) 받기
std::vector<EVENTSOCKET> GetClientList(ROOMINFO& ri)
{
	return ri.ClientList;
}
// 사용자 찾기
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

// 방안의 모두에게 메세지 전송
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
	
	// 채팅일 경우 자기제외 모두에게 전송
	int retByte = recv(si.sSocket, buf, BUFFERSIZE, 0);
	// 서버 콘솔에 프린트
	printf("[%s][%s:%d] %s\n", FindRoom(g_RoomInfo, si.hEvent)->cpRoomName,
		inet_ntoa(si.saSocketAddr.sin_addr), htons(si.saSocketAddr.sin_port), buf);
	ROOMINFO* ri = FindRoom(g_RoomInfo, si.hEvent);
	SendAll(ri, si.hEvent, buf, retByte);
}
