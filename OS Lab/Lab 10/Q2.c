#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid, burst, priority;
    struct process* next;
} Process;

Process* newProcess(int pid, int burst, int priority) {
    Process* p = (Process*)malloc(sizeof(Process));
    p->pid = pid; p->burst = burst; p->priority = priority; p->next = NULL;
    return p;
}

// Insert into queue (simple linked list)
void enqueue(Process** head, Process* p) {
    if (!*head) *head = p;
    else {
        Process* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = p;
    }
}

void runQueue(Process* q, char* name) {
    printf("Running %s Queue:\n", name);
    while (q) {
        printf("Process %d executed (burst=%d, priority=%d)\n", q->pid, q->burst, q->priority);
        q = q->next;
    }
}

int main() {
    Process* Q1 = NULL; // Round Robin
    Process* Q2 = NULL; // Priority
    Process* Q3 = NULL; // FCFS

    enqueue(&Q1, newProcess(1, 5, 3));
    enqueue(&Q2, newProcess(2, 8, 1));
    enqueue(&Q3, newProcess(3, 12, 2));

    runQueue(Q1, "RR");
    runQueue(Q2, "Priority");
    runQueue(Q3, "FCFS");

    return 0;
}
