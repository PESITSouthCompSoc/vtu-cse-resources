/*
*	Authored & Documented by:
		Aditi Anomita Mohanty
		github.com/rheaditi
		
		Abinav Nithya Seelan
		github.com/abinavseelan

*	Problem Statement:
		Write a C/C++ POSIX compliant program that prints the POSIX 
		defined configuration options supported on any given system 
		using feature test macros.

*	Description:
		Through POSIX, an application can query certain limits/availability of certain options or functionality, either at:
			1. Compile-time : through MACROS defined in <unistd.h> and <limits.h>
			2. Run-time : through use of the library functions sysconf(3) and pathconf(3)

*	In the previous program (01) we queried the run-time system-wide limits using the library functions mentioned.
	In this program, we use the feature-test MACROS defined in <unistd.h> and <limits.h>, to check during compile time if certain
	configurations/options are supported.

*	MACROS defined in:
		/usr/include/unistd.h
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
	cout << "Testing features.. \n\n";

	#ifdef _POSIX_JOB_CONTROL
		cout << "Job control is supported." << endl;
	#else
		cout << "Job control is NOT supported." << endl;
	#endif


	#ifdef _POSIX_SAVED_IDS
		cout << "Processes have a saved set-user-ID and a saved set-group-ID." << endl;
	#else
		cout << "Processes DO NOT have a saved set-user-ID and a saved set-group-ID." << endl;
	#endif
	

	#ifdef _POSIX_TIMERS
		cout << "POSIX.4 clocks and timers are supported." << endl;
	#else
		cout << "POSIX.4 clocks and timers are NOT supported." << endl;
	#endif


	#ifdef _POSIX_THREADS
		cout << "POSIX.1c pthreads are supported." << endl;
	#else
		cout << "POSIX.1c pthreads are NOT supported." << endl;
	#endif


	#ifdef _POSIX_CHOWN_RESTRICTED
        cout << "_POSIX_CHOWN_RESTRICTED option is defined with value: " << _POSIX_CHOWN_RESTRICTED << endl;
    #else
        cout << "_POSIX_CHOWN_RESTRICTED is not defined." << endl;
    #endif


    #ifdef _POSIX_NO_TRUNC
        cout << "_POSIX_NO_TRUNC option is defined with value: "<< _POSIX_NO_TRUNC << endl;
    #else
        cout << "_POSIX_NO_TRUNC is not defined." << endl;
    #endif
	
	cout << endl;
}
