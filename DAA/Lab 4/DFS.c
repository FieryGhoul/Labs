#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int n;

void push(int stack[], int* top, int vertex) {
    stack[++(*top)] = vertex;
    printf("Pushed: %d\n", vertex);
}
int pop(int stack[], int* top) {
    int v = stack[(*top)--];
    printf("Popped: %d\n", v);
    return v;
}

void dfs(int start) {
    int stack[MAX_VERTICES], top = -1;
    push(stack, &top, start);
    visited[start] = 1;

    while (top!=-1) {
        int v=pop(stack, &top);
        printf("Visiting: %d\n", v);

        for (int i=0;i<n;i++) {
            if (adj[v][i]==1&&!visited[i]) {
                visited[i]=1;
                push(stack, &top, i);
    }}}}

int main() {
    int edges,u,v;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    for (int i=0;i<n;i++){        
        for (int j=0;j<n;j++) {
            adj[i][j] = 0;
        }
    }
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    printf("Enter the edges (u v):\n");
    for (int i=0;i<edges;i++) {
        scanf("%d %d",&u,&v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    for (int i=0;i<n;i++) {
        visited[i] = 0;
    }
    int start;
    printf("Enter the vertex to start from : ");
    scanf("%d",&start);
    printf("Depth First Search traversal starting from vertex %d:\n",start);
    dfs(start);
}
