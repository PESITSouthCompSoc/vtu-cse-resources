/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Write a C/C++ program that creates a zombie and then calls 
		system to execute the ps command to verify that the process
		is zombie.

*	Make sure the executable file is named 'zombie' or else change the
	grep command to grep for 'a.out' or whatever filename you choose.
*/


#include <iostream>
#include <unistd.h>
#include <stdio.h> //for perror
#include <stdlib.h> //for system
#include <sys/wait.h>

using namespace std;

int main(int argc, char ** argv)
{
	pid_t pid;
	int status=0;

	if( (pid=fork())==-1 )
	{
		perror("fork");
		return -1;
	}
	else if(pid==0)
	{
		cout << "Child process with PID " << getpid() << " created by its parent with PID " << getppid() << ".\n";
		system("ps -o pid,ppid,state,comm");
		cout << "Child process exits ..\n";
	}
	else
	{
		sleep(8);
		cout << "\n\n\n";
		cout << "Parent process with PID " << getpid() << " resumes execution and calls ps:- \n";
		system("ps -o pid,ppid,state,comm");
		cout << "As seen above, child is a zombie process as the parent has not executed wait(2).\n\n";
		sleep(10);
		cout << "\n\n\n";
		cout << "Parent now executes wait..";
		wait(&status);
		cout << "Process table after execution of wait:-\n";
		system("ps -o pid,ppid,state,comm");
		cout << "Child process no longer exists in the process table.\n";
		cout << "Parent exits..\n\n";
	}
}