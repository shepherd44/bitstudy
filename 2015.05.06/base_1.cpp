// Windows API(Application Programing Interface)
//     --> SDK(Software Developement Kit)
//--------------------------------------------------
// --> C언어로 작성된 함수들의 집합!!
// --> 8000새의 함수
// --> windows 관련 구조체
// --> 매크로 정의
//--------------------------------------------------
// MSDN
// --> VS의 사용설명서
// --> VS로 개발 가능한 모든것들에 대한 매뉴얼 !!


#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// CALLBACK : 호출이 반대
// --> OS에 의해서 호출되어지는 함수


// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,			// 프로그램 핸들러
                   HINSTANCE hPrevInstance,		// 사용안됨 --> 이전 인스턴스 핸들
                   LPSTR lpCmdLine,				// 명령행 문자열
                   int nCmdShow)				// 화면 모드(최대화, 최소화)
{
	// 윈도우 핸들러(HWND)
	// --> 프로세서마다 각자 자신의 가상주소를 통해 자신의 인스턴스들을 관리하기 때문에
	//	   프로세서 자체의 주소의 주소로는 윈도우를 찾을 수 없기 때문에
	//	   윈도우 핸들을 통해서 관리
	HWND hwnd;
	

	hInst = hInstance;

	// 1) Windows 프로그램에 필요한 요소들!!
	WNDCLASS wnd;	// --> 윈도우를 추상화한 구조체
	wnd.cbClsExtra		= 0;	// 사용안됨 예약
	wnd.cbWndExtra		= 0;	// 사용안됨 예약
	//GetStockObject: 윈도우즈 내장 객체 사용
	//Windows에서는 자주 사용되어지는 몇가지 색상을 기본으로 정의 !
	// 기본으로 정의된 색상 얻기위해 GetStockObject 함수사용
	wnd.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경색
	wnd.hCursor			= (HCURSOR)LoadCursor( hInstance, IDC_ARROW);	// 커서 모양
	wnd.hIcon			= (HICON)LoadIcon(hInstance, IDI_APPLICATION);	//아이콘 모양
	wnd.hInstance		= hInst;	//
	wnd.lpfnWndProc		= WndProc;		// 윈도우 프로시져 --> 이벤트 발생시 호출되는 함수
	wnd.lpszClassName	= L"Hello";		// classname
	wnd.lpszMenuName	= NULL;
	wnd.style			= CS_HREDRAW | CS_VREDRAW;	// window style

	// 2) window 클래스 등록
	RegisterClass(&wnd);

	// 3) window 생성
	hwnd = CreateWindowEx(0,		// 확장 스타일
						  L"Hello",	// 클래스 이름
						  L"Hello",	// 윈도우 이름
						  WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
						  100,		// 윈도우 X좌표
						  100,		// 윈도우 Y좌표
						  100,		// 윈도우 너비
						  100,		// 윈도우 높이
						  NULL,		// 부모 핸들
						  NULL,		// 메뉴
						  hInst,	//instance 핸들
						  0			//param
						  );

	// 4) showwindow
	ShowWindow(hwnd, SW_SHOW);

	// 5) message loop --> 지속적으로 사용자에게 입력(이벤트)를 받아 들이는 부분!!
	//	--> GetMessage: 메세지큐에서 메세지를 꺼내오는 함수
	
	MSG msg;	// 메세지 구조체 --> 발생한 이벤트에 대한 정보를 담는 구조체
	while(GetMessage(&msg, 0, NULL, NULL))
	{
		TranslateMessage(&msg);	// 키보드 번역
		DispatchMessage(&msg);	// WndProc 전달
	}




	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, //메시지가 발생한 윈도우 핸들
						 UINT msg,	// 메시지
						 WPARAM wParam,	// 부가정보
						 LPARAM lParam	// 부가정보
						 )
{
	//필요한 기능 구현 !!
	switch(msg)
	{
	case WM_MOUSEMOVE:
		{
			//마우스 관련 메시지
			// wParam : key flag : ctr : 0100 shift : 0010
			// lParam : 좌표 x, y
			//		--> 상위, 하위 2byte를 좌표로 사용

			TCHAR buf[256];
			// lParam에서 좌표 구하기
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			wsprintf(buf, L"x : %d, y : %d", x, y);	// 배열에 형식화된 문자열 입력
			SetWindowText(hwnd, buf);	//윈도우 텍스트 변경
		}
	case WM_LBUTTONDOWN:
		return 0;
	case WM_CHAR:		
		return 0;
	case WM_MOUSEHOVER:	
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}


	// DefWindowProc --> 윈도우가 가지는 기본 이벤트를 처리하는 함수
	return DefWindowProc(hwnd, msg, wParam, lParam);
}