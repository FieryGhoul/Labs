#include <stdio.h>
#include <stdlib.h>

#define N 30  // Process limit

typedef struct process {
    int id, burst, queue, priority, counter;
    struct process *next;
} Process;

typedef struct {
    Process *front, *rear;
} Queue;

void enqueue(Queue *q, Process *p) {
    p->next = NULL;
    if (!q->rear)
        q->front = q->rear = p;
    else {
        q->rear->next = p;
        q->rear = p;
    }
}
Process* dequeue(Queue *q) {
    if (!q->front) 
        return NULL;
    Process *p = q->front;
    q->front = p->next;
    if (!q->front) 
        q->rear = NULL;
    return p;
}

void sort_ll(Queue* q){
	int l=0;
	Process* init = q->front;
	while(q->front){
		l++;
		q->front = (q->front)->next;
	}
	q->front = init;
	Process* pr[l];
	for(int i=0; i<l; i++){
		pr[i]=q->front;
		q->front=(q->front)->next;
	}
	q->front=init;
	for(int i=0; i<l-1; i++)
		for(int j=i+1; j<l; j++)
			if(pr[j]->priority<pr[i]->priority){
				pr[j]->counter--;
				//printf("P %d : %d!\n", pr[j]->id, pr[j]->counter);
				Process* temp = pr[i];
				pr[i] = pr[j];
				pr[j] = temp;
			}

	q->front=pr[0];
	q->rear=pr[0];
	//printf("length: %d\n", l);
	for(int i=1; i<l; i++){
		(q->rear)->next=pr[i];
		q->rear=pr[i];
	}
	(q->rear)->next=NULL;
	//printf("Sorting done for pq!\n");
}

int main() {
    Queue q1={0}, q2={0}, q3={0};
    int i, num = 0;
    printf("Enter number of processes: ");
    scanf("%d", &num);
    for(i=0; i<num; i++) {
        Process *p = (Process*)malloc(sizeof(Process));
        printf("Enter burst, priority for P %d:\n", i+1);
        p->id = i+1; scanf("%d%d", &p->burst, &p->priority);
        p->counter=1;
        enqueue(&q1, p);
    }
    printf("Scheduling Q1 (Round Robin), time quantum is 10:\n");
    int quantum = 10;
    while(q1.front) {
        Process *p = dequeue(&q1);
        if (p->burst <= quantum) {
            printf("P %d finished in Q1 (burst %d)\n", p->id, p->burst);
            free(p);
        } else {
            p->burst -= quantum;  // reduce remaining burst
            printf("P %d ran for %d, remaining %d -> moved to Q2\n", p->id, quantum, p->burst);
            enqueue(&q2, p);
        }
    }
    printf("Scheduling Q2 (Priority):\n"); // Add proper sorting for true priority
    sort_ll(&q2);
    while(q2.front) {
        Process *p = dequeue(&q2);
        if(p->counter>=0){
        	printf("P %d\n", p->id);
        	free(p);
        }
        else enqueue(&q3, p);
    }
    printf("Scheduling Q3 (FCFS):\n");
    while(q3.front) {
        Process *p = dequeue(&q3);
        printf("P %d\n", p->id);
        free(p);
    }
    return 0;
}





// #include <stdio.h>
// #include <stdlib.h>


// #define MAX 100


// typedef struct process {
//     int pid, burst, remaining;
//     struct process* next;
// } Process;


// typedef struct {
//     Process* front;
//     Process* rear;
// } Queue;


// void enqueue(Queue *q, Process *p) {
//     p->next = NULL;
//     if(!q->rear) q->front = q->rear = p;
//     else {
//         q->rear->next = p;
//         q->rear = p;
//     }
// }


// Process* dequeue(Queue *q) {
//     if(!q->front) return NULL;
//     Process* temp = q->front;
//     q->front = q->front->next;
//     if(!q->front) q->rear = NULL;
//     return temp;
// }


// void mlfq_scheduling(Process* processes[], int n) {
//     Queue q1={NULL, NULL}, q2={NULL, NULL}, q3={NULL, NULL};
//     int time, tq1=8, tq2=16;
//     for(int i=0;i<n;i++) enqueue(&q1, processes[i]);
//     time = 0;


//     // Q1: Round Robin tq=8
//     while(q1.front) {
//         Process* p = dequeue(&q1);
//         int exec = (p->remaining>tq1) ? tq1 : p->remaining;
//         time += exec;
//         p->remaining -= exec;
//         if(p->remaining>0) enqueue(&q2, p); // Move to Q2 if not finished
//         else printf("Process %d finished at time %d\n", p->pid, time);
//     }
//     // Q2: Round Robin tq=16
//     while(q2.front) {
//         Process* p = dequeue(&q2);
//         int exec = (p->remaining>tq2) ? tq2 : p->remaining;
//         time += exec;
//         p->remaining -= exec;
//         if(p->remaining>0) enqueue(&q3, p); // Move to Q3 if not finished
//         else printf("Process %d finished at time %d\n", p->pid, time);
//     }
//     // Q3: FCFS
//     while(q3.front) {
//         Process* p = dequeue(&q3);
//         time += p->remaining;
//         printf("Process %d finished at time %d\n", p->pid, time);
//     }
// }


// int main() {
//     int n = 3;
//     Process* processes[n];
//     int burst[] = {20, 15, 35};
//     for(int i=0;i<n;i++) {
//         processes[i]=malloc(sizeof(Process));
//         processes[i]->pid = i;
//         processes[i]->burst = processes[i]->remaining = burst[i];
//         processes[i]->next = NULL;
//     }
//     mlfq_scheduling(processes, n);
//     for(int i=0;i<n;i++) free(processes[i]);
//     return 0;
// }
