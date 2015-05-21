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

// MFC --> GDI ������Ʈ -->  Class���� !! 
class CPen 
{	
private : 
	HPEN m_pen;
	COLORREF m_color; 
	        int m_width;
	        int m_style; 

public : 
	// set/get 
	void Sethpen(HPEN pen ) { m_pen = pen; }
	HPEN Gethpen() {return  m_pen;  }
	void SetColor(COLORREF color ){ m_color = color; } 
	COLORREF GetColor() {return m_color; }
	void SetWidth(int w) { 
		if( w > 0 && w<=10) 	
			m_width = w; 
	
	}
	int GetWidth ()   {return m_width; } 
	void SetStyle(int style) { m_style = style; } 
	int  GetStyle()			 { return m_style;}
	
	void Create( int style, int w, COLORREF color )
	{	
		m_color = color; 
		m_width = w; 
		m_style = style;
		m_pen   = ::CreatePen( style, w, color); 
	}
	void Delete() 
	{
		::DeleteObject( m_pen); 	
	}
};




class CDC
{		
protected : 
	HDC   m_hdc; 
	HWND m_hwnd; 
public :
	// �׸� �׸��� 
	void Rectangle( int left, int top, int right, int bottom )
	{	
		::Rectangle( m_hdc, left, top, right,bottom); 
	}
	void Ellipse(int left, int top, int right, int bottom)
	{
		::Ellipse( m_hdc, left, top, right,bottom); 
	}
	// ---  �׸��� �Լ���-------------------------------- 
	// GDI������Ʈ  ����  
	// HPEN, HBRUSH,HBITMAP 
	CPen * SelectObject( CPen * pen  )// ?? GDI ������Ʈ ���� !! 
	{
		HPEN old = (HPEN)::SelectObject( m_hdc, pen->Gethpen() );
		CPen p; 
		p.Sethpen(old);
		return &p;
	}

};

class ClientDC : public CDC 
{
public : 
	ClientDC( HWND hwnd ) 
	{
		m_hwnd = hwnd; 
		m_hdc = GetDC( hwnd );
	}
	
	~ClientDC()
	{
		ReleaseDC( m_hwnd, m_hdc); 
	}
}; 

class PaintDC : public CDC 
{
private: 
	PAINTSTRUCT m_ps; 

public :
	PaintDC( HWND hwnd) 
	{
		m_hwnd = hwnd; 
		m_hdc = BeginPaint( hwnd, &m_ps);
	}
	~PaintDC()
	{
		EndPaint( m_hwnd, &m_ps); 
	}

};



// GETDC, BEGINPAINT, GetWindowDC, CreateDC 














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
	//virtual void OnDraw(CDC *);
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
	 void OnPaint(); 
	 void OnDraw(CDC *);
};

BEING_MSG_MAP

	{ WM_LBUTTONDOWN ,  &OnLButtonDown  },
	{ WM_RBUTTONDOWN ,  &OnRButtonDown  },
	{ WM_DESTROY  ,		 &OnDestroy        },
	{ WM_MOUSEMOVE  ,	 &OnMouseMove    },
	{ WM_PAINT  ,			 &OnPaint            },
	
END_MSG_MAP



// ���� ������ ���� !! 
App  theApp; 

void App::OnDraw(CDC * pDC )
{
	CPen pen; 
	pen.Create( PS_SOLID, 5, RGB(255,0,0)); 

	pDC->SelectObject( &pen );
	pDC->Rectangle(100,100,200,200);
	
}
void App::OnPaint()
{	
	PaintDC dc( this->hwnd); 
	OnDraw(&dc);
}
//-----------------------------------------------------------------------------
void App::OnLButtonDown(  )
{
	ClientDC dc(hwnd); 
	OnDraw(&dc); 
}
void App::OnMouseMove()
{

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

