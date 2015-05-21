#include "omokdef.h"

#define MBOX(str) MessageBox(0,TEXT("str"), TEXT(""), MB_OK)

int IsWin(GAMEMAP* map)
{
	for(int i=2; i<PANROW-2;i++)
	{
		for(int j=2; j<PANCOL-2;j++)
		{
			if(map->ChargedStone[i][j-2]==BLACK && map->ChargedStone[i][j-1]==BLACK &&map->ChargedStone[i][j]==BLACK && map->ChargedStone[i][j+1]==BLACK && map->ChargedStone[i][j+2]==BLACK) //���� ���� �ټ��� ��
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return BLACK;
			}
			else if(map->ChargedStone[i-2][j]==BLACK && map->ChargedStone[i-1][j]==BLACK &&map->ChargedStone[i][j]==BLACK && map->ChargedStone[i+1][j]==BLACK && map->ChargedStone[i+2][j]==BLACK)//���� ���� �ټ��� ��
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return BLACK;
			}

			else if(map->ChargedStone[i][j-2]==WHITE && map->ChargedStone[i][j-1]==WHITE &&map->ChargedStone[i][j]==WHITE && map->ChargedStone[i][j+1]==WHITE && map->ChargedStone[i][j+2]==WHITE)
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return WHITE;
			}
			else if(map->ChargedStone[i-2][j]==WHITE && map->ChargedStone[i-1][j]==WHITE &&map->ChargedStone[i][j]==WHITE && map->ChargedStone[i+1][j]==WHITE && map->ChargedStone[i+2][j]==WHITE)
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return WHITE;
			}

			else if(map->ChargedStone[i-2][j-2]==BLACK && map->ChargedStone[i-1][j-1]==BLACK &&map->ChargedStone[i][j]==BLACK && map->ChargedStone[i+1][j+1]==BLACK && map->ChargedStone[i+2][j+2]==BLACK)
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return BLACK;
			}
			else if(map->ChargedStone[i-2][j+2]==BLACK && map->ChargedStone[i-1][j+1]==BLACK &&map->ChargedStone[i][j]==BLACK && map->ChargedStone[i+1][j-1]==BLACK && map->ChargedStone[i+2][j-2]==BLACK)
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return BLACK;
			}

			else if(map->ChargedStone[i-2][j-2]==WHITE && map->ChargedStone[i-1][j-1]==WHITE &&map->ChargedStone[i][j]==WHITE && map->ChargedStone[i+1][j+1]==WHITE && map->ChargedStone[i+2][j+2]==WHITE)
			{
				memset(map->ChargedStone,0,sizeof(map->ChargedStone));
				return WHITE;
			}
			else if(map->ChargedStone[i-2][j+2]==WHITE && map->ChargedStone[i-1][j+1]==WHITE &&map->ChargedStone[i][j]==WHITE && map->ChargedStone[i+1][j-1]==WHITE && map->ChargedStone[i+2][j-2]==WHITE)
			{
				memset(map->ChargedStone,0,sizeof(GAMEMAP));
				return WHITE;
			}
		}
	}
	return NOT;
}

SOCKET CreateServerSocket( )
{
	WSADATA wsa; 

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL �ε� 
	{
		MBOX("WSAStartup Error !! "); return INVALID_SOCKET ;
	}
	SOCKET ServerSocket;
	ServerSocket = socket( AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		MBOX("socket() error!!");	return INVALID_SOCKET; 
	}
	SOCKADDR_IN ServerAddr; 
	ServerAddr.sin_family		  = AF_INET;
	ServerAddr.sin_port		  = htons(20000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  

	int ret =	bind( ServerSocket,	(SOCKADDR*)&ServerAddr,	sizeof(ServerAddr));
	if( ret == SOCKET_ERROR) 
	{
		MBOX("bind() error !! "); return INVALID_SOCKET; 
	}
	ret = listen( ServerSocket, SOMAXCONN);
	if( ret == SOCKET_ERROR ) 
	{
		MBOX("listen() error !!"); return INVALID_SOCKET; 
	}
	return ServerSocket; 
}

SOCKET CreateClientSocket(SOCKADDR_IN* ServerAddr)
{
	WSADATA wsa; // ��������   

	if( WSAStartup( MAKEWORD(2,2), &wsa) != 0) //DLL �ε� 
	{
		MBOX("WSAStartup Error !! "); return INVALID_SOCKET ;
	}

	SOCKET ServerSocket;  
	
	ServerSocket = socket(AF_INET  , SOCK_STREAM, 0);  

	if( ServerSocket == INVALID_SOCKET)
	{
		MBOX("socket Error !! "); return INVALID_SOCKET ;
	}
	
	if(	connect(ServerSocket,  (SOCKADDR*)ServerAddr, sizeof( *ServerAddr)) != 0)
	{
		MBOX("connet() error!!");	return INVALID_SOCKET; 
	}
	return ServerSocket; 
}

OMOKMATRIX PointToMatrix(POINTS pt)
{
	OMOKMATRIX om;
	
	pt.y -= 25; 
	om.col = pt.x/30;
	om.row  = pt.y/30;
	
	return om; 
}

bool PutStone(GAMEMAP* map, OMOKMATRIX pt)
{
	// �ٵϾ� �ִ��� Ȯ��
	if(map->ChargedStone[pt.row][pt.col] != NOT)
	{
		MBOX("�ٵϾ��� �ֽ��ϴ�.");
		return false;
	}
	if( map->turn )
		map->ChargedStone[pt.row][pt.col] =  BLACK;
	else 
		map->ChargedStone[pt.row][pt.col] =  WHITE;
	return true;
	
}

//------
// �� ����, ����
int CreateRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
int CreateGameRoom(std::vector<CRoomInfo>& v, int rnum, const char* str);
void DeleteRoom(std::vector<CRoomInfo>& v, int index );

void JoinEvent();
// �������� ���� �� ���濡 ���
bool CreateListenSocket();
int ListenClient();
// �� ã��
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, int index);
CRoomInfo* FindRoom(std::vector<CRoomInfo>& v, WSAEVENT wsaevent);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, SOCKET s);
// CRoomInfo& FindRoom(std::vector<ROOMINFO>& v, const char* str);


