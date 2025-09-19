#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
sem_t semaphore1, semaphore2, semaphore3;
int turn=0;
void *func1(void *param)
{
    sem_wait(&semaphore1);
    turn=1;
    if(turn!=0)sleep(1);
    printf("Requesting 2, 3\n");
    sem_wait(&semaphore2);
    sem_wait(&semaphore3);
    printf("Thread 1\n");
    return NULL;
}
void *func2(void *param)
{
    sem_wait(&semaphore2);
    turn=2;
    if(turn!=1)sleep(1);
    printf("Requesting 3, 1\n");
    sem_wait(&semaphore3);
    sem_wait(&semaphore1);
    printf("Thread 2\n");
    return NULL;
}
void *func3(void *param)
{
    sem_wait(&semaphore3);
    turn=1;
    if(turn!=2)sleep(1);
    printf("Requesting 1, 2\n");
    sem_wait(&semaphore1);
    sem_wait(&semaphore2);
    printf("Thread 3\n");
    return NULL;
}
int main()
{
    pthread_t threads[3];
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 1);
    sem_init(&semaphore3, 0, 1);
    pthread_create(&threads[0], NULL, func1, NULL);
    pthread_create(&threads[1], NULL, func2, NULL);
    pthread_create(&threads[2], NULL, func3, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    sem_destroy(&semaphore3);
    return 0;
}
