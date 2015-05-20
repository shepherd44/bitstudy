
//-------------------------------------------------------------------
// --> 2단계  API기본 코드의 클래스화 !! 
//-------------------------------------------------------------------
//  - WinMain함수 WinProc함수는 프로그래머가 알지 말아야 한다 !! 
//  - 가상함수( virtual ) 





#include <windows.h>
#define MBox(x) MessageBox( 0, x, L"", MB_OK)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CObject  
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
	virtual void OnLButtonDown( WORD flag,  POINTS pt )  = 0; 
	virtual void OnRButtonDown( WORD flag,  POINTS pt )  = 0;
	virtual void OnDestroy() = 0; 
	//--------------------------------------------------------------------------
};

class App : public CObject 
{
		
	 void OnLButtonDown( WORD flag,  POINTS pt );
	 void OnRButtonDown( WORD flag,  POINTS pt );
	 void OnDestroy(); 
};

// 전역 포인터 변수 !! 
CObject * theApp; 


//-----------------------------------------------------------------------------
void App::OnLButtonDown( WORD flag,  POINTS pt )
{

}
void App::OnRButtonDown( WORD flag,  POINTS pt )
{

}
void App::OnDestroy()
{

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
	switch( msg )
	{
	case WM_LBUTTONDOWN:
		theApp->OnLButtonDown( wParam, MAKEPOINTS(lParam)); 
		return 0;
	case WM_RBUTTONDOWN:
		theApp->OnRButtonDown( wParam, MAKEPOINTS(lParam)); 
		return 0;
	case WM_DESTROY:
		theApp->OnDestroy(); 
		return 0;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam);
}



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE,
				   PSTR lpCmdLine, int nShowCmd)
{

	theApp =  new App(); 

	theApp->InitInstance( hInstance); 
	theApp->Run(); 
	return theApp->ExitInstance();
	
}

// 부모의 가상함수를 통해 WinMain함수와 Winproc를 숨긴다 !! 

//  상속 구조를 통해 자식에서는 메시지 처리 집중 !! 

// MFC는 virtual을 사용하지 않는다 !! 

// 200개 