#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib;   // shared array
int n;      // number of terms

void* generate_fib(void *arg) {
    fib[0] = 0;
    if (n > 1) fib[1] = 1;
    for (int i = 2; i < n; i++)
        fib[i] = fib[i-1] + fib[i-2];
    pthread_exit(NULL);
}

int main() {
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    fib = (int*)malloc(n * sizeof(int));

    pthread_t tid;
    pthread_create(&tid, NULL, generate_fib, NULL);
    pthread_join(tid, NULL);

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) printf("%d ", fib[i]);
    printf("\n");

    free(fib);
    return 0;
}
