#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define req "requests"
#define res "responses"

using namespace std;

int main(){
	int reqFD, resFD, fileFD, n;
	char fileName[256]="", buffer[1025]="";

	if ( access(req,F_OK)!=0 ){
		mkfifo(req,0755);
	}
	if ( access(res,F_OK)!=0 ){
		mkfifo(res,0755);
	}
	cout << "Waiting for a client's request...\n\n";
	reqFD = open(req,O_RDONLY);
	resFD = open(res,O_WRONLY);

	if( reqFD<0 || resFD<0 ){
		perror("open");
		return -1;
	}

	n=read(reqFD,fileName,256);
	fileName[n]='\0';
	if(n<0){
		perror("read");
		return -1;
	}
	cout << "Received request for \'"<< fileName <<"\'...\n";	
	if( access(fileName,F_OK)!=0 ){
		char msg[] = "File Not Found.\n";
		cout << msg << "\nSending ERROR Message...\n";
		write(resFD,msg,sizeof(msg));
	}
	else{
		fileFD = open(fileName,O_RDONLY);
		while( (n=read(fileFD,buffer,sizeof(buffer))) >0 ){
			write(resFD,buffer,sizeof(buffer));
		}
	}
	cout << "Response sent...\n\n";
	close(resFD);
	close(reqFD);
	close(fileFD);
	unlink(req);
	unlink(res);
}
