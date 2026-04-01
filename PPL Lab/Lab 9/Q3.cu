#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__device__ int flip(int n) {
    if (n == 0) return 1;
    int n1 = n;
    int bits = 0;
    while (n1 > 0) {
        bits++;
        n1 >>= 1;
    }
    int result = 0, power = 1;
    for (int i = 0; i < bits; i++) {
        int bit = (n >> i) & 1;
        bit = !bit;
        result += bit * power;
        power *= 10; 
    }
    return result;
}

__global__ void transform(int *A, int *B, int rows, int cols) {
    int j = blockIdx.x * blockDim.x + threadIdx.x; 
    int i = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < rows && j < cols) {
        if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
            B[i * cols + j] = A[i * cols + j];
        } else {
            B[i * cols + j] = flip(A[i * cols + j]);
        }
    }
}

int main() {
    int rows, cols;
    printf("Enter rows and cols: ");
    if (scanf("%d %d", &rows, &cols) != 2) return -1;

    size_t size = rows * cols * sizeof(int);
    int *h_A = (int*)malloc(size);
    int *h_B = (int*)malloc(size);

    printf("Enter matrix A:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &h_A[i * cols + j]);
        }
    }

    int *d_A, *d_B;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);

    dim3 blocksPerGrid((cols + threadsPerBlock.x - 1) / threadsPerBlock.x, (rows + threadsPerBlock.y - 1) / threadsPerBlock.y);

    transform<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, rows, cols);
    cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);

    printf("\nOutput Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", h_B[i * cols + j]);
        }
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    free(h_A);
    free(h_B);

    return 0;
}