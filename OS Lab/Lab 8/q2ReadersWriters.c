#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
sem_t mutex, wrt;
int readcount;
void *write(void *param)
{
    while(1){
       sem_wait(&wrt);
       printf("Writing!\n");
       sem_post(&wrt);
    }
    return NULL;
}
void *read(void *param)
{
    while(1){
        sem_wait(&mutex);
        readcount++;
        if(readcount==1)sem_wait(&wrt);//writers wait if anyone reading
        sem_post(&mutex);//after putting writers on wait alllow reading
        printf("Reading!\n");
        sem_post(&mutex);//put reading on pause after reading to remove one readers
        readcount--;
        if(readcount==0)sem_post(&wrt);//allow writers if no reader is reading
        else sem_post(&mutex);//free readers to apply for reading permission again
    }
    return NULL;
}
int main()
{
    pthread_t threads[2];
    readcount=0;
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    pthread_create(&threads[0], NULL, read, NULL);
    pthread_create(&threads[1], NULL, write, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    sem_destroy(&wrt);
    sem_destroy(&mutex);
    return 0;
}
