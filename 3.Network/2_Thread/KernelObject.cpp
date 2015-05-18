//--------------------------------------------------------------------
// -  커널오브젝트를 활용한 network 프로그래밍 
//--------------------------------------------------------------------
// - Kernel Object  --> 커널에서 관리하고 커널에 존재는 객체 !! 
	
//  OS의 내부 Kernel 영역에 저장되고  사용되어지는 객체 !! 
//  ---> Process, Thread, ComplitePort, pipe, Event, semaphore, mutex 
//  --->  
/*
user       	[     ]
------------------------
Kernel	       [     ]
*/  

//--------------------------------------------------------------------
//  thead :  독립적으로 실행되는 하나의 실행의 흐름 !! 
//  process VS thread 
//   - CPU에 의해 처리되어지는 단위 -->  쓰레드!! 
//   - Windows 스케쥴러 
//--------------------------------------------------------------------
#include <stdio.h> 
#include <windows.h> 

// 강제로 CPU를 점유시하기 위해 !! 
void busy() 
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<50000; j++){}
}


// Thread 함수 
DWORD WINAPI ThreadFnc( LPVOID p  )
{
	
	while(1)
	{ 
		puts( (char*)p );
		busy(); 
	}
	return 0; 
}

void main() 
{

	DWORD Threadid = 0; 
	char * str = "생성된 쓰레드 ... ";
	HANDLE hThread = CreateThread( 0 , //보안속성 0 부모의 속성 
											  0 , // stack  (쓰레드 함수의 스택메모리 사이즈 ) 
											  (LPTHREAD_START_ROUTINE)ThreadFnc, 
											  (LPVOID)str  , // LPVOID 파라미터 !! 
											  0, // 초기상태 --> 
											  &Threadid); //생성된 쓰레드의 아이디값!! 	
	
	
	while(1) 
	{
		printf("[ %d ] 메인 쓰레드 !! \n");	
		busy();
	}
}
