#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3
#define NUM_CUSTOMERS 10

sem_t customers;
sem_t barber;
sem_t mutex;

int waiting = 0;

void *barber_func(void *arg)
{
    while (1)
    {
        sem_wait(&customers);  // Wait for a customer
        sem_wait(&mutex);
        waiting--;
        printf("Barber is cutting hair, waiting customers = %d\n", waiting);
        sem_post(&barber);
        sem_post(&mutex);

        sleep(3); // Cutting hair
        printf("Barber finished cutting hair\n");
    }
}

void *customer_func(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);
    if (waiting < CHAIRS)
    {
        waiting++;
        printf("Customer %d is waiting. Waiting customers = %d\n", id, waiting);
        sem_post(&customers);
        sem_post(&mutex);

        sem_wait(&barber); // Wait for barber to be ready
        printf("Customer %d is getting haircut\n", id);
    }
    else
    {
        printf("Customer %d leaves, no chairs available\n", id);
        sem_post(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t barber_tid;
    pthread_t customers_tid[NUM_CUSTOMERS];
    int ids[NUM_CUSTOMERS];

    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&barber_tid, NULL, barber_func, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        ids[i] = i + 1;
        sleep(1);  // Customers arrive at different times
        pthread_create(&customers_tid[i], NULL, customer_func, &ids[i]);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++)
        pthread_join(customers_tid[i], NULL);

    // Barber thread runs infinitely; program can be terminated manually

    sem_destroy(&customers);
    sem_destroy(&barber);
    sem_destroy(&mutex);

    return 0;
}

