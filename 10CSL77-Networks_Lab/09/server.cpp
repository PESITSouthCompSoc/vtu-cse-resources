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
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for htons()

using namespace std;

int main(){
	char fileName[256];
	char buffer[1025];
	int sdesc, source, fd, n;

	struct sockaddr_in address;
	address.sin_family = AF_INET; //Internet IPv4 family
	address.sin_port = htons(5000); //convert from host order to network byte order
	address.sin_addr.s_addr = INADDR_ANY; //assign any IP

	if( (sdesc = socket(AF_INET,SOCK_STREAM, 0)) == -1 ){
		perror("socket");
		return -1;
	}

	if( bind(sdesc, (struct sockaddr *) &address, sizeof(address)) == -1 ){
		perror("bind") ; 
		return -1; 
	} 
	cout << "Bound to socket, listening for	connections...\n\n";

	//int listen(int sockfd, int backlog); -> backlog = length of queue for socket requests
	listen(sdesc,3);

	if( ( source = accept(sdesc, NULL, NULL) ) == -1 ){
		perror("accept");
		return -1;
	}

	cout << "Accepted a connection...\n";
	if( (recv(source,fileName,sizeof(fileName),0)) < 0 ){
		perror("recv");
		return -1;
	}

	cout << "Received a request for file: \'" << fileName << "\'\n\n";
	if( access(fileName, F_OK) !=0 ){
		char msg[] = "File Not Found.\n";
		if( send(source,msg,strlen(msg),0) < 0 ){
			perror("send");
			return -1;
		}
		cout << "Error Occurred: " << msg;
	}
	else if( access(fileName, R_OK) !=0 ){
		char msg[] = "Cannot read file. Permission Denied.\n";
		if( send(source,msg,strlen(msg),0) < 0 ){
			perror("send");
			return -1;
		}
		cout << "Error Occurred: " << msg;
	}
	else {
		if( (fd = open (fileName,O_RDONLY))<0){
			perror("open");
			return -1;
		}
		while( (n=read(fd,buffer,1024))>0 ){
			send(source,buffer,n,0);
		}
		cout << "Sent contents of requested file...\n";
		close(fd);
	}
	return 0;
}

