#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define MAX_MASK_SIZE 10

__constant__ float d_M[MAX_MASK_SIZE];

__global__ void convolution1D(float *N, float *P, int mask_width, int width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int half = mask_width / 2;

    if (i < width) {
        float sum = 0.0f;
        for (int j = 0; j < mask_width; j++) {
            int idx = i - half + j;
            if (idx >= 0 && idx < width)
                sum += N[idx] * d_M[j];
        }
        P[i] = sum;
    }
}

int main() {
    int width, mask_width;
    printf("Enter array width: ");
    scanf("%d", &width);
    printf("Enter mask width (odd, max %d): ", MAX_MASK_SIZE);
    scanf("%d", &mask_width);

    float *h_N = (float*)malloc(width * sizeof(float));
    float *h_M = (float*)malloc(mask_width * sizeof(float));
    float *h_P = (float*)malloc(width * sizeof(float));

    printf("Enter %d input values: ", width);
    for (int i = 0; i < width; i++) scanf("%f", &h_N[i]);

    printf("Enter %d mask values: ", mask_width);
    for (int i = 0; i < mask_width; i++) scanf("%f", &h_M[i]);

    float *d_N, *d_P;
    cudaMalloc(&d_N, width * sizeof(float));
    cudaMalloc(&d_P, width * sizeof(float));

    cudaMemcpy(d_N, h_N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(d_M, h_M, mask_width * sizeof(float));

    int BLOCK = 256;
    dim3 blockDim(BLOCK);
    dim3 gridDim((width + BLOCK - 1) / BLOCK);

    convolution1D<<<gridDim, blockDim>>>(d_N, d_P, mask_width, width);
    cudaDeviceSynchronize();

    cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output P: ");
    for (int i = 0; i < width; i++) printf("%.2f ", h_P[i]);
    printf("\n");

    cudaFree(d_N); cudaFree(d_P);
    free(h_N); free(h_M); free(h_P);
    return 0;
}