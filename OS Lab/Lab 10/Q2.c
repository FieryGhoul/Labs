#include <stdio.h>
#include <stdlib.h>


#define MAX 100


typedef struct process {
    int pid, burst, remaining;
    struct process* next;
} Process;


typedef struct {
    Process* front;
    Process* rear;
} Queue;


void enqueue(Queue *q, Process *p) {
    p->next = NULL;
    if(!q->rear) q->front = q->rear = p;
    else {
        q->rear->next = p;
        q->rear = p;
    }
}


Process* dequeue(Queue *q) {
    if(!q->front) return NULL;
    Process* temp = q->front;
    q->front = q->front->next;
    if(!q->front) q->rear = NULL;
    return temp;
}


void mlfq_scheduling(Process* processes[], int n) {
    Queue q1={NULL, NULL}, q2={NULL, NULL}, q3={NULL, NULL};
    int time, tq1=8, tq2=16;
    for(int i=0;i<n;i++) enqueue(&q1, processes[i]);
    time = 0;


    // Q1: Round Robin tq=8
    while(q1.front) {
        Process* p = dequeue(&q1);
        int exec = (p->remaining>tq1) ? tq1 : p->remaining;
        time += exec;
        p->remaining -= exec;
        if(p->remaining>0) enqueue(&q2, p); // Move to Q2 if not finished
        else printf("Process %d finished at time %d\n", p->pid, time);
    }
    // Q2: Round Robin tq=16
    while(q2.front) {
        Process* p = dequeue(&q2);
        int exec = (p->remaining>tq2) ? tq2 : p->remaining;
        time += exec;
        p->remaining -= exec;
        if(p->remaining>0) enqueue(&q3, p); // Move to Q3 if not finished
        else printf("Process %d finished at time %d\n", p->pid, time);
    }
    // Q3: FCFS
    while(q3.front) {
        Process* p = dequeue(&q3);
        time += p->remaining;
        printf("Process %d finished at time %d\n", p->pid, time);
    }
}


int main() {
    int n = 3;
    Process* processes[n];
    int burst[] = {20, 15, 35};
    for(int i=0;i<n;i++) {
        processes[i]=malloc(sizeof(Process));
        processes[i]->pid = i;
        processes[i]->burst = processes[i]->remaining = burst[i];
        processes[i]->next = NULL;
    }
    mlfq_scheduling(processes, n);
    for(int i=0;i<n;i++) free(processes[i]);
    return 0;
}
