#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

typedef struct shared {
    int turn;
    char ch;
} Shared;

void main() {
    void * sharedMemory = (void *) 0;
    Shared *data;
    
	//We create shared memory using the shmget function:
    int shmID = shmget(4321, sizeof(Shared), 0666 | IPC_CREAT);
    if (shmID == -1) {
        printf("Shared memory creation Error.\n");
        exit(1);
    }
    
    //to enable access to the shared memory, we must attach it to the address space of a process.
    sharedMemory = shmat(shmID, 0, 0);
    if (sharedMemory ==  -1) {
        printf("Shared Memory Error\n");
        exit(1);
    }
    
    
    printf("Memory attached at %X\n", sharedMemory);
    
    data = (Shared *) sharedMemory;
    data->turn = 1;
    if (fork() == 0) {
        while(data -> turn == 1)
            sleep(1);
            
        data->ch = data->ch + 1;
        data->turn = 1;
    }
    else {
        char ch;
        printf("Enter a character ");
        scanf("%c", &ch);
        data->ch = ch;

        data->turn = 0;

        while (data->turn == 0) 
            sleep(1);

        printf("Received character: %c\n", data->ch);
    }
    
    //detaches the shared memory from the current process.
    if (shmdt(sharedMemory) == -1) {
        printf("Shared Memory deletion failed\n");
        exit(1);
    }
}

