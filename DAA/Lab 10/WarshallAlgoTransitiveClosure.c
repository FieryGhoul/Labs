#include <stdio.h>
#define MAX 10

unsigned int opCount = 0;

void warshall(int graph[MAX][MAX], int n) {
    int tc[MAX][MAX];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tc[i][j] = graph[i][j];
        }
    }
    //warshall's algo
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tc[i][j] = tc[i][j] || (tc[i][k] && tc[k][j]);
                
                opCount++;
            }
        }
    }
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", tc[i][j]);
        }
        printf("\n");
    }
    printf("Number of operations: %u\n", opCount);
}

int main() {
    int n, graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix lengthwise:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    warshall(graph, n);
}
