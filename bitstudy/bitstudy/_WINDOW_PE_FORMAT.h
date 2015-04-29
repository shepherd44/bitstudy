#pragma once

#ifdef DEBUG
#include <iostream>
#endif
#include <fstream>
#include <windows.h>

using namespace std;

//File Format ����: EXE, SCR, DLL, OCX, SYS, OBJ
//PE Section Length
//#define PEHEADERLENGTH sizeof(IMAGE_DOS_HEADER);

#ifndef _IMAGE_DOS_STUB

typedef struct _IMAGE_DOS_STUB{
	char* DosStub;
}IMAGE_DOS_STUB, *PIMAGE_DOS_STUB;

#endif

/******************************************************
 * PE Header - e_magic: header ����
 *			 - e_lfanew: offset of nt header, �ش� �ּҺ��� nt��� ����
 * dos stub - �켱 char �迭�� ����, e_lfanew ������. ������� null
 * ntheader - 
 *
 ******************************************************/
typedef class _WINDOW_PE_FORMAT
{
	//���� ���� ����
	const char *AllData;
	//char* AllData;
	//�������� ����
	IMAGE_DOS_HEADER ImageDosHeader;			// PE Header
	IMAGE_DOS_STUB ImageDosStub;				// Dos Stub
	IMAGE_NT_HEADERS ImageNtHeaders;			// NT Header
	IMAGE_SECTION_HEADER *pSectionHeader;		// Section Pointer
	IMAGE_IMPORT_DESCRIPTOR *pImportDescriptor;	//

	//���� ���� ����
	int DosHeaderLength;
	int DosStubLength;
	int DosNtHeaderLength;
	

public:
	//������, �Ҹ���
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
