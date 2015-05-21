#include "RoomInfo.h"

CRoomInfo::CRoomInfo(void)
{
	this->m_RoomNum = 0;
	this->m_MaxRoomUser = 0;
	this->m_RoomName = NULL;
}

CRoomInfo::CRoomInfo(int roomnum, char* roomname, int maxuser)
{
	this->m_RoomNum = roomnum;
	this->m_MaxRoomUser = maxuser;
	m_RoomName = new char[strlen(roomname)];
}
CRoomInfo::~CRoomInfo(void)
{
	delete m_RoomName;
}

//COmokRoom 함수 정의-----------------------------------------------------------
// 사용자 찾기
EVENTSOCKET* COmokRoom::FindUser(SOCKET s)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).sSocket == s)
			return &this->m_UserList.at(i);
	}
	return NULL;
}
EVENTSOCKET* COmokRoom::FindUser(WSAEVENT ev)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).hEvent == ev)
			return &this->m_UserList.at(i);
	}
	return NULL;
}
EVENTSOCKET* COmokRoom::FindUser(SOCKET s, UINT* pi)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).sSocket == s)
		{
			*pi = i;
			return &this->m_UserList.at(i);
		}
	}
	return NULL;
}
EVENTSOCKET* COmokRoom::FindUser(WSAEVENT ev, UINT* pi)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).hEvent == ev)
		{
			*pi = i;
			return &this->m_UserList.at(i);
		}
	}
	return NULL;
}
UINT COmokRoom::FindUserIndex(SOCKET s)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).sSocket == s)
			return i;
	}
	return -1;
}
UINT COmokRoom::FindUserIndex(WSAEVENT ev)
{
	for(UINT i = 0; i<this->m_UserList.size(); i++)
	{
		if(this->m_UserList.at(i).hEvent == ev)
			return i;
	}
	return -1;
}
int COmokRoom::AddUser(EventSocket evuser)
{
	EVENTSOCKET* temp = FindUser(evuser.sSocket);
	if(temp == NULL)
	{
		this->m_UserList.push_back(evuser);
		return NOTERROR;
	}
	else
		return FULLROOM;
}

int COmokRoom::OutUser(EventSocket evuser)
{
	UINT index = 0;
	EventSocket* temp = FindUser(evuser.sSocket, &index);
	if(temp != NULL)
	{
		this->m_UserList.erase(this->m_UserList.begin() + index);
		return NOTERROR;
	}
	else
		return EMPTYROOM;
}
// 방안의 모두에게 메세지 전송
void COmokRoom::SendAll(const char *str, int msglen)
{
	for(UINT i = 0; i < this->m_UserList.size() ; i++)
	{
		send(this->m_UserList.at(i).sSocket, str, msglen, 0);
	}
}
void COmokRoom::SendAllExceptMe(SOCKET me, const char* str, int msglen)
{
	for(UINT i = 0; i < this->m_UserList.size() ; i++)
	{
		if(this->m_UserList.at(i).sSocket != me)
			send(this->m_UserList.at(i).sSocket, str, msglen, 0);
	}

}
void COmokRoom::SendTo(SOCKET you, const char* str, int msglen)
{
	EVENTSOCKET* temp = FindUser(you);
	if(temp == NULL)
		return ;

	SOCKET s = temp->sSocket;
	send(s, str, msglen, 0);

}
int COmokRoom::RecvClient(EVENTSOCKET si)
{
	return NULL;
}
bool COmokRoom::IsFoolRoom()
{
	if(this->m_UserList.size() >= (UINT)this->m_MaxRoomUser)
		return true;
	return false;
}
bool COmokRoom::IsEmptyRoom()
{
	if(this->m_UserList.size() < (UINT)this->m_MaxRoomUser)
		return true;
	return false;
}