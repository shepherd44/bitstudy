#include "_WINDOW_PE_FORMAT.h"

#include <iostream>
_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(void)
{
	AllData = NULL;
}


_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(ifstream &filestream)
{
	
}

_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(const char* pcc)
{
	//magic 넘버 
	if((pcc[0] =='M' && pcc[1] =='Z'))
	{
		//우선 PEheader 받아서 크기검사 후 파일을 AllData에 복사
		int length = 1024;
		//AllData = new BYTE[sizeof(IMAGE_DOS_HEADER)];
		//memcpy(AllData, pcc, length);

		AllData = pcc;
		printAllData();

		//PE Header set
		SetDosHeader();

#ifdef _DEBUG
		printf("\nlength: %d\n", length);
#endif

		// 데이터 초기화
		// 
		initData();
	}
	else 
	{	
	}
}

_WINDOW_PE_FORMAT::~_WINDOW_PE_FORMAT(void)
{
	if(AllData != NULL)
		delete AllData;
}

void _WINDOW_PE_FORMAT::initData(void)
{
	SetDosStub();
	SetNtHeaders();
	
	//디버그
	printf("pe header: %d\n", sizeof(ImageDosHeader));
	printf("pe stub: %d\n", sizeof(ImageDosStub));
	printf("nt header: %d\n", sizeof(ImageNtHeaders));
	printf("-sig: %d\n", sizeof(ImageNtHeaders.Signature));
	printf("-file : %d\n", sizeof(ImageNtHeaders.FileHeader));
	printf("-optional: %d\n", sizeof(ImageNtHeaders.OptionalHeader));
	//section 의 위치;
	printf("sizeof pe header: %d\n", ImageNtHeaders.OptionalHeader.SizeOfHeaders);
	//section 헤더의 위치
	printf("sizeof image: %d\n", ImageNtHeaders.OptionalHeader.SizeOfImage);
}
void _WINDOW_PE_FORMAT::SetDosHeader()
{
	int length = sizeof(IMAGE_DOS_HEADER);
	memcpy(&ImageDosHeader, AllData, length);
}
void _WINDOW_PE_FORMAT::SetDosStub()
{
	int length = ImageDosHeader.e_lfanew - sizeof(ImageDosHeader);
	memcpy(&ImageDosStub, AllData + (int)ImageDosHeader.e_lfanew, length);
}
void _WINDOW_PE_FORMAT::SetNtHeaders()
{
	int start = ImageDosHeader.e_lfanew - 1;
	int length = sizeof(ImageNtHeaders);
	printf("%d, %x",length, length);
	memcpy(&ImageNtHeaders, AllData + start, length);
}
IMAGE_DOS_HEADER _WINDOW_PE_FORMAT::GetDosHeader()
{
	return this->ImageDosHeader;
}

IMAGE_DOS_STUB _WINDOW_PE_FORMAT::GetDosStub()
{
	return this->ImageDosStub;
}
IMAGE_NT_HEADERS _WINDOW_PE_FORMAT::GetNtHeaders()
{
	return this->ImageNtHeaders;
}

void _WINDOW_PE_FORMAT::printAllData()
{
	using namespace std;
	int length = sizeof(ImageDosHeader) + sizeof(ImageDosStub) + sizeof(ImageNtHeaders);
	cout<<"------------------------------------------------"<<endl;
	printf("%8X : ", 0);
	for(int i=0;i<length;i++)
	{
		printf("%2.2X ", (BYTE) AllData[i]);
		if(i%8 == 7)
		{
			for(int j=i-7;j<i; j++)
			{
				printf("%c",AllData[j]);
			}
			cout<<endl;
			printf("%8X : ", i+1);
		}
	}
}