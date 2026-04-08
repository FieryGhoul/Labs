#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

// A is (rowsA x colsA), B is (colsA x colsB), C is (rowsA x colsB)
__global__ void matMulKernel(float *A, float *B, float *C, int rowsA, int colsA, int colsB) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rowsA && col < colsB) {
        float sum = 0.0f;
        for (int k = 0; k < colsA; k++)
            sum += A[row * colsA + k] * B[k * colsB + col];
        C[row * colsB + col] = sum;
    }
}

int main() {
    int rowsA, colsA, colsB;

    printf("Enter rows of A: ");
    scanf("%d", &rowsA);
    printf("Enter cols of A (= rows of B): ");
    scanf("%d", &colsA);
    printf("Enter cols of B: ");
    scanf("%d", &colsB);

    int rowsB = colsA;  // must match

    // Allocate host memory
    float *h_A = (float*)malloc(rowsA * colsA * sizeof(float));
    float *h_B = (float*)malloc(rowsB * colsB * sizeof(float));
    float *h_C = (float*)malloc(rowsA * colsB * sizeof(float));

    // Input elements of A
    printf("\nEnter elements of A (%d x %d):\n", rowsA, colsA);
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsA; j++) {
            scanf("%f", &h_A[i * colsA + j]);
        }

    // Input elements of B
    printf("\nEnter elements of B (%d x %d):\n", rowsB, colsB);
    for (int i = 0; i < rowsB; i++)
        for (int j = 0; j < colsB; j++) {
            scanf("%f", &h_B[i * colsB + j]);
        }

    // Allocate device memory
    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, rowsA * colsA * sizeof(float));
    cudaMalloc(&d_B, rowsB * colsB * sizeof(float));
    cudaMalloc(&d_C, rowsA * colsB * sizeof(float));

    // Copy to device
    cudaMemcpy(d_A, h_A, rowsA * colsA * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, rowsB * colsB * sizeof(float), cudaMemcpyHostToDevice);

    // Define dim3 grid and block
    int TILE = 16;
    dim3 blockDim(TILE, TILE);
    dim3 gridDim((int)ceil((float)colsB / TILE), (int)ceil((float)rowsA / TILE));

    printf("\nGrid:  (%d, %d)\n", gridDim.x, gridDim.y);
    printf("Block: (%d, %d)\n", blockDim.x, blockDim.y);

    // Launch kernel
    matMulKernel<<<gridDim, blockDim>>>(d_A, d_B, d_C, rowsA, colsA, colsB);
    cudaDeviceSynchronize();

    // Copy result back
    cudaMemcpy(h_C, d_C, rowsA * colsB * sizeof(float), cudaMemcpyDeviceToHost);

    // Print result matrix C
    printf("\nResult Matrix C (%d x %d):\n", rowsA, colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++)
            printf("%8.2f ", h_C[i * colsB + j]);
        printf("\n");
    }

    // Free memory
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C);

    return 0;
}