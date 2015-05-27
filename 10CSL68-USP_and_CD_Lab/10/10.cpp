/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Write a C/C++ program to set up a real-time clock 
		interval timer using the alarm API.

*	API Used:
		#include <sys/time.h>
       int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);

*	Structures:
		struct itimerval {
               struct timeval it_interval; //next value 
               struct timeval it_value;    //current value
           };
		struct timeval {
		   time_t      tv_sec;         //seconds 
		   suseconds_t tv_usec;        //microseconds 
		};
*/

#include <iostream>
#include <stdio.h> //for perror
#include <signal.h> //for signal handling
#include <sys/time.h> //timeval structure
#include <stdlib.h> //for exit()

using namespace std;

void alarmHandler(int s);
void interruptHandler(int s);
float count=0;

int main(int argc, char ** argv)
{
	struct itimerval t;

	signal(SIGINT,interruptHandler);
	signal(SIGALRM,alarmHandler);

	t.it_interval.tv_sec = 2;
	t.it_interval.tv_usec = 0;

	t.it_value.tv_sec = 6;
	t.it_value.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&t,NULL)==-1)
	{
		perror("setitimer");
		return -1;
	}
	while(1);
}

void alarmHandler(int s)
{
	if(!count)
	{
		count+=6;
		cout << "First time alarm hits!" << endl;
	}
	else
		count+=2;
	cout << count << " seconds.\n";
}

void interruptHandler(int s)
{
	cout << "\nInterrupt occurred. Program now exits..\n\n";
	exit(0);
}