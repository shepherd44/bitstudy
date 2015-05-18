// Windows API(Application Programing Interface)
//     --> SDK(Software Developement Kit)
//--------------------------------------------------
// --> C���� �ۼ��� �Լ����� ����!!
// --> 8000���� �Լ�
// --> windows ���� ����ü
// --> ��ũ�� ����
//--------------------------------------------------
// MSDN
// --> VS�� ��뼳��
// --> VS�� ���� ������ ���͵鿡 ���� �Ŵ��� !!


#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// CALLBACK : ȣ���� �ݴ�
// --> OS�� ���ؼ� ȣ��Ǿ����� �Լ�


// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,			// ���α׷� �ڵ鷯
                   HINSTANCE hPrevInstance,		// ���ȵ� --> ���� �ν��Ͻ� �ڵ�
                   LPSTR lpCmdLine,				// ����� ���ڿ�
                   int nCmdShow)				// ȭ�� ���(�ִ�ȭ, �ּ�ȭ)
{
	// ������ �ڵ鷯(HWND)
	// --> ���μ������� ���� �ڽ��� �����ּҸ� ���� �ڽ��� �ν��Ͻ����� �����ϱ� ������
	//	   ���μ��� ��ü�� �ּ��� �ּҷδ� �����츦 ã�� �� ���� ������
	//	   ������ �ڵ��� ���ؼ� ����
	HWND hwnd;
	

	hInst = hInstance;

	// 1) Windows ���α׷��� �ʿ��� ��ҵ�!!
	WNDCLASS wnd;	// --> �����츦 �߻�ȭ�� ����ü
	wnd.cbClsExtra		= 0;	// ���ȵ� ����
	wnd.cbWndExtra		= 0;	// ���ȵ� ����
	//GetStockObject: �������� ���� ��ü ���
	//Windows������ ���� ���Ǿ����� ��� ������ �⺻���� ���� !
	// �⺻���� ���ǵ� ���� ������� GetStockObject �Լ����
	wnd.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// ����
	wnd.hCursor			= (HCURSOR)LoadCursor( hInstance, IDC_ARROW);	// Ŀ�� ���
	wnd.hIcon			= (HICON)LoadIcon(hInstance, IDI_APPLICATION);	//������ ���
	wnd.hInstance		= hInst;	//
	wnd.lpfnWndProc		= WndProc;		// ������ ���ν��� --> �̺�Ʈ �߻��� ȣ��Ǵ� �Լ�
	wnd.lpszClassName	= L"Hello";		// classname
	wnd.lpszMenuName	= NULL;
	wnd.style			= CS_HREDRAW | CS_VREDRAW;	// window style

	// 2) window Ŭ���� ���
	RegisterClass(&wnd);

	// 3) window ����
	hwnd = CreateWindowEx(0,		// Ȯ�� ��Ÿ��
						  L"Hello",	// Ŭ���� �̸�
						  L"Hello",	// ������ �̸�
						  WS_OVERLAPPEDWINDOW,	// ������ ��Ÿ��
						  100,		// ������ X��ǥ
						  100,		// ������ Y��ǥ
						  100,		// ������ �ʺ�
						  100,		// ������ ����
						  NULL,		// �θ� �ڵ�
						  NULL,		// �޴�
						  hInst,	//instance �ڵ�
						  0			//param
						  );

	// 4) showwindow
	ShowWindow(hwnd, SW_SHOW);

	// 5) message loop --> ���������� ����ڿ��� �Է�(�̺�Ʈ)�� �޾� ���̴� �κ�!!
	//	--> GetMessage: �޼���ť���� �޼����� �������� �Լ�
	
	MSG msg;	// �޼��� ����ü --> �߻��� �̺�Ʈ�� ���� ������ ��� ����ü
	while(GetMessage(&msg, 0, NULL, NULL))
	{
		TranslateMessage(&msg);	// Ű���� ����
		DispatchMessage(&msg);	// WndProc ����
	}




	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, //�޽����� �߻��� ������ �ڵ�
						 UINT msg,	// �޽���
						 WPARAM wParam,	// �ΰ�����
						 LPARAM lParam	// �ΰ�����
						 )
{
	//�ʿ��� ��� ���� !!
	switch(msg)
	{
	case WM_MOUSEMOVE:
		{
			//���콺 ���� �޽���
			// wParam : key flag : ctr : 0100 shift : 0010
			// lParam : ��ǥ x, y
			//		--> ����, ���� 2byte�� ��ǥ�� ���

			TCHAR buf[256];
			// lParam���� ��ǥ ���ϱ�
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			wsprintf(buf, L"x : %d, y : %d", x, y);	// �迭�� ����ȭ�� ���ڿ� �Է�
			SetWindowText(hwnd, buf);	//������ �ؽ�Ʈ ����
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


	// DefWindowProc --> �����찡 ������ �⺻ �̺�Ʈ�� ó���ϴ� �Լ�
	return DefWindowProc(hwnd, msg, wParam, lParam);
}