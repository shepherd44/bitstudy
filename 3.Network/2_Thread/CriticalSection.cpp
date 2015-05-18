//------------------------------------------------------------
// Critical Section ( �Ӱ迵��)
//------------------------------------------------------------
// -- > ����ȭ ������Ʈ  
// -->  ������ �ڿ��� ������ �ϳ��� �����忡���� �����Ҽ� �ֵ��� ���� !
// -->  ������ �����ϰ� �����ȿ��� ���� �޸𸮴� �ϳ��� �����常 ���� !
// -->  Kernel ������Ʈ�� �ƴ� !! 
// -->  �ϳ��� ���μ����ȿ����� ����� �����ϴ� !! 
// -->  Kernel Object ���� ���μ������� ��밡�� 
//------------------------------------------------------------ 
//---------------------------------------------------------------
// Multi Thread Program 
//---------------------------------------------------------------

#include <stdio.h> 
#include <windows.h> 


//  Critical Section ��ü ���� !!  
CRITICAL_SECTION cs; 


// busy waiting !! 
void busy() 
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<10000; j++){}
}



// �������� !! 
int g_Array[10]; 
int g_Count = 0; 

// 1) �迭�� ���� �����ϴ� ������ !! 
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
// 2) �迭�� ���� �����ϴ� ������ !! 
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


// 3) ���� ������ �迭�� ���� ��� !! 
void main()
{
	// CriticalSection �ʱ�ȭ !! 
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
	// CriticalSection ���� !!  
	DeleteCriticalSection( &cs );

}


//----------------------------------------------------------------
// 1) Accept Thread
// --> 
//----------------------------------------------------------------