#include <stdio.h>
#include <pthread.h>

int sum = 0;
int n;

void* compute_sum(void *arg) {
    for (int i = 0; i <= n; i++)
        sum += i;
    pthread_exit(NULL);
}

int main() {
    printf("Enter a non-negative integer n: ");
    scanf("%d", &n);

    pthread_t tid;
    pthread_create(&tid, NULL, compute_sum, NULL);
    pthread_join(tid, NULL);

    printf("Sum of 0 to %d = %d\n", n, sum);
    return 0;
}
