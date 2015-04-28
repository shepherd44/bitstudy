#if 0
#include <iostream>
#include <fstream>

#define MAX_LENGTH 50000
#define MAX_FILENAME 100

using namespace std;
/*
ENUM PEtype = {
	.text, .bss 
};
*/
class CPEFormat{
	string m_DOSheader;
	string m_DOSstup;
	string m_NTheader;
	string m_textbss;
	string m_text;
	string m_rdata;
	string m_data;
	string m_idata;
	string m_rsrc;
	string m_reloc;

}PEHeader, *PPEHeader;
/*
class CFileManager{

}FileManager;
*/

void main()
{
	char filename[MAX_FILENAME];

	cout<<"input filename: "<<endl;
	cin>>filename;

	ifstream infile(filename);
	
	char PEbuffer[MAX_LENGTH];
	int length = 0;
	if (!infile.bad())
	{
		infile.seekg(0, infile.end);
		length = infile.tellg();
		infile.seekg(0, infile.beg);

		infile.read(PEbuffer, length);
		infile.close();
	}

	cout<<length<<endl;
	for(int i=0 ;(i < length) && (i<MAX_LENGTH); i++)
	{
		printf("%c", PEbuffer[i]);
		if(PEbuffer[i] == '\eof')
			break;

	}
}

#endif