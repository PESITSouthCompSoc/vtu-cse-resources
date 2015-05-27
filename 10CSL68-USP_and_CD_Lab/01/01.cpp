/*
	* Documented by:
		Aditi Mohanty
		github.com/rheaditi

	* Problem Statement:
		To Write a C/C++ POSIX compliant program to check the following limits:
			(i) No. of clock ticks
			(ii) Max. no. of child processes
			(iii) Max. path length
			(iv) Max. no. of characters in a file name
			(v) Max. no. of open files/ process

	* Description:
		Through POSIX, an application can query certain limits/availability of certain options or functionality, either at:
			1. Compile-time : through MACROS defined in <unistd.h> and <limits.h>
			2. Run-time : through use of the library functions sysconf(3) and pathconf(3)

	* Use the following:
		1. sysconf - get configuration information at run time
				#include <unistd.h>
		       long sysconf(int name);
		2. fpathconf, pathconf - get configuration values for files
				#include <unistd.h>
		       long fpathconf(int fd, int name);
		       long pathconf(char *path, int name);
*/

//These ensure we expose POSIX1.b limits
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <iostream>
#include <stdio.h> //required for perror()
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
	int returnValue;

	cout << "Run-time limits (POSIX1.b):\n\n";
	if( (returnValue = sysconf(_SC_CLK_TCK)) == -1 )
	{
		perror("sysconf");
		cout << "_SC_CLK_TCK is not defined.\n";
	}
	else
		cout << "No. of clock ticks: " << returnValue << endl;

	if( (returnValue = sysconf(_SC_CHILD_MAX)) == -1 )
	{
		perror("sysconf");
		cout << "_SC_CHILD_MAX is not defined.\n";
	}
	else
		cout << "Maximum no. of simultaneous processes per user ID: " << returnValue << endl;

	if( (returnValue = sysconf(_SC_OPEN_MAX)) == -1 )
	{
		perror("sysconf");
		cout << "_SC_OPEN_MAX is not defined.\n";
	}
	else
		cout << "Maximum no. of files that a process can have open at any time: " << returnValue << endl;

    if( (returnValue = pathconf("/",_PC_PATH_MAX)) == -1 )
	{
		perror("pathconf");
		cout << "_PC_PATH_MAX is not defined.\n";
	}
	else
		cout << "Maximum length of a relative pathname when path is current working directory: " << returnValue << endl;

    if( (returnValue = pathconf("/",_PC_NAME_MAX)) == -1 )
	{
		perror("pathconf");
		cout << "_PC_NAME_MAX is not defined.\n";
	}
	else
		cout << "Maximum length of a filename in the directory that a process is allowed to create: " << returnValue << endl;
	cout << endl;
}