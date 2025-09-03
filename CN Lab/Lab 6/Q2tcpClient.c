#include<stdio.h> // for printf(), perror()
#include<sys/types.h> // for pid_t, socklen_t, size_t
#include<sys/socket.h> // for socket(), bind(), listen(), accept(), connect()
#include<unistd.h> // for read(), write()
#include<netinet/in.h> // for struct sockaddr_in, Macros like AF_INET and INADDR_ANY, htons()
#include<string.h> // for strcpy(), gets()
#include<stdlib.h> // for exit()
#define PORTNO 49155 // select port betw 49152-65535 for program
int main(){
	//define variables for program
	int sock_con, com, client_len, nb, status; //sockets for connecting and commn, length of client address, no of bytes commn, status for syscalls like listen and bind
	struct sockaddr_in in_addr; //structures for server and client address
	do{
		printf("!!\n");
		sock_con=socket(AF_INET, SOCK_STREAM, 0);//make new stream socket for ipv4 using default protocol
	}while(sock_con < 0);
	//initialise values in server struct
	in_addr.sin_family = AF_INET;
	in_addr.sin_addr.s_addr = INADDR_ANY;//use inet_addr if this fails
	in_addr.sin_port = htons( PORTNO );
	//connect to server
	do{
		printf("!\n");
		com = connect(sock_con, (struct sockaddr*) &in_addr, sizeof(in_addr));//connect and get commn status
	}while(com < 0);//keep connecting till no errors
	//accept and connect to the caller
	printf("Connection established.Enter # in start of message start to terminate commn...");
	do{
		char rbuf[256], wbuf[256];//buffers for messages
		//now you can read and write to the socket
		printf("Enter message for server:\n");
		gets(wbuf);	
		printf("Entered string: %s\n", wbuf);
		if(strcmp(wbuf, "stop")==0){
			nb = write(sock_con, wbuf, sizeof(wbuf));
			close(sock_con);
			exit(0);
		}
		else nb = write(sock_con, wbuf, sizeof(wbuf));
		//sleep(5);
		do{nb = read(sock_con, rbuf, sizeof(rbuf));}while(strcmp(rbuf,"")==0);
		printf("Message from server: %s\n", rbuf);
	}while(1);
	return 0;
} 
