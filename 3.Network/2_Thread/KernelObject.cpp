//--------------------------------------------------------------------
// -  Ŀ�ο�����Ʈ�� Ȱ���� network ���α׷��� 
//--------------------------------------------------------------------
// - Kernel Object  --> Ŀ�ο��� �����ϰ� Ŀ�ο� ����� ��ü !! 
	
//  OS�� ���� Kernel ������ ����ǰ�  ���Ǿ����� ��ü !! 
//  ---> Process, Thread, ComplitePort, pipe, Event, semaphore, mutex 
//  --->  
/*
user       	[     ]
------------------------
Kernel	       [     ]
*/  

//--------------------------------------------------------------------
//  thead :  ���������� ����Ǵ� �ϳ��� ������ �帧 !! 
//  process VS thread 
//   - CPU�� ���� ó���Ǿ����� ���� -->  ������!! 
//   - Windows �����췯 
//--------------------------------------------------------------------
#include <stdio.h> 
#include <windows.h> 

// ������ CPU�� �������ϱ� ���� !! 
void busy() 
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<50000; j++){}
}


// Thread �Լ� 
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
	char * str = "������ ������ ... ";
	HANDLE hThread = CreateThread( 0 , //���ȼӼ� 0 �θ��� �Ӽ� 
											  0 , // stack  (������ �Լ��� ���ø޸� ������ ) 
											  (LPTHREAD_START_ROUTINE)ThreadFnc, 
											  (LPVOID)str  , // LPVOID �Ķ���� !! 
											  0, // �ʱ���� --> 
											  &Threadid); //������ �������� ���̵�!! 	
	
	
	while(1) 
	{
		printf("[ %d ] ���� ������ !! \n");	
		busy();
	}
}
