/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Write a C/C++ program that outputs the contents of its Environment List.

*	Description: 
		Comment out lines labeled L1, L2, L3, L4 to demonstrate the race condition.
*/



#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

void waitChild();
void tellChild();
void waitParent();
void tellParent();
void printOne(const char *str);

int pipeP[2], pipeC[2];

int main(int argc, char ** argv)
{
	pid_t pid;
	

	if( pipe(pipeP) || pipe(pipeC) )
	{
		perror("pipe");
		return -1;
	}

	if( (pid=fork())==-1 )
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		//within the child process
		//waitParent(); //L1
		printOne("output from child\n");
		//tellParent(); //L2
		return 0;
	}
	else
	{
		//within the parent process
		//tellChild(); //L3
		//waitChild(); //L4
		printOne("output from parent\n");
		return 0;
	}
}

void printOne(const char *str)
{
	char * s = (char *) str;
	while(*s)
	{
		cout << *s;
		fflush(stdout);
		sleep(1);
		s++;		
	}
}

void tellChild()
{
	//inform child that task is done by writing 'p' to the parent pipe.
	if(write(pipeP[1],"p",1)<1)
	{
		perror("write");
		exit(-1);
	}
}

void tellParent()
{
	//inform parent that task is done by writing 'c' to the child pipe.
	if(write(pipeC[1],"c",1)<1)
	{
		perror("write");
		exit(-1);
	}
}

void waitChild()
{
	//parent waits till child informs of completed task
	char ch;
	if(read(pipeC[0],&ch,1)<1)
	{
		perror("read");
		exit(-1);
	}
	if(ch!='c')
	{
		cout << "Error.\n";
		exit(-1);
	}
}

void waitParent()
{
	//child waits till parent informs of completed task
	char ch;
	if(read(pipeP[0],&ch,1)<1)
	{
		perror("read");
		exit(-1);
	}
	if(ch!='p')
	{
		cout << "Error.\n";
		exit(-1);
	}
}


