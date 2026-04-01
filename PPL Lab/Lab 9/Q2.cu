#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void raise(int* mat, int rows, int cols) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < rows) {
        for (int col = 0; col < cols; col++) {
            int val = mat[row * cols + col];
            int res = 1;
            for (int i = 0; i < (row + 1); i++) res *= val;
            mat[row * cols + col] = res;
        }
    }
}

int main() {
    int rows, cols;
    printf("Enter dimensions (rows cols): ");
    scanf("%d %d", &rows, &cols);

    int size = rows * cols * sizeof(int);
    int *mat = (int*)malloc(size);

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows * cols; i++) scanf("%d", &mat[i]);

    int *d_mat;
    cudaMalloc(&d_mat, size);
    cudaMemcpy(d_mat, mat, size, cudaMemcpyHostToDevice);

    dim3 block(256, 1, 1);
    dim3 grid((rows + block.x - 1) / block.x, 1, 1);

    raise<<<grid, block>>>(d_mat, rows, cols);

    cudaMemcpy(mat, d_mat, size, cudaMemcpyDeviceToHost);

    printf("Result Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) printf("%d ", mat[i * cols + j]);
        printf("\n");
    }

    cudaFree(d_mat);
    free(mat);
    return 0;
}