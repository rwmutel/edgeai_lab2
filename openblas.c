#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cblas.h"

#define SIZE 2048

void generate_random_matrix(float *matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = (float)rand() / RAND_MAX;
    }
}

int main() {
    float *A = (float *)malloc(SIZE * SIZE * sizeof(float));
    float *B = (float *)malloc(SIZE * SIZE * sizeof(float));
    float *C = (float *)malloc(SIZE * SIZE * sizeof(float));

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand((unsigned int)time(NULL));
    
    generate_random_matrix(A, SIZE);
    generate_random_matrix(B, SIZE);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A, SIZE, B, SIZE, 0.0, C, SIZE);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    printf("%f\n", time_taken);

    free(A);
    free(B);
    free(C);

    return 0;
}
