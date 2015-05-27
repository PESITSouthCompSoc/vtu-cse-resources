/*
*	Authored & Documented by:
		Aditi Anomita Mohanty
		github.com/rheaditi
		
		Abinav Nithya Seelan
		github.com/abinavseelan

*	Problem Statement:
		Write a C/C++ program to implement the system function.
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int mySystem(const char * cmd);

int main(int argc, char ** argv)
{
	char buffer[200];
	int ret;
	cout << "Enter command: ";
	fgets(buffer,200,stdin);
	cout << endl;
	ret = mySystem((char*)buffer);
	cout << "\n\nExecuted command with return status: " << ret << ".\n";
	return 0;
}

int mySystem(const char * cmd)
{
	int status;
	pid_t pid;
	if((pid=fork())==-1)
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		execlp("/bin/sh","bash","-c",cmd,NULL);
	}
	else
	{
		waitpid(pid,&status,0);
		return status;
	}
}