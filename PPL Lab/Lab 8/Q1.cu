#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>

// (a) Row-wise: one thread per row
__global__ void addByRow(int *A, int *B, int *C, int rows, int cols) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows) {
        for (int col = 0; col < cols; col++) {
            C[row * cols + col] =
                A[row * cols + col] + B[row * cols + col];
        }
    }
}

// (b) Column-wise: one thread per column
__global__ void addByCol(int *A, int *B, int *C, int rows, int cols) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < cols) {
        for (int row = 0; row < rows; row++) {
            C[row * cols + col] =
                A[row * cols + col] + B[row * cols + col];
        }
    }
}

// (c) Element-wise: one thread per element
__global__ void addByEle(int *A, int *B, int *C, int rows, int cols) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows && col < cols) {
        int idx = row * cols + col;
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    int rows, cols;

    printf("Enter no. of rows: ");
    scanf("%d", &rows);

    printf("Enter no. of cols: ");
    scanf("%d", &cols);

    int size = rows * cols * sizeof(int);

    int *A = (int*)malloc(size);
    int *B = (int*)malloc(size);
    int *C = (int*)malloc(size);

    printf("Enter 1st matrix:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &A[i]);

    printf("Enter 2nd matrix:\n");
    for (int i = 0; i < rows * cols; i++)
        scanf("%d", &B[i]);

    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // ---------------- ROW-WISE ----------------
    dim3 threads1(256);
    dim3 blocks1((rows + 255) / 256);

    addByRow<<<blocks1, threads1>>>(d_A, d_B, d_C, rows, cols);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\n(By Row) Result Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d\t", C[i * cols + j]);
        printf("\n");
    }

    // ---------------- COLUMN-WISE ----------------
    dim3 threads2(256);
    dim3 blocks2((cols + 255) / 256);

    addByCol<<<blocks2, threads2>>>(d_A, d_B, d_C, rows, cols);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\n(By Column) Result Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d\t", C[i * cols + j]);
        printf("\n");
    }

    // ---------------- ELEMENT-WISE ----------------
    dim3 threads3(16, 16);
    dim3 blocks3((cols + 15) / 16, (rows + 15) / 16);

    addByEle<<<blocks3, threads3>>>(d_A, d_B, d_C, rows, cols);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("\n(By Element) Result Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d\t", C[i * cols + j]);
        printf("\n");
    }

    // Free memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}