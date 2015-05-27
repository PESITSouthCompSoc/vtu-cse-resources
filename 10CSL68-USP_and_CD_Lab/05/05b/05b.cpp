/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Write a C/C++ program to emulate the unix ln command.

*	API's used:
	1. link(2) - make a new name for a file, increases link count.
		#include <unistd.h>
       int link(const char *oldpath, const char *newpath);
    2. symlink(2) - make a new name for a file
    	#include <unistd.h>
       int symlink(const char *oldpath, const char *newpath);
*/

#include <iostream>
#include <stdio.h> //for perror
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
	if(argc==3)
	{
		if(link(argv[1],argv[2])==-1)
		{
			perror("link");
			return -1;
		}
		cout << "Hard link created between \'" << argv[1] << "\'' and \'" << argv[2] << "\'.\n";
	}
	else if(argc==4 && argv[1][0]=='-' && argv[1][1]=='s')
	{
		if(symlink(argv[2],argv[3])==-1)
		{
			perror("symlink");
			return -1;
		}
		cout << "Symbolic link \'" << argv[3] << "\' --> \'" << argv[2] << "\' created.\n";
	}
	else 
	{
		cout << "\nInvalid arguments.\nUsage:-\n\n";
		cout << argv[0] << " <file1> <file2>\nTo create a (hard) link from file1 to file2.\n\n";
		cout << argv[0] << " -s <file1> <file2>\nTo create a symbolic link from file1 to file2.\n\n";
	}
	return 0;
}