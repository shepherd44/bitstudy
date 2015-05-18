//------------------------------------------------------------
// Critical Section ( 임계영역)
//------------------------------------------------------------
// -- > 동기화 오브젝트  
// -->  공유된 자원에 접근을 하나의 쓰레드에서만 접근할수 있도록 설정 !
// -->  영역을 설정하고 영역안에서 공유 메모리는 하나의 쓰레드만 접근 !
// -->  Kernel 오브젝트는 아님 !! 
// -->  하나의 프로세스안에서만 사용이 가능하다 !! 
// -->  Kernel Object 여러 프로세스에서 사용가능 
//------------------------------------------------------------ 
//---------------------------------------------------------------
// Multi Thread Program 
//---------------------------------------------------------------

#include <stdio.h> 
#include <windows.h> 


//  Critical Section 객체 선언 !!  
CRITICAL_SECTION cs; 


// busy waiting !! 
void busy() 
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<10000; j++){}
}



// 전역변수 !! 
int g_Array[10]; 
int g_Count = 0; 

// 1) 배열에 값을 삽입하는 쓰레드 !! 
DWORD WINAPI InsertThread( LPVOID p) 
{
	while(1) 
	{
		EnterCriticalSection( &cs );
		g_Array[g_Count] = 1; 
		g_Count++; 
		LeaveCriticalSection( &cs ); 
		busy(); 
	}
}
// 2) 배열에 값을 삭제하는 쓰레드 !! 
DWORD WINAPI DeleteThread( LPVOID p) 
{
	while(1) 
	{
		EnterCriticalSection( &cs );
		g_Array[--g_Count]  = 0 ;
		LeaveCriticalSection( &cs ); 
		busy(); 
	}
}


// 3) 메인 쓰레드 배열의 값을 출력 !! 
void main()
{
	// CriticalSection 초기화 !! 
	InitializeCriticalSection( &cs ); 
	

	HANDLE hTread[2]; 
		
	hTread[0] = CreateThread( 0, 0, InsertThread, 0, 0, 0); 
	hTread[1] = CreateThread( 0, 0, DeleteThread, 0, 0, 0); 
	
	while(1) 
	{	
		EnterCriticalSection( &cs );
		printf("[ %d   ] ", g_Count );
		for( int i = 0; i<10; i++) 
		{
			printf("[%d]", g_Array[i]);
		}
		LeaveCriticalSection( &cs ); 
		puts("");
		busy(); 
	}
	// CriticalSection 해제 !!  
	DeleteCriticalSection( &cs );

}


//----------------------------------------------------------------
// 1) Accept Thread
// --> 
//----------------------------------------------------------------