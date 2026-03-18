#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024
#define WN 20

__device__ int d_strcmp(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 1;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0') ? 0 : 1;
}

__global__ void wordCount(char d_words[][WN], char* d_word, int* d_count, int wc) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < wc) {
        if (d_strcmp(d_words[i], d_word) == 0) {
            atomicAdd(d_count, 1);
        }
    }
}

int main() {
    char sent[N], word[WN], words[N / WN][WN];
    int wc = 0, count = 0;
    char(*d_words)[WN];
    char* d_word;
    int* d_count;
    printf("Enter a sentence: ");
    fgets(sent, sizeof(sent), stdin);
    printf("Enter word: ");
    scanf("%s", word);

    char* token = strtok(sent, " \n");
    while (token != NULL) {
        strncpy(words[wc++], token, WN);
        token = strtok(NULL, " \n");
    }

    cudaMalloc((void**)&d_words, sizeof(words));
    cudaMalloc((void**)&d_word, WN);
    cudaMalloc((void**)&d_count, sizeof(int));

    cudaMemcpy(d_words, words, sizeof(words), cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, WN, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    dim3 threadsPerBlock(256, 1, 1);
    dim3 numBlocks((wc + threadsPerBlock.x - 1) / threadsPerBlock.x, 1, 1);

    cudaEventRecord(start);

    wordCount<<<numBlocks, threadsPerBlock>>>(d_words, d_word, d_count, wc);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Total occurrences: %d\n", count);
    printf("Kernel Execution Time: %f ms\n", milliseconds);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_words);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}