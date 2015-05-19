#pragma once
#include <winsock2.h>
#include "SocketInfo.h"

//������ ������ ��ũ��
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
// ���� �� row, col
#define PANROW		20
#define PANCOL		20
// ���� ���ѽð�
#define LIMITEDTIME		30
// Ÿ�̸� ID
#define IDT_GAMETIMERME		1001
#define IDT_GAMETIMERCOM	1002
// �̹��� ���(���Ļ�(����))
#define ALPHACOLOR			RGB(255,0,0)

// ���� ��ũ�� ����
#define UM_SOCKET			WM_USER + 1
#define UM_CLIENT			WM_USER + 2

// �ٵϵ�
enum STONE { NOT = 0, BLACK, WHITE, STONENUM};
// ���� �÷��� ����
enum GameState {NOTPLAY = 0, PLAY, BLACKWIN, WHITEWIN, INIT, WAITING, STARTMSG};
enum GameTurn {TURN1 = 0, TURN2};
// ���� �� ����ü
typedef struct GameMap {
	int ChargedStone[PANROW][PANCOL];
	bool turn;
	int GameState;
	int GameTurn;
	int MyStone;
	int RoomIndex;
	char buf[32];
} GAMEMAP;

typedef struct OmokMatrix{
	int row;
	int col;
}OMOKMATRIX;

enum OMOKMSG{NOTMSG = 0, PTMSG = 1, WINMSG, CHATMSG, ROOMMSG, TURNMSG, GAMESTARTMSG};
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

// ��������Ʈ �̹��� ����ü
typedef struct SpriteImage{
	HDC hSpriteDC;
	HBITMAP Sprite;
	int Imagewidth;
	int imageheight;
	int widthlevel;
	int heightlevel;
} SPRITEIMAGE;

// ���� �̱��� Ȯ��
int IsWin(GAMEMAP* map);
SOCKET CreateServerSocket();
SOCKET CreateClientSocket(SOCKADDR_IN* ServerAddr);
OMOKMATRIX PointToMatrix(POINTS pt);
bool PutStone(GAMEMAP* map, OMOKMATRIX pt);