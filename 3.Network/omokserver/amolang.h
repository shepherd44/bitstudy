// ���뼱��� �� ��ũ�� ����
//
#pragma once

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>


#define BUFFERSIZE			1024

// �����޽��� ���
void DisplayMessage();

#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}




