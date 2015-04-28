#if 1
#include <iostream>
#include <fstream>
#include "_WINDOW_PE_FORMAT.h"

#define MAX_LENGTH 50000
#define MAX_FILENAME 100

#define DEBUG 1

using namespace std;


void main()
{
	char filename[MAX_FILENAME];


	cout<<"input PE file name: "<<endl;
	//cin>>filename;

	//ifstream infile(filename);
	ifstream infile("bitstudy.exe");

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

	//¼±¾ð
	WINDOW_PE_FORMAT pef(PEbuffer);

	cout<<endl<<length<<endl;

	for(int i=0 ;i<500; i++)
	{
		printf("%c", PEbuffer[i]);
	}
}

#endif