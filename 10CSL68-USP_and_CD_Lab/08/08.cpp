/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Write a C/C++ program to avoid zombie process by forking twice.
*/


#include <iostream>
#include <unistd.h>
#include <stdio.h> //for perror
#include <stdlib.h> //for system
#include <sys/wait.h>

using namespace std;

int main(int argc, char ** argv)
{
	pid_t child1, child2;
	int status=0;

	if( (child1=fork())==-1 )
	{
		perror("fork");
	}
	else if(child1==0)
	{
		cout << "\n\nFirst Child\n\tPID: " << getpid() << "\n\tPPID: " << getppid() << ".\n";
		cout << "First child forks again..\n";
		if( (child2=fork())==-1 )
		{
			perror("fork");
			return -1;
		}
		else if(child2==0)
		{
			cout << "\n\nSecond Child\n\tPID: " << getpid() << "\n\tPPID: " << getppid() << ".\n\n";
			cout << "Second child sleeps..\n\n";
			sleep(5);
			system("ps -o pid,ppid,state,comm");
			cout << "\nSecond child's PPID is now: " << getppid() << " (init)\n";
		}
		else
		{
			sleep(1);
			cout << "First child terminates ..\n";
			return 0;
		}		
	}
	else
	{
		waitpid(child1, NULL, 0);
		cout << "\n";
		sleep(7);
		cout << "Parent terminates..\n";
		return 0;
	}
}