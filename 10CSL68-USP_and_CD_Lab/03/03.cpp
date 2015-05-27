/*
*	Documented by:
		Aditi Mohanty
		github.com/rheaditi

*	Problem Statement:
		Consider the last 100 bytes as a region. Write a C/C++ program to check 
		whether the region is locked or not. If the region is locked, print pid
		of the process which has locked it. If the region is not locked, lock 
		the region with an exclusive lock, read the last 50 bytes and unlock 
		the region.

*	Structure used (defined in <fcntl.h> or <bits/fcntl.h>) :
		struct flock {
	       short l_type;    //Type of lock: F_RDLCK, F_WRLCK, F_UNLCK
	       short l_whence;  How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END
	       off_t l_start;   Starting offset for lock
	       off_t l_len;     Number of bytes to lock
	       pid_t l_pid;     PID of process blocking our lock (F_GETLK only)
	   	};
*/

#include <iostream>
#include <stdio.h> //for perror()
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char ** argv)
{
	int fd; //file descriptor
	struct flock f; //this structure is defined in <fcntl.h> or <bits/fcntl.h>
	char buffer[100]={0};

	if(argc!=2)
	{
		cout << "usage: " << argv[0] << " <example_file_to_demo_locking>\n";
		return 0;
	}

	if ( !access(argv[1],F_OK) )
	{
		if( (fd=open(argv[1],O_RDWR))==-1 )
		{
			perror("open");
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "File %s does not exist.\n", argv[1]);
		return -1;
	}

	//first query the region's lock status
	f.l_type = F_WRLCK; //the lock we would like to place
	f.l_whence = SEEK_END; //from end of file
	f.l_start = -100; //last 100 bytes
	f.l_len = 100;

	if( fcntl(fd,F_GETLK,&f) ==-1 )
	{
		perror("fcntl");
		return -1;
	}

	//above call returns F_UNLCK if the file region is lockable
	if( f.l_type!=F_UNLCK )
	{
		cout << "\nA process with pid: " << f.l_pid << " is already holding a ";
		if( f.l_type==F_RDLCK )
			cout << "read lock";
		else if ( f.l_type == F_WRLCK )
			cout << "write lock";
		cout << " on the required region of the file " << argv[1] << "." << endl;
	}

	//then, try to acquire the lock
	f.l_type = F_WRLCK; //the lock we would like to place
	f.l_whence = SEEK_END; //from end of file
	f.l_start = -100; //last 100 bytes
	f.l_len = 100;

	while ( fcntl(fd,F_SETLK,&f)==-1 )
	{
		;//wait
	}
	
	cout << "\nProcess with pid " << getpid() << " has ACQUIRED the lock on the last 100 bytes of the file " << argv[1] << ".\n";
	
	//reach the last 50 bytes
	if( lseek(fd,-50,SEEK_END) ==-1 )
	{
		perror("lseek");
		return -1;
	}

	//read the last 50 bytes
	if( read(fd,buffer,50)!=50 )
	{
		perror("read");
		return -1;
	}

	cout << "Contents of last 50 bytes of the file: \n\n\"\n";
	cout << buffer << "\n\"\n\n";

	sleep(10); //to demo another process trying to acquire the lock

	//to finally release the lock
	f.l_type = F_UNLCK; //the lock we would like to place
	f.l_whence = SEEK_END; //from end of file
	f.l_start = -100; //last 100 bytes
	f.l_len = 100;

	if ( fcntl(fd,F_SETLK,&f) ==-1 )
	{
		perror("fcntl");
		return -1;
	}
	cout << "Process with pid " << getpid() << " has RELEASED the lock on the last 100 bytes of the file " << argv[1] << ".\n";
	return 0;
}