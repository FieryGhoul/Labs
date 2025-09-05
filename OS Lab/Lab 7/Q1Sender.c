#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>


typedef struct msg {
    long int msgType;
    int num;
} Msg;

void main() {
	int running =1;
    Msg message;
    message.msgType = 1;
    int msgID = msgget(1234, 0666 | IPC_CREAT);
    if (msgID == -1) {
    	printf("Error");
	exit(1);
    }
    
    while(running) { 
        int n;
        printf("Enter number ");
        scanf("%d", &n);
        message.num = n;
        running = 0;
        if (msgsnd(msgID, (void*)&message, sizeof(int), 0) == -1) {
            printf("Message send failure.\n");
            exit(1);
        }
    }
}






/*while(running) {
	if (msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_receive, 0) == -1) {
		fprintf(stderr, “msgrcv failed with error: %d\n”, errno);
		exit(EXIT_FAILURE);
	}
	printf(“You wrote: %s”, some_data.some_text);
	if (strncmp(some_data.some_text, “end”, 3) == 0) {
		running = 0;
		}	
	}
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, “msgctl(IPC_RMID) failed\n”);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}*/



















