//----------------------------------------------------------------
//  네트워크 유틸리티 !! 
//----------------------------------------------------------------
// 주소 변환 관련 --> IP 
//----------------------------------------------------------------
#include <winsock2.h> 
#include <stdio.h> 


void main()
{	
	WSADATA wsa; // 소켓 버전 정보 구조체 !! 
	// 1) Windows DLL파일을 로딩 !!

	if( WSAStartup( MAKEWORD(2,2) , &wsa) != 0) 
	{c
		puts("실패 !!");return;  
	}
	//-------------------------------------------------------------------
	
	char * addr =  "127.0.0.1"; 
	printf("문자열 주소 : %s\n" , addr );
	// 4byte의 정수로 표현 
	// 1byte단위로 저장 
	// [127][0][0][1]  
	// 문자열 IP주소 -->  정수형태의 IP주소로 변환  
	//printf("0x08%x\n" ,	inet_addr( addr ) ); 
	// 정수형태의 주소 -->  문자열  
	
	IN_ADDR in_addr;
	in_addr.s_addr  = inet_addr( addr );
	// 정수형태의 IP주소를 문자열 형태로 변환 !! 
	puts(  inet_ntoa( in_addr )) ;   
		
	//  바이트 정렬  !! 
	//  -->   빅인디언 :  네트워크 통신 표준 방식 !!  
	// -->  리틀인디언 :  로컬에서 사용되는 방식 !! 
  
	unsigned short us = 0x3412; 
	
	printf("0x%08x\n" ,   us ); 
	printf("0x%08x\n" ,   ntohl( us ) ); 
	
	//------------------------------------------------------------------
	// 주소 정보 구조체 !! 
	//------------------------------------------------------------------
	/*
	SOCKADDR_IN addrin;
	addrin.sin_addr.s_addr // IP 
	addrin.sin_port = 2000; // 실제 서비스 포트 :  2000이상 !! 
	addrin.sin_family = AF_INET;
	*/


		
	//-------------------------------------------------------------------
	WSACleanup(); //  DLL 언로딩 !!
}