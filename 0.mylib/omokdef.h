#pragma once
#include <winsock2.h>
#include "RoomInfo.h"

//윈도우 사이즈 매크로
#define GAMESTATUS_WIDTH	30
#define ONEDIGIT_HEIGHT		23
#define MAP_START_X			0
#define MAP_START_Y			ONEDIGIT_HEIGHT
#define MAP_WIDTH			610
#define MAP_HEIGHT			610
#define BLANK				40
#define STONE_SIZE			29
#define LIMITEDTIME			30
#define WINDOW_WIDTH		(MAP_WIDTH+17)
#define WINDOW_HEIGHT		(MAP_HEIGHT + ONEDIGIT_HEIGHT+ BLANK)
#define OMOKMSGBUUFERSIZE	128

#define GAMEBUFFERSIZE		124
// 오목 맵 row, col
#define PANROW		20
#define PANCOL		20
// 게임 제한시간
#define LIMITEDTIME		30
// 타이머 ID
#define IDT_GAMETIMERME		1001
#define IDT_GAMETIMERCOM	1002
// 이미지 배경(알파색(빨강))
#define ALPHACOLOR			RGB(255,0,0)

// 유저 매크로 정의
#define UM_SOCKET			WM_USER + 1
#define UM_CLIENT			WM_USER + 2

// 바둑돌 정의
enum STONE { NOT = 0, BLACK, WHITE, STONENUM};
// 게임 플레이 상태
enum GameState {OMOKNOTPLAY = 0, OMOKPLAY, OMOKINIT, OMOKWAITING, OMOKREADY,OMOKSTART};
enum GameTurn {TURN1 = 0, TURN2};

// 오목 맵 구조체
typedef struct GameMap {
	int ChargedStone[PANROW][PANCOL];
	bool turn;
	int GameState;
	int GameTurn;
	int MyStone;
	int RoomIndex;
	char buf[32];
} GAMEMAP;

struct OmokState{
	bool m_UserTurn;
	int m_GameState;
	int m_GameTurn;
	int m_MyStone;
} OMOKState;

class COmokMap{
	int m_stone[PANROW][PANCOL];
		
};
typedef struct OmokMatrix{
	int row;
	int col;
}OMOKMATRIX;

enum OMOKMSG{NOTMSG = 0, PTMSG = 1, ROOMMSG, WAITINGMSG, READYMSG, GAMESTARTMSG, CHATMSG};
typedef struct OmokMessage{
	int OmokMsg;
	union{
		struct{
		OMOKMATRIX pt;
		int turn;
		}PT;
		struct{
		int roomindex;
		char roomname[32];
		}room;
		bool win;
		char buf[OMOKMSGBUUFERSIZE];
	};
}OMOKMESSAGE;

// 스프라이트 이미지 구조체
typedef struct SpriteImage{
	HDC hSpriteDC;
	HBITMAP Sprite;
	int Imagewidth;
	int imageheight;
	int widthlevel;
	int heightlevel;
} SPRITEIMAGE;

// 게임 이긴지 확인
int IsWin(GAMEMAP* map);
SOCKET CreateServerSocket();
SOCKET CreateClientSocket(SOCKADDR_IN* ServerAddr);
OMOKMATRIX PointToMatrix(POINTS pt);
bool PutStone(GAMEMAP* map, OMOKMATRIX pt);
