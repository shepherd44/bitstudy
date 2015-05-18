// 공통선언부 및 매크로 지정
//
#pragma once

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>


#define BUFFERSIZE			1024

// 오류메시지 출력
void DisplayMessage();

#define EVENTERRORCHECK(ne,ercode)	{if(ne.iErrorCode[ercode] != 0) {		\
	DisplayMessage();	return -1; }}




