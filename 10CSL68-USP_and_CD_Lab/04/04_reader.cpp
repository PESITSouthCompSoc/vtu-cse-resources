/*
*	Authored & Documented by:
		Aditi Anomita Mohanty
		github.com/rheaditi
		
		Abinav Nithya Seelan
		github.com/abinavseelan

*	Problem Statement:
		Write a C/C++ program which demonstrates interprocess communication 
		between a reader process and a writer process. Use mkfifo, open, read, 
		write and close APIs in your program.
*/
	   	
/*** READER PROCESS ***/
#include <iostream>
#include <stdio.h> //for perror
#include <unistd.h>

/*for open, read, write & close APIs */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

#define fifofile "myFIFO"

int main(int argc, char ** argv)
{
	int fd; //file descriptor
	char buffer[200]; //a buffer to read into

	if( access(fifofile,F_OK) )
	{
		cout << "Required FIFO file doesn't exist. Please start the writer process first.\n";
		return -1;
	}

	if( (fd=open(fifofile,O_RDONLY))==-1 )
	{
		perror("open");
		return -1;
	}

	cout << "Reader (" << getpid() << ") got a writer process ..\n\n";
	while(1)
	{
		for(int i=0; i<200; i++) //clear buffer so no extra contents from previous read operation
			buffer[i]='\0';

		cout << "Reader reads:\n";
		if( read(fd,buffer,200) <=0 )
		{
			perror("read");
			return 0;
		}

		cout << buffer;
	}
	return 0;
}