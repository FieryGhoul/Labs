#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int adj[MAX][MAX],visited[MAX],in_degree[MAX];
int n;

void dfs(int v, int stack[], int *top){
    visited[v] = 1;
    for(int i=0;i<n;i++){
        if(adj[v][i] == 1 && !visited[i]){
            dfs(i, stack, top);
        }
    }
    stack[*top] = v;
    (*top)++;
}

void SortDFS(){
    int stack[MAX], top = 0;
    for(int i=0;i<n;i++){
        visited[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            dfs(i, stack, &top);
        }
    }
    printf("Topological Sort (DFS): ");
    for(int i=top-1;i>=0;i--){
        printf("%d ", stack[i]);
    }
    printf("\n");
}


void SortSourceRemoval() {
    int count = 0;
    int stack[MAX];
    
    for(int i = 0; i < n; i++) {
        in_degree[i] = 0;
        for(int j = 0; j < n; j++) {
            if(adj[j][i] == 1) {
                in_degree[i]++;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(in_degree[i] == 0) {
            stack[count++] = i;
        }
    }
    printf("Topological Sort (Source Removal): ");
    int index = 0;
    while(count > 0) {
        int v = stack[--count];
        printf("%d ", v);
        
        for(int i = 0; i < n; i++) {
            if(adj[v][i] == 1) {
                in_degree[i]--;
                if(in_degree[i] == 0) {
                    stack[count++] = i;
                }
            }
        }
    }
    printf("\n");
}

int main() {
    int edges, u, v;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j] = 0;
        }
    }
    printf("Enter the edges (u v) where u -> v: \n");
    for(int i=0;i<edges;i++){
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }
    SortDFS();
    SortSourceRemoval();
}

