//---------------------------------------------------------------
// Multi Thread Program 
//---------------------------------------------------------------

#include <stdio.h> 
#include <windows.h> 

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
		g_Array[g_Count] = 1; 
		g_Count++; 
		busy(); 
	}
}
// 2) 배열에 값을 삭제하는 쓰레드 !! 
DWORD WINAPI DeleteThread( LPVOID p) 
{
	while(1) 
	{
		g_Array[--g_Count] = 0 ;
		busy(); 
	}
}


// 3) 메인 쓰레드 배열의 값을 출력 !! 
void main()
{
	HANDLE hTread[2]; 
	
	hTread[0] = CreateThread( 0, 0, InsertThread, 0, 0, 0); 
	hTread[1] = CreateThread( 0, 0, DeleteThread, 0, 0, 0); 
	
	while(1) 
	{	
		printf("[ %d   ] ", g_Count );
		for( int i = 0; i<10; i++) 
		{
			printf("[%d]", g_Array[i]);
		}
		puts("");
		busy(); 
	}	
}
