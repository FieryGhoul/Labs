#include<stdio.h> // for printf(), perror()
#include<sys/types.h> // for pid_t, socklen_t, size_t
#include<sys/socket.h> // for socket(), bind(), listen(), accept(), connect()
#include<unistd.h> // for read(), write()
#include<netinet/in.h> // for struct sockaddr_in, Macros like AF_INET and INADDR_ANY, htons()
#include<arpa/inet.h>
#include<string.h> // for strcpy()
#include<stdlib.h> // for exit()
#define PORTNO 49155 // select port betw 49152-65535 for program
void remove_duplicates(char sentence[500]) {
    char matWords[50][256], temp[256];
    int l = 0, w = 0, p=0;
    for(int i=0; i<strlen(sentence); i++){
    	if(sentence[i]!=' ')matWords[l][w++] = sentence[i];
    	else{
    		matWords[l][w++]='\0';
    		l++;
    		w=0;
    	 }
    }
    for(int i=0; i<=l; i++){
    	write(1, matWords[i], sizeof(matWords[i]));
    }
    for(int i=0; i<=l; i++){
    	int flag1=0;
    	for(int j=0; j<=l; j++){
    		if(i>j && strcmp(matWords[i], matWords[j])==0){
    			flag1 = 1;
    			break;
    		}
    	}
    	if(flag1==0){
    		for(int j=0; j<strlen(matWords[i]); j++){
    			temp[p++] = matWords[i][j];
    		}
    		if(i<l)temp[p++] = ' ';
    	}
    }
    temp[p++] = '\0';
    strcpy(sentence, temp);
}
int main(){
	//define variables for program
	int sock_lis, sock_new, client_len, nb, status, complete=0; //sockets for listening and commn, length of client address, no of bytes commn, status for syscalls like listen and bind
	struct sockaddr_in server_addr, client_addr; //structures for server and client address
	do{
		sock_lis=socket(AF_INET, SOCK_STREAM, 0);//make new stream socket for ipv4 using default protocol
		printf("!!\n");
	}while(sock_lis < 0);
	//initialise values in server struct
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;//use inet_addr if this fails
	server_addr.sin_port = htons( PORTNO );
	//bind created listening sockets to server_addr
	do{
		status = bind(sock_lis, &server_addr, sizeof(server_addr));
		printf("!\n");
	}while(status < 0);//keep binding till no errors
	//create connection queue and wait for clients
	printf("Server is listening...\n");
	listen(sock_lis, 5);//conn queue is of length 5
	//accept and connect to the caller
	printf("Server is accepting connecs...\n");
	char rbuf[500]="", wbuf[500]="";//buffers for messages
	client_len = sizeof(client_addr);
 	sock_new = accept(sock_lis, &client_addr, &client_len);//accept connection
	printf("Connnection accepted on %d...\n", sock_new);
	do{
		if(fork()==0){
				//now you can read and write to the socket
				nb = read(sock_new, rbuf, sizeof(rbuf));
				if(strcmp("stop", rbuf)==0){
					printf("\nTerminated\n");
					close(sock_new);
					complete=1;
					exit(0);
				}
				printf("Message from client: %s\n", rbuf);
				strcpy(wbuf, rbuf);
				wbuf[strlen(wbuf)]='\0';	
				remove_duplicates(wbuf);
				printf("\nProccesed\n");
				nb = write(sock_new, wbuf, sizeof(rbuf));
				if(nb < 0)printf("Error!\n");
				
		}
		else{
			wait(&complete);
			if(complete==1){
				close(sock_new);
				exit(0);
			}
		}
	}while(complete==0);
} 
