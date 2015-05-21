/*************************************************************************/
/**                                                                     **/
/**  Img source                                                         **/
/**       IP(image processing) class.                                   **/
/**       load, write, color access operations..                        **/
/**                                                                     **/
/**       Made by Jaehyubious, Kim at 2000/01/19                        **/
/**                                                                     **/
/*************************************************************************/

#include "stdafx.h"
#include "Img.h"

//////////////////////////////////////////////////////////////////////
/// Constructor
/// Destructor
/// Copy operator
//////////////////////////////////////////////////////////////////////

Img::Img() {
	_BGR = NULL;
	SetSize(0,0);
}
Img::Img( int width, int height ) {
	_BGR = NULL;
	SetSize(width,height);
}
Img::Img( const Img& img ) {
	_BGR = NULL;
	SetSize(img._Width,img._Height);
	memcpy( (void*)_BGR, (void*)img._BGR, _BufWidth*_Height );
}
Img::~Img() {
	if( _BGR != NULL )
		delete[] _BGR;
}
void Img::operator=( Img& img )
{
	SetSize(img._Width,img._Height);
	memcpy( (void*)_BGR, (void*)img._BGR, _BufWidth*_Height );
}

//////////////////////////////////////////////////////////////////////
/// Defulat public member functions
//////////////////////////////////////////////////////////////////////

void Img::SetSize( int width, int height )
{
	if( _Width*_Height == width*height && _BGR != NULL ) {
		_Width = width;
		_Height = height;
		_BufWidth = ( ( width * _BGRByte + 3 ) / 4 ) * 4;
		_BGRByte = 3;
		_BitmapInfoHeader.biWidth = _Width;
		_BitmapInfoHeader.biHeight = _Height;
		return;
	}
	// set _Width, _Height, _BGRByte
	_Width = width;
	_Height = height;
	_BGRByte = 3;
	_BufWidth = ( ( width * _BGRByte + 3 ) / 4 ) * 4;
	// set _BitmapHeader
	_BitmapHeader.bfType = ((WORD)('M'<<8) | 'B' );
	_BitmapHeader.bfSize;
	_BitmapHeader.bfReserved1 = 0;
	_BitmapHeader.bfReserved2 = 0;
	_BitmapHeader.bfOffBits;
	// set _BitmapInfo
	_BitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	_BitmapInfoHeader.biWidth = _Width;
	_BitmapInfoHeader.biHeight = _Height;
	_BitmapInfoHeader.biPlanes = 1;
	_BitmapInfoHeader.biBitCount = 24;
	_BitmapInfoHeader.biCompression = BI_RGB;
	_BitmapInfoHeader.biSizeImage = 0;
	_BitmapInfoHeader.biXPelsPerMeter;
	_BitmapInfoHeader.biYPelsPerMeter;
	_BitmapInfoHeader.biClrUsed = 0;	// because use the maximum color of biBitCount
	_BitmapInfoHeader.biClrImportant = 0;
	// set _BGR
	if( _BGR != NULL ) delete[] _BGR;
	_BGR = new BYTE[_BufWidth*_Height];
}

//////////////////////////////////////////////////////////////////////
/// BMP load & write
///
/// LOAD
///    4-bit color를 읽는데서 가로 크기가 4*x+4+y, 4*x+y의 형태에서
///    서로 상대적으로 이미지가 틀어지던 문제 해결
///    즉, 4*x+4+y의 형태에서 이미지가 틀어지면, 4*x+y에서는 잘 나오고,
///    4*x+y의 형태에서 이미지가 틀어지면, 4*x+4+y에서는 잘 나오던 문제 해결.
///    ================================================================
///    4-bit color를 읽는데서 이미지가 틀어지는 문제점 해결.
///    ================================================================
///    4-bit, 8-bit, 24-bit color 를 읽을 수 있음.
///    팔래트를 읽어서 사용할 수 있음.
///    4의 배수가 아닌 파일을 읽는데 생기는 문제 해결.
/// WRITE
//////////////////////////////////////////////////////////////////////

char Img::GetExtType( const char* FilePath )
{
	char ExtName[256];
	int i;
	for( i=strlen(FilePath); i>=0; i-- ) {
		if( FilePath[i] == '.' ) break;
		else strcpy( ExtName, FilePath+i );
	}
	_strlwr( ExtName );	// convert to lower case
	if( strcmp(ExtName,"bmp") == 0 ) return 1;	// bitmap
	if( strcmp(ExtName,"raw") == 0 ) return 2;	// raw
	return 0;	// unknown type
}

bool Img::LoadImg( const char* FilePath )                        { return LoadImg(FilePath,NULL,-1,-1); }
bool Img::LoadImg( const char* FilePath, const char* ExtName )   { return LoadImg(FilePath,ExtName,-1,-1); }
bool Img::LoadImg( const char* FilePath, int width, int height ) { return LoadImg( FilePath, NULL, width, height ); }
bool Img::LoadImg( const char* FilePath, const char* ExtName, int width, int height )
{
	char ExtType;
	if( ExtName == NULL ) ExtType = GetExtType(FilePath);
	else                  ExtType = GetExtType(ExtName);
	switch( ExtType ) {
	case 0:	// unknown type
		return false;
	case 1:	// bitmap
		return LoadBMP(FilePath);
	case 2:	// raw data
		if( width != -1 && height != -1 ) return LoadRAW(FilePath,width,height);
		else                              return LoadRAW(FilePath);
	default: // unknown type
		return false;
	}
}

bool Img::WriteImg( const char* FilePath ) { return WriteImg(FilePath,NULL); }
bool Img::WriteImg( const char* FilePath, const char* ExtName )
{
	char ExtType;
	if( ExtName == NULL ) ExtType = GetExtType(FilePath);
	else                  ExtType = GetExtType(ExtName);
	switch( ExtType ) {
	case 0: return false;
	case 1: return WriteBMP(FilePath);
	case 2: return WriteRAW(FilePath);
	default: return false;
	}
}

bool Img::LoadBMP( const char* strFilePath )
{
	BITMAPFILEHEADER BitmapHeader;
	BITMAPINFOHEADER BitmapInfoHeader;
	CFile file;

	// open file
	if( !file.Open( strFilePath, CFile::modeRead ) ) {
		// 화일을 읽을 수 없거나, 존재하지 않는 화일 입니다.
		return false;
	}
	// load bitmap file header
	if( file.Read( (void*)&BitmapHeader, sizeof(BITMAPFILEHEADER) ) != sizeof( BITMAPFILEHEADER ) ) {
		// Bitmap Header를 읽을 수 없습니다.
		file.Close();
		return false;
	}
	if( BitmapHeader.bfType != ((WORD)('M'<<8) | 'B' )) {
		// 비트맵 화일이 아닙니다.
		file.Close();
		return false;
	}
	// load bitmap info header
	if( file.Read( (void*)&BitmapInfoHeader, sizeof(BITMAPINFOHEADER) ) != sizeof(BITMAPINFOHEADER) ) {
		// Bitmap Info Header를 읽을 수 없습니다.
		file.Close();
		return false;
	}
	// load BGR datas
	switch( BitmapInfoHeader.biBitCount ) {
	case 4:	// 16 color
		{
			int i, j;
			int MemIndex, FileIndex;
			int Width, Height, BufWidth;
			RGBQUAD* tmpPAL;
			BYTE* tmpBGR;

			Width = BitmapInfoHeader.biWidth;
			Height = BitmapInfoHeader.biHeight;
			BufWidth = ((Width + 7) / 8) * 8;
			// load pallate
			tmpPAL = new RGBQUAD[16];
			file.Read( (void*)tmpPAL, sizeof(RGBQUAD)*16 );
			// load image
			tmpBGR = new BYTE[BufWidth*Height];
			file.Seek( BitmapHeader.bfOffBits, CFile::begin );
			file.Read( tmpBGR, sizeof(BYTE)*BufWidth*Height );
			// reset this class
			SetSize( Width, Height );
			for( j=0; j<_Height; j++ ) {
				for( i=0; i<_Width; i++ ) {
					MemIndex = _BufWidth * j + i * 3;
					FileIndex = BufWidth * j + i;
					if( FileIndex%2 == 0 ) FileIndex = tmpBGR[FileIndex/2] >> 4;
					else FileIndex = tmpBGR[FileIndex/2] & 0x0F;
					_BGR[MemIndex+0] = tmpPAL[FileIndex].rgbBlue;
					_BGR[MemIndex+1] = tmpPAL[FileIndex].rgbGreen;
					_BGR[MemIndex+2] = tmpPAL[FileIndex].rgbRed;
				}
			}
			delete[] tmpBGR;
			delete[] tmpPAL;
		}
		break;
	case 8: // 256 or gray color
		{
			int i, j;
			int MemIndex, FileIndex;
			int Width, Height, BufWidth, BGRByte;
			RGBQUAD* tmpPAL;
			BYTE* tmpBGR;

			Width = BitmapInfoHeader.biWidth;
			Height = BitmapInfoHeader.biHeight;
			BGRByte = 1;
			BufWidth = ((Width * BGRByte + 3 ) / 4 ) * 4;
			// load pallate
			tmpPAL = new RGBQUAD[256];
			file.Read( (void*)tmpPAL, sizeof(RGBQUAD)*256 );
			// load image
			tmpBGR = new BYTE[BufWidth*Height];
			file.Seek( BitmapHeader.bfOffBits, CFile::begin );
			file.Read( tmpBGR, sizeof(BYTE)*BufWidth*Height );
			// reset this class
			SetSize( Width, Height );
			for( j=0; j<Height; j++ ) {
				for( i=0; i<Width; i++ ) {
					MemIndex = _BufWidth * j + i * 3;
					FileIndex = BufWidth * j + i;
					FileIndex = tmpBGR[FileIndex];
					_BGR[MemIndex+0] = tmpPAL[FileIndex].rgbBlue;
					_BGR[MemIndex+1] = tmpPAL[FileIndex].rgbGreen;
					_BGR[MemIndex+2] = tmpPAL[FileIndex].rgbRed;
				}
			}
			delete[] tmpBGR;
			delete[] tmpPAL;
		}
		break;
	case 24: // high color
		{
			// locate to BGR datas
			file.Seek( BitmapHeader.bfOffBits, CFile::begin );
			SetSize( BitmapInfoHeader.biWidth, BitmapInfoHeader.biHeight );
			file.Read(_BGR,_BufWidth*_Height);
		}
		break;
	default:
		{
			file.Close();
			return false;
		}
	}
	// close file
	file.Close();

	return true;
}

bool Img::WriteBMP( const char* strFilePath )
{
	CFile file;

	try
	{
		file.Open( strFilePath , CFile::modeCreate | CFile::modeWrite );
		//먼저 BITMAPFILEHEADER를 파일에 쓴다.
		file.Write( (LPVOID)&_BitmapHeader, sizeof(BITMAPFILEHEADER) );
		//BITMAPINFO를 파일에 쓴다.
		file.Write( (LPVOID)&_BitmapInfoHeader , sizeof(BITMAPINFOHEADER) );

//		// gray image의 팔래트를 기록.
//		for( int i=0; i<256; i++ ) {
//			RGBQUAD pal;
//			pal.rgbBlue = i;
//			pal.rgbGreen = i;
//			pal.rgbRed = i;
//			pal.rgbReserved = 0;
//			file.Write( (LPVOID)&pal, sizeof(RGBQUAD) );
//		}
		_BitmapHeader.bfOffBits = file.GetPosition();
		file.SeekToBegin();
		file.Write( (LPVOID)&_BitmapHeader, sizeof(BITMAPFILEHEADER) );
		file.Seek( _BitmapHeader.bfOffBits, CFile::begin );
		//픽셀정보를 파일에 쓴다.
		file.Write( (LPVOID)_BGR , _Height*_Width*_BGRByte );

		file.Close();
	}
	catch( CFileException e )
	{
		// Bitmap으로 기록하던중에 에러가 발생하였습니다.
		// file.Close();
		return false;
	}

	return true;
}


bool Img::LoadRAW( const char* strFilePath )
{
	return false;
}

bool Img::LoadRAW( const char* strFilePath, int width, int height )
{
	int x, y;
	unsigned char gray;
	FILE* fd;

	fd = fopen( strFilePath, "rb" );
	if( fd == NULL ) return false;
	SetSize( width, height );
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {
			fread( &gray, sizeof(unsigned char), 1, fd );
			SetGray( x, y, gray );
		}
	}
	return true;
}

bool Img::WriteRAW( const char* strFilePath )
{
	return false;
}




