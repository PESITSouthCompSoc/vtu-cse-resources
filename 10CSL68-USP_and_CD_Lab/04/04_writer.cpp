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

/*** WRITER PROCESS ***/
#include <iostream>
#include <stdio.h> //for perror
#include <unistd.h>
#include <signal.h> //to handle the interrupt
#include <string.h> //for strlen()
#include <stdlib.h> //for exit()

/*for open, read, write & close APIs */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

#define fifofile "myFIFO"

void signalHandler(int s)
{
	cout << "\nInterrupt encountered.\nWriter exits and deletes FIFO file.\n";
	unlink(fifofile);
	exit(0);
}

int main(int argc, char ** argv)
{
	int fd; //file descriptor
	char buffer[200]; //a buffer to use to read/write
	int len; //length of string read/written

	signal(SIGINT, signalHandler); //register the signal handler

	if( access(fifofile,F_OK) )
	{
		if( mkfifo(fifofile,0722)==-1 )
		{
			perror("mkfifo");
			return -1;
		}
	}
	cout << "Waiting for a reader process .. \n";
	if( (fd=open(fifofile,O_WRONLY))==-1 )
	{
		perror("open");
		return -1;
	}

	cout << "Writer (" << getpid() << ") got a reader process ..\n\n";
	while(1)
	{

		for(int i=0; i<200; i++) //clear buffer so no extra contents from previous read operation
			buffer[i]='\0';

		cout << "Writer writes:\n";
		if( fgets(buffer,200,stdin)==NULL ) //read from standard input
		{
			perror("fgets");
			return 0;
		}

		len = strlen(buffer);
		if ( write(fd,buffer,len)< len )
		{
			perror("write");
			return -1;
		}
	}
	return 0;
}