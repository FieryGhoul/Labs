#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>

// (a) Row-wise
__global__ void mulByRow(int *A, int *B, int *C, int cols, int common) {
    int row = blockIdx.x;

    for (int col = 0; col < cols; col++) {
        int sum = 0;
        for (int k = 0; k < common; k++)
            sum += A[row * common + k] * B[k * cols + col];

        C[row * cols + col] = sum;
    }
}

// (b) Column-wise
__global__ void mulByCol(int *A, int *B, int *C, int rows, int cols, int common) {
    int col = threadIdx.x;

    for (int row = 0; row < rows; row++) {
        int sum = 0;
        for (int k = 0; k < common; k++)
            sum += A[row * common + k] * B[k * cols + col];

        C[row * cols + col] = sum;
    }
}

// (c) Element-wise
__global__ void mulByEle(int *A, int *B, int *C, int cols, int common) {
    int row = blockIdx.x;
    int col = threadIdx.x;

    int sum = 0;
    for (int k = 0; k < common; k++)
        sum += A[row * common + k] * B[k * cols + col];

    C[row * cols + col] = sum;
}

int main() {
    int rows1, cols1, rows2, cols2;

    printf("Enter no. of rows and cols for 1st matrix: ");
    scanf("%d%d", &rows1, &cols1);

    printf("Enter no. of rows and cols for 2nd matrix: ");
    scanf("%d%d", &rows2, &cols2);

    if (cols1 != rows2) {
        printf("ERROR: incompatible matrix dimensions\n");
        exit(1);
    }

    int sizeA = rows1 * cols1 * sizeof(int);
    int sizeB = rows2 * cols2 * sizeof(int);
    int sizeC = rows1 * cols2 * sizeof(int);

    int *A = (int*)malloc(sizeA);
    int *B = (int*)malloc(sizeB);
    int *C = (int*)malloc(sizeC);

    printf("Enter 1st matrix:\n");
    for (int i = 0; i < rows1 * cols1; i++)
        scanf("%d", &A[i]);

    printf("Enter 2nd matrix:\n");
    for (int i = 0; i < rows2 * cols2; i++)
        scanf("%d", &B[i]);

    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, sizeA);
    cudaMalloc((void**)&d_B, sizeB);
    cudaMalloc((void**)&d_C, sizeC);

    cudaMemcpy(d_A, A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeB, cudaMemcpyHostToDevice);

    // ---------------- ROW-WISE ----------------
    dim3 grid1(rows1);
    dim3 block1(1);

    mulByRow<<<grid1, block1>>>(d_A, d_B, d_C, cols2, rows2);

    cudaMemcpy(C, d_C, sizeC, cudaMemcpyDeviceToHost);

    printf("(By Row) Result Matrix:\n");
    for (int row = 0; row < rows1; row++) {
        for (int col = 0; col < cols2; col++)
            printf("%d\t", C[row * cols2 + col]);
        printf("\n");
    }

    // ---------------- COLUMN-WISE ----------------
    dim3 grid2(1);
    dim3 block2(cols2);

    mulByCol<<<grid2, block2>>>(d_A, d_B, d_C, rows1, cols2, rows2);

    cudaMemcpy(C, d_C, sizeC, cudaMemcpyDeviceToHost);

    printf("(By Column) Result Matrix:\n");
    for (int row = 0; row < rows1; row++) {
        for (int col = 0; col < cols2; col++)
            printf("%d\t", C[row * cols2 + col]);
        printf("\n");
    }

    // ---------------- ELEMENT-WISE ----------------
    dim3 grid3(rows1);
    dim3 block3(cols2);

    mulByEle<<<grid3, block3>>>(d_A, d_B, d_C, cols2, rows2);

    cudaMemcpy(C, d_C, sizeC, cudaMemcpyDeviceToHost);

    printf("(By Element) Result Matrix:\n");
    for (int row = 0; row < rows1; row++) {
        for (int col = 0; col < cols2; col++)
            printf("%d\t", C[row * cols2 + col]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}