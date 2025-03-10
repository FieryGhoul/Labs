#include <stdio.h>
#include <stdlib.h>
 #define MAX_VERTICES 10
int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int n;

void enqueue(int queue[], int* rear, int vertex) {
    queue[++(*rear)] = vertex;
    printf("Enqueued: %d\n", vertex);
}

int dequeue(int queue[], int* front) {
    int v = queue[(*front)++];
    printf("Dequeued: %d\n", v);
    return v;
}

void bfs(int start) {
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;
    visited[start] = 1;
    enqueue(queue, &rear, start);
    while (front <= rear) {
        int vertex = dequeue(queue, &front);
        printf("Visiting: %d\n", vertex);
        for (int i = 0; i < n; i++) {
            if (adj[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, &rear, i);
            }
        }
    }
}

int main() {
    int edges, u, v;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    int start;
    printf("Enter the vertex to start from: ");
    scanf("%d", &start);
    printf("Breadth First Search traversal starting from vertex %d:\n", start);
    bfs(start);
}
