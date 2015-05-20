//----------------------------------------------------------------
//     virtual 키워드를 대체하는 방법 ! 
//  - virtual 200개 
//  ==> 메시지맵 -->  해당 클래스가 사용해야하는 메시지처리함수의 포인터를 저장 
//  --> 클래스마다 메시지처리함수를 함수포인터 배열의 형태로 저장 ! 
//----------------------------------------------------------------


//-------------------------------------------------------------------
// --> 2단계  API기본 코드의 클래스화 !! 
//-------------------------------------------------------------------
//  - WinMain함수 WinProc함수는 프로그래머가 알지 말아야 한다 !! 
//  - 가상함수( virtual ) 





#include <windows.h>
#define MBox(x) MessageBox( 0, x, L"", MB_OK)
#define BEING_MSG_MAP MESSAGEMAP App::messagemap [] = {
#define END_MSG_MAP 	{ NULL  ,		 NULL  }};
#define DECLARE_MSG_MAP  static MESSAGEMAP messagemap[];	
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CObject  
{
public: //속성 

	WNDCLASS wc;		
	HWND hwnd;
	MSG  msg; 
	HINSTANCE hInstance; 
	
public :  //행동 
	void InitInstance(HINSTANCE); 
	void Run(); 
	int ExitInstance(); 
	
	// virtual 함수 삭제 !! 

};
// 전방 선언 
class App ;


// 멤버 함수 포인터 :  함수 포인터 !! 
//typedef void (FNC*)(); //일반 함수 포인터 
typedef void (App::*AppFnc)();

//------------------------------------------------------
typedef struct msgmap
{
	UINT msg;	 // 윈도우 메시지 
	AppFnc  Fnc; // 멤버함수 포인터 

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



// 전역 포인터 변수 !! 
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
// 윈도우 초기화  등록  !
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

