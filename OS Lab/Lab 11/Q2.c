#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define P 5   // Number of processes
#define R 3   // Number of resources

// Global variables
int available[R];               // Available resources
int max[P][R];                  // Maximum demand of each process
int allocation[P][R];           // Resources currently allocated
int need[P][R];                 // Remaining needs

pthread_mutex_t lock;           // Mutex lock for synchronization

// Function to check if the system is in a safe state
bool isSafe() {
    int work[R];
    bool finish[P] = {false};

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) { // If all needs can be satisfied
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[p][k];
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
            return false;  // No safe sequence
    }

    return true;
}

// Request resources for a process
bool requestResources(int pid, int request[]) {
    pthread_mutex_lock(&lock);

    printf("Process %d requesting: ", pid);
    for (int i = 0; i < R; i++)
        printf("%d ", request[i]);
    printf("\n");

    // Check if request <= need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[pid][i]) {
            printf("Process %d error: exceeds its maximum claim.\n", pid);
            pthread_mutex_unlock(&lock);
            return false;
        }
    }

    // Check if request <= available
    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Process %d must wait: not enough available resources.\n", pid);
            pthread_mutex_unlock(&lock);
            return false;
        }
    }

    // Tentatively allocate
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    // Check safety
    if (isSafe()) {
        printf("Request by process %d granted.\n\n", pid);
        pthread_mutex_unlock(&lock);
        return true;
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        printf("Request by process %d denied (unsafe state).\n\n", pid);
        pthread_mutex_unlock(&lock);
        return false;
    }
}

// Release resources
void releaseResources(int pid) {
    pthread_mutex_lock(&lock);

    printf("Process %d releasing resources...\n", pid);
    for (int i = 0; i < R; i++) {
        available[i] += allocation[pid][i];
        need[pid][i] += allocation[pid][i];
        allocation[pid][i] = 0;
    }

    pthread_mutex_unlock(&lock);
}

// Thread function for each process
void* process(void* pid_arg) {
    int pid = *(int*)pid_arg;
    free(pid_arg);

    while (1) {
        int request[R];
        bool done = true;

        pthread_mutex_lock(&lock);
        for (int i = 0; i < R; i++) {
            if (need[pid][i] > 0)
                done = false;
        }
        pthread_mutex_unlock(&lock);

        if (done) break;  // Process completed

        // Random resource request (<= need)
        for (int i = 0; i < R; i++)
            request[i] = rand() % (need[pid][i] + 1);

        if (requestResources(pid, request)) {
            // Simulate doing work
            sleep(1);
            releaseResources(pid);
        }

        sleep(1 + rand() % 3);
    }

    printf("Process %d completed successfully.\n", pid);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t processes[P];

    // Initialize available resources
    int total[R] = {10, 5, 7};
    for (int i = 0; i < R; i++)
        available[i] = total[i];

    // Initialize sample data (can be replaced with user input)
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximum[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Copy into global matrices
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) {
            allocation[i][j] = alloc[i][j];
            max[i][j] = maximum[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
            available[j] -= allocation[i][j];
        }

    pthread_mutex_init(&lock, NULL);

    // Create process threads
    for (int i = 0; i < P; i++) {
        int* pid = malloc(sizeof(int));
        *pid = i;
        pthread_create(&processes[i], NULL, process, pid);
    }

    // Wait for threads to finish
    for (int i = 0; i < P; i++)
        pthread_join(processes[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("\nAll processes have finished.\n");
    return 0;
}
