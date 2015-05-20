//-------------------------------------------------------------------
// ������ C��� ����� API ���α׷� !! 
//-------------------------------------------------------------------
//  - OOP ( ��ü���� )
//   ��ü ???  �Ӽ� + �ൿ 
// -->  ��ü���� �Ӽ��� ���� ������ �ൿ�� �����ϴ� ���������� ���� !!
// -->  class ����  
//-------------------------------------------------------------------
/*  �߻�ȭ + ĸ��ȭ
//-------------------------------------------------------------------
class  Window 
{
	// �Ӽ� ��� :  ��� ����( �ʵ� )
private: 
	int x; 
	int y; 
	int width; 
	int height; 
	HWND hwnd; 
	// �ൿ ��� :  ��� �Լ�( �޼ҵ� ) 
public : 	
	HWND CreateWindow(); 
	MoveWindow(); 
	ShowWinodow(); 
	DestroyWindow();  
	// ~~~Window 
}; */
//-------------------------------------------------------------------
// --> 1�ܰ�  API�⺻ �ڵ��� Ŭ����ȭ !! 
//-------------------------------------------------------------------

#include <windows.h>
#define MBox(x) MessageBox( 0, x, L"", MB_OK)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class App 
{
private: //�Ӽ� 

	WNDCLASS wc;		
	HWND hwnd;
	MSG  msg; 
	HINSTANCE hInstance; 
	
public :  //�ൿ 
	void InitInstance(HINSTANCE); 
	void Run(); 
	int ExitInstance(); 
	// �޽��� ó�� �Լ� �ۼ� 
	//--------------------------------------------------------------------------
	void OnLButtonDown( WORD flag,  POINTS pt ); 
	void OnRButtonDown( WORD flag,  POINTS pt ); 
	void OnDestroy(); 
	//--------------------------------------------------------------------------
};

// ���� App ��ü !! 
App theApp; 

// ������ �ʱ�ȭ  ���  !
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

