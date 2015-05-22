/*************************************************************************/
/**                                                                     **/
/** Img source                                                          **/
/**      IP(image processing) class.                                    **/
/**      load, write, color access operations..                         **/
/**                                                                     **/
/**      Made by Jaehyubious at 2000/01/19                              **/
/**                                                                     **/
/*************************************************************************/
/**                                                                     **/
/** [2000/09/19]                                                        **/
/**                                                                     **/
/*************************************************************************/

#ifndef _Img_
#define _Img_

class Img
{
public:
	Img();
	Img( int width, int height );
	Img( const Img& img );
	~Img();
public:
	void operator=( Img& img );
	void SetSize( int width, int height );
	
	inline void InitBuf();
	inline int GetWidth();
	inline int GetHeight();

	inline void Draw( CDC* pDC );
	inline void Draw( CDC* pDC, int x, int y );
	inline void Draw( CDC* pDC, int x, int y, int width, int height );

	inline void GetColor( int x, int y, BYTE* R, BYTE* G, BYTE* B );
	inline void GetColor( int x, int y, COLORREF* color );
	inline COLORREF GetColor( int x, int y );
	inline void SetColor( int x, int y, BYTE R, BYTE G, BYTE B );
	inline void SetColor( int x, int y, COLORREF color );
	inline void GetGray( int x, int y, BYTE* Gray );
	inline BYTE GetGray( int x, int y );
	inline void SetGray( int x, int y, BYTE Gray );
	// 회전
	void LeftR();
	void RightR();
	// 색죽이기
	void SetRed(int r);
	void SetGreen(int g);
	void SetBlue(int b);
	void DownRed(int r=0);
	void DownGreen(int g=0);
	void DownBlue(int b=0);
	// RGB UP
	void UpRed(int r=255);
	void UpGreen(int g=255);
	void UpBlue(int b=255);
	// 
	void AddColor(int r=0, int g=0, int b=0);

	inline BYTE* GetBGRBuf();
public:
	char GetExtType( const char* FilePath );	// unknown(0), bitmap(1)
	bool LoadImg( const char* FilePath );
	bool LoadImg( const char* FilePath, const char* ExtType );
	bool LoadImg( const char* FilePath, int width, int height );
	bool LoadImg( const char* FilePath, const char* ExtName, int width, int height );
	bool WriteImg( const char* FilePath );
	bool WriteImg( const char* FilePath, const char* ExtName );
	bool LoadBMP( const char* strFilePath );
	bool WriteBMP( const char* strFilePath );
	bool LoadRAW( const char* strFilePath );
	bool LoadRAW( const char* strFilePath, int width, int height );
	bool WriteRAW( const char* strFilePath );
public:
	// member variables
	int _Width;			// width
	int _Height;		// height
	int _BGRByte;		// bgr byte
	int _BufWidth;		// width of memory buffer
	LPBYTE _BGR;		// buffer of RGB data
	BITMAPFILEHEADER _BitmapHeader;		// bitmap header
	BITMAPINFOHEADER _BitmapInfoHeader;	// bitmap information header
};

inline void Img::InitBuf()  { if( _Width*_Height == 0 ) return; memset( _BGR, 0, sizeof(BYTE)*_BufWidth*_Height ); }
inline int Img::GetWidth()  { return _Width; }
inline int Img::GetHeight() { return _Height; }

inline void Img::Draw( CDC* pDC )                                      { Draw( pDC, 0, 0, _Width, _Height ); }
inline void Img::Draw( CDC* pDC, int x, int y )                        { Draw( pDC, x, y, _Width, _Height ); }
inline void Img::Draw( CDC* pDC, int x, int y, int width, int height ) { if( _BGR == NULL ) return; ::StretchDIBits( pDC->GetSafeHdc(), x, y, width, height, 0, 0, _Width, _Height, _BGR, (LPBITMAPINFO)&_BitmapInfoHeader, DIB_RGB_COLORS, SRCCOPY ); }

inline void Img::GetColor( int x, int y, BYTE* R, BYTE* G, BYTE* B ) { int ref; y = _Height-y-1; ref = _BufWidth * y + x * 3; *B = _BGR[ref+0]; *G = _BGR[ref+1]; *R = _BGR[ref+2]; }
inline void Img::GetColor( int x, int y, COLORREF* color )           { int ref; y = _Height-y-1; ref = _BufWidth * y + x * 3; (*color) = RGB( _BGR[ref+2], _BGR[ref+1], _BGR[ref+0] ); }
inline COLORREF Img::GetColor( int x, int y )                        { COLORREF color; GetColor( x, y, &color ); return color; }
inline void Img::SetColor( int x, int y, BYTE R, BYTE G, BYTE B )    { int ref; y = _Height-y-1; ref = _BufWidth * y + x * 3; _BGR[ref+0] = B; _BGR[ref+1] = G; _BGR[ref+2] = R; }
inline void Img::SetColor( int x, int y, COLORREF color )            { SetColor( x, y, GetRValue(color), GetGValue(color), GetBValue(color) ); }
inline void Img::GetGray( int x, int y, BYTE* gray )                 { BYTE B, G, R; GetColor( x, y, &R, &G, &B ); *gray = (BYTE)(((int)R+(int)G+(int)B)/ 3); }
inline void Img::SetGray( int x, int y, BYTE gray )                  { SetColor( x, y, gray, gray, gray ); }
inline BYTE Img::GetGray( int x, int y )                             { BYTE gray; GetGray( x, y, &gray ); return gray; }

inline BYTE* Img::GetBGRBuf() { return _BGR; }


#endif