// ���뼱��� �� ��ũ�� ����
//
#pragma once

#include <vector>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#include "omokdef.h"
#include "SocketInfo.h"
#include "resource.h"


#define BUFFERSIZE			1024
#define MAX_LOADSTRING	100
#define WIDTHSIZE		100
#define HEIGTHSIZE		100


// �����޽��� ���
void DisplayMessage();

#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}
#define MBOX(str) MessageBox(0,TEXT(str), TEXT(""), MB_OK)



