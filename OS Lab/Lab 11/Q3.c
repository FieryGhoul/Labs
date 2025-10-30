#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX 50

// Structure for Disk Scheduling Algorithm (DSA)
struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

// Function to simulate FCFS Disk Scheduling
void FCFS(struct DSA req[], int n, int start) {
    int total_seek = 0;
    int current = start;

    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Order of Access:\n");

    for (int i = 0; i < n; i++) {
        printf("Request %d (Cylinder %d)\n", req[i].request_id, req[i].cylinder);
        total_seek += abs(current - req[i].cylinder);
        current = req[i].cylinder;
    }

    printf("\nTotal Seek Time: %d", total_seek);
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek / n);
}

// Function to simulate SSTF Disk Scheduling
void SSTF(struct DSA req[], int n, int start) {
    int total_seek = 0;
    int current = start;
    bool done[MAX] = {false};

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Order of Access:\n");

    for (int count = 0; count < n; count++) {
        int min_dist = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int dist = abs(current - req[i].cylinder);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = i;
                }
            }
        }

        done[index] = true;
        printf("Request %d (Cylinder %d)\n", req[index].request_id, req[index].cylinder);
        total_seek += min_dist;
        current = req[index].cylinder;
    }

    printf("\nTotal Seek Time: %d", total_seek);
    printf("\nAverage Seek Time: %.2f\n", (float)total_seek / n);
}

int main() {
    struct DSA req[MAX];
    int n, start;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nRequest %d details:\n", i + 1);
        req[i].request_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &req[i].arrival_time_stamp);
        printf("Cylinder Number: ");
        scanf("%d", &req[i].cylinder);
        printf("Address: ");
        scanf("%d", &req[i].address);
        printf("Process ID: ");
        scanf("%d", &req[i].process_id);
    }

    printf("\nEnter current head position: ");
    scanf("%d", &start);

    // Simulate FCFS and SSTF
    FCFS(req, n, start);
    SSTF(req, n, start);

    return 0;
}
