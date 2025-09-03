//TCP Server Program
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#define PORTNO 49159 // select port betw 49152-65535 for program
int main()
{
	int sockfd,newsockfd,portno,clilen,n=1;
	char buf[256], wbuf[256];
	struct sockaddr_in seraddr,cliaddr;
	int i,value;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = INADDR_ANY;//inet_addr("172.16.59.10"); //**
	seraddr.sin_port = htons(PORTNO);
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	// Create a connection queue, ignore child exit details, and wait for clients
	listen(sockfd,5);
	while(1){
		//Accept the connection
		clilen = sizeof(clilen);newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		//Fork to create a process for this client and perform a test to see whether
		//you’re the parent or the child:
		if(fork()==0){
			// If you’re the child, you can now read/write to the client on newsockfd.
			memset(wbuf, '\0', sizeof(wbuf));
			n = read(newsockfd,buf,sizeof(buf));
			int a = (int)buf[0]-48;
			int b = (int)buf[2]-48;
			int res;
			switch(buf[1]){
				case '+':res=a+b;
				break;
				case '-':res=a-b;
				break;
				case '*':res=a*b;
				break;
				case '/':res=a/b;
				break;
				case '%':res=a%b;
				break;
				default: res=-999;
			}
			//printf(" \nMessage from Client: %s",buf);
			sprintf(buf, "operands: %d ,%d ; operation: %c ; result: %d", a, b, buf[1], res);
			n = write(newsockfd,buf,sizeof(buf));
			close(newsockfd);
			exit(0);
		}
		//Otherwise, you must be the parent and your work for this client is finished
		else{
			wait(NULL);
			close(newsockfd);
			exit(0);
		}
	}
}
