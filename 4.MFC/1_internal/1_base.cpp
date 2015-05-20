//-------------------------------------------------------------------
// 순수한 C언어 기반의 API 프로그램 !! 
//-------------------------------------------------------------------
//  - OOP ( 객체지향 )
//   객체 ???  속성 + 행동 
// -->  객체만의 속성을 갖고 고유의 행동을 수행하는 유형무형의 모든것 !!
// -->  class 문법  
//-------------------------------------------------------------------
/*  추상화 + 캡슐화
//-------------------------------------------------------------------
class  Window 
{
	// 속성 멤버 :  멤버 변수( 필드 )
private: 
	int x; 
	int y; 
	int width; 
	int height; 
	HWND hwnd; 
	// 행동 멤버 :  멤버 함수( 메소드 ) 
public : 	
	HWND CreateWindow(); 
	MoveWindow(); 
	ShowWinodow(); 
	DestroyWindow();  
	// ~~~Window 
}; */
//-------------------------------------------------------------------
// --> 1단계  API기본 코드의 클래스화 !! 
//-------------------------------------------------------------------

#include <windows.h>
#define MBox(x) MessageBox( 0, x, L"", MB_OK)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class App 
{
private: //속성 

	WNDCLASS wc;		
	HWND hwnd;
	MSG  msg; 
	HINSTANCE hInstance; 
	
public :  //행동 
	void InitInstance(HINSTANCE); 
	void Run(); 
	int ExitInstance(); 
	// 메시지 처리 함수 작성 
	//--------------------------------------------------------------------------
	void OnLButtonDown( WORD flag,  POINTS pt ); 
	void OnRButtonDown( WORD flag,  POINTS pt ); 
	void OnDestroy(); 
	//--------------------------------------------------------------------------
};

// 전역 App 객체 !! 
App theApp; 

// 윈도우 초기화  등록  !
void App::InitInstance(HINSTANCE hInstance ) 
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

void App::Run() 
{
	while( GetMessage( &msg, 0, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

int App::ExitInstance() 
{
   return 0;
}

//-----------------------------------------------------------------------------
void App::OnLButtonDown( WORD flag,  POINTS pt )
{
	HDC hdc = GetDC(hwnd);
	
	Rectangle(hdc, 100,100,100,100); 

	ReleaseDC(hwnd, hdc);   
}
void App::OnRButtonDown( WORD flag,  POINTS pt )
{

}
void App::OnDestroy()
{
	PostQuitMessage(0);
}
//-----------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		theApp.OnLButtonDown( wParam, MAKEPOINTS(lParam)); 
		return 0;
	case WM_RBUTTONDOWN:
		theApp.OnRButtonDown( wParam, MAKEPOINTS(lParam)); 
		return 0;
	case WM_DESTROY:
		theApp.OnDestroy(); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE,
				   PSTR lpCmdLine, int nShowCmd)
{
	theApp.InitInstance( hInstance); 
	theApp.Run(); 
	return theApp.ExitInstance();
	
}

