#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

__global__ void buildRS(char* S, char* RS, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        int start = i * n - (i * (i - 1)) / 2;
        for (int j = 0; j < n - i; j++) {
            RS[start + j] = S[j];
        }
    }
}

int main() {
    char S[N], RS[N * N];
    char *d_S, *d_RS;

    printf("Enter a string: ");
    scanf("%s", S);
    
    int nS = (int)strlen(S);
    int nRS = nS * (nS + 1) / 2;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaMalloc((void**)&d_S, nS);
    cudaMalloc((void**)&d_RS, nRS);

    cudaMemcpy(d_S, S, nS, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(nS, 1, 1); 
    dim3 numBlocks(1, 1, 1); 

    cudaEventRecord(start);

    buildRS<<<numBlocks, threadsPerBlock>>>(d_S, d_RS, nS);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);

    cudaMemcpy(RS, d_RS, nRS, cudaMemcpyDeviceToHost);
    RS[nRS] = '\0';
    printf("Output RS: %s\n", RS);
    printf("Time taken = %f ms\n", elapsedTime);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_S);
    cudaFree(d_RS);

    return 0;
}