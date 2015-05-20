//----------------------------------------------------------------
//     virtual Ű���带 ��ü�ϴ� ��� ! 
//  - virtual 200�� 
//  ==> �޽����� -->  �ش� Ŭ������ ����ؾ��ϴ� �޽���ó���Լ��� �����͸� ���� 
//  --> Ŭ�������� �޽���ó���Լ��� �Լ������� �迭�� ���·� ���� ! 
//----------------------------------------------------------------


//-------------------------------------------------------------------
// --> 2�ܰ�  API�⺻ �ڵ��� Ŭ����ȭ !! 
//-------------------------------------------------------------------
//  - WinMain�Լ� WinProc�Լ��� ���α׷��Ӱ� ���� ���ƾ� �Ѵ� !! 
//  - �����Լ�( virtual ) 





#include <windows.h>
#define MBox(x) MessageBox( 0, x, L"", MB_OK)
#define BEING_MSG_MAP MESSAGEMAP App::messagemap [] = {
#define END_MSG_MAP 	{ NULL  ,		 NULL  }};
#define DECLARE_MSG_MAP  static MESSAGEMAP messagemap[];	
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CObject  
{
public: //�Ӽ� 

	WNDCLASS wc;		
	HWND hwnd;
	MSG  msg; 
	HINSTANCE hInstance; 
	
public :  //�ൿ 
	void InitInstance(HINSTANCE); 
	void Run(); 
	int ExitInstance(); 
	
	// virtual �Լ� ���� !! 

};
// ���� ���� 
class App ;


// ��� �Լ� ������ :  �Լ� ������ !! 
//typedef void (FNC*)(); //�Ϲ� �Լ� ������ 
typedef void (App::*AppFnc)();

//------------------------------------------------------
typedef struct msgmap
{
	UINT msg;	 // ������ �޽��� 
	AppFnc  Fnc; // ����Լ� ������ 

}MESSAGEMAP ;
//------------------------------------------------------

class App : public CObject 
{	
public : 	
	 DECLARE_MSG_MAP

	 void OnLButtonDown( );
	 void OnRButtonDown(  );
	 void OnDestroy(); 
	 void OnMouseMove(); 
};

BEING_MSG_MAP

	{ WM_LBUTTONDOWN ,  &OnLButtonDown  },
	{ WM_RBUTTONDOWN ,  &OnRButtonDown  },
	{ WM_DESTROY  ,		 &OnDestroy        },
	{ WM_MOUSEMOVE  ,		 &OnMouseMove},

END_MSG_MAP



// ���� ������ ���� !! 
App  theApp; 

void App::OnMouseMove()
{

}
//-----------------------------------------------------------------------------
void App::OnLButtonDown(  )
{
	SetWindowText( hwnd , L"XXXXX");
}
void App::OnRButtonDown( )
{

}
void App::OnDestroy()
{
	PostQuitMessage(0);
}

//-----------------------------------------------------------------------------
// ������ �ʱ�ȭ  ���  !
void CObject::InitInstance(HINSTANCE hInstance ) 
{
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	
	wc.hCursor			= LoadCursor( 0, IDC_ARROW );
	wc.hIcon			= LoadIcon( 0, IDI_APPLICATION);
	wc.hInstance		= hInstance; 
	wc.lpfnWndProc		= WndProc;
	wc.lpszClassName	= L"First";
	wc.lpszMenuName		= 0;
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	this->hInstance = hInstance; 

	RegisterClass( &wc);
	
	hwnd = CreateWindowEx( 0, L"first",	L"Hello", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		0, 0, 
		hInstance,
		0);  
	
	ShowWindow( hwnd, SW_SHOW );
	UpdateWindow( hwnd );

}

void CObject::Run() 
{
	while( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

int CObject::ExitInstance() 
{
   return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	

	int i = 0; 
	AppFnc MsgProc; 	
	while( App::messagemap[i].msg != NULL) 
	{
		if(  App::messagemap[i].msg == msg) 
		{
			MsgProc = App::messagemap[i].Fnc;
			(theApp.*MsgProc)() ; 
			break; 
		}

		i++; 
	}

	return DefWindowProc( hwnd, msg, wParam, lParam);
}



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE,
				   PSTR lpCmdLine, int nShowCmd)
{

	//theApp =  new App(); 

	theApp.InitInstance( hInstance); 
	theApp.Run(); 
	return theApp.ExitInstance();
	
}

