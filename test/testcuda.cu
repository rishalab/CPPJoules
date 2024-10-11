#include <stdio.h>
#include <cuda_runtime.h>
#include "../include/cppJoules.h"

// CUDA kernel for matrix multiplication
__global__ void matMulKernel(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    float sum = 0.0f;

    if (row < N && col < N)
    {
        for (int k = 0; k < N; ++k)
        {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

// Function to initialize matrices with random values
void initializeMatrix(float *mat, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        mat[i] = static_cast<float>(rand()) / RAND_MAX;
    }
}

int main()
{
    int N = 1024; // Size of the matrices (N x N)
    size_t size = N * N * sizeof(float);

    // Allocate host matrices
    float *h_A = (float *)malloc(size);
    float *h_B = (float *)malloc(size);
    float *h_C = (float *)malloc(size);

    // Initialize host matrices
    initializeMatrix(h_A, N);
    initializeMatrix(h_B, N);

    // Allocate device matrices
    float *d_A;
    float *d_B;
    float *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    // Copy host matrices to device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Define block and grid dimensions
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((N + threadsPerBlock.x - 1) / threadsPerBlock.x, (N + threadsPerBlock.y - 1) / threadsPerBlock.y);

    EnergyTracker tracker;
    // Launch the matrix multiplication kernel
    tracker.start();
    for (int i = 0; i < 10e3; i++)
    {
        matMulKernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    }

    // Copy result matrix back to host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Free device matrices
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // Free host matrices
    free(h_A);
    free(h_B);
    free(h_C);
    tracker.stop();
    tracker.calculate_energy();
    tracker.print_energy();

    printf("Matrix multiplication completed successfully.\n");

    return 0;
}
