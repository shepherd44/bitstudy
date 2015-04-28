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


typedef class _WINDOW_PE_FORMAT
{
	char* AllData;
	IMAGE_DOS_HEADER ImageDosHeader;
	IMAGE_DOS_STUB DosStub;
	IMAGE_NT_HEADERS ImageNtHeaders;
	IMAGE_SECTION_HEADER SectionHeaderText;
	IMAGE_SECTION_HEADER SectionHeaderData;
	IMAGE_SECTION_HEADER SectionHeaderRsrc;

	IMAGE_SECTION_HEADER a;
	
public:
	//생성자, 소멸자
	_WINDOW_PE_FORMAT(void);
	_WINDOW_PE_FORMAT(ifstream&);
	_WINDOW_PE_FORMAT(const char*);
	~_WINDOW_PE_FORMAT(void);
	
	void initData(void);

	//GET, SET
	void SetDosHeader();
	void SetDosStub();
	void SetNtHeaders();
	IMAGE_DOS_HEADER GetDosHeader();
	IMAGE_DOS_STUB GetDosStub();
	IMAGE_NT_HEADERS GetNtHeaders();
}WINDOW_PE_FORMAT, *PWINDOW_PE_FORMAT;
