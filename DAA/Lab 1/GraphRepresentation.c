#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int **adjMatrix = (int **)malloc(n * sizeof(int *));
    for(i = 0; i < n; i++) {
        adjMatrix[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Enter the adjacency matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    printf("\nAdjacency Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for(i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        for(j = 0; j < n; j++) {
            if(adjMatrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }

    for(i = 0;i<n;i++){
    	free(adjMatrix[i]);
    }
    free(adjMatrix);
}
