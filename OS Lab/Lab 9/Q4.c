#include <stdio.h>
#include <pthread.h>

#define SIZE 6
int arr[SIZE] = {1,2,3,4,5,6};
int even_sum = 0, odd_sum = 0;

void* sum_even(void *arg) {
    for (int i = 0; i < SIZE; i++)
        if (arr[i] % 2 == 0) even_sum += arr[i];
    pthread_exit(NULL);
}

void* sum_odd(void *arg) {
    for (int i = 0; i < SIZE; i++)
        if (arr[i] % 2 != 0) odd_sum += arr[i];
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, sum_even, NULL);
    pthread_create(&t2, NULL, sum_odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum of Even numbers = %d\n", even_sum);
    printf("Sum of Odd numbers = %d\n", odd_sum);
    return 0;
}
