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

	char *PEbuffer;

	int length = 0;

	if (!infile.bad())
	{
		infile.seekg(0, infile.end);
		length = infile.tellg();
		infile.seekg(0, infile.beg);

		PEbuffer = new char[length];

		infile.read(PEbuffer, length);
		infile.close();
	}

	
	//����
	WINDOW_PE_FORMAT pef(PEbuffer);
	delete PEbuffer;
	//cout<<endl<<length<<endl;
}

#endif