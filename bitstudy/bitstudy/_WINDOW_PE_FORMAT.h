#pragma once

#ifdef DEBUG
#include <iostream>
#endif
#include <fstream>
#include <windows.h>

using namespace std;

//File Format 종류: EXE, SCR, DLL, OCX, SYS, OBJ
//PE Section Length
//#define PEHEADERLENGTH sizeof(IMAGE_DOS_HEADER);

#ifndef _IMAGE_DOS_STUB

typedef struct _IMAGE_DOS_STUB{
	char* DosStub;
}IMAGE_DOS_STUB, *PIMAGE_DOS_STUB;

#endif

/******************************************************
 * PE Header - e_magic: header 구분
 *			 - e_lfanew: offset of nt header, 해당 주소부터 nt헤더 시작
 * dos stub - 우선 char 배열로 저장, e_lfanew 전까지. 없을경우 null
 * ntheader - 
 *
 ******************************************************/
typedef class _WINDOW_PE_FORMAT
{
	//파일 내용 저장
	const char *AllData;
	//char* AllData;
	//파일형식 저장
	IMAGE_DOS_HEADER ImageDosHeader;			// PE Header
	IMAGE_DOS_STUB ImageDosStub;				// Dos Stub
	IMAGE_NT_HEADERS ImageNtHeaders;			// NT Header
	IMAGE_SECTION_HEADER *pSectionHeader;		// Section Pointer
	IMAGE_IMPORT_DESCRIPTOR *pImportDescriptor;	//

	//형식 길이 저장
	int DosHeaderLength;
	int DosStubLength;
	int DosNtHeaderLength;
	

public:
	//생성자, 소멸자
	_WINDOW_PE_FORMAT(void);
	_WINDOW_PE_FORMAT(ifstream&);
	_WINDOW_PE_FORMAT(const char*);
	~_WINDOW_PE_FORMAT(void);
	
	void initData(void);

	//GET
	void SetDosHeader();
	void SetDosStub();
	void SetNtHeaders();
	//SET
	IMAGE_DOS_HEADER GetDosHeader();
	IMAGE_DOS_STUB GetDosStub();
	IMAGE_NT_HEADERS GetNtHeaders();
	//print
	void printAllData();

}WINDOW_PE_FORMAT, *PWINDOW_PE_FORMAT;
