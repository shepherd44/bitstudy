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



// �������� !! 
int g_Array[10]; 
int g_Count = 0; 

// 1) �迭�� ���� �����ϴ� ������ !! 
DWORD WINAPI InsertThread( LPVOID p) 
{
	while(1) 
	{
		g_Array[g_Count] = 1; 
		g_Count++; 
		busy(); 
	}
}
// 2) �迭�� ���� �����ϴ� ������ !! 
DWORD WINAPI DeleteThread( LPVOID p) 
{
	while(1) 
	{
		g_Array[--g_Count] = 0 ;
		busy(); 
	}
}


// 3) ���� ������ �迭�� ���� ��� !! 
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
