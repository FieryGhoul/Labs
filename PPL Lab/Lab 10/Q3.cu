#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define MAX_MASK_SIZE 10
__constant__ float d_M[MAX_MASK_SIZE];

__global__ void tiledConvolution1D(float *N, float *P, int mask_width, int width) {
    extern __shared__ float tile[];

    int tx        = threadIdx.x;
    int out_idx   = blockIdx.x * blockDim.x + tx;
    int half      = mask_width / 2;
    int tile_size = blockDim.x + mask_width - 1;

     int left = out_idx - half;
    if (left >= 0 && left < width)
        tile[tx] = N[left];
    else
        tile[tx] = 0.0f;

    if (tx < mask_width - 1) {
        int right = left + blockDim.x;
        tile[blockDim.x + tx] = (right >= 0 && right < width) ? N[right] : 0.0f;
    }

    __syncthreads();

    if (out_idx < width) {
        float sum = 0.0f;
        for (int j = 0; j < mask_width; j++)
            sum += tile[tx + j] * d_M[j];
        P[out_idx] = sum;
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

    int shared_mem = (BLOCK + mask_width - 1) * sizeof(float);
    tiledConvolution1D<<<gridDim, blockDim, shared_mem>>>(d_N, d_P, mask_width, width);
    cudaDeviceSynchronize();

    cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output P: ");
    for (int i = 0; i < width; i++) printf("%.2f ", h_P[i]);
    printf("\n");

    cudaFree(d_N); cudaFree(d_P);
    free(h_N); free(h_M); free(h_P);
    return 0;
}