/*
*	Authored & Documented by:
		Aditi Anomita Mohanty
		github.com/rheaditi
		
		Abinav Nithya Seelan
		github.com/abinavseelan

*	Problem Statement:
		Write a C/C++ program that outputs the contents of its Environment List.

*	Description: 
		Environment variables are a set of dynamic named values that can affect the way 
		running processes will behave on a computer. They are part of the environment 
		in which a process runs.

		Within a terminal, we can query any given environment variable using echo. For example:
			echo $HOME
		Will show your home directory.

		Each process receives a list which has all the environment variables it needs, in two ways:
			1. Passed as the 3rd command line argument by the shell.
			2. Through an externally defined variable called 'environ'.
*/

#include <iostream>

using namespace std;

int main(int argc, char ** argv, char ** env_list)
{
	char ** e = env_list;
	cout << "Contents of the environment list are: \n\n";
	while(*e)
	{
		cout << *e << endl;
		e++;
	}
}

/*
//alternative code: 

int main(int argc, char ** argv)
{
	char ** e = environ;
	cout << "Contents of the environment list are: \n\n";
	while(*e)
	{
		cout << *e << endl;
		e++;
	}
}

*/