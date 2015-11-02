#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <string.h>

#define req "requests"
#define res "responses"

using namespace std;

int main(){
	int reqFD, resFD, fileFD, n;
	char fileName[256]="", buffer[1025]="";

	if ( access(req,F_OK)!=0 || access(res,F_OK)!=0 ){
		cout << "Error: No FIFO files found. Start server process first...\n";
		return -1;
	}
	reqFD = open(req,O_WRONLY);
	resFD = open(res,O_RDONLY);
	cout << "Enter filename to request: ";
	scanf("%[^\n]s",fileName);

	cout << "Sending request for \'"<< fileName <<"\'...\n";
	if( write(reqFD,fileName,strlen(fileName))<0 ){
		perror("write");
		return -1;
	}
	cout << "Received a response...\n";
	while( (n=read(resFD,buffer,sizeof(buffer)))>0 ){
		write(STDOUT_FILENO, buffer, strlen(buffer)-1);
	}
	cout << "\n\n";
	close(reqFD);
	close(resFD);

}
