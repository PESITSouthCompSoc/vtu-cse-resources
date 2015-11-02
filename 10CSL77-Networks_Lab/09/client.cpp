/*
	09 - Client Server using Sockets

	Using TCP/IP sockets, write a client-server program to make
	client send the file name and the server to send back the 
	contents of the requested file if present.
*/

#include <iostream>
#include <stdio.h> //for perror
#include <fcntl.h> //for file operations
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for htons()

using namespace std;

int main(){
	char fileName[256];
	char buffer[1025];
	int sdesc, n;

	struct sockaddr_in address;
	address.sin_family = AF_INET; //Internet IPv4 family
	address.sin_port = htons(5000); //convert from host order to network byte order
	address.sin_addr.s_addr = INADDR_ANY; //assign any IP

	//check <socket.h>
	//int socket(int domain, int type, int protocol);
	if( (sdesc=socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return -1;
	}
	if( connect(sdesc, (struct sockaddr *)&address, sizeof(address)) ==-1  ){
		perror("connect");
		return -1;
	}

	cout << "Initiated a connection on socket...\n";
	cout << "Enter filename to request: ";
	scanf("%[^\n]s",fileName);
	cout << "Sending request for \'" << fileName << "\'...\n";

	if( send(sdesc, fileName, sizeof(fileName), 0) ==-1 ){
		perror("send");
		return -1;
	}

	cout << "Received a response...\n\n";
	while( (n=recv(sdesc,buffer,1024,0))>0 ){
		write(STDOUT_FILENO, buffer, n);
	}

	return 0;
}

