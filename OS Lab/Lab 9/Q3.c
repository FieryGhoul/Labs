#include <stdio.h>
#include <pthread.h>
#include <math.h>

int start, end;

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return 0;
    return 1;
}

void* generate_primes(void *arg) {
    printf("Primes between %d and %d:\n", start, end);
    for (int i = start; i <= end; i++)
        if (is_prime(i)) printf("%d ", i);
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    printf("Enter start and end values: ");
    scanf("%d %d", &start, &end);

    pthread_t tid;
    pthread_create(&tid, NULL, generate_primes, NULL);
    pthread_join(tid, NULL);

    return 0;
}
