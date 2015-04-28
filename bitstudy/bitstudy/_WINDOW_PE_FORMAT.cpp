#include "_WINDOW_PE_FORMAT.h"

_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(void)
{
	AllData = NULL;
}


_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(ifstream &filestream)
{
	
}

_WINDOW_PE_FORMAT::_WINDOW_PE_FORMAT(const char* pcc)
{
	if((pcc[0] =='M' && pcc[1] =='Z'))
	{
		SetDosHeader();
		int length = ImageDosHeader.e_cparhdr;
		AllData = new char[sizeof(IMAGE_DOS_HEADER)];
		memcpy(AllData, pcc, length);
		for(int i=0 ;i<length; i++)
		{	
			if(i%16 == 1)
			printf("%c", AllData[i]);

		}
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
	
}
void _WINDOW_PE_FORMAT::SetDosHeader()
{
	int length = sizeof(IMAGE_DOS_HEADER);
	memcpy(&ImageDosHeader, AllData, length);
}
void _WINDOW_PE_FORMAT::SetDosStub()
{

}
void _WINDOW_PE_FORMAT::SetNtHeaders()
{

}
IMAGE_DOS_HEADER _WINDOW_PE_FORMAT::GetDosHeader()
{
	return this->ImageDosHeader;
}

IMAGE_DOS_STUB _WINDOW_PE_FORMAT::GetDosStub()
{
	return this->DosStub;
}
IMAGE_NT_HEADERS _WINDOW_PE_FORMAT::GetNtHeaders()
{
	return this->ImageNtHeaders;
}