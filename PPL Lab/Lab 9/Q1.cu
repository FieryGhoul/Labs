#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void spmv(int rows, float* data, int* col_index, int* row_ptr, float* x, float* y) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < rows) {
        float sum = 0.0f;
        for (int i = row_ptr[row]; i < row_ptr[row + 1]; i++) {
            sum += data[i] * x[col_index[i]];
        }
        y[row] = sum;
    }
}

int main() {
    int rows, cols;
    printf("Enter dimensions of sparse matrix: ");
    scanf("%d%d", &rows, &cols);

    float *data = (float*)malloc(rows * cols * sizeof(float));
    int *col_index = (int*)malloc(rows * cols * sizeof(int));
    int *row_ptr = (int*)malloc((rows + 1) * sizeof(int));
    row_ptr[0] = 0;

    int k = 0;
    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float val;
            scanf("%f", &val);
            if (val != 0) {
                data[k] = val;
                col_index[k++] = j;
            }
        }
        row_ptr[i + 1] = k;
    }

    float *X = (float*)malloc(cols * sizeof(float));
    float *Y = (float*)malloc(rows * sizeof(float));
    printf("Enter vector: ");
    for (int i = 0; i < cols; i++) scanf("%f", &X[i]);

    float *d_data, *d_X, *d_Y;
    int *d_col_index, *d_row_ptr;

    cudaMalloc(&d_data, k * sizeof(float));
    cudaMalloc(&d_col_index, k * sizeof(int));
    cudaMalloc(&d_row_ptr, (rows + 1) * sizeof(int));
    cudaMalloc(&d_X, cols * sizeof(float));
    cudaMalloc(&d_Y, rows * sizeof(float));

    cudaMemcpy(d_data, data, k * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_index, col_index, k * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, (rows + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_X, X, cols * sizeof(float), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(256, 1, 1);
    dim3 blocksPerGrid((rows + threadsPerBlock.x - 1) / threadsPerBlock.x, 1, 1);

    spmv<<<blocksPerGrid, threadsPerBlock>>>(rows, d_data, d_col_index, d_row_ptr, d_X, d_Y);

    cudaMemcpy(Y, d_Y, rows * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Result Vector:\n");
    for (int i = 0; i < rows; i++) printf("%f ", Y[i]);
    printf("\n");

    cudaFree(d_data);
    cudaFree(d_col_index); 
    cudaFree(d_row_ptr);
    cudaFree(d_X); 
    cudaFree(d_Y);
    free(X); free(Y); free(data); free(col_index); free(row_ptr);
    return 0;
}